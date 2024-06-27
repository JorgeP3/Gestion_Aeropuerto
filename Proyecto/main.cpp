//clases
#include "Avion.h"
#include "Piloto.h"
//Estructuras
#include "CircularDoble.h"
#include "ArbolBB.h"
#include "Matriz.h"
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


CircularDoble AvionesMantenimiento;
ArbolBB arbolBBpilotos;
Matriz matrizPilotos;

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
        //CARGA DE AVIONES DISPONIBLES
        if (estado=="Disponible"||estado=="disponible"){
            /*
            string vuelo=item["vuelo"].get<std::string>();
            string numero_de_registro=item["numero_de_registro"].get<std::string>();
            string modelo=item["modelo"].get<std::string>();
            string fabricante=item["fabricante"].get<std::string>();
            int anio_fabricacion= item["ano_fabricacion"].get<int>();
            int capacidad=item["capacidad"].get<int>();
            int peso_max_despegue=item["peso_max_despegue"].get<int>();
            string aerolinea=item["aerolinea"].get<std::string>();
            string estado=item["estado"].get<std::string>();
            */
            
            //cout << "Avion disponible cargado correctamente" << endl;
        //CARGA DE AVIONES en mantenimiento
        }else if(estado=="Mantenimiento"||estado=="mantenimiento"){
            string vuelo=item["vuelo"].get<std::string>();
            string numero_de_registro=item["numero_de_registro"].get<std::string>();
            string modelo=item["modelo"].get<std::string>();
            int capacidad=item["capacidad"].get<int>();
            string aerolinea=item["aerolinea"].get<std::string>();
            string ciudad_destino=item["ciudad_destino"].get<std::string>();
            string estado=item["estado"].get<std::string>();

            Avion avionNuevo(vuelo,numero_de_registro,modelo,capacidad,aerolinea,ciudad_destino,estado);
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

void cargaPilotos(string nombreArchivo) {
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
        string numero_de_id=item["numero_de_id"].get<string>();
        string numero_vuelo=item["vuelo"].get<string>();
        int horasDeVuelo=item["horas_de_vuelo"].get<int>();
        string licencia=item["tipo_de_licencia"].get<string>();

        Piloto pilotoNuevo(nombre,nacionalidad,numero_de_id,numero_vuelo,horasDeVuelo,licencia);
        arbolBBpilotos.insertar(pilotoNuevo);
        cout << "Piloto "+pilotoNuevo.getNumero_de_id()+" ingresado al arbol binario" << endl;
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
        
    }
    archivo.close();

}

void visualizarReportes() {

    cout << "======LISTA DE AVIONES EN MANTENIMIENTO======" << endl;
    AvionesMantenimiento.visualizarLista();
    cout << "======REPORTES DOT.======" << endl;
    AvionesMantenimiento.generarReporte("Aviones_Mantenimiento");
    //arbolBBpilotos.generarReporte("ArbolBinario_Horas");
    Piloto piloto1("","","P0001","",600,"");
    Piloto piloto2("","","P0002","",500,"");
    Piloto piloto3("","","P0003","",650,"");
    Piloto piloto4("","","P0004","",320,"");
    Piloto piloto5("","","P0005","",321,"");
    matrizPilotos.insertar(piloto1,"A100","Colombia");
    //matrizPilotos.insertar(piloto4,"A200","Colombia");
    //matrizPilotos.insertar(piloto2,"A200","Argentina");
    //matrizPilotos.insertar(piloto5,"A200","Guatemala");
    //matrizPilotos.insertar(piloto4,"A300","Argentina");
    //matrizPilotos.insertar(piloto3,"A300","Guatemala");
   
   

    matrizPilotos.generarReporte("Matriz_Dispersa");
    //matrizPilotos.imprimirMatriz();
}

void consultarHorasVuelo(){
     int opcion =0;

    while (opcion!=4){
        cout << "=========Menu horas de vuelo=======" << endl;
        cout << "1. Preorder" << endl;
        cout << "2. Inorder" << endl;
        cout << "3. Postorder" << endl;
        cout << "4. Salir" << endl;
        cout << "==============================" << endl;

        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cout << endl;

        switch (opcion){
            
            case 1:
                cout << "======Recorrido Preorder(R.I.D)======" << endl;
                arbolBBpilotos.RecorridoPreorder();
                break;
           
            case 2:
                cout << "======Recorrido Inorder======(I.R.D.)" << endl;
                arbolBBpilotos.RecorridoInorder();
                break;
          
            case 3:
                cout << "======Recorrido Postorder(I.D.R)======" << endl;
                arbolBBpilotos.RecorridoPostorder();
                break;
           
            case 4:
                cout<< "Salio del menu horas de vuelo"<<endl;
                break;

            default:
                cout<< "Opcion no valida"<<endl;
                break;
        }

    }

}

void menuPrincipal(){

    int opcion =0;

    while (opcion!=8){
        cout << "=========Menu principal=======" << endl;
        cout << "1. Carga de aviones" << endl;
        cout << "2. Carga de pilotos" << endl;
        cout << "3. Carga de rutas" << endl;
        cout << "4. Carga de movimientos" << endl;
        cout << "5. Consultar horas de vuelo" << endl;
        cout << "6. Recomendar ruta" << endl;
        cout << "7. Visualizar reportes" << endl;
        cout << "8. Salir" << endl;
        cout << "==============================" << endl;

        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cout << endl;

        switch (opcion){
            //carga de aviones
            case 1:
                {
                string nombreArchivo="";
                cout << "Ingrese el nombre del archivo de carga de Aviones: ";
                cin >> nombreArchivo;
                
                cargarAviones(nombreArchivo);
                }
                break;
            //carga de pilotos
            case 2:
                {
                string nombreArchivo="";
                cout << "Ingrese el nombre del archivo de carga de Pilotos: ";
                cin >> nombreArchivo;
                cargaPilotos(nombreArchivo);
                }
                
                break;
            //carga de rutas
            case 3:
                
                break;
            //carga de movimientos
            case 4:
                {
                string nombreArchivo="";
                cout << "Ingrese el nombre del archivo de carga de Movimientos: ";
                cin >> nombreArchivo;
                cargaMovimientos(nombreArchivo);
                }
                break;
            //consulta de horas de vuelo
            case 5:
                consultarHorasVuelo();
                break;
            //recomendar ruta
            case 6:
                
                break;
            //visualizar reportes
            case 7:
                visualizarReportes();
                break;
            //salir
            case 8:
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

