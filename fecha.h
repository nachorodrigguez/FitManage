#pragma once
#include <string>

class Fecha{
    private:
        int _dia;
        int _mes;
        int _anio;

    public:
        Fecha(int dia=1, int mes=1, int anio=1900);

        void setDia(int);
        void setMes(int);
        void setAnio(int);

        int getDia();
        int getMes();
        int getAnio();

        void Cargar();
        void Mostrar();
};

#endif 
