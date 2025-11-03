#pragma once
#include <cstring>

#include "fecha.h"

class Persona{
    private:
    char nombre[50];
    char apellido[50];
    char domicilio[50];
    char telefono[15];
    Fecha fechaNacimiento;

    public:
    Persona();

    const char* getNombre();
    const char* getApellido();
    const char* getDomicilio();
    const char* getTelefono();
    Fecha getFechaNacimiento();

    void setNombre(const char *);
    void setApellido(const char *);
    void setDomicilio(const char *);
    void setTelefono(const char *);
    void setFechaNacimiento(Fecha);

    void Cargar();
    void Mostrar();
} ;

