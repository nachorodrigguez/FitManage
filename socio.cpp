#include <iostream>
#include <cstdio>
#include "socio.h"
#include <cstring>
#include "rlutil.h"

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
        rlutil::setColor(rlutil::LIGHTGREEN);
        rlutil::locate(60, 10);
        cout << "=== ALTA DE SOCIO ===" << endl;
        rlutil::locate(60, 11);
        cout << "Ingrese ID del socio (DNI): ";
        cin >> idSocio;
    } else {
        idSocio = idExistente;
    }


    Persona::Cargar();
    cout << endl;
    rlutil::locate(60, 12);
    cout << "Ingrese fecha de inscripcion: " << endl;
    inscripcion.Cargar();

    rlutil::locate(60, 13);
    cout << "Ingrese estado (1 = activo, 0 = inactivo): ";
    cin >> estado;

}

void Socio::Mostrar() {
    cout << endl;
    rlutil::locate(60, 11);
    cout << "ID del socio: " << idSocio << endl;

    Persona::Mostrar();
    cout << endl;
    rlutil::locate(60, 12);
    cout << "Fecha de inscripcion: ";
    inscripcion.Mostrar();
    cout << endl;
    rlutil::locate(60, 13);
    cout << "Estado: " << (estado ? "Activo" : "Inactivo") << endl;
    rlutil::locate(60, 14);
    cout << "Tipo de plan: " << tipoPlan << endl;
}

void Socio::Modificar() {
    rlutil::locate(60, 10);
    cout << "=== MODIFICAR SOCIO ===" << endl;

    Persona::Cargar();
    cout << endl;
    rlutil::locate(60, 11);
    cout << "Ingrese fecha de inscripcion: " << endl;
    inscripcion.Cargar();

    rlutil::locate(60, 12);
    cout << "Ingrese estado (1 = activo, 0 = inactivo): ";
    cin >> estado;
}

