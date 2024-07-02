#include <iostream>
#include <fstream>
#include "Pagina.h"
#include <sstream>
#include <vector>
#include <string> // Incluir la biblioteca de strings
using namespace std;

class ArbolB {
protected:
    int orden;
    Pagina* raiz;

public:
    ArbolB() {
        orden = 0;
        raiz = NULL;
    };
    ArbolB(int m) {
        orden = m;
        raiz = NULL;
    }
    bool arbolBvacio() {
        return raiz == NULL;
    }
    Pagina* Oraiz() {
        return raiz;
    }
    void Praiz(Pagina* r) {
        raiz = r;
    }
    int Oorden() {
        return orden;
    }
    void Porden(int ord) {
        orden = ord;
    }
    void crear() {
        orden = 0;
        raiz = NULL;
    }
    Pagina* buscar(tipoClave cl, int& n);
    Pagina* buscar(Pagina* actual, tipoClave cl, int& n);
    void insertar(tipoClave cl);
    Pagina* insertar(Pagina* raiz, tipoClave cl);
    bool empujar(Pagina* actual, tipoClave cl, tipoClave& mediana, Pagina*& nuevo);
    void meterPagina(Pagina* actual, tipoClave cl, Pagina* ramaDr, int k);
    void dividirNodo(Pagina* actual, tipoClave& mediana, Pagina*& nuevo, int pos);
    void escribir();
    void escribir(Pagina* r, int h);
    void eliminar(tipoClave cl);
    void generarDot(string nombreArchivo);
    void generarDotRecursivo(ofstream& archivoDot, Pagina* nodo, int& contador);

    bool buscarNodo(Pagina* actual, tipoClave cl, int& k);
};
void ArbolB::generarDot(string nombreArchivo) {
    ofstream archivoDot(nombreArchivo+".dot");
    if (archivoDot.is_open()) {
        archivoDot << "digraph ArbolB {\n";
        archivoDot << "node [shape=record];\n";
        int contador = 0;
        generarDotRecursivo(archivoDot, raiz, contador);
        archivoDot << "}\n";
        archivoDot.close();
        
        string comandoRenderizar="dot -Tsvg "+nombreArchivo+".dot -o "+nombreArchivo+".svg";
        const char* comandoRenderizar_cstr=comandoRenderizar.c_str();
        system(comandoRenderizar_cstr);
        //abrir el dot
        string open_command="start "+nombreArchivo+".svg";
        system(open_command.c_str());
    } else {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
    }
}

void ArbolB::generarDotRecursivo(ofstream& archivoDot, Pagina* nodo, int& contador) {
    if (nodo != NULL) {
        int nodoActual = contador++;
        archivoDot << "n" << nodoActual << " [label=\"";
        for (int i = 1; i <= nodo->Ocuenta(); i++) {
            archivoDot << "<f" << i << "> " << nodo->Oclave(i);
            if (i < nodo->Ocuenta()) {
                archivoDot << "|";
            }
        }
        archivoDot << "\"];\n";

        for (int i = 0; i <= nodo->Ocuenta(); i++) {
            if (nodo->Orama(i) != NULL) {
                int nodoHijo = contador;
                generarDotRecursivo(archivoDot, nodo->Orama(i), contador);
                archivoDot << "n" << nodoActual << ":f" << (i + 1) << " -> n" << nodoHijo << ";\n";
            }
        }
    }
}
// El método devuelve true si encuentra la clave en el árbol
bool ArbolB::buscarNodo(Pagina* actual, tipoClave cl, int& k) {
    int index;
    bool encontrado;
    if (cl < actual->Oclave(1)) {
        encontrado = false;
        index = 0;
    } else { // orden descendente
        index = actual->Ocuenta();
        while (cl < actual->Oclave(index) && (index > 1))
            index--;
        encontrado = cl == actual->Oclave(index);
    }
    k = index;
    return encontrado;
}

Pagina* ArbolB::buscar(tipoClave cl, int& n) {
    return buscar(raiz, cl, n);
}

Pagina* ArbolB::buscar(Pagina* actual, tipoClave cl, int& n) {
    if (actual == NULL) {
        return NULL;
    } else {
        bool esta = buscarNodo(actual, cl, n);
        if (esta) // la clave se encuentra en el nodo actual         
            return actual;
        else
            return buscar(actual->Orama(n), cl, n);  // llamada recursiva    
    }
}

// método público
void ArbolB::insertar(tipoClave cl) {
    raiz = insertar(raiz, cl);
}

// método privado
Pagina* ArbolB::insertar(Pagina* raiz, tipoClave cl) {
    bool subeArriba;
    tipoClave mediana;
    Pagina* nd;
    subeArriba = empujar(raiz, cl, mediana, nd);
    if (subeArriba) {
        // El árbol crece en altura por la raíz.
        // sube una nueva clave mediana y un nuevo hijo derecho nd       
        // en la implementación se mantiene que las claves que son
        // menores que mediana se encuentran en raiz y las mayores en nd        
        Pagina* p;
        p = new Pagina(orden); // nuevo nodo
        p->Pcuenta(1); // tiene una sola clave
        p->Pclave(1, mediana);
        p->Prama(0, raiz); // claves menores
        p->Prama(1, nd); // claves mayores
        raiz = p;
    }
    return raiz;
}

