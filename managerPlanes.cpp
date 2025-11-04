#include <iostream>
#include "managerPlanes.h"

using namespace std;

ManagerPlanes::ManagerPlanes(){
    _cantidadOpcines = 3 ;
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
        cout << "1 - PLANES"<< endl;
        cout << "2 - EDITAR PRECIOS" << endl;
        cout << "0 - SALIR"<< endl;
        cout << "======================"<< endl;
}

int ManagerPlanes::seleccionOpcion(){
    int opcion;
    mostrarOpciones();
    cout << "Opcion: ";
    cin >> opcion;

    while (opcion < 0 || opcion > _cantidadOpcines){
        cout << "Opcion incorrecta..." << endl;
        cout << "Opcion: ";
        cin  >> opcion;
    }
    return opcion;

}

void ManagerPlanes::ejecutarOpcion(int opcion){
    switch(opcion){
        case 1:{
        system("pause");
        break;
        }
        case 2 : {
        system("pause");
        break;
        }
        case 0:{
        break;
        }
    }
}
