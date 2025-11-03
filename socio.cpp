#include <iostream>
#include <cstdio>
#include "socio.h"

using namespace std;

Socio::Socio() {
    idSocio = 0;
    estado = true;
}

void Socio::setId(int valor) {
    idSocio = valor;
}

void Socio::setInscripcion(Fecha f) {
    inscripcion = f;
}

void Socio::setEstado(bool valor) {
    estado = valor;
}

int Socio::getId() {
    return idSocio;
}

Fecha Socio::getInscripcion() {
    return inscripcion;
}

bool Socio::getEstado() {
    return estado;
}

void Socio::Cargar() {
    cout << "=== ALTA DE SOCIO ===" << endl;
    cout << "Ingrese ID del socio ( DNI ): ";
    cin >> idSocio;

    persona.Cargar();

    cout << "Ingrese fecha de inscripcion: " << endl;
    inscripcion.Cargar();

    cout << "Ingrese estado (1 = activo, 0 = inactivo): ";
    cin >> estado;
}

void Socio::Mostrar() {
    cout << endl;
    cout << "ID del socio: " << idSocio << endl;

    persona.Mostrar();

    cout << "Fecha de inscripcion: ";
    inscripcion.Mostrar();
    cout << endl;
    cout << "Estado: " << (estado ? "Activo" : "Inactivo") << endl;
}


void Socio::run(){
    int opcion;
    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
    }while(opcion!=0);
}

void Socio::mostrarOpciones(){
        cout << "MENU PRINCIPAL"<<endl;
        cout << "====================="<< endl;
        cout << "1 - CARGAR SOCIO"<< endl;
        cout << "2 - MOSTRAR SOCIO" << endl;
        cout << "0 - SALIR"<< endl;
        cout << "======================"<< endl;
}

int Socio::seleccionOpcion(){
    int opcion;
    mostrarOpciones();
    cout << "Opcion: ";
    cin >> opcion;

    while (opcion < 0 || opcion > 3){
        cout << "Opcion incorrecta..." << endl;
        cout << "Opcion: ";
        cin  >> opcion;
    }
    return opcion;
}

void Socio::ejecutarOpcion(int opcion){
    switch(opcion){
        case 1:{
        Cargar();
        system("pause");
        break;
        }
        case 2:{
        Mostrar();
        system("pause");
        break;
        }
        case 0:{
        break;
        }
    }
}

