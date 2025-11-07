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

void Instructor::Cargar(){
    Persona::Cargar();
    cout << "Ingrese id del instructor: ";
    cin >> _idInstructor;
    cin.ignore();

    setEspecialidad();
}
void Instructor::Mostrar(){
    Persona::Mostrar();
    cout << endl;
    cout << "Id Instructor: " << _idInstructor << endl;
    cout << "Especialidad: " << _especialidad << endl;
}
