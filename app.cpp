#include <iostream>
#include "app.h"

using namespace std;

App::App():
    managersocios("socios.dat"),
    managerplanes("planes.dat"),
    managerinstructores("instructores.dat"),
    managercob("cobranzas.dat"),
    managerclases("clases.dat"),
    managerrep("cobranzas.dat")
        {
            _cantidadOpciones = 8 ;
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
        cout << "6 - REPORTES"<< endl;
        cout << "7 - CONFIGURACIONES"<< endl;
        cout << "0 - SALIR"<< endl;
        cout << "======================"<< endl;
}

int App::seleccionOpcion(){
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

void App::ejecutarOpcion(int opcion){
    switch(opcion){
        case 1:{
        managersocios.run();
        break;
        system("pause");
        }
        case 2:{
        managerinstructores.run();
        break;
        system("pause");
        }
        case 3:{
        managerplanes.run();
        break;
        system("pause");
        }
        case 4:{
        managerclases.run();
        break;
        system("pause");
        }
        case 5:{
        managercob.run();
        break;
        }
        case 6:{
        managerrep.run();
        break;
        }
        case 7:{
        break;
        }
    }
}
