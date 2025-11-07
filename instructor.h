#pragma once
#include <string>
#include "Persona.h"

class Instructor: public Persona{
    private:
        int _idInstructor;
        char _especialidad[50];

    public:
        Instructor();

        int getidInstructor();
        const char* getEspecialidad();

        void setidInstructor(int);
        void setEspecialidad();

        void Cargar();
        void Mostrar();

} ;

