#pragma once
#include <string>

class ClasexSocio{
    private:
    char nombreClase[50];
    char descripcion[50];
    int tiempoDuracion;
    int capacidadMax;

    public:
    ClasexSocio();

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
