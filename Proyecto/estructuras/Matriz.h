#include <string.h>
#include <iostream>
#include <fstream> //cabecera para manejar archivos (leer y escribir)
#include <cstdlib> 
using namespace std;
#include "NodoMatriz.h"

class Matriz
{
private:
    
public:
    NodoMatriz* root;
    Matriz(/* args */);
    NodoMatriz* buscarFila(string fila, NodoMatriz* inicio);
    NodoMatriz* buscarColumna(string columna, NodoMatriz* inicio);
    NodoMatriz* crearFila(string fila);
    NodoMatriz* crearColumna(string columna);
    void insertar(Piloto dato, string fila, string columna);
    void generarReporte(string titulo);
    void recorrerMatriz();
    void imprimirMatriz();
    void eliminarNodo(string id);
    ~Matriz();
};

Matriz::Matriz(/* args */)
{
    root = new NodoMatriz("Root","Root", "Root"); //-1 y -1 para encabezado root
}

NodoMatriz* Matriz::buscarFila(string fila, NodoMatriz* inicio)
{
    NodoMatriz* aux = inicio; //inicio puede ser el root
    while (aux != nullptr)
    {
        if (aux->getFila() == fila)
        {
            return aux; //Si se encuentra la cabecera fila, la retorno
        }
        aux = aux->getAbajo();
    }
    return nullptr; //Si no la encuentra quiere decir que no existe la cabecera fila
}
                                    //nombre de la columna y la raiz
NodoMatriz* Matriz::buscarColumna(string columna, NodoMatriz* inicio)
{
    NodoMatriz* aux = inicio; //inicio puede ser el root
    while (aux != nullptr)
    {
        if (aux->getColumna() == columna)
        {
            return aux; //Si se encuentra la cabecera columna, la retorno
        }
        aux = aux->getSiguiente();
    }
    return nullptr; //Si no la encuentra quiere decir que no existe la cabecera columna
}

NodoMatriz* Matriz::crearFila(string fila)//crea la fila y devuelve dicha fila
{
    NodoMatriz* f = new NodoMatriz("Fila", fila, "-1");
    NodoMatriz* aux = root;
    while (aux->getAbajo() != nullptr)
    {
        aux = aux->getAbajo();
    }
    aux->setAbajo(f);
    f->setArriba(aux);
    return f;
}

NodoMatriz* Matriz::crearColumna(string columna)
{
    NodoMatriz* c = new NodoMatriz("Columna", "-1", columna);
    NodoMatriz* aux = root;
    while (aux->getSiguiente() != nullptr)
    {
        aux = aux->getSiguiente();
    }
    aux->setSiguiente(c);
    c->setAnterior(aux);
    return c;
}

void Matriz::insertar(Piloto dato, string fila, string columna)
{
    NodoMatriz* NodoMatrizDato = new NodoMatriz(dato, fila, columna);//el nodo que voy a insertar
    NodoMatriz* NodoMatrizFila; //Para saber en que fila insertar
    NodoMatriz* NodoMatrizColumna; //Para saber en que columna insertar

    NodoMatrizFila = buscarFila(fila, root);
    NodoMatrizColumna = buscarColumna(columna, root);

    //REVISAMOS SI EXISTEN LOS ENCABEZADOS
    /*if (NodoMatrizFila == nullptr)
    {
        NodoMatrizFila = crearFila(fila);
    }
    if (NodoMatrizColumna == nullptr)
    {
        NodoMatrizColumna = crearColumna(columna);
    }*/

   if (NodoMatrizFila == nullptr && NodoMatrizColumna == nullptr) //Caso 1
   {
        NodoMatrizFila = crearFila(fila);
        NodoMatrizColumna = crearColumna(columna);
   }
   else if (NodoMatrizFila != nullptr && NodoMatrizColumna == nullptr) //Caso 2
   {
        NodoMatrizColumna = crearColumna(columna);
   }
   else if (NodoMatrizFila == nullptr && NodoMatrizColumna != nullptr)//Caso 3
   {
        NodoMatrizFila = crearFila(fila);
   }
   
    
    //INSERTAR NodoMatrizDATO EN LAS CABECERAS
    /*if (NodoMatrizFila->getSiguiente() == nullptr)
    {
        NodoMatrizFila->setSiguiente(NodoMatrizDato);
        NodoMatrizDato->setAnterior(NodoMatrizFila);
    }

    if (NodoMatrizColumna->getAbajo() == nullptr)
    {
        NodoMatrizColumna->setAbajo(NodoMatrizDato);
        NodoMatrizDato->setArriba(NodoMatrizColumna);
    }*/

   //Insertando NodoMatrizDato en la cabecera fila
   NodoMatriz* auxFila = NodoMatrizFila;
   while (auxFila != nullptr)
   {
        if (auxFila->getSiguiente() == nullptr) //Encontre el último NodoMatriz (puede ser la misma cabecera)
        {
            //Hacemos los enlaces correspondientes
            auxFila->setSiguiente(NodoMatrizDato);
            NodoMatrizDato->setAnterior(auxFila);
            break;
        }
        auxFila = auxFila->getSiguiente();
   }

   //Insertando NodoMatrizDato en la cabecera columna
   NodoMatriz* auxColumna = NodoMatrizColumna;
   while (auxColumna != nullptr)
   {
        if (auxColumna->getAbajo() == nullptr) //Encontre el último NodoMatriz (puede ser la misma cabecera)
        {
            //Hacemos los enlaces correspondientes
            auxColumna->setAbajo(NodoMatrizDato);
            NodoMatrizDato->setArriba(auxColumna);
            break;
        }
        auxColumna = auxColumna->getAbajo();  
   }    
}

