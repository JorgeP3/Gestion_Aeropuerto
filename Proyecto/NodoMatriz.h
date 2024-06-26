#include <iostream>
#include <string.h>
#include "Piloto.h"
using namespace std;

class NodoMatriz
{
private:
    /* data */
    Piloto dato;
    string datoString;
    string fila, columna;
    NodoMatriz* anterior;
    NodoMatriz* siguiente;
    NodoMatriz* arriba;
    NodoMatriz* abajo;
    
public:
    NodoMatriz(/* args */);
    NodoMatriz(Piloto dato, string fila, string columna);
    NodoMatriz(string datoString, string fila, string columna);

    string getDatoString();

    Piloto getDato();
    void setDato(Piloto dato);
    string getFila();
    void setFila(string fila);
    string getColumna();
    void setColumna(string columna);

    NodoMatriz* getAnterior();
    void setAnterior(NodoMatriz* anterior);
    NodoMatriz* getSiguiente();
    void setSiguiente(NodoMatriz* siguiente);
    NodoMatriz* getArriba();
    void setArriba(NodoMatriz* arriba);
    NodoMatriz* getAbajo();
    void setAbajo(NodoMatriz* abajo);
    ~NodoMatriz();
};

NodoMatriz::NodoMatriz(/* args */)
{

}
NodoMatriz::NodoMatriz(string datoString, string fila, string columna)//constructor para string
{
    this->datoString = datoString;
    this->fila = fila;
    this->columna = columna;
    anterior = siguiente = arriba = abajo = nullptr;
}

NodoMatriz::NodoMatriz(Piloto dato, string fila, string columna)//constructor para objetos
{
    this->dato = dato;
    this->fila = fila;
    this->columna = columna;
    anterior = siguiente = arriba = abajo = nullptr;
}

NodoMatriz* NodoMatriz::getAnterior()
{
    return anterior;
}

void NodoMatriz::setAnterior(NodoMatriz* anterior)
{
    this->anterior = anterior;
}


NodoMatriz* NodoMatriz::getSiguiente()
{
    return siguiente;
}

void NodoMatriz::setSiguiente(NodoMatriz* siguiente)
{
    this->siguiente = siguiente;
}



NodoMatriz* NodoMatriz::getArriba()
{
    return arriba;
}

void NodoMatriz::setArriba(NodoMatriz* arriba)
{
    this->arriba = arriba;
}


NodoMatriz* NodoMatriz::getAbajo()
{
    return abajo;
}

void NodoMatriz::setAbajo(NodoMatriz* abajo)
{
    this->abajo = abajo;
}

string NodoMatriz::getFila(){
    return fila;
}

void NodoMatriz::setFila(string fila)
{
    this->fila = fila;
}

string NodoMatriz::getColumna()
{
    return columna;
}

void NodoMatriz::setColumna(string columna)
{
    this->columna = columna;
}

Piloto NodoMatriz::getDato(){
    return dato;
}

string NodoMatriz::getDatoString(){
    return datoString;
}

void NodoMatriz::setDato(Piloto dato)
{
    this->dato = dato;
}

NodoMatriz::~NodoMatriz()
{
}