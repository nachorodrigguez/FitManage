#pragma once
#include "ManagerInstructores.h"
#include "managersocios.h"
#include "managerplanes.h"
#include "managerCobranzas.h"
#include "Managerlistados.h"

class App{
    public:
    App();
    void run();

    protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

    ManagerSocios managersocios;
    ManagerPlanes managerplanes;
    ManagerInstructores managerinstructores;
    ManagerCobranzas managercob;
    ManagerListados managerlis;

    private:
    int _cantidadOpciones;

};
