#pragma once
#include "ManagerInstructores.h"
#include "managersocios.h"
#include "managerPlanes.h"
#include "managerCobranzas.h"
#include "ManagerListados.h"

class App{
    public:
    App();
    void run();

    protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

    ManagerInstructores managerIns;
    ManagerSocios managersocios;
    ManagerPlanes managerplanes;
    ManagerCobranzas managercob;
    ManagerListados managerlis;
    private:
    int _cantidadOpcines;

};
