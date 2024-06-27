#include <iostream>
using namespace std;
#include "ListaSimple.h"

class TablaHash
{
private:
    /* data */
    int tamTabla;
    int numElementos;
    ListaSimple *tabla;//arreglo de listas simples
public:
    TablaHash(/* args */);
    int Clave(string valor);
    void Insertar(Piloto dato);
    void imprimirTabla();
    void generarReporte();
    ~TablaHash();
};

TablaHash::TablaHash(/* args */)
{
    tamTabla = 18;//si es 10 llega de 0 a 9 si es 18 llega de 0 a 17
    tabla = new ListaSimple[18];
    for (int i = 0; i < tamTabla; i++)
    {
        //cout << tabla->estaVacia() << endl;
    }
    numElementos = 0;    
}

int TablaHash::Clave(string valorS)
{
    int valorAscii=static_cast<int>(valorS[0]);
    cout << "ASSI LETRA " << valorAscii << endl;
    int tamanoCad=valorS.size();
    int suma=0;

    for (int i = 1; i < tamanoCad; i++)
    {
        suma+=(valorS[i])-'0';
    }
    cout << "SUMA " << suma << endl;
    
    int valor=valorAscii+suma;
    int i;
    i = (int)(valor % tamTabla);
    cout << "Llave asignada: " << i << endl;
    return i;
}

void TablaHash::Insertar(Piloto dato)
{
    string valor=dato.getNumero_de_id();
    int indice = Clave(valor);
    tabla[indice].insertarFinal(dato);
}

void TablaHash::imprimirTabla()
{
    for (int i = 0; i < tamTabla; i++)
    {
        cout << "[" << i << "] -> ";
        tabla[i].visualizarLista();
    }
    
}

void TablaHash::generarReporte(){

}





TablaHash::~TablaHash()
{
}