#include <iostream>
using namespace std;
#include "NodoS.h"

class ListaSimple
{
private:
    /* NECESITAMOS UNA REFERENCIA DEL PRIMER Y ÚLTIMO NODOSNodoS DE LA LISTA */
    NodoS *primero, *ultimo;
public:
    ListaSimple(/* args */);
    bool estaVacia();
    void insertarInicio(Piloto dato);
    void insertarFinal(Piloto dato);
    void eliminarInicio();
    void eliminarFinal();
    void visualizarLista();
    void eliminarPorId(string munero_id);
    string txt_lista();
    ~ListaSimple();
};

ListaSimple::ListaSimple(/* args */)
{
    primero = ultimo = nullptr;
}

bool ListaSimple::estaVacia()
{
    return (primero == nullptr) && (ultimo == nullptr);
}

void ListaSimple::insertarInicio(Piloto dato)
{
    NodoS *nuevo = new NodoS(dato); //Se crea el nuevo nodoSNodoS
    if (ListaSimple::estaVacia())
    {
        /* code */
        primero = ultimo = nuevo;
    }
    else
    {
        nuevo->setSiguiente(primero); //Se enlaza el nuevo nodoSNodoS al primero
        primero = nuevo; //Se verifica que el nodoSNodoS creado sea el primero
    }
    
}

void ListaSimple::insertarFinal(Piloto dato)
{
    NodoS *nuevo = new NodoS(dato);
    if (ListaSimple::estaVacia())
    {
        /* code */
        primero = ultimo = nuevo;
    }
    else
    {
        ultimo->setSiguiente(nuevo); //Se enlaza el último nodoSNodoS al nuevo
        ultimo = nuevo; //Se verfica que el nodoSNodoS creado sea el último
    }
}

void ListaSimple::eliminarInicio()
{
    if (ListaSimple::estaVacia())
    {
        /* code */
        cout << "La lista está vacía" << endl;
    }
    else
    {
        if (primero == ultimo)//si solo hay un elemento
        {
            /* code */
            delete primero;
            primero = ultimo = nullptr;
        }
        else
        {
            NodoS *segundo = primero->getSiguiente();
            delete primero;
            primero = segundo;
        }   
    } 
}

void ListaSimple::eliminarFinal()
{
    if (ListaSimple::estaVacia())
    {
        cout << "La lista está vacía" << endl;
    }
    else{
        NodoS* temporal = primero;
        if (primero == ultimo)
        {
            /* code */
            delete primero;
            primero = ultimo = nullptr;
        }
        else{
            while (temporal != nullptr)
            {
                /* code */
                if (temporal->getSiguiente() == ultimo) //Si el siguiente de temporal es el último, entonces temporal es el antepenultimo
                {
                    /* code */
                    delete ultimo;
                    temporal->setSiguiente(nullptr);
                    ultimo = temporal;
                }
                temporal = temporal->getSiguiente(); //Recorriendo la lista
            }
            
        }
        
    }
    
}

void ListaSimple::visualizarLista()
{
    if (ListaSimple::estaVacia())
    {
        /* code */
        cout << "La lista está vacía" << endl;
    }
    else
    {
        Piloto nodoDato;
        NodoS *actual = primero;
        while (actual != nullptr)
        {
            /* code */
            nodoDato = actual->getDato();
            //cout << nodoSNodoSDato << endl;
            cout << nodoDato.getNumero_de_id() << (actual->getSiguiente() != nullptr ? " -> ": "\n");
            actual = actual->getSiguiente();
        }
        
    }
    
}
string ListaSimple::txt_lista(){
    if (ListaSimple::estaVacia())
    {
        return " ";
    }
    else
    {
        string codigoDot="";
        Piloto nodoDato;
        NodoS *actual = primero;
        while (actual != nullptr)
        {
            /* code */
            nodoDato = actual->getDato();
            //cout << nodoSNodoSDato << endl;
            codigoDot+= nodoDato.getNumero_de_id()+(actual->getSiguiente() != nullptr ? " -> ": "\n");
            actual = actual->getSiguiente();
        }
        return codigoDot;
    }

}

void ListaSimple::eliminarPorId(string numero_id)
{
    if (ListaSimple::estaVacia())
    {
        cout << "La lista está vacía" << endl;
    }
    else
    {
        NodoS* temporal = primero;
        NodoS* anterior = nullptr;

        while (temporal != nullptr)
        {
            if (temporal->getDato().getNumero_de_id() == numero_id) // Si encontramos el elemento con el ID buscado
            {
                if (temporal == primero) // Si es el primer elemento
                {
                    eliminarInicio();
                }
                else if (temporal == ultimo) // Si es el último elemento
                {
                    eliminarFinal();
                }
                else // Si está en medio de la lista
                {
                    anterior->setSiguiente(temporal->getSiguiente());
                    delete temporal;
                }
                return; // Salimos del método después de eliminar el elemento
            }

            anterior = temporal;
            temporal = temporal->getSiguiente();
        }

        cout << "No se encontró ningún elemento con el ID " << numero_id << endl;
    }
}

ListaSimple::~ListaSimple()
{
}