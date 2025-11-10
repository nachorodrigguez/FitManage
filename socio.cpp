#include <iostream>
#include <cstdio>
#include "socio.h"
#include <cstring>

using namespace std;

Socio::Socio() {
    idSocio = 0;
    estado = true;
    strcpy(tipoPlan, "Sin asignar");
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

void Socio::setTipoPlan(const char* tp) {
    if(tp == nullptr) { strcpy(tipoPlan, "Sin asignar"); return; }
    strncpy(tipoPlan, tp, sizeof(tipoPlan)-1);
    tipoPlan[sizeof(tipoPlan)-1] = '\0';
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

const char* Socio::getTipoPlan() const { return tipoPlan; }

void Socio::Cargar(int idExistente) {

    if (idExistente == 0) {
        cout << "=== ALTA DE SOCIO ===" << endl;
        cout << "Ingrese ID del socio (DNI): ";
        cin >> idSocio;
    } else {
        idSocio = idExistente;
    }


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
    cout << endl;

    cout << "Fecha de inscripcion: ";
    inscripcion.Mostrar();
    cout << endl;
    cout << "Estado: " << (estado ? "Activo" : "Inactivo") << endl;
    cout << "Tipo de plan: " << tipoPlan << endl;
}

void Socio::Modificar() {
    cout << "=== MODIFICAR SOCIO ===" << endl;

    Persona::Cargar();
    cout << endl;

    cout << "Ingrese fecha de inscripcion: " << endl;
    inscripcion.Cargar();

    cout << "Ingrese estado (1 = activo, 0 = inactivo): ";
    cin >> estado;
}

