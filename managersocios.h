#pragma once
#include "socio.h"

class ManagerSocios{
    public:
    ManagerSocios();
    void run();

    protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

    private:
    int _cantidadOpcines;
    Socio socio;

};
