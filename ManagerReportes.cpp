#include <iostream>
#include "ManagerReportes.h"

using namespace std;

ManagerReportes::ManagerReportes(std::string nombreArchivoCobranzas){
    _cantidadOpciones = 4;
}

void ManagerReportes::run(){
    int opcion;
    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
    }while(opcion!=0);
}

void ManagerReportes::mostrarOpciones(){
       cout << "MENU PRINCIPAL"<<endl;
        cout << "====================="<< endl;
        cout << "1 - RECAUDACION ANUAL Y MENSUAL" << endl;
        cout << "2 - SOCIOS ACTIVOS POR PLAN" << endl;
        cout << "3 - CLASES MAS DEMANDADAS" << endl;
        cout << "4 - PAGOS PENDIENTES O ATRASADOS" << endl;
        cout << "0 - SALIR"<< endl;
        cout << "======================"<< endl;
}


int ManagerReportes::seleccionOpcion(){
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

void ManagerReportes::ejecutarOpcion(int opcion){
    switch(opcion){
        case 1: {
            break;
            }
        case 2: {
            break;
            }
        case 3: {
            break;
        }
        case 5: {
        break;
        }
    }
}


