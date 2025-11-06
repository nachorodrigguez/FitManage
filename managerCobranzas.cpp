#include <iostream>
#include "ManagerCobranzas.h"

using namespace std;

ManagerCobranzas::ManagerCobranzas(){
    _cantidadOpcines = 3 ;
}

void ManagerCobranzas::run(){
    int opcion;
    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
    }while(opcion!=0);
}

void ManagerCobranzas::mostrarOpciones(){
        cout << "MENU PRINCIPAL"<<endl;
        cout << "====================="<< endl;
        cout << "1 - GENERAR PAGO"<< endl;
        cout << "2 - FACTURA" << endl;
        cout << "0 - SALIR"<< endl;
        cout << "======================"<< endl;
}

int ManagerCobranzas::seleccionOpcion(){
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

void ManagerCobranzas::ejecutarOpcion(int opcion){
    switch(opcion){
        case 1:{
        cobranza.Cargar();
        system("pause");
        break;
        }
        case 2 : {
        cobranza.Mostrar();
        system("pause");
        break;
        }
        case 0:{
        break;
        }
    }
}

