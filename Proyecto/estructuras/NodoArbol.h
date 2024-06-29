#include "../clases/Piloto.h" 
#include <iostream>
using namespace std;
//este te nodo sera usado para guardar objetos tipo piloto
class NodoArbol
{
private:
    /* data */
    Piloto dato;
    NodoArbol* izq; //Hijo izquierdo
    NodoArbol* der; //Hijo derecho
public:
    NodoArbol(Piloto dato);
    void setDato(Piloto dato);
    Piloto getDato();
    void setIzq(NodoArbol* izq);
    NodoArbol* getIzq();
    void setDer(NodoArbol* der);
    NodoArbol* getDer();
    ~NodoArbol();
};

NodoArbol::NodoArbol(Piloto dato)
{
    this->dato = dato;
    this->izq = nullptr;
    this->der = nullptr;
}

void NodoArbol::setDato(Piloto  dato)
{
    this->dato = dato;
}

void NodoArbol::setIzq(NodoArbol* izq)
{
    this->izq = izq;
}

void NodoArbol::setDer(NodoArbol* der)
{
    this->der = der;
}

Piloto  NodoArbol::getDato()
{
    return this->dato;
}

NodoArbol* NodoArbol::getIzq()
{
    return this->izq;
}

NodoArbol* NodoArbol::getDer()
{
    return this->der;
}

NodoArbol::~NodoArbol()
{
}