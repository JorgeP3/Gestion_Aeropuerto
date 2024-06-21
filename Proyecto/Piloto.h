#ifndef PILOTO_H
#define PILOTO_H

#include <string>
#include <iostream>
using namespace std;

class Piloto
{
private:
    string nombre;
    string nacionalidad;
    string numero_de_id;
    string vuelo;
    int horas_de_vuelo;
    string tipo_de_licencia;
public:
    //Construtores
    Piloto(/* args */);
    Piloto(string nombre, string nacionalidad, string numero_de_id,
    string vuelo, int horas_de_vuelo, string tipo_de_licencia);

    //Getters
    string getNombre() const;
    string getNacionalidad() const;
    string getNumero_de_id() const;
    string getVuelo() const;
    int getHoras_de_vuelo() const;
    string getTipo_de_licencia() const;

    //Setters
    void setNombre(string nombre);
    void setNacionalidad(string nacionalidad);
    void setNumero_de_id(string numero_de_id);
    void setVuelo(string vuelo);
    void setHorasDeVuelo(int horas_de_vuelo);
    void setTipoDeLicencia(string tipo_de_licencia);

    //ToString
    string ToString() const;
    
    //destructor
    ~Piloto();
};

Piloto::Piloto(){

}

Piloto::Piloto(string nombre, string nacionalidad, string numero_de_id,
    string vuelo, int horas_de_vuelo, string tipo_de_licencia)
{
    this->nombre=nombre;
    this->nacionalidad=nacionalidad;
    this->numero_de_id=numero_de_id;
    this->vuelo=vuelo;
    this->horas_de_vuelo=horas_de_vuelo;
    this->tipo_de_licencia=tipo_de_licencia;
}

//Getters
string Piloto::getNombre() const {
    return nombre;
}

string Piloto::getNacionalidad() const {
    return nacionalidad;
}

string Piloto::getNumero_de_id() const {
    return numero_de_id;
}

string Piloto::getVuelo() const {
    return vuelo;
}

int Piloto::getHoras_de_vuelo() const {
    return horas_de_vuelo;
}

string Piloto::getTipo_de_licencia() const {
    return tipo_de_licencia;
}

//Setters
void Piloto::setNombre(string nombre){
    this->nombre=nombre;
}

void Piloto::setNacionalidad(string nacionalidad){
    this->nacionalidad=nacionalidad;
}

void Piloto::setNumero_de_id(string numero_de_id){
    this->numero_de_id=numero_de_id;
}

void Piloto::setVuelo(string vuelo){
    this->vuelo=vuelo;
}

void Piloto::setHorasDeVuelo(int horas_de_vuelo){
    this->horas_de_vuelo=horas_de_vuelo;
}

void Piloto::setTipoDeLicencia(string tipo_de_licencia){
    this->tipo_de_licencia=tipo_de_licencia;
}

string Piloto::ToString() const{
    return "Nombre: "+nombre+"\n"+
            "Nacionalidad: "+nacionalidad+"\n"
            "Numero de ID: "+numero_de_id+"\n"
            "Vuelo: "+vuelo+"\n"
            "Horas de vuelo: "+to_string(horas_de_vuelo)+"\n"
            "Tipo de licencia: "+tipo_de_licencia+"\n";
}
    
Piloto::~Piloto()
{
}


#endif 