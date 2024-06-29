
//clases
#include "NodoAvion.h"
#include "../clases/Avion.h"
//librerias
#include <iostream>
#include <fstream> //cabecera para manejar archivos (leer y escribir)
#include <cstdlib> //cabecera para manejar el system (cmd)

using namespace std;

class CircularDoble
{
private:
    NodoAvion *primero;
    NodoAvion *ultimo;
public:
    CircularDoble();
    bool estaVacia();
    void insertarInicio(Avion dato);
    void insertarFinal(Avion dato);
    void eliminarInicio();
    void eliminarFinal();
    void visualizarLista();
    void generarReporte(string titulo);
    void eliminarPorNumeroDeRegistro(string numeroDeRegistro);
    Avion buscarPorNumeroDeRegistro(string numeroDeRegistro);
    string buscarPorNumeroDeVuelo(string vuelo);
    void ordenar();
    ~CircularDoble();
};

CircularDoble::CircularDoble()
{
    primero = nullptr;
    ultimo = nullptr;
}

bool CircularDoble::estaVacia(){
    return (primero == nullptr) && (ultimo == nullptr);
}

void CircularDoble::insertarInicio(Avion dato){
    NodoAvion *nuevo = new NodoAvion(dato);
    if (CircularDoble::estaVacia())
    {
        nuevo->setSiguiente(nuevo);
        nuevo->setAnterior(nuevo);
        primero = ultimo = nuevo;
    }
    else
    {
        nuevo->setSiguiente(primero);
        nuevo->setAnterior(ultimo);
        ultimo->setSiguiente(nuevo);
        primero->setAnterior(nuevo);
        primero = nuevo;
    }
}

void CircularDoble::insertarFinal(Avion dato){
    NodoAvion *nuevo = new NodoAvion(dato);
    if (CircularDoble::estaVacia()){
        nuevo->setSiguiente(nuevo);
        nuevo->setAnterior(nuevo);
        primero = ultimo = nuevo;
    }
    else{
        nuevo->setSiguiente(primero);
        nuevo->setAnterior(ultimo);
        ultimo->setSiguiente(nuevo);
        primero->setAnterior(nuevo);
        ultimo = nuevo;
    }
}

void CircularDoble::eliminarInicio(){
    if (CircularDoble::estaVacia()){
        cout<<"La lista circular doble esta vacia"<<endl;
    }
    else{
        if(primero == ultimo){
            delete primero;
            primero = ultimo = nullptr;
        }
        else{
            NodoAvion *segundo = primero->getSiguiente();
            ultimo->setSiguiente(segundo);
            segundo->setAnterior(ultimo);
            delete primero;
            primero = segundo;
        }
    }
}

void CircularDoble::eliminarFinal(){
    if (CircularDoble::estaVacia()){
        cout<<"La lista circular doble esta vacia"<<endl;
    }
    else{
        if (primero == ultimo){
            delete primero;
            primero = ultimo = nullptr;
        }
        else{
            NodoAvion *penultimo = ultimo->getAnterior();
            penultimo->setSiguiente(primero);
            primero->setAnterior(penultimo);
            delete ultimo;
            ultimo = penultimo;
        }
    }
}

void CircularDoble::visualizarLista(){
    if (CircularDoble::estaVacia()){
        cout<<"La lista circular doble esta vacia\n"<<endl;
    }
    else{
        NodoAvion *actual = primero;
        do{
            cout << actual->getDato().toString() << endl; 
            actual = actual->getSiguiente();
        }while (actual != primero);
    }
}

