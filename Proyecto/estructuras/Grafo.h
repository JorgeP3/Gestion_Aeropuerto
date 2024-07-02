#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
using namespace std;
#include "Vertice.h"

class Grafo
{
private:
    /* data */
    int numVertices; //número de vértices actuales en el grafo
    int maxVertices; //número máximo de vértices en el grafo
    Vertice* vertices; //arreglo de vértices
    int** matrizAdy; //matriz de adyacencia

    int minimoDistancia(int dist[], bool sptSet[]);

    ofstream archivo;
    string arco;
public:
    Grafo(/* args */);

    Grafo(int max);
    int getNumVertices(); //Obtiene el número de vértices
    void setNumVertices(int n); //Establecer el número de vértices

    void nuevoVertice(string nombre);
    int existeVertice(string nombre); //Comprueba si el nombre recibido se encuentra en la lista de vértices
    void nuevoArco(string nom1, string nom2, int distancia); //Agrega 1 a la matriz de adyacencia si los 2 vértices existen
    void imprimirMatriz();
    void generarReporte(string titulo);
    void encontrarRutaMasCorta(string ciudadOrigen, string ciudadDestino);
    int getMaxVertices();
    void setMaxvertices(int maxVertices);
    ~Grafo();
};

Grafo::Grafo(/* args */)
{
}

typedef int* int_m; //para la dimension de la matriz
Grafo::Grafo(int max)
{
    numVertices = 0; //número de vértices en el grafo, cuando se crea el grafo este aún no tiene nodos
    maxVertices = max; //Número máximo de vértices en el grafo
    vertices = new Vertice[max]; //arreglo de vértices
    matrizAdy = new int_m[max]; //arreglo de punteros
    for (int i = 0; i < max; i++)
    {
        matrizAdy[i] = new int[max]; //Completando la matriz de adyacencia
    }

    for (int i = 0; i < maxVertices; i++)
    {
        for (int j = 0; j < maxVertices; j++)
        {
            matrizAdy[i][j] = 0;
        } 
    }
    
    /**/
}


int Grafo::getNumVertices()
{
    return this->numVertices;
}

void Grafo::setNumVertices(int n)
{
    this->numVertices = n;
}

void Grafo::nuevoVertice(string nombre)
{
    bool existe = (existeVertice(nombre) >= 0);
    if (!existe) //Si no existe
    {
        Vertice nuevo = Vertice(nombre,numVertices);
        vertices[numVertices] = nuevo; //Se agrega el nuevo vértice a la lista
        numVertices++;
    }
}

int Grafo::existeVertice(string nombre)
{   //Busca el vértice en el arreglo vértices, retorna -1 si no lo encuentra
    int i = 0;
    bool encontrado = false;
    while (i < numVertices && !encontrado)
    {   //El ciclo se repite mientras no se haya iterado una cantidad mayor o igual al número de toal de vertices existentes
        //Y mientras no se haya encontrado un vértice con el mismo nombre al que se desea agregar
        encontrado = vertices[i].esIgual(nombre); //Falso mientras no se haya encontrado un vértice con el mismo nombre
        if (!encontrado)
        {
            i++;
        }
    }
    //Si 'i' es menor al número total de vértices, quiere decir que lo encontró en alguna de todas las iteraciones
    return (i < numVertices) ? i : -1;
}

void Grafo::nuevoArco(string nom1, string nom2,int distancia)
{   //Recibe el nombre de los 2 vértices que forman el arco y los busca en el arreglo de vértices
    //Si existen agrego 1 a la matriz de adyacencia
    int vertice1, vertice2;
    vertice1 = existeVertice(nom1);//si existe regresa el indice
    vertice2 = existeVertice(nom2);//si existe regresa el indice
    if (vertice1 >= 0 && vertice2 >= 0)
    {
        matrizAdy[vertice1][vertice2] = distancia;  
    }
    else
    {
        cout << "Error, uno de los vértices no existe\n";
    }
}

void Grafo::imprimirMatriz()
{
    for (int i = 0; i < maxVertices; i++)
    {
        for (int j = 0; j < maxVertices; j++)
        {
            cout << " " << matrizAdy[i][j] << " ";
        }  
        cout << endl;
    }
}

void Grafo::generarReporte(string titulo)
{
    if (getNumVertices() == 0) {//Grafo vacío
        cout << "el grafo esta vacio";
    } 
    else{
        string codigoDot="digraph Grafo1 {\nrankdir = \"TB\"\nlabel=\""+titulo+"\"\n";
        codigoDot+="labelloc=\"t\"\n";
        codigoDot+="node[]\n";//atributos del los nodos
        codigoDot+="edge[]\n"; // atributos de las aristas

        for (int i = 0; i < maxVertices; i++)
        {
            for (int j = 0; j < maxVertices; j++)
            {
                if (matrizAdy[i][j] > 0)
                {
                    /* code */
                    codigoDot+= vertices[i].getNombre() + " -> " + vertices[j].getNombre() +"[label=\""+to_string(matrizAdy[i][j])+"\"]\n";
                    
                }
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

int Grafo::minimoDistancia(int dist[], bool sptSet[])
{
    int min = INT_MAX, minIndex;
    for (int v = 0; v < numVertices; v++)
    {
        if (!sptSet[v] && dist[v] <= min)
        {
            min = dist[v], minIndex = v;
        }
    }
    return minIndex;
}

void Grafo::encontrarRutaMasCorta(string ciudadOrigen, string ciudadDestino)
{
    int src = existeVertice(ciudadOrigen);
    int dest = existeVertice(ciudadDestino);

    if (src == -1 || dest == -1)
    {
        cout << "Una de las ciudades no existe en el grafo." << endl;
        return;
    }

    int dist[numVertices];
    bool sptSet[numVertices];
    int parent[numVertices];

    for (int i = 0; i < numVertices; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < numVertices - 1; count++)
    {
        int u = minimoDistancia(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < numVertices; v++)
        {
            if (!sptSet[v] && matrizAdy[u][v] && dist[u] != INT_MAX && dist[u] + matrizAdy[u][v] < dist[v])
            {
                dist[v] = dist[u] + matrizAdy[u][v];
                parent[v] = u;
            }
        }
    }

    vector<string> path;
    for (int v = dest; v != -1; v = parent[v])
    {
        path.push_back(vertices[v].getNombre());
    }

    cout << "Ruta mas corta de " << ciudadOrigen << " a " << ciudadDestino << ": ";
    for (int i = path.size() - 1; i >= 0; i--)
    {
        cout << path[i];
        if (i != 0) cout << " -> ";
    }
    cout << endl;
}


Grafo::~Grafo()
{
    delete[] vertices;
    for (int i = 0; i < maxVertices; i++)
    {
        delete[] matrizAdy[i];
    }
    delete[] matrizAdy;
}