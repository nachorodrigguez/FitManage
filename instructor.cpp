#include <iostream>
#include <cstring>
#include "instructor.h"

using namespace std;

Instructor::Instructor(){
    _idInstructor = 0;
    estado = true;
    strcpy(_especialidad, "Sin especialidad");
    idClaseAsignada = 0;
}

int Instructor::getidInstructor(){
    return _idInstructor;
}

void Instructor::setEstado(bool valor){
    estado = valor; }


const char* Instructor::getEspecialidad(){
    return _especialidad;
}

void Instructor::setidInstructor(int ID){
    _idInstructor = ID;
}
bool Instructor::getEstado() const {
    return estado; }

int Instructor::getIdClaseAsignada() const {
    return idClaseAsignada;
}

void Instructor::setIdClaseAsignada(int idClase) {
    idClaseAsignada = idClase;
}

void Instructor::setEspecialidad(){

    int opcion;
    cout << endl;
    cout << "ESPECIALIDAD" << endl;
    cout << "========================="<< endl;
    cout << "1) Spinning" << endl;
    cout << "2) Boxeo" << endl;
    cout << "3) Yoga" << endl;
    cout << "4) Crossfit" << endl;
    cout << "5) Pilates" << endl;
    cout << "6) Funcional" << endl;

    cout << "Opcion: ";
    cin >> opcion;


    while (opcion < 0 || opcion > 6){
        cout << "Opcion incorrecta..." << endl;
        cout << "Opcion: ";
        cin >> opcion;
    }

    switch(opcion){
        case 1: {
            strcpy(_especialidad,"Spinning");
            break;
        }
        case 2:{
            strcpy(_especialidad,"Boxeo");
            break;
        }
        case 3:{
            strcpy(_especialidad,"Yoga");
            break;
        }
        case 4: {
            strcpy(_especialidad,"Yoga");
            break;
        }
        case 5:{
            strcpy(_especialidad,"Crossfit");
            break;
        }
        case 6:{
            strcpy(_especialidad,"Pilates");
            break;
        }
        case 7:{
            strcpy(_especialidad,"Funcional");
            break;
        }
    }
}

void Instructor::Cargar(int idExistente) {

    if (idExistente == 0) {
        cout << "=== ALTA DE INSTRUCTOR ===" << endl;
        cout << "Ingrese ID del INSTRUCTOR (DNI): ";
        cin >>_idInstructor ;
    } else {
        _idInstructor = idExistente;
    }

    Persona::Cargar();
    estado = 1;

}

void Instructor::Mostrar(){
    cout << "ID Instructor (DNI): " << _idInstructor << endl;
    cout << "Especialidad: " << _especialidad << endl;
    Persona::Mostrar();
    cout << endl;
    cout << "ID de Clase asignada: ";
    if (idClaseAsignada == 0) cout << "Ninguna" << endl;
    else cout << idClaseAsignada << endl;
    cout << "Estado: " << (estado ? "Activo" : "Inactivo") << endl;

}

void Instructor::Modificar() {
    cout << "=== MODIFICAR INSTRUCTOR ===" << endl;

    Persona::Cargar();
    cout << endl;

    cout << "Ingrese estado (1 = activo, 0 = inactivo): ";
    cin >> estado;
}

