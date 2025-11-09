#include "archivoInstructores.h"
#include <cstdio>

ArchivoInstructores::ArchivoInstructores(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

bool ArchivoInstructores::Guardar(Instructor instructor) {
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "ab");
    if (pArchivo == NULL) return false;

    size_t escritos = fwrite(&instructor, sizeof(Instructor), 1, pArchivo);
    fclose(pArchivo);
    return (escritos == 1);
}

bool ArchivoInstructores::Guardar(const Instructor& instructor, int posicion) {
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb+");
    if (pArchivo == NULL) return false;

    int cantidad = CantidadRegistros();
    if (posicion < 0 || posicion >= cantidad) {
        fclose(pArchivo);
        return false;
    }

    fseek(pArchivo, sizeof(Instructor) * posicion, SEEK_SET);
    size_t escritos = fwrite(&instructor, sizeof(Instructor), 1, pArchivo);
    fclose(pArchivo);
    return (escritos == 1);
}

int ArchivoInstructores::Buscar(int idInstructor) {
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == NULL) return -1;

    Instructor instructor;
    int i = 0;
    while (fread(&instructor, sizeof(Instructor), 1, pArchivo) == 1) {
        if (instructor.getidInstructor() == idInstructor) {  // usa tu método exacto
            fclose(pArchivo);
            return i;
        }
        i++;
    }

    fclose(pArchivo);
    return -1;
}

Instructor ArchivoInstructores::Leer(int posicion) {
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == NULL) return Instructor();

    Instructor instructor;
    fseek(pArchivo, sizeof(Instructor) * posicion, SEEK_SET);
    fread(&instructor, sizeof(Instructor), 1, pArchivo);
    fclose(pArchivo);

    return instructor;
}

int ArchivoInstructores::CantidadRegistros() {
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == NULL) return 0;

    fseek(pArchivo, 0, SEEK_END);
    int cantidad = ftell(pArchivo) / sizeof(Instructor);
    fclose(pArchivo);
    return cantidad;
}

void ArchivoInstructores::Leer(int cantidadRegistros, Instructor* vector) {
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == NULL) return;

    for (int i = 0; i < cantidadRegistros; i++) {
        fread(&vector[i], sizeof(Instructor), 1, pArchivo);
    }

    fclose(pArchivo);
}

bool ArchivoInstructores::ModificarPorId(int idInstructorBuscado, const Instructor& instructorNuevo) {
    int posicion = Buscar(idInstructorBuscado);
    if (posicion < 0) return false;
    return Guardar(instructorNuevo, posicion);
}

bool ArchivoInstructores::EliminarPorId(int idInstructorBuscado) {
    int posicion = Buscar(idInstructorBuscado);
    if (posicion < 0) return false;

    // Como Instructor no tiene campo de estado, eliminamos físicamente:
    int cantidad = CantidadRegistros();
    Instructor* vector = new Instructor[cantidad];
    Leer(cantidad, vector);

    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "wb");
    if (pArchivo == NULL) {
        delete[] vector;
        return false;
    }

    for (int i = 0; i < cantidad; i++) {
        if (i != posicion) {
            fwrite(&vector[i], sizeof(Instructor), 1, pArchivo);
        }
    }

    fclose(pArchivo);
    delete[] vector;
    return true;
}
