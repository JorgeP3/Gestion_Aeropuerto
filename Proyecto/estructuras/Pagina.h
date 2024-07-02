#include <iostream>
#include <fstream>
#include <string> // Incluir la biblioteca de strings
using namespace std;

typedef string tipoClave; // Cambiar int a string

class Pagina;
typedef Pagina* PPagina;

class Pagina {
protected:
    tipoClave* claves; // puntero array de claves variables
    PPagina* ramas;    // puntero array de punteros a páginas variable
    int cuenta;        // número de claves que almacena la página

private:
    int m; // máximo número de claves que puede almacenar la página

public:
    // crea una página vacía de un cierto orden dado
    Pagina(int orden);
    bool nodoLLeno();
    bool nodoSemiVacio();
    tipoClave Oclave(int i);
    void Pclave(int i, tipoClave clave);
    Pagina* Orama(int i);
    void Prama(int i, Pagina* p);
    int Ocuenta();
    void Pcuenta(int valor);
    ~Pagina();
};

Pagina::Pagina(int orden) {
    m = orden;
    claves = new tipoClave[orden];
    ramas = new PPagina[orden + 1]; // Cambiado a orden + 1
    for (int k = 0; k <= orden; k++)
        ramas[k] = NULL;
    cuenta = 0; // Inicializa cuenta a 0
}

// decide si un nodo está lleno
bool Pagina::nodoLLeno() {
    return (cuenta == m - 1);
}

// decide si una página tiene menos de la mitad de claves
bool Pagina::nodoSemiVacio() {
    return (cuenta < m / 2);
}

// obtener la clave que ocupa la posición i en el array de claves      
tipoClave Pagina::Oclave(int i) {
    return claves[i - 1]; // Índice ajustado para que sea compatible con 1-based
}

// cambiar la clave que ocupa la posición i en el array de claves
void Pagina::Pclave(int i, tipoClave clave) {
    claves[i - 1] = clave; // Índice ajustado para que sea compatible con 1-based
}

// obtener la rama que ocupa la posición i en el array de ramas
Pagina* Pagina::Orama(int i) {
    return ramas[i]; // Índice ajustado para que sea compatible con 1-based
}

// cambiar la rama que ocupa la posición i en el array de ramas
void Pagina::Prama(int i, Pagina* p) {
    ramas[i] = p; // Índice ajustado para que sea compatible con 1-based
}

// obtener el valor de cuenta
int Pagina::Ocuenta() {
    return cuenta;
}

// cambiar el valor de cuenta
void Pagina::Pcuenta(int valor) {
    cuenta = valor;
}

Pagina::~Pagina() {
    delete[] claves;
    delete[] ramas;
}
