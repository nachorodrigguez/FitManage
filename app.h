#pragma once
#include "ManagerInstructores.h"
#include "managersocios.h"
#include "managerplanes.h"
#include "managerClases.h"
#include "managerCobranzas.h"
#include "ManagerReportes.h"

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
    ManagerClases managerclases;
    ManagerCobranzas managercob;
    ManagerReportes managerrep;

    private:
    int _cantidadOpciones;

};
