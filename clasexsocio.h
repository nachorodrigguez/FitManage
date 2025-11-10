#pragma once
#include "fecha.h"

class ClasexSocio{
private:
    int _IDClasexSocio;    // ID de la inscripcion (puede ser autonumerico desde el manager)
    int _idSocio;          // ID o DNI del socio
    int _IDClase;          // ID de la clase (1-7 segun Clase::Cargar)
    Fecha _fechaInscripcion;
    bool _estado;          // true = inscripto / false = baja de la inscripcion

public:
    ClasexSocio();

    // Getters
    int getIDClasexSocio() const;
    int getIdSocio() const;
    int getIDClase() const;
    Fecha getFechaInscripcion() const;
    bool getEstado() const;

    // Setters
    void setIDClasexSocio(int);
    void setIdSocio(int);
    void setIDClase(int);
    void setFechaInscripcion(const Fecha &);
    void setEstado(bool);

    void Cargar();      // pide datos para una nueva inscripcion
    void Mostrar() const; // muestra la inscripcion
};
