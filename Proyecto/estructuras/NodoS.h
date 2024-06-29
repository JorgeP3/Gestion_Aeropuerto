#ifndef NODOS_H
#define NODOS_H
#include "../clases/Piloto.h"
#include <iostream>

using namespace std;

class NodoS
{
private:
    Piloto dato;
    NodoS *siguiente;

public:
    NodoS(Piloto dato);
    NodoS *getSiguiente();
    void setSiguiente(NodoS *siguiente);
    Piloto getDato();
    void setDato(Piloto dato);
    ~NodoS();
};

NodoS::NodoS(Piloto dato)
{
    this->dato = dato;
    this->siguiente = nullptr;
}

NodoS* NodoS::getSiguiente()
{
    return this->siguiente;
}

void NodoS::setSiguiente(NodoS *siguiente)
{
    this->siguiente = siguiente;
}

Piloto NodoS::getDato()
{
    return this->dato;
}

void NodoS::setDato(Piloto dato)
{
    this->dato = dato;
}

NodoS::~NodoS()
{
}

#endif