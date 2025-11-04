#pragma once
#include <string>
#include "Fecha.h"
#include "clase.h"
#include "socio.h"

class ClasexSocio{
    private:
    int _IDClasexSocio;
    Clase _IDClase;
    Socio _idSocio;
    Fecha _fechaInscripcion;

    public:
    ClasexSocio();

    int getIDClasexSocio();
    Clase getIDClase();
    Socio getId();
    Fecha getFechaInscripcion();

    void setIDClasexSocios(int);
    void setIDClase(Clase);
    void setidSocio(Socio);
    void setFechaInscripcion(Fecha);

    void Cargar();
    void Mostrar();
} ;
