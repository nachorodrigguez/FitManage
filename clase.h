#pragma once
#include <string>

class Clase{
    private:
    char nombreClase[50];
    char descripcion[100];
    int tiempoDuracion; // en minutos
    int capacidadMax; // cantidad de alumnos permitida

    public:
    Clase();

    const char* getNombreClase();
    const char* getDescripcion();
    int getTiempoDuracion();
    int getCapacidadMax();

    void setNombreclase(const char *);
    void setDescripcion (const char *);
    void setTiempoDuracion(int);
    void setCapacidadMax(int);

    void Cargar();
    void Mostrar();

} ;

