#include <cstdio>
#include "archivoplanes.h"

ArchivoPlanes::ArchivoPlanes(std::string nombreArchivo)
{
    _nombreArchivo = nombreArchivo;
}

//Agregar nuevo plan al final del archivo
bool ArchivoPlanes::Guardar(Plan plan)
{
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "ab");
    if (pArchivo == NULL) {
        return false;
    }
    size_t registrosEscritos = fwrite(&plan, sizeof(Plan), 1, pArchivo);
    fclose(pArchivo);
    return (registrosEscritos == 1);
}

//Modificar plan existente
bool ArchivoPlanes::Guardar(const Plan& plan, int posicion)
{
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb+");
    if (pArchivo == NULL) {
        return false;
    }

    // Verificar que la posicion sea valida
    int cantidad = CantidadRegistros();
    if (posicion < 0 || posicion >= cantidad)
    {
        fclose(pArchivo);
        return false;
    }

    fseek(pArchivo, sizeof(Plan) * posicion, SEEK_SET);
    //size_t porque fwrite devuelve cantidad y no booleano
    size_t registrosEscritos = fwrite(&plan, sizeof(Plan), 1, pArchivo);
    fclose(pArchivo);

    return (registrosEscritos == 1);
}

int ArchivoPlanes::Buscar(int idPlan)
{
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == NULL) {
        return -1;
    }

    Plan plan;
    int i = 0;
    while (fread(&plan, sizeof(Plan), 1, pArchivo) == 1) {
        if (plan.getIdPlan() == idPlan) {
            fclose(pArchivo);
            return i;
        }
        i++;
    }
    fclose(pArchivo);
    return -1;
}

Plan ArchivoPlanes::Leer(int posicion)
{
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == NULL) {
        return Plan();
    }

    int cantidad = CantidadRegistros();
    if (posicion < 0 || posicion >= cantidad) {
        fclose(pArchivo);
        return Plan();
    }

    Plan plan;
    fseek(pArchivo, sizeof(Plan) * posicion, SEEK_SET);
    size_t leidos = fread(&plan, sizeof(Plan), 1, pArchivo);
    fclose(pArchivo);

    if (leidos != 1) return Plan();
    return plan;
}

void ArchivoPlanes::Leer(int cantidadRegistros, Plan* vector)
{
    if (cantidadRegistros <= 0 || vector == nullptr) return;

    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == NULL) return;

    for (int i = 0; i < cantidadRegistros; i++) {
        size_t leidos = fread(&vector[i], sizeof(Plan), 1, pArchivo);
        if (leidos != 1) break;
    }
    fclose(pArchivo);
}

bool ArchivoPlanes::ModificarPorId(int idPlanBuscado, const Plan& planNuevo)
{
    int posicion = Buscar(idPlanBuscado);
    if (posicion < 0) return false;
    return Guardar(planNuevo, posicion);
}

int ArchivoPlanes::CantidadRegistros() {
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == NULL) {
        return 0;
    }

    fseek(pArchivo, 0, SEEK_END);           // Mover al final del archivo
    int cantidadRegistros = ftell(pArchivo) / sizeof(Plan); // Calcular cantidad
    fclose(pArchivo);

    return cantidadRegistros;
}

bool ArchivoPlanes::EliminarPorId(int idPlanBuscado) {
    int posicion = Buscar(idPlanBuscado);
    if (posicion < 0) {
        return false;
    }

    Plan plan = Leer(posicion);
    plan.setEstado(false);  // baja lógica: marcar como inactivo

    return Guardar(plan, posicion);
}
