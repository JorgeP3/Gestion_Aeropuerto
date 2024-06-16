#ifndef NODOPASAJERO_H
#define NODOPASAJERO_H

#include "Pasajero.h"
#include <iostream>

using namespace std;
//NODO PASAJEROS PARA LISTA DOBLE
class NodoPasajero
{
private:
    Pasajero dato;
    NodoPasajero *anterior;
    NodoPasajero *siguiente;

public:
    NodoPasajero(Pasajero dato);
    NodoPasajero *getSiguiente();
    NodoPasajero *getAnterior();
    void setSiguiente(NodoPasajero *siguiente);
    void setAnterior(NodoPasajero *anterior);
    Pasajero getDato();
    void setDato(Pasajero dato);
    ~NodoPasajero();
};

NodoPasajero::NodoPasajero(Pasajero dato)
{
    this->dato = dato;
    this->anterior = nullptr;
    this->siguiente = nullptr;
}

NodoPasajero* NodoPasajero::getSiguiente()
{
    return this->siguiente;
}

NodoPasajero* NodoPasajero::getAnterior()
{
    return this->anterior;
}

void NodoPasajero::setSiguiente(NodoPasajero *siguiente)
{
    this->siguiente = siguiente;
}

void NodoPasajero::setAnterior(NodoPasajero *anterior)
{
    this->anterior = anterior;
}

Pasajero NodoPasajero::getDato()
{
    return this->dato;
}

void NodoPasajero::setDato(Pasajero dato)
{
    this->dato = dato;
}

NodoPasajero::~NodoPasajero()
{
}

#endif