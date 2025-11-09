#pragma once
#include <string>

class Plan{
    private:
        static int ultimoID;
        int idPlan;
        char tipoPlan[50];         // Flex, Plus o Total
        char descripcion[50];
        char periodo[20];          // Mensual o Anual
        float precio;
        int duracionMeses;
        bool estado;

    public:
        //Constructor
        Plan(int id = 0, const char* tip = "", const char* per = "", float pre = 0.0, int dur = 0);

        //SETTERS
        void setIdPlan(int id);
        void setDescripcion(const char* desc);
        void setTipoPlan(const char* tip);
        void setPeriodo(const char* per);
        void setPrecio(float pre);
        void setDuracion(int dur);
        void setEstado(bool valor);

        //GETTERS
        int getIdPlan() const;
        const char* getTipo() const;
        const char* getDescripcion() const;
        const char* getPeriodo() const;
        float getPrecio() const;
        int getDuracion() const;
        bool getEstado() const;

        //FUNCIONES GENERALES
        void Cargar();
        void Mostrar() const;
        static void EstablecerUltimoId(int valor);
        static int ObtenerUltimoId();

} ;


