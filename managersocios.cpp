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
        cout << "4 - ASIGNAR PLAN A SOCIO" << endl;
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
        case 1: {
            cout << "=== ALTA DE SOCIO ===" << endl;
            cout << endl;

            int idNuevo;
            bool idValido = false;

            // Validacion por ID duplicado
            do {
                cout << "Ingrese ID del socio (DNI): ";
                cin >> idNuevo;

                int posicionExistente = archivoSocios.Buscar(idNuevo);
                if (posicionExistente >= 0) {
                    cout << "Error: ya existe un socio con ese ID. Intente con otro." << endl;
                } else {
                    idValido = true;
                }
            } while (!idValido);

            socio.Cargar(idNuevo);

            // Guardar
            if (archivoSocios.Guardar(socio)) {
                cout << "Socio guardado exitosamente!" << endl;
            } else {
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
        // Listar socios activos
        case 3: {
            int cantidad = archivoSocios.CantidadRegistros();
            if (cantidad == 0) {
                cout << "No hay socios cargados." << endl;
                system("pause");
                break;
            }

            int opcionListado;

            do {
                system("cls");
                cout << "1 - SOCIOS ACTIVOS" << endl;
                cout << "2 - SOCIOS INACTIVOS" << endl;
                cout << "3 - TODOS LOS SOCIOS" << endl;
                cout << "0 - VOLVER AL MENU PRINCIPAL" << endl;
                cout << "===============================" << endl;
                cout << "OPCION: ";
                cin >> opcionListado;

                if (opcionListado == 0) break;

                while (opcionListado < 0 || opcionListado > 3) {
                    cout << "OPCION INCORRECTA. INGRESE NUEVAMENTE: ";
                    cin >> opcionListado;
                }

                system("cls");

                Socio* vectorSocios = new Socio[cantidad];
                archivoSocios.Leer(cantidad, vectorSocios);
                bool hayResultados = false;

                switch (opcionListado) {
                    case 1: {
                        cout << "=== SOCIOS ACTIVOS ===" << endl;
                        for (int i = 0; i < cantidad; i++) {
                            if (vectorSocios[i].getEstado() == true) {
                                vectorSocios[i].Mostrar();
                                cout << "------------------" << endl;
                                hayResultados = true;
                            }
                        }
                        if (!hayResultados) cout << "NO HAY SOCIOS ACTIVOS." << endl;
                        break;
                    }
                    case 2: {
                        cout << "=== SOCIOS INACTIVOS ===" << endl;
                        for (int i = 0; i < cantidad; i++) {
                            if (vectorSocios[i].getEstado() == false) {
                                vectorSocios[i].Mostrar();
                                cout << "------------------" << endl;
                                hayResultados = true;
                            }
                        }
                        if (!hayResultados) cout << "NO HAY SOCIOS INACTIVOS." << endl;
                        break;
                    }
                    case 3: {
                        cout << "=== TODOS LOS SOCIOS ===" << endl;
                        for (int i = 0; i < cantidad; i++) {
                            vectorSocios[i].Mostrar();
                            cout << "------------------" << endl;
                            hayResultados = true;
                        }
                        if (!hayResultados) cout << "NO HAY SOCIOS CARGADOS." << endl;
                        break;
                    }
                }

                delete[] vectorSocios;
                cout << endl;
                system("pause");

            } while (opcionListado != 0);

            break;
        }
        case 4: {
            // 1) Pedir ID del socio
            int idBuscado;
            cout << "Ingrese el ID (DNI) del socio: ";
            cin >> idBuscado;

            int posSocio = archivoSocios.Buscar(idBuscado);
            if (posSocio < 0) {
                cout << "No existe un socio con ese ID.\n";
                system("pause");
                break;
            }

            Socio s = archivoSocios.Leer(posSocio);
            if (!s.getEstado()) {
                cout << "El socio está inactivo. No se puede asignar un plan.\n";
                system("pause");
                break;
            }

            // 2) Cargar planes y listar sólo activos
            ArchivoPlanes repoPlanes("planes.dat");
            int cant = repoPlanes.CantidadRegistros();
            if (cant <= 0) {
                cout << "No hay planes cargados.\n";
                system("pause");
                break;
            }

            Plan* vec = new Plan[cant];
            repoPlanes.Leer(cant, vec);

            cout << "=== PLANES DISPONIBLES (ACTIVOS) ===\n";
            bool hayActivos = false;
            for (int i = 0; i < cant; i++) {
                if (vec[i].getEstado()) {
                    cout << "ID: " << vec[i].getIdPlan()
                         << " | Tipo: " << vec[i].getTipo()
                         << " | Periodo: " << vec[i].getPeriodo()
                         << " | Precio: $" << vec[i].getPrecio()
                         << " | Duracion: " << vec[i].getDuracion() << " meses\n";
                    hayActivos = true;
                }
            }

            if (!hayActivos) {
                cout << "No hay planes activos.\n";
                delete[] vec;
                system("pause");
                break;
            }

            // 3) Elegir ID de plan (validado contra archivo)
            int idPlanSel;
            cout << "\nIngrese el ID del plan a asignar: ";
            cin >> idPlanSel;

            int posPlan = repoPlanes.Buscar(idPlanSel);
            if (posPlan < 0) {
                cout << "ID de plan inexistente.\n";
                delete[] vec;
                system("pause");
                break;
            }

            Plan elegido = repoPlanes.Leer(posPlan);
            if (!elegido.getEstado()) {
                cout << "El plan está inactivo.\n";
                delete[] vec;
                system("pause");
                break;
            }

            // 4) Asignar al socio el tipoPlan EXACTO del plan elegido
            s.setTipoPlan(elegido.getTipo());

            // 5) Persistir el socio modificado en su misma posición
            if (archivoSocios.Guardar(s, posSocio)) {
                cout << "Plan asignado correctamente al socio " << s.getId()
                     << " (tipoPlan = " << s.getTipoPlan() << ").\n";
            } else {
                cout << "Error al guardar el socio con el nuevo tipo de plan.\n";
            }

            delete[] vec;
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

            cout << "\n Confirma que desea eliminar este socio? (s/n): ";
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
