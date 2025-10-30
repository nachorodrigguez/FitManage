#pragma once
#include "ManagerInstructores.h"

class App{
    public:
    App();
    void run();

    protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

    ManagerInstructores managerIns;

    private:
    int _cantidadOpcines;

};
