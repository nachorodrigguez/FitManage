#pragma once
#include "plan.h"
#include "archivoplanes.h"

class ManagerPlanes{
    private:
        int _cantidadOpciones;
        Plan plan;
        ArchivoPlanes archivoPlanes;

    protected:
        void mostrarOpciones();
        int seleccionOpcion();
        void ejecutarOpcion(int opcion);

    public:
        ManagerPlanes(std::string nombreArchivoPlanes);
        void run();

};
