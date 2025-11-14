#include <iostream>
#include <cstring>
#include "cobranza.h"
#include "archivoplanes.h"

using namespace std;

Cobranza::Cobranza(){
    _dniSocio = 0;
    _numTransaccion = 0;
    _idPlan = 0;
    strcpy(_plan, "Indefinido");
    _fechaTransaccion = Fecha::FechaActual();
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
int Cobranza::getIdPlan(){
    return _idPlan;
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
void Cobranza::setIdPlan(int id){
    _idPlan = id;
}
void Cobranza::setFechaTransaccion(Fecha fechaTransaccion){
    _fechaTransaccion = fechaTransaccion;
}
void Cobranza::setDescuentos(float descuentos){
    _descuentos = descuentos;

    _montoTotal = _montoTotal - (_montoTotal *(_descuentos / 100));
}
void Cobranza::setMontoTotal(int id){
    ArchivoPlanes archPlanes("planes.dat");
    int posicion = archPlanes.Buscar(id);

    if (posicion == -1){
        cout << "Error: Plan no encontrado en el archivo." << endl;
        _montoTotal = 0;
        return;
    }
    Plan plan = archPlanes.Leer(posicion);

    _montoTotal = plan.getPrecio();
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
                    int id = 1;
                    setMontoTotal(id);
                    strcpy(_plan,"FLEX MENSUAL");
                    break;
                }
                case 2:{
                    int id = 2;
                    setMontoTotal(id);
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
                    int id = 3;
                    setMontoTotal(id);
                    strcpy(_plan,"PLUS MENSUAL");
                    break;
                }
                case 2:{
                    int id = 4;
                    setMontoTotal(id);
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
                    int id = 5;
                    setMontoTotal(id);
                    strcpy(_plan,"TOTAL MENSUAL");
                    break;
                }
                case 2:{
                    int id = 6;
                    setMontoTotal(id);
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

        cout << "¿Desea aplicar un descuento? (S/N): ";
        char respuesta;
        cin >> respuesta;

        if(respuesta == 'S' || respuesta == 's'){
            float descuentos;
            cout << "Ingrese descuento: ";
            cin >> descuentos;
            setDescuentos(descuentos);
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
