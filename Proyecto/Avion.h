#ifndef AVION_H
#define AVION_H

#include <string>
#include <iostream>
using namespace std;

class Avion
{
private:
    string vuelo;
    string numero_de_registro;
    string modelo;
    int capacidad;
    string aerolinea;
    string ciudad_destino;
    string estado;

public:
    Avion();
    // Constructor
    Avion(string vuelo, string numero_de_registro, string modelo,
         int capacidad,  string aerolinea,string ciudad_destino, string estado);
    
    // Getters
    string getVuelo() const;
    string getNumeroDeRegistro() const;
    string getModelo() const;
    int getCapacidad() const;
    string getAerolinea() const;
    string getCiudadDestino() const;
    string getEstado() const;

    // Setters
    void setVuelo(string vuelo);
    void setNumeroDeRegistro(string numero_de_registro);
    void setModelo(string modelo);
    void setCapacidad(int capacidad);
    void setAerolinea(string aerolinea);
    void setCiudadDestino(string ciudad_destino);
    void setEstado(string estado);

    // ToString
    string toString() const;

    // Destructor
    ~Avion();
};

Avion::Avion()
    : vuelo(""), numero_de_registro(""), modelo(""), capacidad(0), 
      aerolinea(""),ciudad_destino(""), estado("") {}

// Constructor implementation
Avion::Avion(string vuelo, string numero_de_registro, string modelo,
              int capacidad, string aerolinea,string ciudad_destino, string estado)
{
    this->vuelo = vuelo;
    this->numero_de_registro = numero_de_registro;
    this->modelo = modelo;
    this->capacidad = capacidad;
    this->aerolinea = aerolinea;
    this->ciudad_destino=ciudad_destino;
    this->estado = estado;
}

// Getters implementation
string Avion::getVuelo() const { return vuelo; }
string Avion::getNumeroDeRegistro() const { return numero_de_registro; }
string Avion::getModelo() const { return modelo; }
int Avion::getCapacidad() const { return capacidad; }
string Avion::getAerolinea() const { return aerolinea; }
string Avion::getCiudadDestino() const{return ciudad_destino;}
string Avion::getEstado() const { return estado; }

// Setters implementation
void Avion::setVuelo(string vuelo) { this->vuelo = vuelo; }
void Avion::setNumeroDeRegistro(string numero_de_registro) { this->numero_de_registro = numero_de_registro; }
void Avion::setModelo(string modelo) { this->modelo = modelo; }
void Avion::setCapacidad(int capacidad) { this->capacidad = capacidad; }
void Avion::setAerolinea(string aerolinea) { this->aerolinea = aerolinea; }
void Avion::setCiudadDestino(string ciudad_destino){this->ciudad_destino=ciudad_destino;}
void Avion::setEstado(string estado) { this->estado = estado; }

// ToString implementation
string Avion::toString() const {
    return "Vuelo: " + vuelo + "\n" +
           "Numero de Registro: " + numero_de_registro + "\n" +
           "Modelo: " + modelo + "\n" +
           "Capacidad: " + to_string(capacidad) + "\n" +
           "Aerolinea: " + aerolinea + "\n" +
           "Ciudad de destino: "+ciudad_destino+"\n"+
           "Estado: " + estado + "\n";
}

Avion::~Avion() {}

#endif // AVION_H