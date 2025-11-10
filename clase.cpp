#include "clase.h"
#include <iostream>
#include <cstring>
#include <limits>

using namespace std;

void Clase::Cargar(){
    int opcion;

    cout << "=== Carga de Clase ===" << endl;
    cout << "Seleccione la clase:" << endl;
    cout << "1) Spinning" << endl;
    cout << "2) Boxeo" << endl;
    cout << "3) Yoga" << endl;
    cout << "4) Crossfit" << endl;
    cout << "5) Pilates" << endl;
    cout << "6) Funcional" << endl;
    cout << "7) Otra" << endl;

    // leer y validar opcion (1-7)
    do{
        cout << "Opcion (1-7): ";
        if (!(cin >> opcion)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Intente nuevamente." << endl;
            opcion = -1;
            continue;
        }

        if (opcion < 1 || opcion > 7){
            cout << "Opcion fuera de rango. Intente nuevamente." << endl;
        }

    }while(opcion < 1 || opcion > 7);

    // limpiar salto de linea antes de usar getline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // asignar nombre segun opcion
    switch(opcion){
        case 1: setNombreclase("Spinning");   break;
        case 2: setNombreclase("Boxeo");      break;
        case 3: setNombreclase("Yoga");       break;
        case 4: setNombreclase("Crossfit");   break;
        case 5: setNombreclase("Pilates");    break;
        case 6: setNombreclase("Funcional");  break;
        case 7:
            cout << "Ingrese el nombre de la nueva clase: ";
            cin.getline(nombreClase, 50);     // o usar tu funcion cargarCadena
            break;
    }

    // descripcion
    cout << "Descripcion: ";
    cin.getline(descripcion, 100);

    // duracion (en minutos)
    int tDur;
    do{
        cout << "Duracion (en minutos): ";
        if (!(cin >> tDur)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Ingrese un numero entero." << endl;
            tDur = -1;
            continue;
        }
        if (tDur <= 0){
            cout << "La duracion debe ser mayor a 0." << endl;
        }
    }while(tDur <= 0);
    setTiempoDuracion(tDur);

    // capacidad maxima
    int cMax;
    do{
        cout << "Capacidad maxima (cantidad de alumnos): ";
        if (!(cin >> cMax)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Ingrese un numero entero." << endl;
            cMax = -1;
            continue;
        }
        if (cMax <= 0){
            cout << "La capacidad debe ser mayor a 0." << endl;
        }
    }while(cMax <= 0);
    setCapacidadMax(cMax);

    // limpiar buffer para futuras lecturas con getline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
