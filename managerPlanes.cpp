#include <iostream>
#include "managerplanes.h"
#include <cstring>


using namespace std;


bool existeNombrePlan(const char* nombreBuscado, ArchivoPlanes &archivo) {
    int cantidad = archivo.CantidadRegistros();

    for (int i = 0; i < cantidad; i++) {
        Plan plan = archivo.Leer(i);

        if (plan.getEstado()) {

            if (strcasecmp(plan.getTipo(), nombreBuscado) == 0) {
                return true;
            }
        }
    }

    return false;
}

int seleccionarPlan(ArchivoPlanes &archivo) {
    int cantidad = archivo.CantidadRegistros();
    if (cantidad == 0) {
        cout << "No hay planes cargados.\n";
        return -1;
    }


    Plan* vec = new Plan[cantidad];
    archivo.Leer(cantidad, vec);

    cout << "=== LISTA DE PLANES ACTIVOS ===\n";

    int indices[200];
    int cantMostrar = 0;

    for (int i = 0; i < cantidad; i++) {
        if (vec[i].getEstado()) {
            cout << (cantMostrar + 1) << " - " << vec[i].getTipo() << endl;
            indices[cantMostrar] = i;
            cantMostrar++;
        }
    }

    if (cantMostrar == 0) {
        cout << "\nNo hay planes activos.\n";
        delete[] vec;
        return -1;
    }

    cout << "\nSELECCIONE UN PLAN  (0 para cancelar): ";
    int opcion;
    cin >> opcion;
    while(cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Entrada invalida. Ingrese un numero: ";
        cin >> opcion;
    }

    if (opcion == 0) {
        delete[] vec;
        return -1;
    }

    if (opcion < 1 || opcion > cantMostrar) {
        cout << "Opcion incorrecta.\n";
        delete[] vec;
        return -1;
    }

    int posReal = indices[opcion - 1];
    delete[] vec;
    return posReal;
}



ManagerPlanes::ManagerPlanes(std::string nombreArchivoPlanes)
    : archivoPlanes(nombreArchivoPlanes) {
    _cantidadOpciones = 4; // (CARGAR, MODIFICAR, LISTADO, ELIMINAR)

    int cantidadDePlanes = archivoPlanes.CantidadRegistros();
    Plan::EstablecerUltimoId(cantidadDePlanes);
}

void ManagerPlanes::run(){
    int opcion;
    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
    }while(opcion!=0);
}

void ManagerPlanes::mostrarOpciones(){
        cout << "MENU PRINCIPAL"<<endl;
        cout << "====================="<< endl;
        cout << "1 - CARGAR PLAN"<< endl;
        cout << "2 - MODIFICAR PLAN" << endl;
        cout << "3 - LISTADO DE PLANES" << endl;
        cout << "4 - ELIMINAR PLAN" << endl;
        cout << "0 - SALIR"<< endl;
        cout << "======================"<< endl;
}

