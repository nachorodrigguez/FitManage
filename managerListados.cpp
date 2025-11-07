#include <iostream>
#include "ManagerListados.h"

using namespace std;

ManagerListados::ManagerListados(){
    _cantidadOpcines = 5 ;
}

void ManagerListados::run(){
    int opcion;
    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
    }while(opcion!=0);
}

void ManagerListados::mostrarOpciones(){
        cout << "MENU PRINCIPAL"<<endl;
        cout << "=====================" << endl;
        cout << "1 - LISTADO CLIENTES" << endl;
        cout << "2 - LISTADO INSTRUCTORES" << endl;
        cout << "3 - LISTADO PLANES" << endl;
        cout << "4 - LISTADO CLASES" << endl;
        cout << "5 - LISTADO PAGOS" << endl;
        cout << "======================"<< endl;
}

int ManagerListados::seleccionOpcion(){
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

void ManagerListados::ejecutarOpcion(int opcion){
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
