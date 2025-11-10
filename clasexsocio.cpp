#include "clasexsocio.h"
#include <iostream>
#include <limits>

using namespace std;

ClasexSocio::ClasexSocio(){
    _IDClasexSocio = 0;
    _idSocio = 0;
    _IDClase = 0;
    _estado = true;   // por defecto, inscripcion activa
}

// Getters
int ClasexSocio::getIDClasexSocio() const{
    return _IDClasexSocio;
}

int ClasexSocio::getIdSocio() const{
    return _idSocio;
}

int ClasexSocio::getIDClase() const{
    return _IDClase;
}

Fecha ClasexSocio::getFechaInscripcion() const{
    return _fechaInscripcion;
}

bool ClasexSocio::getEstado() const{
    return _estado;
}

// Setters
void ClasexSocio::setIDClasexSocio(int id){
    _IDClasexSocio = id;
}

void ClasexSocio::setIdSocio(int idSocio){
    _idSocio = idSocio;
}

void ClasexSocio::setIDClase(int idClase){
    _IDClase = idClase;
}

void ClasexSocio::setFechaInscripcion(const Fecha &f){
    _fechaInscripcion = f;
}

void ClasexSocio::setEstado(bool e){
    _estado = e;
}

// Cargar: crea una nueva inscripcion socio -> clase
void ClasexSocio::Cargar(){
    cout << "\n=== Nueva inscripcion de socio a clase ===\n";

    // ID del socio
    cout << "ID del socio: ";
    while(!(cin >> _idSocio)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida. Ingrese nuevamente ID del socio: ";
    }

    // ID de la clase
    cout << "ID de la clase (1-7): ";
    while(!(cin >> _IDClase) || _IDClase < 1 || _IDClase > 7){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida. Ingrese un ID de clase entre 1 y 7: ";
    }

    // Fecha de inscripcion
    cout << "\nFecha de inscripcion:\n";
    _fechaInscripcion.Cargar();

    _estado = true;  // inscripcion activa

    // limpiar buffer
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Mostrar: muestra la inscripcion socio -> clase
void ClasexSocio::Mostrar() const{
    cout << "ID Inscripcion: " << _IDClasexSocio << endl;
    cout << "ID Socio: " << _idSocio << endl;
    cout << "ID Clase: " << _IDClase << endl;
    cout << "Fecha de inscripcion: ";
    _fechaInscripcion.Mostrar();
    cout << endl;
    cout << "Estado: " << (_estado ? "Activa" : "Baja") << endl;
}
