#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
#include "NodoPasajeroS.h"

class PilaEquipaje
{
private:
    NodoPasajeroS *primero, *ultimo;
public:
    PilaEquipaje(/* args */);
    bool estaVacia();
    void insertarFinal(Pasajero dato);
    void eliminarFinal();
    void visualizarPila();
    void generarReporte(string titulo);
    ~PilaEquipaje();
};


PilaEquipaje::PilaEquipaje(/* args */)
{
    primero = ultimo = nullptr;
}

bool PilaEquipaje::estaVacia(){
    return (primero==nullptr)&&(ultimo==nullptr);
}

void PilaEquipaje::insertarFinal(Pasajero dato){
    NodoPasajeroS *nuevo=new NodoPasajeroS(dato);
    if (PilaEquipaje::estaVacia())
    {
        primero=ultimo=nuevo;
    }else{
        ultimo->setSiguiente(nuevo);
        ultimo=nuevo;
    }
}

void PilaEquipaje::eliminarFinal(){
    if (PilaEquipaje::estaVacia())
    {
        cout << "La pila está vacía" << endl;
    }else{
        NodoPasajeroS *temporal=primero;
        if (primero==ultimo)
        {
            delete primero;
            primero=ultimo=nullptr;
        }else{
            while (temporal!=nullptr)
            {
                if (temporal->getSiguiente()==ultimo)//Si el siguiente de temporal es el último, entonces temporal es el antepenultimo
                {
                    delete ultimo;
                    temporal->setSiguiente(nullptr);
                    ultimo=temporal;
                }
                temporal=temporal->getSiguiente();
            }
            
        }
        
    }
}

void PilaEquipaje::visualizarPila(){
    if (PilaEquipaje::estaVacia())
    {
        cout << "La pila está vacía" << endl;
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



void PilaEquipaje::generarReporte(string titulo){
    string codigoDot="digraph Grafo1 {\nrankdir = \"BT\"\nlabel=\""+titulo+"\""+"\nnode[shape=rectangle]\n";
    codigoDot+="Head\n";//el primer nodo
    if (PilaEquipaje::estaVacia()){
        cout<<"La pila esta vacia\n"<<endl;
    }else{
        Pasajero nodoDato;
        NodoPasajeroS *actual=primero;
        //NODOS
        while (actual != nullptr)
        {
            string pasaporte=actual->getDato().getNumero_pasaporte();
            string nombre=actual->getDato().getNombre();
            string equipaje=to_string(actual->getDato().getEquipaje_facturado());

            codigoDot+=pasaporte+"[label=\""+pasaporte+"\\n"+nombre+"\\nEquipaje: "+equipaje+"\"]\n";

            actual = actual->getSiguiente();
        }
        actual=primero;
        //ARISTAS
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

PilaEquipaje::~PilaEquipaje()
{
}