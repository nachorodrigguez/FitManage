#pragma once
#include "fecha.h"

class Socio {
private:
    int idSocio;
    Fecha inscripcion;
    bool estado;

public:
    Socio();

    int getId();
    Fecha getInscripcion();
    bool getEstado();

    void setId(int);
    void setInscripcion(Fecha);
    void setEstado(bool);

    void Cargar();
    void Mostrar();

    //bool escribirDisco(int pos);
    //bool leerDisco(int pos);
};

