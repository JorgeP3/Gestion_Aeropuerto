#ifndef NODOAVION_H
#define NODOAVION_H

#include "Avion.h"
#include <iostream>
using namespace std;

class NodoAvion
{
private:
    Avion dato;
    NodoAvion *anterior;
    NodoAvion *siguiente;
public:
    NodoAvion(Avion dato);
    NodoAvion *getSiguiente();
    NodoAvion *getAnterior();
    void setSiguiente(NodoAvion *siguiente);
    void setAnterior(NodoAvion *anterior);
    Avion getDato();
    void setDato(Avion dato);
    ~NodoAvion();
};

NodoAvion::NodoAvion(Avion dato)
{
    this->dato = dato;
    this->anterior = nullptr;
    this->siguiente = nullptr;
}

NodoAvion* NodoAvion::getSiguiente(){
    return this->siguiente;
}

NodoAvion* NodoAvion::getAnterior(){
    return this->anterior;
}

void NodoAvion::setSiguiente(NodoAvion *siguiente){
    this->siguiente = siguiente;
}

void NodoAvion::setAnterior(NodoAvion *anterior){
    this->anterior = anterior;
}

Avion NodoAvion::getDato(){
    return this->dato;
}

void NodoAvion::setDato(Avion dato){
    this->dato = dato;
}


NodoAvion::~NodoAvion()
{
}

#endif
/*

class NodoAvion
{
private:
    int dato;
    NodoAvion *anterior;
    NodoAvion *siguiente;
public:
    NodoAvion(int dato);
    NodoAvion *getSiguiente();
    NodoAvion *getAnterior();
    void setSiguiente(NodoAvion *siguiente);
    void setAnterior(NodoAvion *anterior);
    int getDato();
    void setDato(int dato);
    ~NodoAvion();
};

NodoAvion::NodoAvion(int dato)
{
    this->dato = dato;
    this->anterior = nullptr;
    this->siguiente = nullptr;
}

NodoAvion* NodoAvion::getSiguiente(){
    return this->siguiente;
}

NodoAvion* NodoAvion::getAnterior(){
    return this->anterior;
}

void NodoAvion::setSiguiente(NodoAvion *siguiente){
    this->siguiente = siguiente;
}

void NodoAvion::setAnterior(NodoAvion *anterior){
    this->anterior = anterior;
}

int NodoAvion::getDato(){
    return this->dato;
}


NodoAvion::~NodoAvion()
{
} */