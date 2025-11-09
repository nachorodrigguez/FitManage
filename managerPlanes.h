#pragma once
#include "plan.h"
#include "archivoplanes.h"

class ManagerPlanes{
    public:
        ManagerPlanes(std::string nombreArchivoPlanes);
        void run();

    protected:
        void mostrarOpciones();
        int seleccionOpcion();
        void ejecutarOpcion(int opcion);

    private:
        int _cantidadOpciones;
        Plan plan;
        ArchivoPlanes archivoPlanes;

};
