#include "clase.h"
#include <iostream>
#include <cstring>   // strcpy
#include <limits>    // numeric_limits

using namespace std;

Clase::Clase() {
    _IDClase = 0;
    strcpy(nombreClase, "SIN CLASE");
    strcpy(descripcion, "SIN DESCRIPCION");
    tiempoDuracion = 0;
    capacidadMax = 0;
}

// Getters
int Clase::getIDClase() const {
    return _IDClase;
}

const char* Clase::getNombreClase() const {
    return nombreClase;
}

const char* Clase::getDescripcion() const {
    return descripcion;
}

int Clase::getTiempoDuracion() const {
    return tiempoDuracion;
}

int Clase::getCapacidadMax() const {
    return capacidadMax;
}

// Setters
void Clase::setIDClase(int IDClase){
    _IDClase = IDClase;
}

void Clase::setNombreclase(const char *n) {
    if (n != nullptr) {
        strcpy(nombreClase, n);
    }
}

void Clase::setDescripcion(const char *d) {
    if (d != nullptr) {
        strcpy(descripcion, d);
    }
}

void Clase::setTiempoDuracion(int tDur) {
    if (tDur < 0) tDur = 0;   // validación mínima
    tiempoDuracion = tDur;
}

void Clase::setCapacidadMax(int cMax) {
    if (cMax < 0) cMax = 0;   // validación mínima
    capacidadMax = cMax;
}

// Cargar: las 6 clases del informe + opcion 7) Otra
void Clase::Cargar() {
    int opcion;
    bool ok = false;

    cout << "\n=== Carga de Clase ===\n";
    cout << "Seleccione la clase:\n";
    cout << "1) Spinning\n";
    cout << "2) Boxeo\n";
    cout << "3) Yoga\n";
    cout << "4) Crossfit\n";
    cout << "5) Pilates\n";
    cout << "6) Funcional\n";
    cout << "7) Otra\n";

    // leer y validar opción (1-7)
    do {
        cout << "Opcion (1-7): ";
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Intente nuevamente.\n";
            continue;
        }
        if (opcion < 1 || opcion > 7) {
            cout << "Opcion fuera de rango. Intente nuevamente.\n";
            continue;
        }
        ok = true;
    } while (!ok);

    // limpiar el '\n' que queda después de leer la opción
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    _IDClase = opcion;

    switch (opcion) {
        case 1: setNombreclase("Spinning");   break;
        case 2: setNombreclase("Boxeo");      break;
        case 3: setNombreclase("Yoga");       break;
        case 4: setNombreclase("Crossfit");   break;
        case 5: setNombreclase("Pilates");    break;
        case 6: setNombreclase("Funcional");  break;
        case 7:
            cout << "Ingrese el nombre de la nueva clase: ";
            cin.getline(nombreClase, 50);     // o usar cargarCadena
            break;
    }

    cout << "Clase seleccionada: " << nombreClase
         << " (ID: " << _IDClase << ")\n\n";

    // Descripcion
    cout << "Descripcion de la clase: ";
    cin.getline(descripcion, 100);

    // Tiempo de duracion (minutos)
    int tDur;
    do {
        cout << "Tiempo de duracion (en minutos): ";
        if (!(cin >> tDur)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Intente nuevamente.\n";
            tDur = -1;
        }
        else if (tDur <= 0) {
            cout << "Debe ser mayor que 0.\n";
        }
    } while (tDur <= 0);

    setTiempoDuracion(tDur);

    // Capacidad maxima de alumnos
    int cMax;
    do {
        cout << "Capacidad maxima de alumnos: ";
        if (!(cin >> cMax)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Intente nuevamente.\n";
            cMax = -1;
        }
        else if (cMax <= 0) {
            cout << "Debe ser mayor que 0.\n";
        }
    } while (cMax <= 0);

    setCapacidadMax(cMax);

    // Limpiar el resto de la linea
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Mostrar: muestra todos los datos de la clase
void Clase::Mostrar() {
    cout << "--- INFORMACION DE CLASE ---" << endl;
    cout << "ID Clase: " << _IDClase << endl;
    cout << "Clase: " << nombreClase << endl;
    cout << "Descripcion: " << descripcion << endl;
    cout << "Duracion: " << tiempoDuracion << " minutos" << endl;
    cout << "Capacidad maxima: " << capacidadMax << " alumnos" << endl;
}
