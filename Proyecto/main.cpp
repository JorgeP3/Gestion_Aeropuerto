//clases
#include "Avion.h"
#include "Pasajero.h"
//listas
#include "CircularDoble.h"
#include "ColaPasajeros.h"
#include "PilaEquipaje.h"
#include "ListaDoble.h"
//librerias
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;
#include "json.hpp"
using json = nlohmann::json;

CircularDoble AvionesDisponibles;
CircularDoble AvionesMantenimiento;
ColaPasajeros colaPasajeros;
PilaEquipaje pilaDeEquipaje;
ListaDoble listaDoblePasajeros;

void cargarAviones(string nombreArchivo){

    string path="C:\\Users\\lmpgp\\OneDrive\\Escritorio\\"+nombreArchivo;

    ifstream archivo(path);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    json j;
    archivo >> j;

    for (const auto& item : j) {

        string estado= item["estado"].get<string>();
        if (estado=="Disponible"||estado=="disponible"){
            string vuelo=item["vuelo"].get<std::string>();
            string numero_de_registro=item["numero_de_registro"].get<std::string>();
            string modelo=item["modelo"].get<std::string>();
            string fabricante=item["fabricante"].get<std::string>();
            int anio_fabricacion= item["ano_fabricacion"].get<int>();
            int capacidad=item["capacidad"].get<int>();
            int peso_max_despegue=item["peso_max_despegue"].get<int>();
            string aerolinea=item["aerolinea"].get<std::string>();
            string estado=item["estado"].get<std::string>();

            Avion avionNuevo(vuelo,numero_de_registro,modelo,fabricante,anio_fabricacion,capacidad,peso_max_despegue,aerolinea,estado);
            AvionesDisponibles.insertarFinal(avionNuevo);
            cout << "Avion disponible cargado correctamente" << endl;

        }else if(estado=="Mantenimiento"||estado=="mantenimiento"){
            string vuelo=item["vuelo"].get<std::string>();
            string numero_de_registro=item["numero_de_registro"].get<std::string>();
            string modelo=item["modelo"].get<std::string>();
            string fabricante=item["fabricante"].get<std::string>();
            int anio_fabricacion= item["ano_fabricacion"].get<int>();
            int capacidad=item["capacidad"].get<int>();
            int peso_max_despegue=item["peso_max_despegue"].get<int>();
            string aerolinea=item["aerolinea"].get<std::string>();
            string estado=item["estado"].get<std::string>();

            Avion avionNuevo(vuelo,numero_de_registro,modelo,fabricante,anio_fabricacion,capacidad,peso_max_despegue,aerolinea,estado);
            AvionesMantenimiento.insertarFinal(avionNuevo);

            cout << "Avion en mantenimiento cargado correctamente" << endl;

        }else{
            cout << "No se pudo cargar el avion" << endl;
        }

    }
}

std::vector<std::string> split(const std::string& str, const std::string& delimiters) {
    std::vector<std::string> tokens;
    std::string token;
    size_t start = 0;
    size_t end = 0;

    while ((end = str.find_first_of(delimiters, start)) != std::string::npos) {
        if (end != start) {
            tokens.push_back(str.substr(start, end - start));
        }
        start = end + 1;
    }

    if (start != str.length()) {
        tokens.push_back(str.substr(start));
    }

    return tokens;
}

void cargaPasajeros(string nombreArchivo) {
    string path="C:\\Users\\lmpgp\\OneDrive\\Escritorio\\"+nombreArchivo;

    ifstream archivo(path);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    json j;
    archivo >> j;

    for (const auto& item : j) {
        string nombre=item["nombre"].get<string>();
        string nacionalidad=item["nacionalidad"].get<string>();
        string numero_pasaporte=item["numero_de_pasaporte"].get<string>();
        string numero_vuelo=item["vuelo"].get<string>();
        int asiento=item["asiento"].get<int>();
        string destino=item["destino"].get<string>();
        string origen=item["origen"].get<string>();
        int equipaje_facturado=item["equipaje_facturado"].get<int>();

        Pasajero pasajeroNuevo(nombre, nacionalidad,numero_pasaporte,numero_vuelo,asiento,destino,origen,equipaje_facturado);
        colaPasajeros.insertarFinal(pasajeroNuevo);
        cout << "Pasajero cargado correctamente" << endl;
    }  
}

