#pragma once
#include "ManagerInstructores.h"
#include "managersocios.h"
#include "managerplanes.h"
#include "managerClases.h"
#include "managerCobranzas.h"
#include "ManagerReportes.h"
#include "rlutil.h"

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
    const int CENTER_X = 60;
    int _cantidadOpciones;

};
