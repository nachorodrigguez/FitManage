#pragma once
#include "instructor.h"
#include "archivoInstructores.h"

class ManagerInstructores{
    public:
        ManagerInstructores(std::string nombreArchivoInstructores);
        void run();

    protected:
        void mostrarOpciones();
        int seleccionOpcion();
        void ejecutarOpcion(int opcion);

    private:
        int _cantidadOpciones;
        Instructor ins;
        ArchivoInstructores archivoInstructores;

};
