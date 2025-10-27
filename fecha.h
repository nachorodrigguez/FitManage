#pragma once
#include <string>

class Fecha{
    private:
        int _dia;
        int _mes;
        int _anio;

    public:
        Fecha(int dia=1, int mes=1, int anio=2000);

        int getDia();
        int getMes();
        int getAnio();

        void setDia(int);
        void setMes(int);
        void setAnio(int);

        void Cargar();
        void Mostrar();
};
