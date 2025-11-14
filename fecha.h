#pragma once

class Fecha{
    private:
        int dia;
        int mes;
        int anio;
//helpers
static bool esBisiesto(int a);
static int diasDelMes(int m, int a);
static bool esValida(int d, int m, int a);

    public:
        //constructor
        Fecha();
        Fecha(int d, int m, int a);

        int getDia() const;
        int getMes() const;
        int getAnio() const;

        static Fecha FechaActual();
        void setDia(int d);
        void setMes(int m);
        void setAnio(int a);

        void Cargar();
        void Mostrar() const;
};



