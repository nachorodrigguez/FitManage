#include <iostream>
#include <cstring>
#include "persona.h"

using namespace std;

Persona::Persona(){
    strcpy(nombre, "S/N");
    strcpy(apellido, "S/A");
    strcpy(domicilio, "S/D");
    strcpy(telefono, "00 0000 0000");
}

void Persona::setNombre(const char *n){
    strcpy(nombre, n);
}

void Persona::setApellido(const char *n){
    strcpy(apellido, n);
}

void Persona::setDomicilio(const char *n){
    strcpy(domicilio, n);
}

void Persona::setTelefono(const char *n){
    strcpy(telefono, n);
}

void Persona::setFechaNacimiento(Fecha fN){
    fechaNacimiento= fN;
}

const char* Persona::getNombre(){
    return nombre;
}

const char* Persona::getApellido(){
    return apellido;
}

const char* Persona::getDomicilio(){
    return domicilio;
}

const char* Persona::getTelefono(){
    return telefono;
}

Fecha Persona::getFechaNacimiento(){
    return fechaNacimiento;
}

void Persona::Cargar(){
    cin.ignore();
    cout << "Ingrese nombre: ";
    cin.getline(nombre, 50);

    cout << "Ingrese apellido: ";
    cin.getline(apellido,50);

    cout << "Ingrese domicilio: ";
    cin.getline(domicilio, 50);

    cout << "Ingrese telefono: " ;
    cin.getline(telefono,15);

    cout <<"Fecha de nacimiento " << endl ;
    fechaNacimiento.Cargar();
}

void Persona::Mostrar(){
    cout << "Nombre: " << nombre << endl;
    cout << "Apellido: " << apellido << endl;
    cout << "Domicilio: " << domicilio << endl;
    cout << "Telefono: " << telefono << endl;
    cout << "Fecha de nacimiento: ";
    fechaNacimiento.Mostrar();
}
