#pragma once
#include <string>
//#include "Fecha.h"

class Socio{
    private:
    int idSocio;
    //Fecha fechaInscripcion;
    bool estado;

    public:
    Socio();

    int getidSocio();
    bool getEstado();

    //Fecha getInscripcion();

    void setidSocio(int);
    void setEstado(bool);
    //void setFechaInscripcion(Fecha);

    void Cargar();
    void Mostrar();

} ;
