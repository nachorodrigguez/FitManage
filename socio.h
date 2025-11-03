#pragma once
#include "fecha.h"
#include "persona.h"

class Socio : public Persona{
private:
    Persona persona;
    int idSocio;
    Fecha inscripcion;
    bool estado;

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

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
    void run();

    //bool escribirDisco(int pos);
    //bool leerDisco(int pos);
};

