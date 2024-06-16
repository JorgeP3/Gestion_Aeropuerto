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
    string fabricante;
    int anio_fabricacion;
    int capacidad;
    int peso_max_despegue;
    string aerolinea;
    string estado;

public:
    Avion();
    // Constructor
    Avion(string vuelo, string numero_de_registro, string modelo,
          string fabricante, int anio_fabricacion, int capacidad, 
          int peso_max_despegue, string aerolinea, string estado);
    
    // Getters
    string getVuelo() const;
    string getNumeroDeRegistro() const;
    string getModelo() const;
    string getFabricante() const;
    int getAnioFabricacion() const;
    int getCapacidad() const;
    int getPesoMaxDespegue() const;
    string getAerolinea() const;
    string getEstado() const;

    // Setters
    void setVuelo(string vuelo);
    void setNumeroDeRegistro(string numero_de_registro);
    void setModelo(string modelo);
    void setFabricante(string fabricante);
    void setAnioFabricacion(int anio_fabricacion);
    void setCapacidad(int capacidad);
    void setPesoMaxDespegue(int peso_max_despegue);
    void setAerolinea(string aerolinea);
    void setEstado(string estado);

    // ToString
    string toString() const;

    // Destructor
    ~Avion();
};

Avion::Avion()
    : vuelo(""), numero_de_registro(""), modelo(""), fabricante(""),
      anio_fabricacion(0), capacidad(0), peso_max_despegue(0), 
      aerolinea(""), estado("") {}

// Constructor implementation
Avion::Avion(string vuelo, string numero_de_registro, string modelo,
             string fabricante, int anio_fabricacion, int capacidad, 
             int peso_max_despegue, string aerolinea, string estado)
{
    this->vuelo = vuelo;
    this->numero_de_registro = numero_de_registro;
    this->modelo = modelo;
    this->fabricante = fabricante;
    this->anio_fabricacion = anio_fabricacion;
    this->capacidad = capacidad;
    this->peso_max_despegue = peso_max_despegue;
    this->aerolinea = aerolinea;
    this->estado = estado;
}

// Getters implementation
string Avion::getVuelo() const { return vuelo; }
string Avion::getNumeroDeRegistro() const { return numero_de_registro; }
string Avion::getModelo() const { return modelo; }
string Avion::getFabricante() const { return fabricante; }
int Avion::getAnioFabricacion() const { return anio_fabricacion; }
int Avion::getCapacidad() const { return capacidad; }
int Avion::getPesoMaxDespegue() const { return peso_max_despegue; }
string Avion::getAerolinea() const { return aerolinea; }
string Avion::getEstado() const { return estado; }

// Setters implementation
void Avion::setVuelo(string vuelo) { this->vuelo = vuelo; }
void Avion::setNumeroDeRegistro(string numero_de_registro) { this->numero_de_registro = numero_de_registro; }
void Avion::setModelo(string modelo) { this->modelo = modelo; }
void Avion::setFabricante(string fabricante) { this->fabricante = fabricante; }
void Avion::setAnioFabricacion(int anio_fabricacion) { this->anio_fabricacion = anio_fabricacion; }
void Avion::setCapacidad(int capacidad) { this->capacidad = capacidad; }
void Avion::setPesoMaxDespegue(int peso_max_despegue) { this->peso_max_despegue = peso_max_despegue; }
void Avion::setAerolinea(string aerolinea) { this->aerolinea = aerolinea; }
void Avion::setEstado(string estado) { this->estado = estado; }

// ToString implementation
string Avion::toString() const {
    return "Vuelo: " + vuelo + "\n" +
           "Numero de Registro: " + numero_de_registro + "\n" +
           "Modelo: " + modelo + "\n" +
           "Fabricante: " + fabricante + "\n" +
           "Fecha de Fabricacion: " + to_string(anio_fabricacion) + "\n" +
           "Capacidad: " + to_string(capacidad) + "\n" +
           "Peso Maximo de Despegue: " + to_string(peso_max_despegue) + "\n" +
           "Aerolinea: " + aerolinea + "\n" +
           "Estado: " + estado + "\n";
}

// Destructor implementation
Avion::~Avion() {}

#endif // AVION_H