void cargaMovimientos(string nombreArchivo) {
    string path="C:\\Users\\lmpgp\\OneDrive\\Escritorio\\"+nombreArchivo;

    ifstream archivo(path);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) {
            continue; // Saltar líneas vacías
        }
        vector<std::string> palabras =split(linea,",;");
        /*PROCESADO DEL COMANDO EQUIPAJES*/
        if (palabras[0]=="IngresoEquipajes" || palabras[0]=="ingresoequipajes")
        {
            Pasajero pasajero=colaPasajeros.obtenerPrimerElemento();//obtego al pasajero que voy a eliminar de la cola
            colaPasajeros.eliminarInicio();//elimino al pasajero de la cola de pasajeros

            if (pasajero.getNumero_pasaporte()!=""){//si devuelve un objeto vacio
                if (pasajero.getEquipaje_facturado()>0)
                {
                    pilaDeEquipaje.insertarFinal(pasajero);
                    cout << "se agrego equipaje a la pila" << endl;
                }
                listaDoblePasajeros.insertarFinal(pasajero);//agrego el pasajero a la lista doble
                cout << "se agrego un pasajero a la lista doble" << endl;
            }
            
        /*PROCESADO DEL MANTENIMIENTO DE AVIONES*/
        }else if(palabras[0]=="MantenimientoAviones"||palabras[0]=="mantenimientoaviones"){
            if (palabras[1]=="Ingreso" || palabras[1]=="ingreso")
            {
                string numero_registro=palabras[2];
                Avion avionAcambiar=AvionesDisponibles.buscarPorNumeroDeRegistro(numero_registro);
                if (avionAcambiar.getNumeroDeRegistro()!="")//si devuelve un avion
                {
                    AvionesDisponibles.eliminarPorNumeroDeRegistro(numero_registro);//lo elimino
                    avionAcambiar.setEstado("Mantenimiento");//seteo su estado
                    AvionesMantenimiento.insertarFinal(avionAcambiar);//lo agrego a la otra lista
                    cout << "se ingreso un avion a la lista de mantenimiento y se elimino de la lista de disponibles " << endl;
                }
                

            }else if(palabras[1]=="Salida" || palabras[1]=="salida") {
                string numero_registro=palabras[2];
                Avion avionAcambiar=AvionesMantenimiento.buscarPorNumeroDeRegistro(numero_registro);
                if (avionAcambiar.getNumeroDeRegistro()!="")//si devuelve un avion
                {
                    AvionesMantenimiento.eliminarPorNumeroDeRegistro(numero_registro);//lo elimino
                    avionAcambiar.setEstado("Disponible");//seteo su estado
                    AvionesDisponibles.insertarFinal(avionAcambiar);//lo agrego a la otra lista
                    cout << "se elimino un avion de la lista de mantenimiento y se ingreso a la lista de disponibles" << endl;
                }
            }else{
                cout << "no se reconocio el comando" << endl;
            }
        }else{
            cout << "no se reconocio el comando" << endl;
        }
    }
    archivo.close();

}

void consultarPasajeros() {
    string numero_pasaporte="";
    cout << "Ingrese un numero de pasaporte a consultar: ";
    cin >> numero_pasaporte;
    cout << "------indormacion del pasajero---------"<< endl;
    listaDoblePasajeros.buscarPorNumeroPasaporte(numero_pasaporte);
}

void visualizarReportes() {
    cout << "======LISTA DE AVIONES DISPONIBLES======" << endl;
    AvionesDisponibles.visualizarLista();
    cout << "======LISTA DE AVIONES EN MANTENIMIENTO======" << endl;
    AvionesMantenimiento.visualizarLista();
    cout << "======COLA DE PASAJEROS======" << endl;
    colaPasajeros.visualizarCola();
    cout << "======PILA EQUIPAJE======" << endl;
    pilaDeEquipaje.visualizarPila();
    cout << "======LISTA DOBLE DE PASAJEROS======" << endl;
    listaDoblePasajeros.visualizarLista();

    cout << "======REPORTE DOT.======" << endl;
    AvionesDisponibles.generarReporte("Aviones_Disponibles");
    AvionesMantenimiento.generarReporte("Aviones_Mantenimiento");
    colaPasajeros.generarReporte("Cola_Pasajeros");
    pilaDeEquipaje.generarReporte("Pila_equipaje");
    //Ordenar lista y mostrar
    listaDoblePasajeros.ordenarLista();
    listaDoblePasajeros.generarReporte("Lista_Doble_pasajeros");
    
}

void menuPrincipal(){

    int opcion =0;

    while (opcion!=6){
        cout << "=========Menu principal=======" << endl;
        cout << "1. Carga de aviones" << endl;
        cout << "2. Carga de pasajeros" << endl;
        cout << "3. Carga de movimientos" << endl;
        cout << "4. Consultar pasajeros" << endl;
        cout << "5. Visualizar reportes" << endl;
        cout << "6. Salir" << endl;
        cout << "==============================" << endl;

        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cout << endl;

        switch (opcion){
            case 1:
                {
                string nombreArchivo="";
                cout << "Ingrese el nombre del archivo de carga de Aviones: ";
                cin >> nombreArchivo;
                
                cargarAviones(nombreArchivo);
                }
                break;
            case 2:
                {
                string nombreArchivo="";
                cout << "Ingrese el nombre del archivo de carga de Pasajeros: ";
                cin >> nombreArchivo;
                cargaPasajeros(nombreArchivo);
                }
                
                break;
            case 3:
                {
                string nombreArchivo="";
                cout << "Ingrese el nombre del archivo de carga de Movimientos: ";
                cin >> nombreArchivo;
                cargaMovimientos(nombreArchivo);
                }
                break;
            case 4:
                consultarPasajeros();
                break;
            case 5:
                visualizarReportes();
                break;
            case 6:
                cout << "Que tenga un buen dia" << endl;
                break;

            default:
                cout<< "Opcion no valida"<<endl;
                break;
        }

    }
}

int main(){
    menuPrincipal();
    return 0;
}

