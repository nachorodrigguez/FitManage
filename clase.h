#pragma once
#include <string>
#include "instructor.h"

class Clase{
    private:
    int _IDClase;
    char nombreClase[50];
    char descripcion[100];
    int tiempoDuracion; // en minutos
    int capacidadMax; // cantidad de alumnos permitida

    public:
    Clase();

    int getIDClase();
    const char* getNombreClase();
    const char* getDescripcion();
    int getTiempoDuracion();
    int getCapacidadMax();

    void setidInstructor(Instructor);
    void setIDClase(int IDClase);
    void setNombreclase(const char *);
    void setDescripcion (const char *);
    void setTiempoDuracion(int tDur);
    void setCapacidadMax(int cMax);

    void Cargar();
    void Mostrar();

} ;


