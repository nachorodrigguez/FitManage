#pragma once
#include "instructor.h"

class ManagerInstructores{
    public:
    ManagerInstructores();
    void run();

    protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

    Instructor instructor;

    private:
    int _cantidadOpcines;

};
