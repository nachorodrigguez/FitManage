#include <iostream>
#include "ManagerCobranzas.h"

using namespace std;

ManagerCobranzas::ManagerCobranzas(std::string nombreArchivo): archivocobranzas(nombreArchivo), archivosocios("socios.dat"){
    _cantidadOpcines = 3 ;
}

void ManagerCobranzas::run(){
    int opcion;
    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
    }while(opcion!=0);
}

void ManagerCobranzas::mostrarOpciones(){
        cout << "MENU PRINCIPAL"<<endl;
        cout << "====================="<< endl;
        cout << "1 - GENERAR PAGO"<< endl;
        cout << "2 - FACTURA" << endl;
        cout << "3 - LISTADO DE PAGOS" << endl;
        cout << "0 - SALIR"<< endl;
        cout << "======================"<< endl;
}

int ManagerCobranzas::seleccionOpcion(){
    int opcion;
    mostrarOpciones();
    cout << "Opcion: ";
    cin >> opcion;

    while (opcion < 0 || opcion > _cantidadOpcines){
        cout << "Opcion incorrecta..." << endl;
        cout << "Opcion: ";
        cin  >> opcion;
    }
    return opcion;

}

void ManagerCobranzas::ejecutarOpcion(int opcion){
    switch(opcion){
        case 1:{
            int dni;
            bool idValido = false;

            //verifica si el socio existe dentro de ArchivoSocios
            do{
                cout << "Ingrese ID del socio (DNI): ";
                cin >> dni;

                int posicionExiste = archivosocios.Buscar(dni);

                if (posicionExiste == -1){
                    cout << "Socio no ingresado en el sistema." << endl;
                    system("pause");
                    return;
                }else{
                    idValido = true;
                    socio = archivosocios.Leer(posicionExiste);
                }
            }while(!idValido);

            if (socio.getEstado() == true){
                int cantidad = archivocobranzas.CantidadRegistros();
                int nuevoNumero = 1;

                if(cantidad > 0){
                    Cobranza ultimoReg = archivocobranzas.Leer(cantidad - 1);
                    nuevoNumero = ultimoReg.getNumTransaccion() + 1;
                }

                cobranza.setNumTransaccion(nuevoNumero);
                cobranza.setDniSocio(dni);
                cobranza.Cargar();
                if (archivocobranzas.Guardar(cobranza)){
                    cout << "Pago registrado exitosamente!" << endl;
                }else{
                    cout << "Error al guardar el pago." << endl;
                }
            }else {
                cout << "Socio inactivo. No se puede registrar el pago." << endl;
            }
            system("pause");
            break;
            }
        case 2 : {
            int cantidad = archivocobranzas.CantidadRegistros();

            if(cantidad > 0){
                Cobranza ultimo = archivocobranzas.Leer(cantidad -1);
                ultimo.Mostrar();
            }
            else {
                cout << "No hay pagos registrados." << endl;
            }
            system("pause");
        break;
        }
        case 3 : {
            int cantidad = archivocobranzas.CantidadRegistros();
            if(cantidad == 0){
                cout << "No se registraron pagos." << endl;
                system("pause");
                break;
            }

            Cobranza* vectorCob = new Cobranza[cantidad];
            archivocobranzas.Leer(cantidad, vectorCob);
            bool hayResultados = false;

            cout << "LISTADO DE PAGOS" << endl;
            for (int i=0; i<cantidad; i++){
            vectorCob[i].Mostrar();
            cout << endl;
            hayResultados = true;
                }
            delete [] vectorCob;
            cout << endl;
            system("pause");
            break;
            }
        case 0:{
            break;
        }
    }
}


