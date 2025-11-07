#include <iostream>
#include "app.h"

using namespace std;

App::App(){
    _cantidadOpcines = 9 ;
}

void App::run(){
    int opcion;
    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
    }while(opcion!=0);
}

void App::mostrarOpciones(){
        cout << "MENU PRINCIPAL"<<endl;
        cout << "====================="<< endl;
        cout << "1 - SOCIOS"<< endl;
        cout << "2 - INSTRUCTORES" << endl;
        cout << "3 - PLANES"<< endl;
        cout << "4 - CLASES"<< endl;
        cout << "5 - PAGOS"<< endl;
        cout << "6 - LISTADOS"<< endl;
        cout << "7 - CONSULTAS"<< endl;
        cout << "8 - INFORMES"<< endl;
        cout << "9 - CONFIGURACIONES"<< endl;
        cout << "0 - SALIR"<< endl;
        cout << "======================"<< endl;
}

int App::seleccionOpcion(){
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

void App::ejecutarOpcion(int opcion){
    switch(opcion){
        case 1:{
        managersocios.run();
        break;
        system("pause");
        }
        case 2:{
        managerIns.run();
        break;
        system("pause");
        }
        case 3:{
        managerplanes.run();
        break;
        system("pause");
        }
        case 5:{
        managercob.run();
        break;
        }
        case 6:{
        managerlis.run();
        break;
        }
    }
}
