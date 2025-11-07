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

    Persona::Cargar();
    cout << endl;

    cout << "Ingrese fecha de inscripcion: " << endl;
    inscripcion.Cargar();

    cout << "Ingrese estado (1 = activo, 0 = inactivo): ";
    cin >> estado;

}

void Socio::Mostrar() {
    cout << endl;
    cout << "ID del socio: " << idSocio << endl;

    Persona::Mostrar();

    cout << "Fecha de inscripcion: ";
    inscripcion.Mostrar();
    cout << endl;
    cout << "Estado: " << (estado ? "Activo" : "Inactivo") << endl;
}

