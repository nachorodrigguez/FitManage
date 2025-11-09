#include "Fecha.h"
#include "ArchivoSocios.h"

ArchivoSocios::ArchivoSocios(std::string nombreArchivo)
{
    _nombreArchivo = nombreArchivo;
}

//Agregar nuevo socio al final del archivo
bool ArchivoSocios::Guardar(Socio socio)
{
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "ab");
    if(pArchivo == NULL)
    {
        return false;
    }
    bool ok = fwrite(&socio, sizeof(Socio), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

//Modificar socio existente
bool ArchivoSocios::Guardar(const Socio& socio, int posicion)
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

    fseek(pArchivo, sizeof(Socio) * posicion, SEEK_SET);
    //size_t porque fwrite devuelve cantidad y no booleano
    size_t registrosEscritos = fwrite(&socio, sizeof(Socio), 1, pArchivo);
    fclose(pArchivo);

    return (registrosEscritos == 1);
}

int ArchivoSocios::Buscar(int idSocio)
{
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL)
    {
        return -1;
    }
    Socio socio;
    int i = 0;
    while(fread(&socio, sizeof(Socio), 1, pArchivo))
    {
        if(socio.getId() == idSocio)
        {
            fclose(pArchivo);
            return i;
        }
        i++;
    }
    fclose(pArchivo);
    return -1;
}

Socio ArchivoSocios::Leer(int posicion)
{
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL)
    {
        return Socio();
    }
    Socio socio;
    fseek(pArchivo, sizeof(Socio) * posicion, SEEK_SET);
    fread(&socio, sizeof(Socio), 1, pArchivo);
    fclose(pArchivo);
    return socio;
}

int ArchivoSocios::CantidadRegistros()
{
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL)
    {
        return 0;
    }
    fseek(pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivo) / sizeof(Socio);
    fclose(pArchivo);
    return cantidadRegistros;
}

void ArchivoSocios::Leer(int cantidadRegistros, Socio *vector)
{
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL)
    {
        return;
    }
    for(int i = 0; i < cantidadRegistros; i++)
    {
        fread(&vector[i], sizeof(Socio), 1, pArchivo);
    }
    fclose(pArchivo);
}

bool ArchivoSocios::ModificarPorId(int idSocioBuscado, const Socio& socioNuevo)
{
    int posicion = Buscar(idSocioBuscado);
    if (posicion < 0)
    {
        return false; // No se encontro el socio
    }

    return Guardar(socioNuevo, posicion);
}

bool ArchivoSocios::EliminarPorId(int idSocioBuscado)
{
    int posicion = Buscar(idSocioBuscado);
    if (posicion < 0)
    {
        return false;
    }

    Socio socio = Leer(posicion);
    socio.setEstado(false); // baja logica

    return Guardar(socio, posicion);
}
