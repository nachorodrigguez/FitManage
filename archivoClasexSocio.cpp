#include "archivoClasexSocio.h"

bool ArchivoClasexSocio::Guardar(const ClasexSocio& reg){
    FILE* f = std::fopen(_path, "ab");
    if(f == nullptr) return false;
    bool ok = std::fwrite(&reg, sizeof(ClasexSocio), 1, f) == 1;
    std::fclose(f);
    return ok;
}

bool ArchivoClasexSocio::Leer(int pos, ClasexSocio& reg) const{
    FILE* f = std::fopen(_path, "rb");
    if(f == nullptr) return false;
    std::fseek(f, pos * (int)sizeof(ClasexSocio), SEEK_SET);
    bool ok = std::fread(&reg, sizeof(ClasexSocio), 1, f) == 1;
    std::fclose(f);
    return ok;
}

ClasexSocio ArchivoClasexSocio::Leer(int pos) const{
    ClasexSocio reg;
    Leer(pos, reg);
    return reg;
}

bool ArchivoClasexSocio::Leer(int cant, ClasexSocio* vec) const{
    FILE* f = std::fopen(_path, "rb");
    if(f == nullptr) return false;
    bool ok = std::fread(vec, sizeof(ClasexSocio), cant, f) == (size_t)cant;
    std::fclose(f);
    return ok;
}

int ArchivoClasexSocio::CantidadRegistros() const{
    FILE* f = std::fopen(_path, "rb");
    if(f == nullptr) return 0;
    std::fseek(f, 0, SEEK_END);
    long bytes = std::ftell(f);
    std::fclose(f);
    return (int)(bytes / sizeof(ClasexSocio));
}

int ArchivoClasexSocio::BuscarUltimoID() const{
    int n = CantidadRegistros();
    if(n <= 0) return 0;
    ClasexSocio reg;
    int maxId = 0;
    for(int i=0; i<n; i++){
        if(Leer(i, reg)){
            if(reg.getIDClasexSocio() > maxId) maxId = reg.getIDClasexSocio();
        }
    }
    return maxId;
}

int ArchivoClasexSocio::BuscarPorSocioYClase(int idSocio, int idClase) const{
    int n = CantidadRegistros();
    ClasexSocio reg;
    for(int i=0; i<n; i++){
        if(Leer(i, reg)){
            if(reg.getIdSocio() == idSocio && reg.getIDClase() == idClase && reg.getEstado()){
                return i;
            }
        }
    }
    return -1;
}

bool ArchivoClasexSocio::Sobrescribir(int pos, const ClasexSocio& reg){
    FILE* f = std::fopen(_path, "rb+");
    if(f == nullptr) return false;
    std::fseek(f, pos * (int)sizeof(ClasexSocio), SEEK_SET);
    bool ok = std::fwrite(&reg, sizeof(ClasexSocio), 1, f) == 1;
    std::fclose(f);
    return ok;
}
