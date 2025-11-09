#pragma once
#include <string>
#include "instructor.h"

class ArchivoInstructores {
    private:
        std::string _nombreArchivo;

    public:
        ArchivoInstructores(std::string nombreArchivo);

        bool Guardar(Instructor instructor);                  // agrega al final
        bool Guardar(const Instructor& instructor, int posicion); // guarda por posición

        int  Buscar(int idInstructor);                        // busca por ID
        Instructor Leer(int posicion);                        // lee un registro
        int  CantidadRegistros();                             // total de registros
        void Leer(int cantidadRegistros, Instructor* vector); // lee varios registros

        bool ModificarPorId(int idInstructorBuscado, const Instructor& instructorNuevo);
        bool EliminarPorId(int idInstructorBuscado);           // eliminación física (sin estado)
};
