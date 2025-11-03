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

    private:
    int _cantidadOpcines;
    Instructor ins;

};
