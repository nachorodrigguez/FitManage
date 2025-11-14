#pragma once
#include "clase.h"
#include "archivoClases.h"
#include "archivoClasexSocio.h"
#include "socio.h"
#include "archivoSocios.h"
#include "clasexsocio.h"

using namespace std;

class ManagerClases {
public:
    ManagerClases(string nombreArchivo);
    void run();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

private:
    int _cantidadOpciones;
    Clase clase;
    ArchivoClases archivoClases;
    ArchivoClasexSocio archivoclasesxsocio;
    Socio socio;
    ArchivoSocios archivosocios;
    ClasexSocio clasexsocio;
};
