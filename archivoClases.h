#ifndef ARCHIVOCLASES_H_INCLUDED
#define ARCHIVOCLASES_H_INCLUDED

#include <string>
#include "clase.h"

class ArchivoClases {
private:
    std::string _nombreArchivo;

public:
    ArchivoClases(std::string nombreArchivo);
    bool Guardar(Clase clase);
    bool Guardar(const Clase& clase, int posicion);
    int Buscar(int idClase);
    Clase Leer(int posicion);
    int CantidadRegistros();
    void Leer(int cantidadRegistros, Clase* vector);
    void Listar();
    bool LeerPorID (int, Clase &clase);
};


#endif // ARCHIVOCLASES_H_INCLUDED
