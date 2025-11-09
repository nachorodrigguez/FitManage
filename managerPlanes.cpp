#include <iostream>
#include "managerplanes.h"

using namespace std;

ManagerPlanes::ManagerPlanes(std::string nombreArchivoPlanes)
    : archivoPlanes(nombreArchivoPlanes) {
    _cantidadOpciones = 4; // (CARGAR, MODIFICAR, LISTADO, ELIMINAR)
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
        case 0:{
        break;
        }
    }
}
