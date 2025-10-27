#include <iostream>
#include <cstring>
#include  "Fecha.h"

using namespace std;

Fecha::Fecha(int dia, int mes, int anio){
    _dia = dia;
    _mes = mes;
    _anio = anio;
}

void Fecha::setDia(int dia){
    _dia = dia;
}

void Fecha::setMes(int mes){
    _mes = mes;
}

void Fecha::setAnio(int anio){
    _anio = anio;
}

int Fecha::getDia(){
    return _dia;
}

int Fecha::getMes(){
    return _mes;
}

int Fecha::getAnio(){
    return _anio;
}

void Fecha::Cargar(){
    cout << "Dia: ";
    cin >> _dia;

    cout << "Mes: ";
    cin >> _mes;

    cout << "Anio: ";
    cin >> _anio;
}

void Fecha::Mostrar(){
    cout << _dia << "/" << _mes << "/" <<_anio;
}
