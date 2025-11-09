#pragma once
#include "socio.h"
#include "archivoSocios.h"

class ManagerSocios{
    public:
    ManagerSocios(std::string nombreArchivo);
    void run();

    protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

    private:
    int _cantidadOpcines;
    Socio socio;
    ArchivoSocios archivoSocios;

};
