#include <iostream>
#include <fstream> 
#include <cstdlib> 
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
    void generarReporte(string titulo);
    void eliminarPiloto(string numero_id);
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
    int tamanoCad=valorS.size();
    int suma=0;

    for (int i = 1; i < tamanoCad; i++)
    {
        suma+=(valorS[i])-'0';
    }
    int valor=valorAscii+suma;
    int i;
    i = (int)(valor % tamTabla);
    
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
        cout << "[" << i << "]";
        if (!tabla[i].estaVacia()){
            cout << "->";
            tabla[i].visualizarLista();
        }else{
            cout << "\n";
        }
    }
}

void TablaHash::generarReporte(string titulo){
    string codigoDot="digraph Grafo1 {\nrankdir = \"LR\"\nlabel=\""+titulo+"\"\n";
    codigoDot+="labelloc=\"t\"\n";
    codigoDot+="node[shape=plaintext]\n";//atributos del los nodos
    codigoDot+="edge[]\n"; // atributos de las aristas

    //ARREGLO
    codigoDot+="hash_table[label=<";
    codigoDot+="<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\">";
    for (int i = 0; i < tamTabla; i++)
    {
        codigoDot+= "<TR><TD PORT=\"index"+to_string(i)+"\" WIDTH=\"30\" HEIGHT=\"55\">"+to_string(i)+"</TD></TR>\n";
        
    }
    codigoDot+="</TABLE>\n>];\n\n";

    //Listas
    codigoDot+="node [shape=rectangle]\n\n";
    for (int i = 0; i < tamTabla; i++)
    {
        if (!tabla[i].estaVacia()){
            codigoDot+="hash_table:index"+to_string(i)+"->"+tabla[i].txt_lista();  
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

void TablaHash::eliminarPiloto(string numero_id){

    int indice = Clave(numero_id);
    tabla[indice].eliminarPorId(numero_id);

}




TablaHash::~TablaHash()
{
}