void Matriz::generarReporte(string titulo){
    if (root->getSiguiente()==nullptr && root->getAbajo()==nullptr)
    {
        cout << "La matriz esta vacia" << endl;
    }else{
        
       
        //Encabezado
        string codigoDot="digraph Grafo1 {\nrankdir = \"TB\"\nlabel=\""+titulo+"\"\n";
        codigoDot+="labelloc=\"t\"\n";
        codigoDot+="node[shape=rectangle]\n";//atributos del los nodos
        codigoDot+="edge[]\n"; // atributos de las aristas
        
        //imprimir las cabeceras de las columnas
        NodoMatriz *columnaActual=root;
        codigoDot+= "/*------------Cabeceras columnas------------*/\n";
        int contador=1;
        while (columnaActual!=nullptr)
        {
            codigoDot+=columnaActual->getColumna()+"[group="+to_string(contador)+"]\n";
            columnaActual=columnaActual->getSiguiente();
            contador=contador+1;
        }

        //imprimir las cabeceras filas
        NodoMatriz *filaActual=root;
        codigoDot+= "/*------------Cabeceras filas------------*/\n";
        while (filaActual!=nullptr)
        {
            codigoDot+=filaActual->getFila()+"[group=1]\n";
            filaActual=filaActual->getAbajo();
        }
        //nodos
        codigoDot+= "/*------------Nodos-----------*/\n";

         
        columnaActual = root->getSiguiente(); // Empieza desde el primer encabezado de columna
        contador=2;
        while (columnaActual != nullptr) {
            NodoMatriz* nodoActual = columnaActual->getAbajo(); // Empieza desde el primer nodo en la columna
            while (nodoActual != nullptr) {
                string numero_id=nodoActual->getDato().getNumero_de_id();
                string horas_vuelo=to_string(nodoActual->getDato().getHoras_de_vuelo());//se usa horas de vuelo por que es algo unico
                codigoDot+=horas_vuelo+"[label=\""+numero_id+"\" group="+to_string(contador)+"]\n";
                nodoActual = nodoActual->getAbajo(); // Avanza al siguiente nodo en la fila
            }
            columnaActual = columnaActual->getSiguiente(); // Avanza al siguiente encabezado de columna
            contador=contador+1;
        } 


        /*
        filaActual = root->getAbajo(); // Empieza desde el primer encabezado de fila
        
        while (filaActual != nullptr) {
            contador=2;
            NodoMatriz* nodoActual = filaActual->getSiguiente(); // Empieza desde el primer nodo en la fila
            while (nodoActual != nullptr) {
                string numero_id=nodoActual->getDato().getNumero_de_id();
                string horas_vuelo=to_string(nodoActual->getDato().getHoras_de_vuelo());//se usa horas de vuelo por que es algo unico
                codigoDot+=horas_vuelo+"[label=\""+numero_id+"\" group="+to_string(contador)+"]\n";
                nodoActual = nodoActual->getSiguiente(); // Avanza al siguiente nodo en la fila
                contador=contador+1;
            }
            filaActual = filaActual->getAbajo(); // Avanza al siguiente encabezado de fila
            
        } */  

        //imprimir relaciones horizontales
        codigoDot+= "/*------------Relaciones horizontales------------*/\n";
        columnaActual=root;

            //CABECERAS COLUMNAS
                //apuntadores siguientes
        while (columnaActual!=nullptr)
        {
            codigoDot+=columnaActual->getColumna();

            if (columnaActual->getSiguiente()!=nullptr)
            {
                codigoDot+="->";
                columnaActual=columnaActual->getSiguiente();
            }else{
                codigoDot+="\n";
                break;
            } 
        }
                //apuntadores anteriores
        while (columnaActual!=nullptr)
        {
            codigoDot+=columnaActual->getColumna();

            if (columnaActual->getAnterior()!=nullptr)
            {
                codigoDot+="->";
                columnaActual=columnaActual->getAnterior();
            }else{
                codigoDot+="\n";
                break;
            } 
        }
            //relaciones de los nodos

        filaActual=root->getAbajo();//segunda fila
        while (filaActual!=nullptr)
        {
            NodoMatriz* nodoActual = filaActual->getSiguiente();
            codigoDot+=filaActual->getFila()+"->";//imprime la cabecera fila
            
            while (nodoActual != nullptr)
            {
                string horas_vuelo=to_string(nodoActual->getDato().getHoras_de_vuelo());
                codigoDot+=horas_vuelo;

                if (nodoActual->getSiguiente()!=nullptr)
                {
                    codigoDot+="->";
                    nodoActual=nodoActual->getSiguiente();
                }else{
                    codigoDot+="\n";
                    break;
                } 
            }
            while (nodoActual != nullptr)
            {
                string horas_vuelo=to_string(nodoActual->getDato().getHoras_de_vuelo());
                codigoDot+=horas_vuelo+"->";
                                                        //condicion de salida para cuando encuentre la fila
                if (nodoActual->getAnterior()!=nullptr && nodoActual->getAnterior()->getDatoString()!="Fila")
                {
                    nodoActual=nodoActual->getAnterior();
                }else{
                    codigoDot+=filaActual->getFila()+"\n";
                    break;
                } 
            }


            filaActual=filaActual->getAbajo();
        }

        //imprimir relaciones verticales
        codigoDot+= "/*------------Relaciones verticales------------*/\n";
        filaActual=root;

            //CABECERAS FILAS
                //apuntadores abajo
        while (filaActual!=nullptr)
        {
            codigoDot+=filaActual->getFila();

            if (filaActual->getAbajo()!=nullptr)
            {
                codigoDot+="->";
                filaActual=filaActual->getAbajo();
            }else{
                codigoDot+="\n";
                break;
            } 
        }
                //apuntadires arriba
        while (filaActual!=nullptr)
        {
            codigoDot+=filaActual->getFila();

            if (filaActual->getArriba()!=nullptr)
            {
                codigoDot+="->";
                filaActual=filaActual->getArriba();
            }else{
                codigoDot+="\n";
                break;
            } 
        }

                //relaciones de los nodos

        columnaActual=root->getSiguiente();//segunda columna
        while (columnaActual!=nullptr)
        {
            NodoMatriz* nodoActual = columnaActual->getAbajo();
            codigoDot+=columnaActual->getColumna()+"->";
            
            while (nodoActual != nullptr)
            {
                string horas_vuelo=to_string(nodoActual->getDato().getHoras_de_vuelo());
                codigoDot+=horas_vuelo;

                if (nodoActual->getAbajo()!=nullptr)
                {
                    codigoDot+="->";
                    nodoActual=nodoActual->getAbajo();
                }else{
                    codigoDot+="\n";
                    break;
                } 
            }
            while (nodoActual != nullptr)
            {
                string horas_vuelo=to_string(nodoActual->getDato().getHoras_de_vuelo());
                codigoDot+=horas_vuelo+"->";
                                                        //condicion de salida para cuando encuentre la fila
                if (nodoActual->getArriba()!=nullptr && nodoActual->getArriba()->getDatoString()!="Columna")
                {
                    nodoActual=nodoActual->getArriba();
                }else{
                    codigoDot+=columnaActual->getColumna()+"\n";
                    break;
                } 
            }
            columnaActual=columnaActual->getSiguiente();
        }

        //alineacion =relaciones horizontales
        codigoDot+= "/*------------encuadre------------*/\n";
        columnaActual=root;
        codigoDot+="{rank=same; ";
        while (columnaActual!=nullptr)
        {
            codigoDot+=columnaActual->getColumna()+"; ";

            if (columnaActual->getSiguiente()!=nullptr)
            {
                columnaActual=columnaActual->getSiguiente();
            }else{
                codigoDot+="}\n";
                break;
            } 
        }

        filaActual=root->getAbajo();//segunda fila
        while (filaActual!=nullptr)
        {
            NodoMatriz* nodoActual = filaActual->getSiguiente();
            codigoDot+="{rank=same; "+filaActual->getFila()+"; ";//imprime la cabecera fila
            
            while (nodoActual != nullptr)
            {
                string horas_vuelo=to_string(nodoActual->getDato().getHoras_de_vuelo())+"; ";
                codigoDot+=horas_vuelo;

                if (nodoActual->getSiguiente()!=nullptr)
                {
                    nodoActual=nodoActual->getSiguiente();
                }else{
                    codigoDot+="}\n";
                    break;
                } 
            }
            filaActual=filaActual->getAbajo();
        }


        codigoDot+="\n}";
        //Creacion del archivo
        ofstream archivo; //
        archivo.open(titulo+".dot", ios::out);
        archivo<<codigoDot;
        archivo.close();
        //renderizar el dot
        string comandoRenderizar="dot -Tsvg "+titulo+".dot -o "+titulo+".svg";
        const char* comandoRenderizar_cstr=comandoRenderizar.c_str();
        system(comandoRenderizar_cstr);
        //abrir el dot
        string open_command="start "+titulo+".svg";
        system(open_command.c_str()); 
    }
    
}
void Matriz::imprimirMatriz() {
    // Imprimir encabezado de columnas
    NodoMatriz* columnaActual = root->getSiguiente();
    cout << "Root";
    while (columnaActual != nullptr) {
        cout << "|" << columnaActual->getColumna();
        columnaActual = columnaActual->getSiguiente();
    }
    cout << endl;

    // Recorrer cada fila
    NodoMatriz* filaActual = root->getAbajo();
    while (filaActual != nullptr) {
        cout << filaActual->getFila(); // Imprimir encabezado de fila
        columnaActual = root->getSiguiente();

        while (columnaActual != nullptr) {
            NodoMatriz* nodoActual = filaActual->getSiguiente();
            bool found = false;
            while (nodoActual != nullptr) {
                if (nodoActual->getColumna() == columnaActual->getColumna()) {
                    cout << "|" << nodoActual->getDato().getNumero_de_id();
                    found = true;
                    break;
                }
                nodoActual = nodoActual->getSiguiente();
            }
            if (!found) {
                cout << "|";
            }
            columnaActual = columnaActual->getSiguiente();
        }
        cout << endl;
        filaActual = filaActual->getAbajo();
    }
}

