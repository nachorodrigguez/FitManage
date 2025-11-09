#include <iostream>
#include "managerplanes.h"

using namespace std;

ManagerPlanes::ManagerPlanes(std::string nombreArchivoPlanes)
    : archivoPlanes(nombreArchivoPlanes) {
    _cantidadOpciones = 4; // (CARGAR, MODIFICAR, LISTADO, ELIMINAR)

    int cantidadDePlanes = archivoPlanes.CantidadRegistros();
    Plan::EstablecerUltimoId(cantidadDePlanes);
}

void ManagerPlanes::run(){
    int opcion;
    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
    }while(opcion!=0);
}

void ManagerPlanes::mostrarOpciones(){
        cout << "MENU PRINCIPAL"<<endl;
        cout << "====================="<< endl;
        cout << "1 - CARGAR PLAN"<< endl;
        cout << "2 - MODIFICAR PLAN" << endl;
        cout << "3 - LISTADO DE PLANES" << endl;
        cout << "4 - ELIMINAR PLAN" << endl;
        cout << "0 - SALIR"<< endl;
        cout << "======================"<< endl;
}

int ManagerPlanes::seleccionOpcion(){
    int opcion;
    mostrarOpciones();
    cout << "Opcion: ";
    cin >> opcion;

    while (opcion < 0 || opcion > _cantidadOpciones){
        cout << "Opcion incorrecta..." << endl;
        cout << "Opcion: ";
        cin  >> opcion;
    }
    return opcion;

}

void ManagerPlanes::ejecutarOpcion(int opcion){
    switch(opcion){
        case 1:{
            plan.Cargar();
            if (archivoPlanes.Guardar(plan)) {
            cout << "Plan guardado exitosamente!" << endl;
            } else {
                cout << "Error al guardar el plan." << endl;
            }
            system("pause");
            break;
            }
        case 2 :{
            plan.Mostrar();
            system("pause");
            break;
        }

        case 3: {
            int cantidad = archivoPlanes.CantidadRegistros();
            if (cantidad == 0) {
                cout << "No hay planes cargados." << endl;
                system("pause");
                break;
            }

            int opcionListado = -1;
            do {
                system("cls");
                cout << "=== SUBMENU - LISTAR PLANES ===" << endl;
                cout << "1 - Planes Activos" << endl;
                cout << "2 - Planes Inactivos" << endl;
                cout << "3 - Todos los planes" << endl;
                cout << "0 - Volver al menu principal" << endl;
                cout << "===============================" << endl;
                cout << "Opcion: ";
                cin >> opcionListado;

                if (opcionListado == 0) break;
                if (opcionListado < 0 || opcionListado > 3) {
                    cout << "Opcion incorrecta..." << endl;
                    system("pause");
                    continue;
                }

                system("cls");

                Plan* vectorPlanes = new Plan[cantidad];
                archivoPlanes.Leer(cantidad, vectorPlanes);

                bool hayResultados = false;
                switch (opcionListado) {
                    case 1: {
                        cout << "=== PLANES ACTIVOS ===" << endl;
                        for (int i = 0; i < cantidad; i++) {
                            if (vectorPlanes[i].getEstado() == true) {
                                vectorPlanes[i].Mostrar();
                                cout << "-------------------------" << endl;
                                hayResultados = true;
                            }
                        }
                        if (!hayResultados) cout << "No hay planes activos." << endl;
                        break;
                    }
                    case 2: {
                        cout << "=== PLANES INACTIVOS ===" << endl;
                        for (int i = 0; i < cantidad; i++) {
                            if (vectorPlanes[i].getEstado() == false) {
                                vectorPlanes[i].Mostrar();
                                cout << "-------------------------" << endl;
                                hayResultados = true;
                            }
                        }
                        if (!hayResultados) cout << "No hay planes inactivos." << endl;
                        break;
                    }
                    case 3: {
                        cout << "=== TODOS LOS PLANES ===" << endl;
                        for (int i = 0; i < cantidad; i++) {
                            vectorPlanes[i].Mostrar();
                            cout << "-------------------------" << endl;
                            hayResultados = true;
                        }
                        break;
                    }
                }

                delete[] vectorPlanes;
                cout << endl;
                system("pause");

            } while (opcionListado != 0);

            break;
        }
        case 0:{
        break;
        }
    }
}
