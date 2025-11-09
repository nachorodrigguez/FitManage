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

    public:
        Plan(int id = 0, const char* tip = "", const char* per = "", float pre = 0.0, int dur = 0);

        void setIdPlan(int id);
        void setDescripcion(const char* desc);
        void setTipoPlan(const char* tip);
        void setPeriodo(const char* per);
        void setPrecio(float pre);
        void setDuracion(int dur);

        int getIdPlan() const;
        const char* getTipo() const;
        const char* getDescripcion() const;
        const char* getPeriodo() const;
        float getPrecio() const;
        int getDuracion() const;

    void Cargar();
    void Mostrar() const;

} ;


