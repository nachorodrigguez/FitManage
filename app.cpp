#include <iostream>
#include "app.h"
#include "rlutil.h"

using namespace std;

App::App():
    managersocios("socios.dat"),
    managerplanes("planes.dat"),
    managerinstructores("instructores.dat"),
    managercob("cobranzas.dat"),
    managerclases("clases.dat"),
    managerrep("cobranzas.dat")
        {
            _cantidadOpciones = 7 ;
        }

void App::run(){
    int opcion;
    do{
        rlutil::cls();
        opcion = seleccionOpcion();
        rlutil::cls();
        ejecutarOpcion(opcion);
    }while(opcion!=0);
}

void App::mostrarOpciones(){
    rlutil::setColor(rlutil::CYAN);
    rlutil::locate(CENTER_X, 10);
    cout << "FITMANAGE - SISTEMA DE GESTION DE GIMNASIO";

    rlutil::resetColor();

    rlutil::locate(CENTER_X, 14);
    cout << "==============================";

    rlutil::locate(CENTER_X, 15);
    cout << "        MENU PRINCIPAL";

    rlutil::locate(CENTER_X, 16);
    cout << "==============================";

    rlutil::setColor(rlutil::LIGHTGREEN);
    rlutil::locate(CENTER_X, 18);  cout << "1 - SOCIOS";
    rlutil::locate(CENTER_X, 19);  cout << "2 - INSTRUCTORES";
    rlutil::locate(CENTER_X,20);  cout << "3 - PLANES";
    rlutil::locate(CENTER_X,21);  cout << "4 - CLASES";
    rlutil::locate(CENTER_X,22);  cout << "5 - PAGOS";
    rlutil::locate(CENTER_X,23);  cout << "6 - REPORTES";
    rlutil::locate(CENTER_X,24);  cout << "7 - CONFIGURACIONES";
    rlutil::locate(CENTER_X,26);  cout << "0 - SALIR";

    rlutil::resetColor();

    rlutil::locate(CENTER_X,28);
    cout << "Seleccione una opcion: ";
}

int App::seleccionOpcion() {
    int opcion;
    mostrarOpciones();
    cin >> opcion;

    while (opcion < 0 || opcion > _cantidadOpciones){
        rlutil::setColor(rlutil::RED);
        rlutil::locate(CENTER_X,30);
        cout << "Opcion incorrecta...   ";
        rlutil::resetColor();

        rlutil::locate(CENTER_X,28);
        cout << "Seleccione una opcion: ";
        cin >> opcion;
    }
    return opcion;
}

void App::ejecutarOpcion(int opcion){
    switch(opcion){
        case 1:{
        managersocios.run();
        break;
        rlutil::anykey();
        }
        case 2:{
        managerinstructores.run();
        break;
        rlutil::anykey();
        }
        case 3:{
        managerplanes.run();
        break;
        rlutil::anykey();
        }
        case 4:{
        managerclases.run();
        break;
        rlutil::anykey();
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
