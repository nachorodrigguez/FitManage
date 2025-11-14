#pragma once
#include "socio.h"
#include "archivoSocios.h"
#include "archivoplanes.h"

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
//----------------------------------------------------------------------
        void asignarPlanOClase();  // submenú Asignar plan/clase
        int  menuPlanes();         // 1) Plan 1, 2) Plan 2, 3) Plan 3, 0) Cancelar
        int  pedirIdSocio();       // leer/validar ID socio
        int  buscarPosSocioPorID(int idBuscado);

};

