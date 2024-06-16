#ifndef PASAJERO_H
#define PASAJERO_H

#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class Pasajero
{
private:
    string nombre;
    string nacionalidad;
    string numero_pasaporte;
    string numero_vuelo;
    int asiento;
    string destino;
    string origen;
    int equipaje_facturado;
public:
    Pasajero(/* args */);
    //constructor con parametros
    Pasajero(string nombre, string nacionalidad, 
    string numero_pasaporte,string numero_vuelo, int asiento, 
    string destino, string origen, int equipaje_facturado);

    //getters
    string getNombre() const;
    string getNacionalidad() const;
    string getNumero_pasaporte() const;
    string getNumero_vuelo() const;
    int getAsiento() const;
    string getDestino() const;
    string getOrigen() const;
    int getEquipaje_facturado() const;

    // Setters
    void setNombre(const string &nombre);
    void setNacionalidad(const string &nacionalidad);
    void setNumero_pasaporte(const string &numero_pasaporte);
    void setNumero_vuelo(const string &numero_vuelo);
    void setAsiento(int asiento);
    void setDestino(const string &destino);
    void setOrigen(const string &origen);
    void setEquipaje_facturado(int equipaje_facturado);

    // ToString 
    string ToString() const;

    ~Pasajero();
};

Pasajero::Pasajero(/* args */)
{
}

Pasajero::Pasajero(string nombre, string nacionalidad, 
    string numero_pasaporte,string numero_vuelo, int asiento, 
    string destino, string origen, int equipaje_facturado)
     : nombre(nombre), nacionalidad(nacionalidad), numero_pasaporte(numero_pasaporte), numero_vuelo(numero_vuelo), asiento(asiento), destino(destino), origen(origen), equipaje_facturado(equipaje_facturado) {}

//implementacion getters
string Pasajero::getNombre() const { return nombre; }
string Pasajero::getNacionalidad() const { return nacionalidad; }
string Pasajero::getNumero_pasaporte() const { return numero_pasaporte; }
string Pasajero::getNumero_vuelo() const { return numero_vuelo; }
int Pasajero::getAsiento() const { return asiento; }
string Pasajero::getDestino() const { return destino; }
string Pasajero::getOrigen() const { return origen; }
int Pasajero::getEquipaje_facturado() const { return equipaje_facturado; }

//implementacion setters
void Pasajero::setNombre(const string &nombre) { this->nombre = nombre; }
void Pasajero::setNacionalidad(const string &nacionalidad) { this->nacionalidad = nacionalidad; }
void Pasajero::setNumero_pasaporte(const string &numero_pasaporte) { this->numero_pasaporte = numero_pasaporte; }
void Pasajero::setNumero_vuelo(const string &numero_vuelo) { this->numero_vuelo = numero_vuelo; }
void Pasajero::setAsiento(int asiento) { this->asiento = asiento; }
void Pasajero::setDestino(const string &destino) { this->destino = destino; }
void Pasajero::setOrigen(const string &origen) { this->origen = origen; }
void Pasajero::setEquipaje_facturado(int equipaje_facturado) { this->equipaje_facturado = equipaje_facturado; }

string Pasajero::ToString() const {
    stringstream ss;
    ss << "Nombre: " << nombre << endl;
    ss << "Nacionalidad: " << nacionalidad << endl;
    ss << "Numero de Pasaporte: " << numero_pasaporte << endl;
    ss << "Numero de Vuelo: " << numero_vuelo << endl;
    ss << "Asiento: " << asiento << endl;
    ss << "Destino: " << destino << endl;
    ss << "Origen: " << origen << endl;
    ss << "Equipaje Facturado: " << equipaje_facturado << endl;
    return ss.str();
}

Pasajero::~Pasajero()
{
}

#endif