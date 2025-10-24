#pragma once
#include <string>

class Clase{
    private:
    char nombreClase[50];
    char descripcion[100];

    public:
    Clase();

    const char* getNombreClase();
    const char* getDescripcion();

    void setNombreclase(const char *);
    void setDescripcion (const char *);

    void Cargar();
    void Mostrar();

} ;
