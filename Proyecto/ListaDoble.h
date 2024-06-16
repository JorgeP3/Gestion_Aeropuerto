#include <iostream>
using namespace std;
#include "NodoPasajero.h"

class ListaDoble
{
private:
    NodoPasajero *primero;
    NodoPasajero *ultimo;
public:
    ListaDoble();
    bool estaVacia();
    void insertarInicio(Pasajero dato);
    void insertarFinal(Pasajero dato);
    void eliminarInicio();
    void eliminarFinal();
    void visualizarLista();
    void generarReporte(string titulo);
    void buscarPorNumeroPasaporte(string numeroPasaporte);
    void ordenarLista();
    ~ListaDoble();
};

ListaDoble::ListaDoble()
{
    primero = nullptr;
    ultimo = nullptr;
}

bool ListaDoble::estaVacia()
{
    return (primero == nullptr) && (ultimo == nullptr);
}

void ListaDoble::insertarInicio(Pasajero dato)
{
    NodoPasajero *nuevo = new NodoPasajero(dato); // Se crea el nuevo nodo
    if (ListaDoble::estaVacia())
    {
        primero = ultimo = nuevo;
    }
    else
    {
        primero->setAnterior(nuevo); // Se enlaza el primer nodo al nuevo
        nuevo->setSiguiente(primero); // Se enlaza el nuevo nodo al primero
        primero = nuevo; // Se verifica que el nodo creado sea el primero
    }
}

void ListaDoble::insertarFinal(Pasajero dato)
{
    NodoPasajero *nuevo = new NodoPasajero(dato);
    if (ListaDoble::estaVacia())
    {
        primero = ultimo = nuevo;
    }
    else
    {
        ultimo->setSiguiente(nuevo); // Se enlaza el último nodo al nuevo
        nuevo->setAnterior(ultimo); // Se enlaza el nuevo nodo al último
        ultimo = nuevo; // Se verifica que el nodo creado sea el último
    }
}

void ListaDoble::eliminarInicio()
{
    if (ListaDoble::estaVacia())
    {
        cout << "La lista pasajeros esta vacia" << endl;
    }
    else
    {
        if (primero == ultimo)
        {
            delete primero;
            primero = ultimo = nullptr;
        }
        else
        {
            NodoPasajero *segundo = primero->getSiguiente();
            segundo->setAnterior(nullptr);
            delete primero;
            primero = segundo;
        }
    }
}

void ListaDoble::eliminarFinal()
{
    if (ListaDoble::estaVacia())
    {
        cout << "La lista pasajeros esta vacia" << endl;
    }
    else
    {
        if (primero == ultimo)
        {
            delete primero;
            primero = ultimo = nullptr;
        }
        else
        {
            NodoPasajero* antepenultimo = ultimo->getAnterior(); // Guardo la referencia del antepenúltimo nodo
            delete ultimo;
            antepenultimo->setSiguiente(nullptr);
            ultimo = antepenultimo;
        }
    }
}

void ListaDoble::visualizarLista()
{
    if (ListaDoble::estaVacia())
    {
        cout << "La lista pasajeros esta vacia\n" << endl;
    }
    else
    {
        NodoPasajero *actual = ultimo;//va de atras para adelante
        while (actual != nullptr)
        {
            cout << actual->getDato().ToString() << endl; // Supongamos que Pasajero tiene un método toString
            actual = actual->getAnterior();
        }
    }
}

void ListaDoble::buscarPorNumeroPasaporte(string numeroPasaporte){
    if (ListaDoble::estaVacia()){
        cout<<"La listaPasajeros esta vacia\n"<<endl;
    }else{
        NodoPasajero *actual=primero;
        while (actual != nullptr)
        {
            if (actual->getDato().getNumero_pasaporte() == numeroPasaporte)
            {
                Pasajero pasajero=actual->getDato();
                cout<<pasajero.ToString()<<endl;
                return;
            }
            actual = actual->getSiguiente();
        }
        cout << "No se encontro al pasajero con el numero de pasaporte " << numeroPasaporte << endl;
    }
}

void ListaDoble::generarReporte(string titulo){

    string codigoDot="digraph Grafo1 {\nrankdir = \"LR\"\nlabel=\""+titulo+"\""+"\nnode[shape=rectangle]\nedge[constraint=false]\n";
    codigoDot+="Primero[label=\"Primero\\n(NULL)\"]\n";
    codigoDot+="Ultimo[label=\"Ultimo\\n(NULL)\"]\n";
    
    if (ListaDoble::estaVacia()){
        cout<<"La listaPasajeros esta vacia\n"<<endl;
    }
    else{
        NodoPasajero *actual=primero;
        //nodos
        do{
            string pasaporte=actual->getDato().getNumero_pasaporte();
            string nombre=actual->getDato().getNombre();
            string vuelo=actual->getDato().getNumero_vuelo();
            string asiento=to_string(actual->getDato().getAsiento());
            codigoDot+=pasaporte+"[label=\""+pasaporte+"\\n"+nombre+"\\nVuelo: "+vuelo+"\\nAsiento: "+asiento+"\"]\n";
            actual = actual->getSiguiente();
        }while (actual != nullptr);
        actual=primero;
        do{
            string pasaporte=actual->getDato().getNumero_pasaporte();
           
            codigoDot+=pasaporte+"->";
            actual = actual->getSiguiente();
            if (actual == nullptr)
            {   
                codigoDot+="Ultimo\n";
            }
        }while (actual != nullptr);
        actual=ultimo;
        do{
            string pasaporte=actual->getDato().getNumero_pasaporte();
           
            codigoDot+=pasaporte+"->";
            actual = actual->getAnterior();
            if (actual == nullptr)
            {   
                codigoDot+="Primero\n";
            }
        }while (actual != nullptr);

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

void ListaDoble::ordenarLista() {
    if (estaVacia()) {
        return;
    }

    bool swapped;
    NodoPasajero* current;
    NodoPasajero* last = nullptr;

    do {
        swapped = false;
        current = primero;

        while (current->getSiguiente() != last) {
            Pasajero pasajero1 = current->getDato();
            Pasajero pasajero2 = current->getSiguiente()->getDato();

            if (pasajero1.getNumero_vuelo() > pasajero2.getNumero_vuelo() ||
                (pasajero1.getNumero_vuelo() == pasajero2.getNumero_vuelo() && pasajero1.getAsiento() > pasajero2.getAsiento())) {
                // Intercambiar datos
                current->setDato(pasajero2);
                current->getSiguiente()->setDato(pasajero1);
                swapped = true;
            }
            current = current->getSiguiente();
        }
        last = current;
    } while (swapped);
}

ListaDoble::~ListaDoble() {}