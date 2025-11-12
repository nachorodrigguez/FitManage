#include "archivoClases.h"
#include <iostream>
using namespace std;

ArchivoClases::ArchivoClases(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

bool ArchivoClases::Guardar(Clase clase) {
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "ab");
    if (pArchivo == NULL) return false;

    bool ok = fwrite(&clase, sizeof(Clase), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

bool ArchivoClases::Guardar(const Clase& clase, int posicion) {
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb+");
    if (pArchivo == NULL) return false;

  fseek(pArchivo, sizeof(Clase) * posicion, SEEK_SET);
    size_t escritos = fwrite(&clase, sizeof(Clase), 1, pArchivo);
    fclose(pArchivo);

    return (escritos == 1);
}

Clase ArchivoClases::Leer(int posicion) {
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == NULL) return Clase();

    Clase clase;
    fseek(pArchivo, sizeof(Clase) * posicion, SEEK_SET);
    fread(&clase, sizeof(Clase), 1, pArchivo);
    fclose(pArchivo);
    return clase;
}

int ArchivoClases::CantidadRegistros() {
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == NULL) return 0;

    fseek(pArchivo, 0, SEEK_END);
    int cantidad = ftell(pArchivo) / sizeof(Clase);
    fclose(pArchivo);
    return cantidad;
}

void ArchivoClases::Listar() {
    int cantidad = CantidadRegistros();
    for (int i = 0; i < cantidad; i++) {
        Clase c = Leer(i);
        c.Mostrar();
        cout << "--------------------" << endl;
    }
}

bool ArchivoClases::LeerPorID(int id, Clase &clase) {
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == NULL) return false;

    Clase aux;
    while (fread(&aux, sizeof(Clase), 1, pArchivo)) {
        if (aux.getIDClase() == id) {
            clase = aux;
            fclose(pArchivo);
            return true;
        }
    }

    fclose(pArchivo);
    return false;
}
