#pragma once
#include "cobranza.h"

class ManagerCobranzas{
    public:
    ManagerCobranzas();
    void run();

    protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

    private:
    int _cantidadOpcines;
    Cobranza cobranza;
};
