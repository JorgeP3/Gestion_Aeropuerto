#include <iostream>
#include <fstream>
using namespace std;
#include "NodoArbol.h"


class ArbolBB
{
private:
    /* data */
    NodoArbol* raiz;
    ofstream archivo;
    Piloto nodoDato;
    NodoArbol* eliminarNodo(NodoArbol* nodoPtr, string numero_de_id);
    NodoArbol* encontrarMaximo(NodoArbol* nodoPtr);
    
public:
    int recorrido = 0;
    ArbolBB(/* args */);
    bool estaVacio();
    void insertar(Piloto dato);
    NodoArbol* insertarNodo(Piloto dato, NodoArbol* nodoPtr);//Me retorna un objeto tipo Nodo
    void buscar(int dato);
    Piloto buscarNodo(int dato, NodoArbol* nodoPtr);


    //Recorridos
    void RecorridoPreorder();
    void RecorridoPreorder(NodoArbol* nodoPtr);
    void RecorridoInorder();
    void RecorridoInorder(NodoArbol* nodoPtr);
    void RecorridoPostorder();
    void RecorridoPostorder(NodoArbol* nodoPtr);
    
    void generarReporte(string titulo);
    string imprimirNodo(NodoArbol* nodoPtr);
    void eliminarNodo(string numero_de_id);
    ~ArbolBB();
};

ArbolBB::ArbolBB(/* args */)
{
    raiz = nullptr;
}

bool ArbolBB::estaVacio()
{
    return (raiz == nullptr);
}

void ArbolBB::insertar(Piloto dato)
{
    raiz = insertarNodo(dato, raiz);//Dato que voy a insertar que es te tipo Piloto, y la Raiz que es de tipo Nodo.
}

NodoArbol* ArbolBB::insertarNodo(Piloto dato, NodoArbol* nodoPtr)
{
    if (nodoPtr == nullptr)//si la raiz esta vacia //condicion de salida de la recursividad
    {
        NodoArbol* nuevo = new NodoArbol(dato);//crea un nuevo objeto Nodo con el Piloto como dato
        nodoPtr = nuevo;//La Raiz es igual al nuevo nodo
    }
    else if (dato.getHoras_de_vuelo() < nodoPtr->getDato().getHoras_de_vuelo())
    {
        nodoPtr->setIzq(insertarNodo(dato, nodoPtr->getIzq()));
    }
    else if (dato.getHoras_de_vuelo() > nodoPtr->getDato().getHoras_de_vuelo())
    {
        nodoPtr->setDer(insertarNodo(dato, nodoPtr->getDer()));
    }
    else{
        cout << "Nodo duplicado\n";
    }
    return nodoPtr;
}
                    
void ArbolBB::buscar(int dato)
{
    cout << "Recorrido del nodo encontrado: " << buscarNodo(dato, raiz).getHoras_de_vuelo() << ", " << recorrido;
}

Piloto ArbolBB::buscarNodo(int dato, NodoArbol* nodoPtr)
{
    if (nodoPtr == nullptr)
    {
        cout << "NodoArbol no encontrado\n";
        return Piloto();
    }
    else if(dato == nodoPtr->getDato().getHoras_de_vuelo()){
        recorrido++;
        return nodoPtr->getDato();
    }
    else if(dato < nodoPtr->getDato().getHoras_de_vuelo())
    {
        recorrido++;
        return buscarNodo(dato, nodoPtr->getIzq());
    }
    else if(dato > nodoPtr->getDato().getHoras_de_vuelo())
    {
        recorrido ++;
        return buscarNodo(dato, nodoPtr->getDer());
    }
    return Piloto();
}

void ArbolBB::RecorridoPreorder()
{
    RecorridoPreorder(raiz);
    cout << endl;

}

void ArbolBB::RecorridoPreorder(NodoArbol* nodoPtr)
{   
    if (nodoPtr != nullptr)
    {
        cout << nodoPtr->getDato().getHoras_de_vuelo()<<", ";
        RecorridoPreorder(nodoPtr->getIzq());
        RecorridoPreorder(nodoPtr->getDer());
    }
    
}

void ArbolBB::RecorridoInorder()
{
    RecorridoInorder(raiz);
    cout << endl;

}

void ArbolBB::RecorridoInorder(NodoArbol* nodoPtr)
{   
    if (nodoPtr != nullptr)
    {
        RecorridoInorder(nodoPtr->getIzq());
        cout << nodoPtr->getDato().getHoras_de_vuelo()<<", ";
        RecorridoInorder(nodoPtr->getDer());
    }
    
}

