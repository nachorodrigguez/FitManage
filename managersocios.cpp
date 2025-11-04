#include <iostream>
#include "managersocios.h"

using namespace std;

ManagerSocios::ManagerSocios(){
    _cantidadOpcines = 3 ;
}

void ManagerSocios::run(){
    int opcion;
    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
    }while(opcion!=0);
}

void ManagerSocios::mostrarOpciones(){
        cout << "MENU PRINCIPAL"<<endl;
        cout << "====================="<< endl;
        cout << "1 - CARGAR SOCIO"<< endl;
        cout << "2 - MOSTRAR SOCIO" << endl;
        cout << "0 - SALIR"<< endl;
        cout << "======================"<< endl;
}

int ManagerSocios::seleccionOpcion(){
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

void ManagerSocios::ejecutarOpcion(int opcion){
    switch(opcion){
        case 1:{
        socio.Cargar();
        system("pause");
        break;
        }
        case 2 :{
        socio.Mostrar();
        system("pause");
        break;
        }
        case 0:{
        break;
        }
    }
}
