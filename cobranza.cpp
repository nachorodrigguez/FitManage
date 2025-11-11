#include <iostream>
#include <cstring>
#include "cobranza.h"

using namespace std;

Cobranza::Cobranza(){
    _dniSocio = 0;
    _numTransaccion = 0;
    strcpy(_plan, "Indefinido");
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
const char* Cobranza::getPlan(){
    return _plan;
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
void Cobranza::setMontoTotal(){
    if(strcmp(_plan, "FLEX MENSUAL") == 0){
        _montoTotal = 44000;
    }
    else if (strcmp(_plan, "FLEX ANUAL") == 0){
        _montoTotal = 528000;
    }
    else if (strcmp(_plan, "PLUS MENSUAL") == 0){
        _montoTotal = 68000;
    }
    else if (strcmp(_plan, "PLUS ANUAL") == 0){
        _montoTotal = 816000;
    }
    else if (strcmp(_plan, "TOTAL MENSUAL") == 0){
        _montoTotal = 80000;
    }
    else if (strcmp(_plan, "TOTAL ANUAL") == 0){
        _montoTotal = 960000;
    }
    else{
        _montoTotal = 0;
    }
}

void Cobranza::setPlan(){
    int opcion;
    cout << "PLAN" << endl;
    cout << "======================" << endl;
    cout << "1 - FLEX" << endl;
    cout << "2 - PLUS" << endl;
    cout << "3 - TOTAL" << endl;
    cout << "======================" << endl;

    cout << "Opcion: ";
    cin >> opcion;

    while (opcion < 0 || opcion >3){
        cout << "Opcion incorrecta..." << endl;
        cout << "Opcion: ";
        cin >> opcion;
    }
    switch(opcion){
        case 1: {
            cout << "======================" << endl;
            cout << "1 - MENSUAL" << endl;
            cout << "2 - ANUAL" << endl;
            cout << "======================" << endl;

            cout << "Opcion: ";
            cin >> opcion;
            while (opcion < 0 || opcion >3){
                cout << "Opcion incorrecta..." << endl;
                cout << "Opcion: ";
                cin >> opcion;
                }
            switch(opcion){
                case 1:{
                    strcpy(_plan,"FLEX MENSUAL");
                    break;
                }
                case 2:{
                    strcpy(_plan, "FLEX ANUAL");
                    break;
                }
            }
            break;
        }
        case 2:{
            cout << "======================" << endl;
            cout << "1 - MENSUAL" << endl;
            cout << "2 - ANUAL" << endl;
            cout << "======================" << endl;

            cout << "Opcion: ";
            cin >> opcion;
            while (opcion < 0 || opcion >3){
                cout << "Opcion incorrecta..." << endl;
                cout << "Opcion: ";
                cin >> opcion;
                }
            switch(opcion){
                case 1:{
                    strcpy(_plan,"PLUS MENSUAL");
                    break;
                }
                case 2:{
                    strcpy(_plan, "PLUS ANUAL");
                    break;
                }
            }
            break;
        }
        case 3:{
            cout << "======================" << endl;
            cout << "1 - MENSUAL" << endl;
            cout << "2 - ANUAL" << endl;
            cout << "======================" << endl;

            cout << "Opcion: ";
            cin >> opcion;
            while (opcion < 0 || opcion >3){
                cout << "Opcion incorrecta..." << endl;
                cout << "Opcion: ";
                cin >> opcion;
                }
            switch(opcion){
                case 1:{
                    strcpy(_plan,"TOTAL MENSUAL");
                    break;
                }
                case 2:{
                    strcpy(_plan, "TOTAL ANUAL");
                    break;
                }
            }
            break;
        }
    }
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
        cout << "Numero de transaccion: " << _numTransaccion << endl;
        cout << "Fecha de transaccion: ";
        _fechaTransaccion.Mostrar();

        cout << endl;

        setPlan();

        cout << endl;

        setMetodoPago();

        setMontoTotal();
        cout << "¿Desea aplicar un descuento? (S/N): ";
        char respuesta;
        cin >> respuesta;

        if(respuesta == 'S' || respuesta == 's'){
            float descuentos;
            cout << "Ingrese descuento: ";
            cin >> descuentos;
            setDescuentos(descuentos);

            getMontoTotal();
        }
        Mostrar();
}

void Cobranza::Mostrar(){
    cout << "==========================" << endl;
    cout << "FACTURA"<< endl;
    cout << "==========================" << endl;
    cout << "CLIENTE: " << _dniSocio << endl;
    cout << "Transaccion N°: " << _numTransaccion << endl;
    cout << "Fecha: ";
    _fechaTransaccion.Mostrar();
    cout << endl;
    cout << "PLAN: " << _plan << endl;
    cout << "--------------------------" << endl;
    if(_descuentos != 0){
        cout << "Descuento: " << _descuentos << "%" << endl;
    }
    cout << "Monto total: $" << _montoTotal << endl;
    cout << "Metodo de pago: " << _metodoPago << endl;
    cout << "==========================" << endl;
}
