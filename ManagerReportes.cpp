#include <iostream>
#include <iomanip>
#include "ManagerReportes.h"
#include "ArchivoCobranzas.h"
#include "cobranza.h"


using namespace std;

ManagerReportes::ManagerReportes(std::string nombreArchivoCobranzas){
    _cantidadOpciones = 4;
}

void ManagerReportes::run(){
    int opcion;
    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
    }while(opcion!=0);
}

void ManagerReportes::mostrarOpciones(){
       cout << "MENU PRINCIPAL"<<endl;
        cout << "====================="<< endl;
        cout << "1 - RECAUDACION ANUAL Y MENSUAL" << endl;
        cout << "2 - SOCIOS ACTIVOS POR PLAN" << endl;
        cout << "3 - CLASES MAS DEMANDADAS" << endl;
        cout << "4 - PAGOS PENDIENTES O ATRASADOS" << endl;
        cout << "0 - SALIR"<< endl;
        cout << "======================"<< endl;
}


int ManagerReportes::seleccionOpcion(){
    int opcion;
    mostrarOpciones();
    cout << "Opcion: ";
    cin >> opcion;

    while (opcion < 0 || opcion > _cantidadOpciones){
        cout << "Opcion incorrecta..." << endl;
        cout << "Opcion: ";
        cin  >> opcion;
    }
    return opcion;

}

void ManagerReportes::ejecutarOpcion(int opcion){
    switch(opcion){
        case 1: {
            ArchivoCobranzas archivocob("cobranzas.dat");
            Cobranza cob;

            int cantidad = archivocob.CantidadRegistros();
            float recMensual[12] = {};
            float recAnual = 0;

            int anio;
            cout <<  "INGRESE ANIO: " ;
            cin >> anio;
            cout << endl;

            for(int i=0; i<cantidad; i++){
                cob = archivocob.Leer(i);

                if(cob.getFechaTransaccion().getAnio() == anio){
                    int mes = cob.getFechaTransaccion().getMes();
                    float monto = cob.getMontoTotal();

                    recMensual[mes-1] += monto;
                    recAnual += monto;
                    }
                }
            cout << fixed << setprecision(0);
            cout << "FACTURACION MENSUAL - ANUAL " << anio << endl;

            string meses [12]={"Enero",
                               "Febrero",
                               "Marzo",
                               "Abril",
                               "Mayo",
                               "Junio",
                               "Julio",
                               "Agosto",
                               "Septiembre",
                               "Octubre",
                               "Noviembre",
                               "Diciembre"};
            cout << "=== RECAUDACION MENSUAL ===" << endl;
            for (int i=0; i <12; i++){
                cout << left << setw(12) << meses[i] << ": $" << right << recMensual[i] << endl;
            }
            cout << "=== RECAUDACION ANUAL ===" << endl;
            cout << "Total: $" << recAnual << endl;
            system("pause");
            break;
            }
        case 2: {
            break;
            }
        case 3: {
            break;
        }
        case 5: {
        break;
        }
    }
}


