#pragma once
#include <string>
#include "fecha.h"


class Cobranza{
    private:
    int _dniSocio;
    int _numTransaccion;
    Fecha _fechaTransaccion;
    float _descuentos;
    float _montoTotal;
    char _metodoPago[50];

    public:
    Cobranza();

    int getDniSocio();
    int getNumTransaccion();
    Fecha getFechaTransaccion();
    float getDescuentos();
    float getMontoTotal();
    const char* getMetodoPago();

    void setDniSocio(int);
    void setNumTransaccion(int);
    void setFechaTransaccion(Fecha);
    void setDescuentos(float);
    void setMontoTotal(float);
    void setMetodoPago();

    void Cargar();
    void Mostrar();
};
