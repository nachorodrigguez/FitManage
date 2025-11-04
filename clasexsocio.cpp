#pragma once
#include <cstring>
#include "clasexsocio.h"

using namespace std;

ClasexSocio::ClasexSocio(){
    _IDClasexSocio = 0;
}
int ClasexSocio::getIDClasexSocio(){
    return _IDClasexSocio;
}

Clase ClasexSocio::getIDClase(){
    return _IDClase;
}

Socio ClasexSocio::getId(){
    return _idSocio;
}

Fecha ClasexSocio::getFechaInscripcion(){
    return _fechaInscripcion;
}

void ClasexSocio::setIDClasexSocios(int ID){
    _IDClasexSocio = ID;
}

void ClasexSocio::setIDClase(Clase clase){
    _IDClase = clase;
}

void ClasexSocio::setidSocio(Socio socio){
    _idSocio = socio;
}

void ClasexSocio::setFechaInscripcion(Fecha fecha){
    _fechaInscripcion = fecha;
}

void Cargar(){

}

void Mostrar();