void CircularDoble::generarReporte(string titulo){
   
    //Encabezado
    string codigoDot="digraph Grafo1 {\nrankdir = \"LR\"\nlabel=\""+titulo+"\"\n";
    codigoDot+="labelloc=\"t\"\n";
    codigoDot+="node[shape=rectangle]\n";//atributos del los nodos
    codigoDot+="edge[constraint=false]\n"; // atributos de los 
    if (CircularDoble::estaVacia()){
        cout<<"La lista circular doble esta vacia\n"<<endl;
    }
    else{
        
        NodoAvion *actual = primero;

        do{
            string numero_registro_actual=actual->getDato().getNumeroDeRegistro();
            string estado=actual->getDato().getEstado();
            codigoDot+=numero_registro_actual+"[label=\""+numero_registro_actual+"\\n"+estado+"\"]\n";
            actual = actual->getSiguiente();
        }while (actual != primero);
        do{
            string numero_registro_actual=actual->getDato().getNumeroDeRegistro();
            //string estado=actual->getDato().getEstado();
            codigoDot+=numero_registro_actual+"->";
            actual = actual->getSiguiente();
            if (actual == primero)
            {   
                codigoDot+=actual->getDato().getNumeroDeRegistro()+"\n";
            }
        }while (actual != primero);
        actual=ultimo;
        do{
            
            string numero_registro_actual=actual->getDato().getNumeroDeRegistro();
            //string estado=actual->getDato().getEstado();
            codigoDot+=numero_registro_actual+"->";
            actual = actual->getAnterior();
            if (actual == ultimo)
            {   
                codigoDot+=actual->getDato().getNumeroDeRegistro();
            }
        }while (actual != ultimo);

        codigoDot+="\n}";
        //cout << codigoDot << endl;
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

void CircularDoble::eliminarPorNumeroDeRegistro(string numeroDeRegistro) {
    if (CircularDoble::estaVacia()){
        cout<<"La lista circular doble esta vacia"<<endl;
        return;
    }

    NodoAvion *actual = primero;
    do {
        if (actual->getDato().getNumeroDeRegistro() == numeroDeRegistro) {
            if (actual == primero && actual == ultimo) {
                // Solo un elemento en la lista
                delete actual;
                primero = ultimo = nullptr;
            } else if (actual == primero) {
                // Eliminar el primero
                NodoAvion *segundo = primero->getSiguiente();
                ultimo->setSiguiente(segundo);
                segundo->setAnterior(ultimo);
                delete primero;
                primero = segundo;
            } else if (actual == ultimo) {
                // Eliminar el último
                NodoAvion *penultimo = ultimo->getAnterior();
                penultimo->setSiguiente(primero);
                primero->setAnterior(penultimo);
                delete ultimo;
                ultimo = penultimo;
            } else {
                // Eliminar un nodo en medio
                NodoAvion *anterior = actual->getAnterior();
                NodoAvion *siguiente = actual->getSiguiente();
                anterior->setSiguiente(siguiente);
                siguiente->setAnterior(anterior);
                delete actual;
            }
            cout << "Avion con numero de registro " << numeroDeRegistro << " eliminado." << endl;
            return;
        }
        actual = actual->getSiguiente();
    } while (actual != primero);

    cout << "No se encontro un avion con el numero de registro " << numeroDeRegistro << endl;
}

Avion CircularDoble::buscarPorNumeroDeRegistro(string numeroDeRegistro) {
    if (CircularDoble::estaVacia()){
        cout<<"La lista circular doble esta vacia"<<endl;
        // Devolver un objeto Avion predeterminado o especial
        return Avion();
    }

    NodoAvion *actual = primero;
    do {
        if (actual->getDato().getNumeroDeRegistro() == numeroDeRegistro) {
            return actual->getDato();
        }
        actual = actual->getSiguiente();
    } while (actual != primero);

    cout << "No se encontro un avion con el numero de registro " << numeroDeRegistro << endl;
    return Avion();
}

string CircularDoble::buscarPorNumeroDeVuelo(string vuelo) {//esto metodo al ingresarle un vuelo lo busca y devuelve su ciuda
    if (CircularDoble::estaVacia()){
        cout<<"La lista circular doble esta vacia"<<endl;
        // Devolver un objeto Avion predeterminado o especial
        return Avion().getCiudadDestino();
    }

    NodoAvion *actual = primero;
    do {
        if (actual->getDato().getVuelo() == vuelo) {
            return actual->getDato().getCiudadDestino();
        }
        actual = actual->getSiguiente();
    } while (actual != primero);

    cout << "No se encontro un avion con el numero de registro " << vuelo << endl;
    return Avion().getCiudadDestino();
}

CircularDoble::~CircularDoble()
{
    while (!estaVacia()) {
        eliminarInicio();
    }
}