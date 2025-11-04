#pragma once
#include "ManagerInstructores.h"
#include "socio.h"
#include "managersocios.h"
#include "managerPlanes.h"

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
    ManagerSocios managersocios;
    ManagerPlanes managerplanes;

    private:
    int _cantidadOpcines;

};
