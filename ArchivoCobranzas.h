#pragma once
#include <string>
#include "cobranza.h"

class ArchivoCobranzas{
    private:
        std::string _nombreArchivo;

    public:
        ArchivoCobranzas(std::string nombreArchivo);
        bool Guardar(Cobranza cobranza);
        bool Guardar(const Cobranza& cobranza, int posicion);
        int Buscar(int numTransaccion);
        Cobranza Leer(int posicion);
        int CantidadRegistros();
        void Leer(int cantidadRegistros, Cobranza *vector);
};
