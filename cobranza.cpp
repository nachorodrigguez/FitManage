#include <iostream>
#include <cstring>
#include "cobranza.h"

using namespace std;

Cobranza::Cobranza(){
    _numTransaccion = 0;
    _descuentos = 0;
    _montoTotal = 0;
    strcpy(_metodoPago, "Indefinido");
}

int Cobranza::getNumTransaccion(){
    return _numTransaccion;
}
Fecha Cobranza::getFechaTransaccion(){
    return _fechaTransaccion;
}
float Cobranza::getDescuentos(){
    return _descuentos;
}
float Cobranza::getMontoTotal(){
    return _montoTotal;
}
const char* Cobranza::getMetodoPago(){
    return _metodoPago;
}

void Cobranza::setNumTransaccion(int numTransaccion){
    _numTransaccion = numTransaccion;
}
void Cobranza::setFechaTransaccion(Fecha fechaTransaccion){
    _fechaTransaccion = fechaTransaccion;
}
void Cobranza::setDescuentos(float descuentos){
    _descuentos = descuentos;

    _montoTotal = _montoTotal - (_montoTotal *(_descuentos / 100));
}
void Cobranza::setMontoTotal(float montoTotal){
    _montoTotal = montoTotal;
}

void Cobranza::Cargar(){
        _numTransaccion++;
        float descuentos;

        cout << "Numero de transaccion: " << _numTransaccion << endl;
        cout << "Fecha de transaccion: ";
        _fechaTransaccion.Mostrar();

        cout << endl;
        cin.ignore();

        cout << "Metodo de pago: ";
        cin.getline(_metodoPago,50);

        cout << "Descuentos: ";
        cin >> descuentos;

        setDescuentos(descuentos);

        cout << "Monto total: " << _montoTotal << endl;
}

void Cobranza::Mostrar(){
    cout << "Transaccion N°: " << _numTransaccion << endl;
    cout << "Fecha: ";
    _fechaTransaccion.Mostrar();

    cout << "Descuento: " << _descuentos << "%" << endl;
    cout << "Monto total: $" << _montoTotal << endl;
    cout << "Metodo de pago: " << _metodoPago << endl;
}
