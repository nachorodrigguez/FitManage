#pragma once
#include "socio.h"
#include "cobranza.h"
#include "archivoSocios.h"
#include "ArchivoCobranzas.h"

class ManagerCobranzas{
    public:
    ManagerCobranzas(std::string nombreArchivo);
    void run();

    protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

    private:
    int _cantidadOpcines;
    Socio socio;
    Cobranza cobranza;
    ArchivoCobranzas archivocobranzas;
    ArchivoSocios archivosocios;
};
