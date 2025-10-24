#pragma once
#include <string>

class Instructor{
    private:
    int idInstructor;
    char especialidad[50];

    public:
    Instructor();

    int getidInstructor();
    const char* getEspecialidad();

    void setidInstructorint);
    void setEspecialidad(const char *);

    void Cargar();
    void Mostrar();

} ;
