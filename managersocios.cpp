#include <iostream>
#include "ManagerSocios.h"

using namespace std;

ManagerSocios::ManagerSocios(std::string nombreArchivo): archivoSocios(nombreArchivo){
    _cantidadOpcines = 5 ;
}

void ManagerSocios::run(){
    int opcion;
    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
    }while(opcion!=0);
}

void ManagerSocios::mostrarOpciones(){
        cout << "MENU PRINCIPAL"<<endl;
        cout << "====================="<< endl;
        cout << "1 - CARGAR SOCIO"<< endl;
        cout << "2 - MODIFICAR SOCIO" << endl;
        cout << "3 - LISTADO DE SOCIOS" << endl;
        cout << "5 - ELIMINAR SOCIO" << endl;
        cout << "0 - SALIR"<< endl;
        cout << "======================"<< endl;
}

int ManagerSocios::seleccionOpcion(){
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

void ManagerSocios::ejecutarOpcion(int opcion){
    switch(opcion){
        case 1:{
            socio.Cargar();
            if (archivoSocios.Guardar(socio)){
                cout << "Socio guardado exitosamente!" << endl;
            }else{
                cout << "Error al guardar el socio." << endl;
            }
            system("pause");
            break;
            }
        case 2 :{
            int idBuscado;
            cout << "Ingrese el ID (DNI) del socio a modificar: ";
            cin >> idBuscado;

            int posicion = archivoSocios.Buscar(idBuscado);
            if (posicion < 0) {
                cout << "No existe un socio con ese ID." << endl;
                system("pause");
                break;
            }

            // (Opcional) mostrar datos actuales
            Socio socioActual = archivoSocios.Leer(posicion);
            cout << "\n--- Datos actuales ---\n";
            socioActual.Mostrar();

            cout << "\n=== Reingrese los datos del socio (se guardaran como nuevos datos) ===\n";
            Socio socioNuevo;
            socioNuevo.setId(idBuscado);
            socioNuevo.Modificar();

            if (archivoSocios.ModificarPorId(idBuscado, socioNuevo)) {
                cout << "Socio modificado correctamente." << endl;
            } else {
                cout << "Error al modificar el socio." << endl;
            }
            system("pause");
            break;
            }
        //Listar socios
        case 3: {
            int cantidad = archivoSocios.CantidadRegistros();
            if (cantidad == 0){
                cout << "No hay socios cargados." << endl;
            }else{
                Socio *vecAux = new Socio[cantidad];
                archivoSocios.Leer(cantidad, vecAux);
                for (int i=0; i < cantidad; i++){
                    vecAux[i].Mostrar();
                    cout << "------------------" << endl;
                }
                delete[] vecAux;
            }
            system("pause");
            break;
        }
        case 5: {
            int idBuscado;
            cout << "Ingrese el ID (DNI) del socio a eliminar: ";
            cin >> idBuscado;

            int posicion = archivoSocios.Buscar(idBuscado);
            if (posicion < 0) {
                cout << "No existe un socio con ese ID." << endl;
                system("pause");
                break;
            }

            Socio socioActual = archivoSocios.Leer(posicion);
            cout << "\n--- Datos del socio a eliminar ---\n";
            socioActual.Mostrar();

            cout << "\n¿Confirma que desea eliminar este socio? (s/n): ";
            char confirmacion;
            cin >> confirmacion;

            if (confirmacion == 's' || confirmacion == 'S') {
                if (archivoSocios.EliminarPorId(idBuscado)) {
                    cout << "Socio eliminado (marcado como inactivo)." << endl;
                } else {
                    cout << "Error al eliminar el socio." << endl;
                }
            } else {
                cout << "Operacion cancelada." << endl;
            }

            system("pause");
            break;
        }
        case 0:{
            break;
        }
    }
}
