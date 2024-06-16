#ifndef NODOPASAJEROS_H
#define NODOPASAJEROS_H

#include "Pasajero.h"
#include <iostream>

using namespace std;

class NodoPasajeroS
{
private:
    Pasajero dato;
    NodoPasajeroS *siguiente;

public:
    NodoPasajeroS(Pasajero dato);
    NodoPasajeroS *getSiguiente();
    void setSiguiente(NodoPasajeroS *siguiente);
    Pasajero getDato();
    void setDato(Pasajero dato);
    ~NodoPasajeroS();
};

NodoPasajeroS::NodoPasajeroS(Pasajero dato)
{
    this->dato = dato;
    this->siguiente = nullptr;
}

NodoPasajeroS* NodoPasajeroS::getSiguiente()
{
    return this->siguiente;
}

void NodoPasajeroS::setSiguiente(NodoPasajeroS *siguiente)
{
    this->siguiente = siguiente;
}

Pasajero NodoPasajeroS::getDato()
{
    return this->dato;
}

void NodoPasajeroS::setDato(Pasajero dato)
{
    this->dato = dato;
}

NodoPasajeroS::~NodoPasajeroS()
{
}

#endif