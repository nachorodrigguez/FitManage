#pragma once
#include "plan.h"

class ManagerPlanes{
    public:
    ManagerPlanes();
    void run();

    protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

    private:
    int _cantidadOpcines;
    Plan plan;

};
