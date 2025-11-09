#include <iostream>
#include "ManagerInstructores.h"

using namespace std;

ManagerInstructores::ManagerInstructores(std::string nombreArchivoInstructores)
    : archivoInstructores(nombreArchivoInstructores) {
    _cantidadOpciones = 4; // (CARGAR, MODIFICAR, LISTADO, ELIMINAR)
}

void ManagerInstructores::run(){
    int opcion;
    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
    }while(opcion!=0);
}

void ManagerInstructores::mostrarOpciones(){
        cout << "MENU PRINCIPAL"<<endl;
        cout << "====================="<< endl;
        cout << "1 - CARGAR INSTRUCTOR"<< endl;
        cout << "2 - MOSTRAR INSTRUCTORES" << endl;
        cout << "0 - SALIR"<< endl;
        cout << "======================"<< endl;
}

int ManagerInstructores::seleccionOpcion(){
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

void ManagerInstructores::ejecutarOpcion(int opcion){
    switch(opcion){
        case 1:{
        ins.Cargar();
        system("pause");
        break;
        }
        case 2 : {
        ins.Mostrar();
        system("pause");
        break;
        }
        case 0:{
        break;
        }
    }
}