void Matriz::eliminarNodo(string id)
{
    NodoMatriz* filaActual = root->getAbajo();
    while (filaActual != nullptr) {
        NodoMatriz* nodoActual = filaActual->getSiguiente();
        while (nodoActual != nullptr) {
            if (nodoActual->getDato().getNumero_de_id() == id) { 
                NodoMatriz* nodoAEliminar = nodoActual;
                NodoMatriz* anterior = nodoActual->getAnterior();
                NodoMatriz* siguiente = nodoActual->getSiguiente();
                NodoMatriz* arriba = nodoActual->getArriba();
                NodoMatriz* abajo = nodoActual->getAbajo();

               
                if (anterior != nullptr) anterior->setSiguiente(siguiente);
                if (siguiente != nullptr) siguiente->setAnterior(anterior);
                if (arriba != nullptr) arriba->setAbajo(abajo);
                if (abajo != nullptr) abajo->setArriba(arriba);

                
                if (filaActual->getSiguiente() == nullptr) {
                    NodoMatriz* filaAnterior = filaActual->getArriba();
                    NodoMatriz* filaSiguiente = filaActual->getAbajo();
                    if (filaAnterior != nullptr) filaAnterior->setAbajo(filaSiguiente);
                    if (filaSiguiente != nullptr) filaSiguiente->setArriba(filaAnterior);
                    delete filaActual;
                }

                
                NodoMatriz* columnaActual = root->getSiguiente();
                while (columnaActual != nullptr) {
                    if (columnaActual->getColumna() == nodoAEliminar->getColumna()) {
                        if (columnaActual->getAbajo() == nullptr) {
                            NodoMatriz* columnaAnterior = columnaActual->getAnterior();
                            NodoMatriz* columnaSiguiente = columnaActual->getSiguiente();
                            if (columnaAnterior != nullptr) columnaAnterior->setSiguiente(columnaSiguiente);
                            if (columnaSiguiente != nullptr) columnaSiguiente->setAnterior(columnaAnterior);
                            delete columnaActual;
                        }
                        break;
                    }
                    columnaActual = columnaActual->getSiguiente();
                }

                delete nodoAEliminar;
                return;
            }
            nodoActual = nodoActual->getSiguiente();
        }
        filaActual = filaActual->getAbajo();
    }
}


/*
void Matriz::recorrerMatriz() {
    NodoMatriz* filaActual = root->getAbajo(); // Empieza desde el primer encabezado de fila
    while (filaActual != nullptr) {
        NodoMatriz* nodoActual = filaActual->getSiguiente(); // Empieza desde el primer nodo en la fila
        while (nodoActual != nullptr) {
            cout << "Dato: " << nodoActual->getDato() << ", Fila: " << nodoActual->getFila() << ", Columna: " << nodoActual->getColumna() << endl;
            nodoActual = nodoActual->getSiguiente(); // Avanza al siguiente nodo en la fila
        }
        filaActual = filaActual->getAbajo(); // Avanza al siguiente encabezado de fila
    }
}
*/
Matriz::~Matriz()
{
}
