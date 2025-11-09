#pragma once
#include "fecha.h"
#include "persona.h"

class Socio : public Persona{
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
    void Modificar();
};

