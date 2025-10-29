#include <iostream>
#include <cstring>

#include "instructor.h"

using namespace std;

Instructor::Instructor(){
    _idInstructor = 0;
    strcpy(_especialidad, "Sin especialidad");
}

int Instructor::getidInstructor(){
    return _idInstructor;
}
const char* Instructor::getEspecialidad(){
    return _especialidad;
}

void Instructor::setidInstructor(int ID){
    _idInstructor = ID;
}
void Instructor::setEspecialidad(const char *n){
    strcpy(_especialidad,n);
}

void Instructor::Cargar(){
    Persona::Cargar();
    cout << "Ingrese id del instructor: ";
    cin >> _idInstructor;
    cin.ignore();
    cout << "Especialidad: ";
    cin.getline(_especialidad,50);
}
void Instructor::Mostrar(){
    Persona::Mostrar();
    cout << "Id Instructor: " << _idInstructor << endl;
    cout << "Especialidad: " << _especialidad << endl;
}
