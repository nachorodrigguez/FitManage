#pragma once
#include <string>
#include "Persona.h"

class Instructor: public Persona{
    private:
        int _idInstructor;
        char _especialidad[50];
        bool estado;
        int idClaseAsignada;

    public:
        //CONSTRUCTORES
        Instructor();

        //GETTERS
        int getidInstructor();
        const char* getEspecialidad();
        bool getEstado() const;
        int getIdClaseAsignada() const;

        //SETTERS
        void setId(int);
        void setidInstructor(int);
        void setEspecialidad();
        void setEstado(bool valor);
        void setIdClaseAsignada(int idClase);

        //FUNCIONES GENERALES
        void Cargar(int idInstructor);
        void Mostrar();
        void Modificar();
} ;



