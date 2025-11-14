#include <iostream>
#include "ManagerInstructores.h"
#include "Instructor.h"
#include "ArchivoInstructores.h"
#include "Clase.h"
#include "ArchivoClases.h"

using namespace std;

ManagerInstructores::ManagerInstructores(std::string nombreArchivoInstructores)
    : archivoInstructores(nombreArchivoInstructores) {
    _cantidadOpciones = 5; // (CARGAR, MODIFICAR, LISTADO, ESPECIALIDAD, ELIMINAR)
}

void ManagerInstructores::run(){
    int opcion;
    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
    }while(opcion!=0);
}

void ManagerInstructores::mostrarOpciones(){
       cout << "MENU PRINCIPAL"<<endl;
        cout << "====================="<< endl;
        cout << "1 - CARGAR INSTRUCTOR"<< endl;
        cout << "2 - MODIFICAR INSTRUCTOR" << endl;
        cout << "3 - LISTADO DE INSTRUCTORES" << endl;
        cout << "4 - ASIGNAR CLASE A INSTRUCTOR" << endl;
        cout << "5 - ELIMINAR INSTRUCTOR" << endl;
        cout << "0 - SALIR"<< endl;
        cout << "======================"<< endl;
}


int ManagerInstructores::seleccionOpcion(){
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

void ManagerInstructores::ejecutarOpcion(int opcion){
    switch(opcion){
        case 1: {
            cout << "=== ALTA DE INSTRUCTOR ===" << endl;
            cout << endl;

            int idNuevo;
            bool idValido = false;

            // Validacion por ID duplicado
            do {
            cout << "Ingrese ID del instructor (DNI): ";
            cin >> idNuevo;

                int posicionExistente = archivoInstructores.Buscar(idNuevo);
                if (posicionExistente >= 0) {
                    cout << "Error: ya existe un instructor con ese ID. Intente con otro." << endl;
                } else {
                    idValido = true;
                }
            } while (!idValido);

            ins.Cargar(idNuevo);

            // Guardar
            if (archivoInstructores.Guardar(ins)) {
                cout << "Instructor guardado exitosamente!" << endl;
            }  else {
                 cout << "Error al guardar el instructor." << endl;
            }
            system("pause");
            break;
            }
        case 2: {
                 int idBuscado;
            cout << "Ingrese el ID (DNI) del instructor a modificar: ";
            cin >> idBuscado;

            int posicion = archivoInstructores.Buscar(idBuscado);
            if (posicion < 0) {
                cout << "No existe un instructor con ese ID." << endl;
                system("pause");
                break;
            }

            // (Opcional) mostrar datos actuales
            Instructor instructorActual = archivoInstructores.Leer(posicion);
            cout << "\n--- Datos actuales ---\n";
            instructorActual.Mostrar();

            cout << "\n=== Reingrese los datos del instructor (se guardaran como nuevos datos) ===\n";
            Instructor instructorNuevo;
            instructorNuevo.setidInstructor(idBuscado);
            instructorNuevo.Modificar();

            if (archivoInstructores.ModificarPorId(idBuscado, instructorNuevo)) {
                cout << "Instructor modificado correctamente." << endl;
            } else {
                cout << "Error al modificar el instructor." << endl;
            }
            system("pause");
            break;
            }
            // Listar socios activos
        case 3: {
            int cantidad = archivoInstructores.CantidadRegistros();
            if (cantidad == 0) {
                cout << "No hay Instructores cargados." << endl;
                system("pause");
                break;
            }

            int opcionListado;

            do {
                system("cls");
                cout << "1 - INSTRUCTORES ACTIVOS" << endl;
                cout << "2 - INSTRUCTORES INACTIVOS" << endl;
                cout << "3 - TODOS LOS INSTRUCTORES" << endl;
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

                Instructor* vectorInstructor= new Instructor[cantidad];
                archivoInstructores.Leer(cantidad, vectorInstructor);
                bool hayResultados = false;

                switch (opcionListado) {
                    case 1: {
                        cout << "=== INSTRUCTORES ACTIVOS ===" << endl;
                        cout << endl;
                        for (int i = 0; i < cantidad; i++) {
                            if (vectorInstructor[i].getEstado() == true) {
                                vectorInstructor[i].Mostrar();
                                cout << "------------------" << endl;
                                hayResultados = true;
                            }
                        }
                        if (!hayResultados) cout << "NO HAY INSTRUCTORES ACTIVOS." << endl;
                        break;
                    }
                    case 2: {
                        cout << "=== INSTRUCTORES INACTIVOS ===" << endl;
                        cout << endl;
                        for (int i = 0; i < cantidad; i++) {
                            if (vectorInstructor[i].getEstado() == false) {
                                vectorInstructor[i].Mostrar();
                                cout << "------------------" << endl;
                                hayResultados = true;
                            }
                        }
                        if (!hayResultados) cout << "NO HAY INSTRUCTORES INACTIVOS." << endl;
                        break;
                    }
                    case 3: {
                        cout << "=== TODOS LOS INSTRUCTORES ===" << endl;
                        cout << endl;
                        for (int i = 0; i < cantidad; i++) {
                            vectorInstructor[i].Mostrar();
                            cout << "------------------" << endl;
                            hayResultados = true;
                        }
                        if (!hayResultados) cout << "NO HAY INSTRUCTORES CARGADOS." << endl;
                        break;
                    }
                }

                delete[] vectorInstructor;
                cout << endl;
                system("pause");

            } while (opcionListado != 0);

            break;
        }
        case 4: {
            cout << "=== ASIGNAR CLASE A INSTRUCTOR ===" << endl;

            int idInstructor;
            cout << "Ingrese el ID del instructor: ";
            cin >> idInstructor;

            int posInstructor = archivoInstructores.Buscar(idInstructor);
            if (posInstructor < 0) {
                cout << "No existe un instructor con ese ID." << endl;
                system("pause");
                break;
            }

            Instructor inst = archivoInstructores.Leer(posInstructor);
            cout << "\nInstructor encontrado:\n";
            inst.Mostrar();
            cout << endl;

            // Mostrar clases disponibles
            ArchivoClases archivoClases("clases.dat");
            int cantClases = archivoClases.CantidadRegistros();

            if (cantClases == 0) {
                cout << "No hay clases cargadas." << endl;
                system("pause");
                break;
            }

            cout << "=== LISTA DE CLASES ===" << endl;

            for (int i = 0; i < cantClases; i++) {
                Clase c = archivoClases.Leer(i);
                cout << "ID: " << c.getIDClase()
                     << " - " << c.getNombreClase() << endl;
            }

            cout << "\nIngrese el ID de la clase a asignar: ";
            int idClase;
            cin >> idClase;

            Clase claseSeleccionada;
            if (!archivoClases.LeerPorID(idClase, claseSeleccionada)) {
                cout << "No existe una clase con ese ID." << endl;
                system("pause");
                break;
            }

            // Asignación real
            inst.setIdClaseAsignada(idClase);

            if (archivoInstructores.ModificarPorId(idInstructor, inst)) {
                cout << "\nClase asignada correctamente!" << endl;
            } else {
                cout << "Error al asignar la clase." << endl;
            }

            system("pause");
            break;
        }

        case 5: {
            int idBuscado;
            cout << "Ingrese el ID del instructor a eliminar: ";
            cin >> idBuscado;

            int posicion = archivoInstructores.Buscar(idBuscado);
            if (posicion < 0) {
                cout << "No existe un instructor con ese ID." << endl;
                system("pause");
                break;
            }

            // Mostrar para confirmar
            Instructor instructorActual = archivoInstructores.Leer(posicion);
            cout << "\n--- Instructor seleccionado ---\n";
            instructorActual.Mostrar();

            cout << "\nConfirma eliminar este instructor? (s/n): ";
            char confirmar;
            cin >> confirmar;

            if (confirmar == 's' || confirmar == 'S') {
                if (archivoInstructores.EliminarPorId(idBuscado)) {
                    cout << "Instructor eliminado correctamente." << endl;
                } else {
                    cout << "Error al eliminar el instructor." << endl;
                }
            } else {
                cout << "Operación cancelada." << endl;
            }

            system("pause");
            break;
        }
        break;
        }
    }