bool ArbolB::empujar(Pagina* actual, tipoClave cl, tipoClave& mediana, Pagina*& nuevo) {
    int k;
    bool subeArriba = false;
    if (actual == NULL) {
        // envía hacia arriba la clave cl y su rama derecha NULL
        // para que se inserte en la Página padre
        subeArriba = true;
        mediana = cl;
        nuevo = NULL;
        // el dato Página de nuevo está a NULL
    } else {
        bool esta;
        esta = buscarNodo(actual, cl, k);
        if (esta)
            throw "\nClave duplicada";
        // siempre se ejecuta
        subeArriba = empujar(actual->Orama(k), cl, mediana, nuevo);
        // devuelve control; vuelve por el camino de búsqueda       
        if (subeArriba) {
            if (actual->nodoLLeno()) // hay que dividir la página             
                dividirNodo(actual, mediana, nuevo, k);
            else { // cabe en la página, se inserta la mediana y su rama derecha         
                subeArriba = false;
                meterPagina(actual, mediana, nuevo, k);
            }
        }
    }
    return subeArriba;
}

void ArbolB::meterPagina(Pagina* actual, tipoClave cl, Pagina* ramaDr, int k) {
    // desplaza a la derecha los elementos para hacer un hueco     
    for (int i = actual->Ocuenta(); i >= k + 1; i--) {
        actual->Pclave(i + 1, actual->Oclave(i));
        actual->Prama(i + 1, actual->Orama(i));
    }
    // pone la clave y la rama derecha en la posición k+1     
    actual->Pclave(k + 1, cl);
    actual->Prama(k + 1, ramaDr);
    // incrementa el contador de claves almacenadas     
    actual->Pcuenta(actual->Ocuenta() + 1);
}

void ArbolB::dividirNodo(Pagina* actual, tipoClave& mediana, Pagina*& nuevo, int pos) {
    int i, posMdna, k;
    Pagina* nuevaPag;
    k = pos;
    // posición de clave mediana
    posMdna = (k <= orden / 2) ? orden / 2 : orden / 2 + 1;
    nuevaPag = new Pagina(orden);
    for (i = posMdna + 1; i <= actual->Ocuenta(); i++) {
        // desplazada la mitad derecha a la nueva Página, la clave mediana se queda en Página actual
        nuevaPag->Pclave(i - posMdna, actual->Oclave(i));
        nuevaPag->Prama(i - posMdna, actual->Orama(i));
    }
    nuevaPag->Pcuenta(actual->Ocuenta() - posMdna); // claves de nueva Página    
    actual->Pcuenta(posMdna);  // claves en Página origen
    // inserta la clave y rama en la Página que le corresponde     
    if (k <= orden / 2)
        meterPagina(actual, mediana, nuevo, pos); // en Página origen     
    else {
        pos = k - posMdna;
        meterPagina(nuevaPag, mediana, nuevo, pos); // en Página nueva     
    }
    // extrae clave mediana de la Página origen
    mediana = actual->Oclave(actual->Ocuenta());
    // Rama0 del nuevo nodo es la rama de la mediana     
    nuevaPag->Prama(0, actual->Orama(actual->Ocuenta()));
    actual->Pcuenta(actual->Ocuenta() - 1); // se quita la mediana     
    nuevo = nuevaPag; // devuelve la nueva Página
}

void ArbolB::escribir() {
    escribir(raiz, 1);
}

void ArbolB::escribir(Pagina* r, int h) {
    int i;
    if (r != NULL) {
        escribir(r->Orama(0), h + 5);
        for (i = 1; i <= r->Ocuenta() / 2; i++) { // llamadas recursivas a la mitad de los subárboles
            escribir(r->Orama(i), h + 5);
            cout << endl;
        }
        // visualización de las claves de la página apuntada por r        
        for (i = 1; i <= r->Ocuenta(); i++) {
            for (int j = 0; j <= h; j++)
                cout << " ";
            cout << r->Oclave(i) << endl;
        }
        // llamadas recursivas a la otra mitad de los subárboles        
        for (i = r->Ocuenta() / 2 + 1; i <= r->Ocuenta(); i++)
            escribir(r->Orama(i), h + 5);
        cout << endl;
    }
}




/*
void ArbolB::generarDot(string nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }
    
    archivo << "digraph ArbolB {" << endl;
    int contador = 0;
    generarDotRecursivo(archivo, raiz, contador);
    archivo << "}" << endl;
    
    archivo.close();
    cout << "Archivo .dot generado correctamente: " << nombreArchivo << endl;
}

void ArbolB::generarDotRecursivo(ofstream& archivoDot, Pagina* nodo, int& contador) {
    if (nodo != NULL) {
        // Generar nodos y relaciones para cada clave en la página
        stringstream nodoSS;
        for (int i = 1; i <= nodo->Ocuenta(); ++i) {
            nodoSS.str(""); // Limpiar el stringstream
            nodoSS << "N" << contador << "_" << nodo->Oclave(i);
            archivoDot << nodoSS.str() << " [label=\"" << nodo->Oclave(i) << "\"];" << endl;
            contador++;
        }
        
        // Generar relaciones entre los nodos
        for (int i = 0; i <= nodo->Ocuenta(); ++i) {
            if (nodo->Orama(i) != NULL) {
                archivoDot << "N" << contador - (nodo->Ocuenta() + 1) + i << " -> ";
                generarDotRecursivo(archivoDot, nodo->Orama(i), contador);
            }
        }
    }
}*/
