#pragma once
#include <string>

class Plan{
    private:
    int idPlan;
    float precio;
    char descripcion[50];
    char tipoPlan[50];

    public:
    Plan();

    int getIdPlan();
    float getPrecio();
    const char* getDescripcion();
    const char* getTipoPlan();

    void setIdPlan(int);
    void setPrecio(float);
    void setDescripcion (const char *);
    void setTipoPlan(const char *);

    void Cargar();
    void Mostrar();

} ;
