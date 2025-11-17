#include <iostream>
#include <iomanip>
#include "ManagerReportes.h"
#include "ArchivoCobranzas.h"
#include "cobranza.h"
#include "ArchivoSocios.h"
#include <map>
#include <string>

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
        cout << "4 - PAGOS PENDIENTES" << endl;
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
            ArchivoSocios archivosocios("socios.dat");
            int cant = archivosocios.CantidadRegistros();

            // Vectores dinámicos
            string* planes = new string[cant];
            int* cantidades = new int[cant];

            if (planes == nullptr || cantidades == nullptr) {
                cout << "Error de memoria." << endl;
                return;
            }

            int cantPlanes = 0;

            // Recorro todos los socios del archivo
            for (int i = 0; i < cant; i++) {
                Socio socio = archivosocios.Leer(i);

                if (socio.getEstado() == false) continue;


                string plan = socio.getTipoPlan();

                bool encontrado = false;
                // Recorro los planes que ya tengo guardados para ver si este ya existe
                for (int j = 0; j < cantPlanes; j++)
                    {
                    if (planes[j] == plan) {
                        cantidades[j]++;
                        encontrado = true;

                        break;
                    }
                }
                if (!encontrado) {

                    planes[cantPlanes] = plan;
                    cantidades[cantPlanes] = 1;
                    cantPlanes++;
                }
            }

            cout << "SOCIOS ACTIVOS POR PLAN\n\n";
            cout << left << setw(25) << "PLAN" << "SOCIOS" << endl;
            cout << "-------------------------------------\n";

            int total = 0;

            for (int i = 0; i < cantPlanes; i++) {
                cout << left << setw(25) << planes[i] << cantidades[i] << endl;
                total += cantidades[i];
            }

            cout << "-------------------------------------\n";
            cout << left << setw(25) << "TOTAL SOCIOS:" << total << endl;
            system("pause");

            delete[] planes;
            delete[] cantidades;
            break;
        }

        case 3: {
            break;
        }
        case 4: {
            ArchivoCobranzas archivocob("cobranzas.dat");
            ArchivoSocios archivosocios("socios.dat");
            Cobranza cob;
            Fecha fecha;
            Fecha fechaVencimiento;
            Plan plan;
            Socio socio;


            bool hayVencidos = false;

            cout << "=== PAGOS PENDIENTES ===" << endl;
            cout << "Fecha actual: ";
            fecha.FechaActual().Mostrar();
            cout << endl;
            cout << "---------------------------------------------" << endl;
            int cantidad = archivocob.CantidadRegistros();

            for(int i=0; i<cantidad; i++){
                cob = archivocob.Leer(i);
                int id = cob.getDniSocio();
                int pos = archivosocios.Buscar(id);
                socio = archivosocios.Leer(pos);

                bool Vencidos = false;
                if(cob.getIdPlan() == 1 || cob.getIdPlan() == 3 || cob.getIdPlan() == 5 ){
                        int dia = cob.getFechaTransaccion().getDia();
                        int mes = cob.getFechaTransaccion().getMes()+1;
                        int anio = cob.getFechaTransaccion().getAnio();
                        if(mes > 12){
                            mes = 1;
                            anio++;
                        }
                        fechaVencimiento.setDia(dia);
                        fechaVencimiento.setMes(mes);
                        fechaVencimiento.setAnio(anio);

                            if(fecha.FechaActual().getDia() >=  fechaVencimiento.getDia() and fecha.FechaActual().getMes()== fechaVencimiento.getMes()){
                                Vencidos = true;
                                    }
                        if(Vencidos){
                        cout << "ID Socio: " << cob.getDniSocio() << endl;
                        cout << "Nombre: " << socio.getNombre() << " " << socio.getApellido() << endl;
                        cout << "Fecha ultimo pago: ";
                        cob.getFechaTransaccion().Mostrar();
                        cout << endl;
                        cout << "Fecha vencimiento: ";
                        fechaVencimiento.Mostrar();
                        cout << endl;
                        cout << "---------------------------------------" << endl;

                        hayVencidos = true;
                    }
                }

                if(cob.getIdPlan() == 2 || cob.getIdPlan() == 4 || cob.getIdPlan() == 6){
                        int dia = cob.getFechaTransaccion().getDia();
                        int mes = cob.getFechaTransaccion().getMes();
                        int anio = cob.getFechaTransaccion().getAnio()+1;

                        fechaVencimiento.setDia(dia);
                        fechaVencimiento.setMes(mes);
                        fechaVencimiento.setAnio(anio);


                            if(fecha.FechaActual().getDia() >=  fechaVencimiento.getDia() and fecha.FechaActual().getMes()== fechaVencimiento.getMes()
                            and fecha.FechaActual().getAnio() == fechaVencimiento.getAnio()){
                                Vencidos = true;
                            }
                            if(Vencidos){
                        cout << "ID Socio: " << cob.getDniSocio() << endl;
                        cout << "Nombre: " << socio.getNombre() << " " << socio.getApellido() << endl;
                        cout << "Fecha ultimo pago: ";
                        cob.getFechaTransaccion().Mostrar();
                        cout << endl;
                        cout << "Fecha vencimiento: ";
                        fechaVencimiento.Mostrar();
                        cout << endl;
                        cout << "---------------------------------------" << endl;

                        hayVencidos = true;
                    }
                }
            }
        if(!hayVencidos){
            cout << "No hay pagos pendientes." << endl;
        }
        system("pause");
        break;
        }
    }
}