void ArbolBB::RecorridoPostorder()
{
    RecorridoPostorder(raiz);
    cout << endl;
}

void ArbolBB::RecorridoPostorder(NodoArbol* nodoPtr)
{   
    if (nodoPtr != nullptr)
    {
        RecorridoPostorder(nodoPtr->getIzq());
        RecorridoPostorder(nodoPtr->getDer());
        cout << nodoPtr->getDato().getHoras_de_vuelo()<<", ";
    }
    
}


void ArbolBB::generarReporte(string titulo)
{
    if (ArbolBB::estaVacio()){
        cout<<"El arbol binario esta vacio"<<endl;
    }
    else
    {
        //Encabezado
        string codigoDot="digraph Grafo1 {\nrankdir = \"TB\"\nlabel=\""+titulo+"\"\n";
        codigoDot+="labelloc=\"t\"\n";
        codigoDot+="node[shape=circle]\n";//atributos del los nodos
        codigoDot+="edge[]\n"; // atributos de las aristas

        codigoDot+=imprimirNodo(raiz);

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

string ArbolBB::imprimirNodo(NodoArbol* nodoPtr)
{
    string codigoDot="";
    if (nodoPtr == nullptr)
    {
        return codigoDot;
    }
    if (nodoPtr->getIzq() != nullptr)//si el izquiero de raiz actual es diferente de nulo
    {
        nodoDato = nodoPtr->getDato();
        codigoDot+=to_string(nodoDato.getHoras_de_vuelo()); 
        codigoDot+="->";
        nodoDato = nodoPtr->getIzq()->getDato();
        codigoDot+=to_string(nodoDato.getHoras_de_vuelo())+"\n";
    }
    codigoDot+=imprimirNodo(nodoPtr->getIzq());
    
    if (nodoPtr->getDer()!= nullptr)
    {
        nodoDato = nodoPtr->getDato();
        codigoDot+=to_string(nodoDato.getHoras_de_vuelo()); 
        codigoDot+= "->";
        nodoDato = nodoPtr->getDer()->getDato();
        codigoDot+=to_string(nodoDato.getHoras_de_vuelo())+"\n";
    }
    codigoDot+=imprimirNodo(nodoPtr->getDer());
    return codigoDot;
    
}

NodoArbol* ArbolBB::encontrarMaximo(NodoArbol* nodoPtr) {
    while (nodoPtr->getDer() != nullptr) {
        nodoPtr = nodoPtr->getDer();
    }
    return nodoPtr;
}

NodoArbol* ArbolBB::eliminarNodo(NodoArbol* nodoPtr, string numero_de_id) {
    if (nodoPtr == nullptr) {
        return nodoPtr;
    }

    if (numero_de_id < nodoPtr->getDato().getNumero_de_id()) {
        nodoPtr->setIzq(eliminarNodo(nodoPtr->getIzq(), numero_de_id));
    } else if (numero_de_id > nodoPtr->getDato().getNumero_de_id()) {
        nodoPtr->setDer(eliminarNodo(nodoPtr->getDer(), numero_de_id));
    } else {
        // Caso 1: Nodo hoja
        if (nodoPtr->getIzq() == nullptr && nodoPtr->getDer() == nullptr) {
            delete nodoPtr;
            nodoPtr = nullptr;
        }
        // Caso 2: Nodo con un solo hijo
        else if (nodoPtr->getIzq() == nullptr) {
            NodoArbol* temp = nodoPtr;
            nodoPtr = nodoPtr->getDer();
            delete temp;
        } else if (nodoPtr->getDer() == nullptr) {
            NodoArbol* temp = nodoPtr;
            nodoPtr = nodoPtr->getIzq();
            delete temp;
        }
        // Caso 3: Nodo con dos hijos
        else {
            NodoArbol* temp = encontrarMaximo(nodoPtr->getIzq());
            nodoPtr->setDato(temp->getDato());
            nodoPtr->setIzq(eliminarNodo(nodoPtr->getIzq(), temp->getDato().getNumero_de_id()));
        }
    }
    return nodoPtr;
}

void ArbolBB::eliminarNodo(string numero_de_id) {
    raiz = eliminarNodo(raiz, numero_de_id);
}

ArbolBB::~ArbolBB()
{
}