#pragma once
#include "clasexsocio.h"
#include <cstdio>
#include <cstring>

class ArchivoClasexSocio {
    char _path[64];
public:
    ArchivoClasexSocio(const char* p = "inscripciones.dat"){
        std::strncpy(_path, p, sizeof(_path));
        _path[sizeof(_path)-1] = '\0';
    }

    bool Guardar(const ClasexSocio& reg);
    bool Leer(int pos, ClasexSocio& reg) const;   // true si leyó
    ClasexSocio Leer(int pos) const;              // conveniencia
    bool Leer(int cant, ClasexSocio* vec) const;  // bloque

    int  CantidadRegistros() const;
    int  BuscarUltimoID() const;                  // máx _IDClasexSocio (0 si vacío)
    int  BuscarPorSocioYClase(int idSocio, int idClase) const; // pos o -1 (solo activas)
    bool Sobrescribir(int pos, const ClasexSocio& reg);
};
