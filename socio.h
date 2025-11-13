#pragma once
#include "fecha.h"
#include "persona.h"

class Socio : public Persona{
private:
    int idSocio;
    Fecha inscripcion;
    bool estado;
    char tipoPlan[50];

public:
    Socio();

    void setId(int);
    void setInscripcion(Fecha);
    void setEstado(bool);
    void setTipoPlan(const char*);

    int getId();
    Fecha getInscripcion();
    bool getEstado();
    const char* getTipoPlan() const;

    void Cargar(int idExistente = 0);
    void Mostrar();
    void Modificar();

    bool tienePlan() const {
        return strcmp(tipoPlan, "Sin asignar") != 0;
        }
};

