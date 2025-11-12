#include <iostream>
#include "managerClases.h"
using namespace std;

ManagerClases::ManagerClases(string nombreArchivo) : archivoClases(nombreArchivo) {
    _cantidadOpciones = 3;
}

void ManagerClases::run() {
    int opcion;
    do {
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
    } while (opcion != 0);
}

void ManagerClases::mostrarOpciones() {
    cout << "MENU CLASES" << endl;
    cout << "=====================" << endl;
    cout << "1 - AGREGAR CLASE" << endl;
    cout << "2 - LISTAR CLASES" << endl;
    cout << "3 - BUSCAR CLASE" << endl;
    cout << "0 - SALIR" << endl;
    cout << "======================" << endl;
}

int ManagerClases::seleccionOpcion() {
    int opcion;
    mostrarOpciones();
    cout << "Opcion: ";
    cin >> opcion;

    while (opcion < 0 || opcion > _cantidadOpciones) {
        cout << "Opcion incorrecta..." << endl;
        cout << "Opcion: ";
        cin >> opcion;
    }
    return opcion;
}

void ManagerClases::ejecutarOpcion(int opcion) {
    switch (opcion) {
        case 1: {
            cout << "=== AGREGAR CLASE ===" << endl;
            clase.Cargar();
            archivoClases.Guardar(clase);
            cout << "Clase agregada correctamente." << endl;
            system("pause");
            break;
        }
        case 2: {
            cout << "=== LISTADO DE CLASES ===" << endl;
            archivoClases.Listar();
            system("pause");
            break;
        }
        case 3: {
            cout << "=== BUSCAR CLASE ===" << endl;
            int id;
            cout << "Ingrese ID de clase: ";
            cin >> id;
            Clase c;
            if (archivoClases.LeerPorID(id, c)) {
                c.Mostrar();
            } else {
                cout << "No se encontró una clase con ese ID." << endl;
            }
            system("pause");
            break;
        }
        case 0:
            cout << "Saliendo del menú de Clases..." << endl;
            break;
    }
}
