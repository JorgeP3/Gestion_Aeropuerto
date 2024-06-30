//clases
#include "./clases/Avion.h"
#include "./clases/Piloto.h"
//Estructuras
#include "./estructuras/CircularDoble.h"
#include "./estructuras/ArbolBB.h"
#include "./estructuras/Matriz.h"
#include "./estructuras/TablaHash.h"
#include "./estructuras/Grafo.h"

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

CircularDoble avionesDisponibles;
CircularDoble AvionesMantenimiento;
ArbolBB arbolBBpilotos;
Matriz matrizPilotos;
TablaHash tablahashPilotos;
Grafo* grafoRutas=nullptr;

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
        
            string vuelo=item["vuelo"].get<std::string>();
            string numero_de_registro=item["numero_de_registro"].get<std::string>();
            string modelo=item["modelo"].get<std::string>();
            int capacidad=item["capacidad"].get<int>();
            string aerolinea=item["aerolinea"].get<std::string>();
            string ciudad_destino=item["ciudad_destino"].get<std::string>();
            string estado=item["estado"].get<std::string>();

            Avion avionNuevo(vuelo,numero_de_registro,modelo,capacidad,aerolinea,ciudad_destino,estado);
            avionesDisponibles.insertarFinal(avionNuevo);
            cout << "Avion disponible cargado correctamente" << endl;
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
        tablahashPilotos.Insertar(pilotoNuevo);

        string fila=pilotoNuevo.getVuelo();
        string columna="";

        if (avionesDisponibles.buscarPorNumeroDeVuelo(fila)!="")
        {
            columna=avionesDisponibles.buscarPorNumeroDeVuelo(fila);

        }else if (AvionesMantenimiento.buscarPorNumeroDeVuelo(fila)!="")
        {
            columna=AvionesMantenimiento.buscarPorNumeroDeVuelo(fila);
        }else{
            cout << "No se encontro el avion con numero de vuelo " << fila <<endl;
        }
        
        matrizPilotos.insertar(pilotoNuevo,fila,columna);

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
        vector<std::string> palabras =split(linea,",();");
        /*PROCESADO DEL COMANDO EQUIPAJES*/
        if (palabras[0]=="DarDeBaja" || palabras[0]=="dardebaja")
        {
            string id_piloto=palabras[1];
            
            tablahashPilotos.eliminarPiloto(id_piloto);
            matrizPilotos.eliminarNodo(id_piloto);
            
        /*PROCESADO DEL MANTENIMIENTO DE AVIONES*/
        }else if(palabras[0]=="MantenimientoAviones"||palabras[0]=="mantenimientoaviones"){
            if (palabras[1]=="Ingreso" || palabras[1]=="ingreso")
            {
                string numero_registro=palabras[2];
                Avion avionAcambiar=avionesDisponibles.buscarPorNumeroDeRegistro(numero_registro);
                if (avionAcambiar.getNumeroDeRegistro()!="")//si devuelve un avion
                {
                    avionesDisponibles.eliminarPorNumeroDeRegistro(numero_registro);//lo elimino
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
                    avionesDisponibles.insertarFinal(avionAcambiar);//lo agrego a la otra lista
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

bool buscarCiudad(vector <string> ciudades,string ciudad){//devuelve true si ya existe y false si no
    auto it = std::find(ciudades.begin(), ciudades.end(), ciudad);
    if (it != ciudades.end()) {
        return true;
    } else {
        return false;
    }
}

void cargarRutas(string nombreArchivo){
    string path="C:\\Users\\lmpgp\\OneDrive\\Escritorio\\"+nombreArchivo;

    ifstream archivo(path);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    vector<string> vectorCiudades;


    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) {
            continue; // Saltar líneas vacías
        }
        vector<std::string> ciudad =split(linea,"/;");

        if(!buscarCiudad(vectorCiudades,ciudad[0])){
            vectorCiudades.push_back(ciudad[0]);
        }

        if(!buscarCiudad(vectorCiudades,ciudad[1])){
            vectorCiudades.push_back(ciudad[1]);
        }
    }
    archivo.close();

    int numeroVertices=vectorCiudades.size();
    grafoRutas=new Grafo(numeroVertices);

    for (size_t i = 0; i < vectorCiudades.size(); i++)
    {
        grafoRutas->nuevoVertice(vectorCiudades[i]);
    }
    
    
    ifstream archivo1(path);
    if (!archivo1.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    while (getline(archivo1, linea)) {
        if (linea.empty()) {
            continue; // Saltar líneas vacías
        }
        vector<std::string> ciudad =split(linea,"/;");

        grafoRutas->nuevoArco(ciudad[0],ciudad[1],stoi(ciudad[2]));
        
    }
    archivo1.close();
    
}

void visualizarReportes() {

    cout << "======REPORTES DOT.======" << endl;
    avionesDisponibles.generarReporte("Aviones_Disponibles");
    AvionesMantenimiento.generarReporte("Aviones_Mantenimiento");
    arbolBBpilotos.generarReporte("ArbolBinario_Horas");
    tablahashPilotos.generarReporte("Tabla_hash");
    matrizPilotos.generarReporte("Matriz_Dispersa");
    if (grafoRutas!=nullptr)
    {
        grafoRutas->generarReporte("Grafo_Rutas");
    }else{
        cout << "El grafo no ha sido creado" << endl;
    }
    //grafoRutas->imprimirMatriz();
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
                {
                string nombreArchivo="";
                cout << "Ingrese el nombre del archivo de carga de Rutas: ";
                cin >> nombreArchivo;
                
                cargarRutas(nombreArchivo);
                }
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

