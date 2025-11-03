#pragma once
#include "ManagerInstructores.h"
#include "socio.h"

class App{
    public:
    App();
    void run();

    protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

    ManagerInstructores managerIns;
    Socio socio;

    private:
    int _cantidadOpcines;

};
