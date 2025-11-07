#include <iostream>
#include "ManagerSocios.h"

using namespace std;

ManagerSocios::ManagerSocios(std::string nombreArchivo): archivosocios(nombreArchivo){
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
        cout << "3 - LISTAR SOCIO" << endl;
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
        if (archivosocios.Guardar(socio)){
            cout << "Socio guardado exitosamente!" << endl;
        }else{
            cout << "Error al guardar el socio." << endl;
        }
        system("pause");
        break;
        }
        case 2 :{
        socio.Mostrar();
        system("pause");
        break;
        }
        case 3: {
            int cantidad = archivosocios.CantidadRegistros();
            if (cantidad == 0){
                cout << "No hay socios cargados." << endl;
            }else{
                Socio *vecAux = new Socio[cantidad];
                archivosocios.Leer(cantidad, vecAux);
                for (int i=0; i < cantidad; i++){
                    vecAux[i].Mostrar();
                    cout << "------------------" << endl;
                }
                delete[] vecAux;
            }
            system("pause");
            break;
        }
        case 0:{
            break;
        }
    }
}
