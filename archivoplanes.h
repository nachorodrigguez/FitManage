#pragma once
#include <string>
#include "Plan.h"

class ArchivoPlanes {
    private:
        std::string _nombreArchivo;

    public:
        explicit ArchivoPlanes(std::string nombreArchivo);
        bool Guardar(Plan plan);
        bool Guardar(const Plan& plan, int posicion);
        int  Buscar(int idPlan);
        Plan Leer(int posicion);
        int  CantidadRegistros();
        void Leer(int cantidadRegistros, Plan* vector);
        bool ModificarPorId(int idPlanBuscado, const Plan& planNuevo);
        bool EliminarPorId(int idPlanBuscado);
};