int ManagerPlanes::seleccionOpcion(){
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

void ManagerPlanes::ejecutarOpcion(int opcion){
    switch(opcion){

    case 1: {
            cin.ignore();
            string nombre;

            do {
                cout << "INGRESE EL NOMBRE DEL PLAN: ";
                getline(cin, nombre);
                cout << endl;

                if (existeNombrePlan(nombre.c_str(), archivoPlanes)) {
                    cout << "Ya existe un plan con ese nombre. Intente otro.\n";
                    cout << endl;
                }
            } while (existeNombrePlan(nombre.c_str(), archivoPlanes));

            plan.setTipoPlan(nombre.c_str());

            plan.Cargar();


            if (archivoPlanes.Guardar(plan)) {
                cout << "PLAN GUARDADO EXITOSAMENTE!" << endl;
            } else {
                cout << "Error al guardar el plan." << endl;
            }

            system("pause");
            break;
        }
        case 2: {
            int posicion = seleccionarPlan(archivoPlanes);
            if (posicion < 0) {
                system("pause");
                break;
            }

            Plan planActual = archivoPlanes.Leer(posicion);

            cout << "\n--- PLAN ENCONTRADO ---\n";
            planActual.Mostrar();
            cout << "-------------------------" << endl;

            cout << "\nDesea modificar este plan? (s/n): ";
            char confirmar;
            cin >> confirmar;
            if (confirmar != 's' && confirmar != 'S') {
                cout << "Operacion cancelada." << endl;
                system("pause");
                break;
            }

            // Creamos un nuevo objeto Plan con los datos modificados
            Plan planModificado = planActual;

            cin.ignore();

            string nuevoTipo;
            cout << "Nuevo nombre del plan (actual: " << planActual.getTipo() << "): ";
            getline(cin, nuevoTipo);
            if (!nuevoTipo.empty()) planModificado.setTipoPlan(nuevoTipo.c_str());

            string nuevaDescripcion;
            cout << "Nueva descripcion (actual: " << planActual.getDescripcion() << "): ";
            getline(cin, nuevaDescripcion);
            if (!nuevaDescripcion.empty()) planModificado.setDescripcion(nuevaDescripcion.c_str());

            int opcionPeriodo;
            cout << "Seleccione nuevo periodo (1 = Mensual, 2 = Anual, 0 = mantener actual): ";
            cin >> opcionPeriodo;
            if (opcionPeriodo == 1) planModificado.setPeriodo("Mensual");
            else if (opcionPeriodo == 2) planModificado.setPeriodo("Anual");

            float nuevoPrecio;
            cout << "Nuevo precio (actual $" << planActual.getPrecio() << ", 0 para mantener): ";
            cin >> nuevoPrecio;
            if (nuevoPrecio > 0) planModificado.setPrecio(nuevoPrecio);

            int nuevaDuracion;
            cout << "Nueva duracion en meses (actual " << planActual.getDuracion() << ", 0 para mantener): ";
            cin >> nuevaDuracion;
            if (nuevaDuracion > 0) planModificado.setDuracion(nuevaDuracion);

            // Guardamos cambios (ID y estado se mantienen)
            if (archivoPlanes.Guardar(planModificado, posicion)) {
                cout << "\nPLAN MODIFICADO CORRECTAMENTE." << endl;
            } else {
                cout << "\nError al modificar el plan." << endl;
            }

            system("pause");
            break;
        }

        case 3: {
            int cantidad = archivoPlanes.CantidadRegistros();
            if (cantidad == 0) {
                cout << "No hay planes cargados." << endl;
                system("pause");
                break;
            }

            int opcionListado = -1;
            do {
                system("cls");
                cout << "=== SUBMENU - LISTAR PLANES ===" << endl;
                cout << "1 - Planes Activos" << endl;
                cout << "2 - Planes Inactivos" << endl;
                cout << "3 - Todos los planes" << endl;
                cout << "0 - Volver al menu principal" << endl;
                cout << "===============================" << endl;
                cout << "Opcion: ";
                cin >> opcionListado;

                if (opcionListado == 0) break;
                if (opcionListado < 0 || opcionListado > 3) {
                    cout << "Opcion incorrecta..." << endl;
                    system("pause");
                    continue;
                }

                system("cls");

                Plan* vectorPlanes = new Plan[cantidad];
                archivoPlanes.Leer(cantidad, vectorPlanes);

                bool hayResultados = false;
                switch (opcionListado) {
                    case 1: {
                        cout << "=== PLANES ACTIVOS ===" << endl;
                        for (int i = 0; i < cantidad; i++) {

                            if (vectorPlanes[i].getEstado() == true) {
                                vectorPlanes[i].Mostrar();
                                cout << "-------------------------" << endl;
                                hayResultados = true;
                            }
                        }
                        if (!hayResultados) cout << "No hay planes activos." << endl;
                        break;
                    }
                    case 2: {
                        cout << "=== PLANES INACTIVOS ===" << endl;
                        for (int i = 0; i < cantidad; i++) {
                            if (vectorPlanes[i].getEstado() == false) {
                                vectorPlanes[i].Mostrar();
                                cout << "-------------------------" << endl;
                                hayResultados = true;
                            }
                        }
                        if (!hayResultados) cout << "No hay planes inactivos." << endl;
                        break;
                    }
                    case 3: {
                        cout << "=== TODOS LOS PLANES ===" << endl;
                        for (int i = 0; i < cantidad; i++) {
                            vectorPlanes[i].Mostrar();
                            cout << "-------------------------" << endl;
                            hayResultados = true;
                        }
                        break;
                    }
                }

                delete[] vectorPlanes;
                cout << endl;
                system("pause");

            } while (opcionListado != 0);

            break;
        }
        case 4: {
            int idPlanBuscado;
            cout << "Ingrese el ID del plan a eliminar: ";
            cin >> idPlanBuscado;

            int posicion = archivoPlanes.Buscar(idPlanBuscado);
            if (posicion < 0) {
                cout << "No existe un plan con ese ID." << endl;
                system("pause");
                break;
            }

            Plan planActual = archivoPlanes.Leer(posicion);
            cout << "\n--- Plan seleccionado ---\n";
            planActual.Mostrar();

            cout << "Confirma que desea eliminar este plan? (s/n): ";
            char confirmacion;
            cin >> confirmacion;

            if (confirmacion == 's' || confirmacion == 'S') {
                if (archivoPlanes.EliminarPorId(idPlanBuscado)) {
                    cout << "Plan eliminado correctamente." << endl;
                } else {
                    cout << "Error al eliminar el plan." << endl;
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
