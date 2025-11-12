#ifndef MANAGERCLASES_H_INCLUDED
#define MANAGERCLASES_H_INCLUDED

#include "clase.h"
#include "archivoClases.h"

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
};

#endif // MANAGERCLASES_H_INCLUDED
