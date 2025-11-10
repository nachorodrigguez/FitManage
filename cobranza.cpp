#include <iostream>
#include <cstring>
#include "cobranza.h"

using namespace std;

Cobranza::Cobranza(){
    _dniSocio = 0;
    _numTransaccion = 0;
    _descuentos = 0;
    _montoTotal = 0;
    strcpy(_metodoPago, "Indefinido");
}

int Cobranza::getDniSocio(){
    return _dniSocio;
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

void Cobranza::setDniSocio(int dni){
    _dniSocio = dni;
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

void Cobranza::setMetodoPago(){
    int opcion;
    cout << "METODO DE PAGO" << endl;
    cout << "======================" << endl;
    cout << "1 - EFECTIVO" << endl;
    cout << "2 - TRANSFERENCIA" << endl;
    cout << "3 - TARJETA CREDITO" << endl;
    cout << "======================" << endl;

    cout << "Opcion: ";
    cin >> opcion;

    while (opcion < 0 || opcion > 3){
        cout << "Opcion incorrecta..." << endl;
        cout << "Opcion: " ;
        cin >> opcion;
    }

    switch(opcion){
        case 1: {
            strcpy(_metodoPago, "Efectivo");
            break;
        }
        case 2:{
            strcpy(_metodoPago, "Transferencia");
            break;
        }
        case 3:{
            strcpy(_metodoPago, "Tarjeta Credito");
            break;
        }
    }
}

void Cobranza::Cargar(){
        _numTransaccion++;
        float descuentos;
        cout << "Numero de transaccion: " << _numTransaccion << endl;
        cout << "Fecha de transaccion: ";
        _fechaTransaccion.Mostrar();

        cout << endl;

        setMetodoPago();

        cout << "Descuentos: ";
        cin >> descuentos;

        setDescuentos(descuentos);

        cout << "Monto total: " << _montoTotal << endl;
}

void Cobranza::Mostrar(){
    cout << "=======================" << endl;
    cout << "FACTURA"<< endl;
    cout << "=======================" << endl;
    cout << "CLIENTE: " << _dniSocio << endl;
    cout << "Transaccion N°: " << _numTransaccion << endl;
    cout << "Fecha: ";
    _fechaTransaccion.Mostrar();
    cout << endl;
    cout << "Descuento: " << _descuentos << "%" << endl;
    cout << "Monto total: $" << _montoTotal << endl;
    cout << "Metodo de pago: " << _metodoPago << endl;
}
