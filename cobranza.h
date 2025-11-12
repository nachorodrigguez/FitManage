#pragma once
#include <string>
#include "fecha.h"
#include "archivoplanes.h"

class Cobranza{
    private:
    int _dniSocio;
    int _numTransaccion;
    int _idPlan;
    char _plan[50];
    Fecha _fechaTransaccion;
    float _descuentos;
    float _montoTotal;
    char _metodoPago[50];

    public:
    Cobranza();

    int getDniSocio();
    int getNumTransaccion();
    int getIdPlan();
    const char* getPlan();
    Fecha getFechaTransaccion();
    float getDescuentos();
    float getMontoTotal();
    const char* getMetodoPago();

    void setDniSocio(int);
    void setNumTransaccion(int);
    void setIdPlan(int);
    void setPlan();
    void setFechaTransaccion(Fecha);
    void setDescuentos(float);
    void setMontoTotal(int);
    void setMetodoPago();


    void Cargar();
    void Mostrar();
};
