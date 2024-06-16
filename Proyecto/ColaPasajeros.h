
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
#include "NodoPasajeroS.h"

class ColaPasajeros
{
private:
    NodoPasajeroS *primero, *ultimo;
public:
    ColaPasajeros(/* args */);
    bool estaVacia();
    void insertarFinal(Pasajero dato);
    void eliminarInicio();
    void visualizarCola();
    void generarReporte(string titulo);
    Pasajero obtenerPrimerElemento();
    ~ColaPasajeros();
};


ColaPasajeros::ColaPasajeros(/* args */)
{
    primero = ultimo = nullptr;
}

bool ColaPasajeros::estaVacia(){
    return (primero==nullptr)&&(ultimo==nullptr);
}

void ColaPasajeros::insertarFinal(Pasajero dato){
    NodoPasajeroS *nuevo=new NodoPasajeroS(dato);
    if (ColaPasajeros::estaVacia())
    {
        primero=ultimo=nuevo;
    }else{
        ultimo->setSiguiente(nuevo);
        ultimo=nuevo;
    }
}

void ColaPasajeros::eliminarInicio(){
    if (ColaPasajeros::estaVacia())
    {
        cout << "La cola está vacía" << endl;
    }else{
        if (primero==ultimo)
        {
            delete primero;
            primero=ultimo=nullptr;
        }else{
            NodoPasajeroS *segundo=primero->getSiguiente();
            delete primero;
            primero=segundo;
        }
        
    }
}

void ColaPasajeros::visualizarCola(){
    if (ColaPasajeros::estaVacia())
    {
        cout << "La cola está vacía" << endl;
    }else{
        Pasajero nodoDato;
        NodoPasajeroS *actual = primero;
        while (actual != nullptr)
        {
            /* code */
            nodoDato = actual->getDato();
            cout << nodoDato.ToString() << endl;
            actual = actual->getSiguiente();
        }
    }
    
}

Pasajero ColaPasajeros::obtenerPrimerElemento() {
    if (ColaPasajeros::estaVacia()) {
        cout << "La cola está vacía" << endl;
        return Pasajero(); 
    } else {
        return primero->getDato();
    }
}

void ColaPasajeros::generarReporte(string titulo){
    string codigoDot="digraph Grafo1 {\nrankdir = \"RL\"\nlabel=\""+titulo+"\""+"\nnode[shape=rectangle]\n";
    codigoDot+="Head\n";//el primer nodo
    if (ColaPasajeros::estaVacia()){
        cout<<"La cola esta vacia\n"<<endl;
    }else{
        Pasajero nodoDato;
        NodoPasajeroS *actual=primero;

        while (actual != nullptr)
        {
            string pasaporte=actual->getDato().getNumero_pasaporte();
            string nombre=actual->getDato().getNombre();
            string equipaje=to_string(actual->getDato().getEquipaje_facturado());

            codigoDot+=pasaporte+"[label=\""+pasaporte+"\\n"+nombre+"\\nEquipaje: "+equipaje+"\"]\n";

            actual = actual->getSiguiente();
        }
        actual=primero;
        codigoDot+="Head->";//la primera arista
        while (actual != nullptr)
        {
            string pasaporte=actual->getDato().getNumero_pasaporte();

            codigoDot+=pasaporte+"->";
            actual = actual->getSiguiente();
            if (actual == nullptr)
            {   
                codigoDot+="Tail\n";
            }
        }
        codigoDot+="\n}";
        
        //Creacion del archivo
        ofstream archivo; //
        archivo.open(titulo+".dot", ios::out);
        archivo<<codigoDot;
        archivo.close();
        //renderizar el dot
        string comandoRenderizar="dot -Tsvg "+titulo+".dot -o "+titulo+".svg";
        const char* comandoRenderizar_cstr=comandoRenderizar.c_str();
        system(comandoRenderizar_cstr);
        //abrir el dot
        string open_command="start "+titulo+".svg";
        system(open_command.c_str());
    }

}

ColaPasajeros::~ColaPasajeros()
{
}
