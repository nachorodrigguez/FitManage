#include "Fecha.h"
#include "ArchivoCobranzas.h"

ArchivoCobranzas::ArchivoCobranzas(std::string nombreArchivo)
{
    _nombreArchivo = nombreArchivo;
}

//Agregar pago al final del archivo
bool ArchivoCobranzas::Guardar(Cobranza cobranza)
{
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "ab");
    if(pArchivo == NULL)
    {
        return false;
    }
    bool ok = fwrite(&cobranza, sizeof(Cobranza), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

//Modificar pago existente
bool ArchivoCobranzas::Guardar(const Cobranza& cobranza, int posicion)
{
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb+");
    if(pArchivo == NULL)
    {
        return false;
    }

    // Verificar que la posicion sea valida
    int cantidad = CantidadRegistros();
    if (posicion < 0 || posicion >= cantidad)
    {
        fclose(pArchivo);
        return false;
    }

    fseek(pArchivo, sizeof(Cobranza) * posicion, SEEK_SET);
    //size_t porque fwrite devuelve cantidad y no booleano
    size_t registrosEscritos = fwrite(&cobranza, sizeof(Cobranza), 1, pArchivo);
    fclose(pArchivo);

    return (registrosEscritos == 1);
}

int ArchivoCobranzas::Buscar(int numTransaccion)
{
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL)
    {
        return -1;
    }
    Cobranza cobranza;
    int i = 0;
    while(fread(&cobranza, sizeof(Cobranza), 1, pArchivo))
    {
        if(cobranza.getNumTransaccion() == numTransaccion)
        {
            fclose(pArchivo);
            return i;
        }
        i++;
    }
    fclose(pArchivo);
    return -1;
}

Cobranza ArchivoCobranzas::Leer(int posicion)
{
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL)
    {
        return Cobranza();
    }
    Cobranza cobranza;
    fseek(pArchivo, sizeof(Cobranza) * posicion, SEEK_SET);
    fread(&cobranza, sizeof(Cobranza), 1, pArchivo);
    fclose(pArchivo);
    return cobranza;
}

int ArchivoCobranzas::CantidadRegistros()
{
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL)
    {
        return 0;
    }
    fseek(pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivo) / sizeof(Cobranza);
    fclose(pArchivo);
    return cantidadRegistros;
}

void ArchivoCobranzas::Leer(int cantidadRegistros, Cobranza *vector)
{
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL)
    {
        return;
    }
    for(int i = 0; i < cantidadRegistros; i++)
    {
        fread(&vector[i], sizeof(Cobranza), 1, pArchivo);
    }
    fclose(pArchivo);
}
