#pragma once
#include <string>
#include "socio.h"

class ArchivoSocios{
    private:
        std::string _nombreArchivo;

    public:
        ArchivoSocios(std::string nombreArchivo);
        bool Guardar(Socio socio);
        bool Guardar(const Socio& socio, int posicion);
        int Buscar(int idSocio);
        Socio Leer(int posicion);
        int CantidadRegistros();
        void Leer(int cantidadRegistros, Socio *vector);
        bool ModificarPorId(int idSocioBuscado, const Socio& socioNuevo);
        bool EliminarPorId(int idSocioBuscado);
};
