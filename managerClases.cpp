#include <iostream>
#include <cstring>      // para strcmp
#include "managerClases.h"
using namespace std;

// Lista los socios inscriptos ACTIVOS en una clase.
// Devuelve true si encontró al menos uno.
static bool listarSociosDeClase(ArchivoClasexSocio& archivoIns,
                                ArchivoSocios& archivoSocios,
                                int idClase) {
    int cantIns = archivoIns.CantidadRegistros();
    if (cantIns <= 0) {
        cout << "No hay inscripciones cargadas." << endl;
        return false;
    }

    ClasexSocio ins;
    bool hayResultados = false;

    cout << "=== SOCIOS INSCRIPTOS EN LA CLASE ID " << idClase << " ===" << endl;

    for (int i = 0; i < cantIns; i++) {
        if (!archivoIns.Leer(i, ins)) continue;

        if (ins.getIDClase() == idClase && ins.getEstado()) {
            int idSocio = ins.getIdSocio();
            int posSocio = archivoSocios.Buscar(idSocio);

            if (posSocio >= 0) {
                Socio s = archivoSocios.Leer(posSocio);  // ← acá el cambio
                cout << "- DNI: " << s.getId()
                     << " | Nombre: " << s.getNombre()
                     << " " << s.getApellido()
                     << " | ID Inscripcion: " << ins.getIDClasexSocio() << endl;
            } else {
                cout << "- DNI: " << idSocio
                     << " (no encontrado en socios.dat)"
                     << " | ID Inscripcion: " << ins.getIDClasexSocio() << endl;
            }

            hayResultados = true;
        }
    }

    if (!hayResultados) {
        cout << "No hay socios activos inscriptos en esta clase." << endl;
    }

    return hayResultados;
}

// Ordena vector de clases por nombre (A..Z)
static void ordenarClasesPorNombre(Clase* vec, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            const char* nomI = vec[i].getNombreClase();
            const char* nomJ = vec[j].getNombreClase();
            if (std::strcmp(nomI, nomJ) > 0) {
                Clase aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;
            }
        }
    }
}

// Ordena vector de clases por duración (de menor a mayor)
static void ordenarClasesPorDuracion(Clase* vec, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (vec[i].getTiempoDuracion() > vec[j].getTiempoDuracion()) {
                Clase aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;
            }
        }
    }
}

ManagerClases::ManagerClases(string nombreArchivo) 
    : archivoClases("clases.dat"),
      archivoclasesxsocio("inscripciones.dat"),
      archivosocios("socios.dat")
{
    _cantidadOpciones = 5;
}

void ManagerClases::run() {
    int opcion;
    do {
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
    } while (opcion != 0);
}

void ManagerClases::mostrarOpciones() {
    cout << "MENU CLASES" << endl;
    cout << "=====================" << endl;
    cout << "1 - AGREGAR CLASE" << endl;
    cout << "2 - LISTAR CLASES" << endl;
    cout << "3 - CONSULTAS DE CLASES" << endl;
    cout << "4 - INSCRIBIR SOCIO A CLASE" << endl;
    cout << "5 - ELIMINAR SOCIO DE CLASE" << endl;
    cout << "0 - SALIR" << endl;
    cout << "======================" << endl;
}

int ManagerClases::seleccionOpcion() {
    int opcion;
    mostrarOpciones();
    cout << "Opcion: ";
    cin >> opcion;

    while (opcion < 0 || opcion > _cantidadOpciones) {
        cout << "Opcion incorrecta..." << endl;
        cout << "Opcion: ";
        cin >> opcion;
    }
    return opcion;
}

void ManagerClases::ejecutarOpcion(int opcion) {
    switch (opcion) {
        case 1: {
            cout << "=== AGREGAR CLASE ===" << endl;
            clase.Cargar();
            archivoClases.Guardar(clase);
            cout << "Clase agregada correctamente." << endl;
            system("pause");
            break;
        }
        
        case 2: {
            int cantidad = archivoClases.CantidadRegistros();
            if (cantidad <= 0) {
                cout << "No hay clases cargadas." << endl;
                system("pause");
                break;
            }

            int opcionListado;

            do {
                system("cls");
                cout << "=== LISTADO DE CLASES ===" << endl;
                cout << "1 - LISTAR TODAS (SIN ORDENAR)" << endl;
                cout << "2 - LISTAR ORDENADAS POR NOMBRE DE CLASE" << endl;
                cout << "3 - LISTAR ORDENADAS POR DURACION (MINUTOS)" << endl;
                cout << "0 - VOLVER AL MENU CLASES" << endl;
                cout << "===============================" << endl;
                cout << "OPCION: ";
                cin >> opcionListado;

                if (opcionListado == 0) break;

                while (opcionListado < 0 || opcionListado > 3) {
                    cout << "OPCION INCORRECTA. INGRESE NUEVAMENTE: ";
                    cin >> opcionListado;
                }

                system("cls");

               // Leer todas las clases en un vector (una por una)
                Clase* vectorClases = new Clase[cantidad];
                for (int i = 0; i < cantidad; i++) {
                vectorClases[i] = archivoClases.Leer(i);
                }

                switch (opcionListado) {
                    case 1: {
                        cout << "=== TODAS LAS CLASES (SIN ORDENAR) ===" << endl;
                        for (int i = 0; i < cantidad; i++) {
                            vectorClases[i].Mostrar();
                            cout << "------------------" << endl;
                        }
                        break;
                    }
                    case 2: {
                        cout << "=== CLASES ORDENADAS POR NOMBRE ===" << endl;
                        ordenarClasesPorNombre(vectorClases, cantidad);
                        for (int i = 0; i < cantidad; i++) {
                            vectorClases[i].Mostrar();
                            cout << "------------------" << endl;
                        }
                        break;
                    }
                    case 3: {
                        cout << "=== CLASES ORDENADAS POR DURACION (MINUTOS) ===" << endl;
                        ordenarClasesPorDuracion(vectorClases, cantidad);
                        for (int i = 0; i < cantidad; i++) {
                            vectorClases[i].Mostrar();
                            cout << "------------------" << endl;
                        }
                        break;
                    }
                }

                delete[] vectorClases;
                cout << endl;
                system("pause");

            } while (opcionListado != 0);

            break;
        }
        
         case 3: {
            int cantidad = archivoClases.CantidadRegistros();
            if (cantidad <= 0) {
                cout << "No hay clases cargadas." << endl;
                system("pause");
                break;
            }

            int opcionConsulta;
            do {
                system("cls");
                cout << "=== CONSULTAS DE CLASES ===" << endl;
                cout << "1 - BUSCAR CLASE POR ID" << endl;
                cout << "2 - BUSCAR CLASES POR NOMBRE" << endl;
                cout << "3 - LISTAR CLASES POR CAPACIDAD MINIMA" << endl;
                cout << "0 - VOLVER AL MENU CLASES" << endl;
                cout << "============================" << endl;
                cout << "OPCION: ";
                cin >> opcionConsulta;

                if (opcionConsulta == 0) break;

                while (opcionConsulta < 0 || opcionConsulta > 3) {
                    cout << "OPCION INCORRECTA. INGRESE NUEVAMENTE: ";
                    cin >> opcionConsulta;
                }

                system("cls");
                bool hayResultados = false;

                switch (opcionConsulta) {
                    case 1: {   // Buscar por ID (lo que ya tenías)
                        cout << "=== BUSCAR CLASE POR ID ===" << endl;
                        int id;
                        cout << "Ingrese ID de clase: ";
                        cin >> id;
                        Clase c;
                        if (archivoClases.LeerPorID(id, c)) {
                            c.Mostrar();
                        } else {
                            cout << "No se encontró una clase con ese ID." << endl;
                        }
                        break;
                    }

                    case 2: {   // Buscar por nombre de clase
                        cout << "=== BUSCAR CLASES POR NOMBRE ===" << endl;
                        char nombreBuscado[50];
                        cout << "Ingrese el NOMBRE de la clase (sin espacios): ";
                        cin >> nombreBuscado;

                        for (int i = 0; i < cantidad; i++) {
                            Clase c = archivoClases.Leer(i);
                            if (std::strcmp(c.getNombreClase(), nombreBuscado) == 0) {
                                c.Mostrar();
                                cout << "------------------" << endl;
                                hayResultados = true;
                            }
                        }

                        if (!hayResultados) {
                            cout << "No se encontraron clases con ese nombre." << endl;
                        }
                        break;
                    }

                    case 3: {   // Filtrar por capacidad mínima
                        cout << "=== CLASES POR CAPACIDAD MINIMA ===" << endl;
                        int capMin;
                        cout << "Ingrese capacidad minima: ";
                        cin >> capMin;

                        for (int i = 0; i < cantidad; i++) {
                            Clase c = archivoClases.Leer(i);
                            if (c.getCapacidadMax() >= capMin) {
                                c.Mostrar();
                                cout << "------------------" << endl;
                                hayResultados = true;
                            }
                        }

                        if (!hayResultados) {
                            cout << "No se encontraron clases con esa capacidad minima." << endl;
                        }
                        break;
                    }
                }

                cout << endl;
                system("pause");

            } while (opcionConsulta != 0);

            break;
        }
        
        case 4: {
            cout << "=== INSCRIBIR SOCIO A CLASE ===" << endl;

            int dni;
            bool idValido = false;

            // Buscar socio por DNI
            do {
                cout << "Ingrese ID del socio (DNI): ";
                cin >> dni;

                int posicionExiste = archivosocios.Buscar(dni);

                if (posicionExiste == -1) {
                    cout << "Socio no ingresado en el sistema." << endl;
                    system("pause");
                    return;
                } else {
                    idValido = true;
                    socio = archivosocios.Leer(posicionExiste);
                }
            } while (!idValido);

            if (!socio.getEstado()) {
                cout << "Socio inactivo. No se puede inscribir a clases." << endl;
                system("pause");
                break;
            }

            // Mostrar clases disponibles
            int cantClases = archivoClases.CantidadRegistros();
            if (cantClases <= 0) {
                cout << "No hay clases cargadas en el sistema." << endl;
                system("pause");
                break;
            }

            cout << "\n=== LISTADO DE CLASES DISPONIBLES ===" << endl;
            archivoClases.Listar();
            cout << "======================================" << endl;

            int idClase;
            cout << "Ingrese el ID de la clase a la que desea inscribir al socio: ";
            cin >> idClase;

            // Verificar que la clase exista
            Clase c;
            if (!archivoClases.LeerPorID(idClase, c)) {
                cout << "No existe una clase con ese ID." << endl;
                system("pause");
                break;
            }

            // Verificar si ya está inscripto en esa clase
            int posExistente = archivoclasesxsocio.BuscarPorSocioYClase(dni, idClase);
            if (posExistente >= 0) {
                cout << "El socio ya está inscripto en esa clase." << endl;
                system("pause");
                break;
            }

            // Crear la inscripcion igual que en SOCIOS
            ClasexSocio reg;
            int nuevoID = archivoclasesxsocio.BuscarUltimoID() + 1;
            reg.setIDClasexSocio(nuevoID);
            reg.setIdSocio(dni);
            reg.setIDClase(idClase);

            Fecha f;
            cout << "\nFecha de inscripcion:\n";
            f.Cargar();
            reg.setFechaInscripcion(f);
            reg.setEstado(true);

            if (archivoclasesxsocio.Guardar(reg)) {
                cout << "Socio inscripto correctamente en la clase." << endl;
            } else {
                cout << "Error al inscribir socio en la clase." << endl;
            }

            system("pause");
            break;
        }
    
         case 5: {
            cout << "=== ELIMINAR SOCIO DE CLASE ===" << endl;

            int idClase;
            cout << "Ingrese ID de la clase: ";
            cin >> idClase;

            // Verificamos que la clase exista
            Clase c;
            if (!archivoClases.LeerPorID(idClase, c)) {
                cout << "No existe una clase con ese ID." << endl;
                system("pause");
                break;
            }

            cout << "\nClase encontrada:" << endl;
            c.Mostrar();
            cout << endl;

            // Listar socios inscriptos en esa clase
            bool haySocios = listarSociosDeClase(archivoclasesxsocio, archivosocios, idClase);
            if (!haySocios) {
                // No hay nadie para eliminar
                system("pause");
                break;
            }

            int dniSocio;
            cout << "\nIngrese el DNI del socio que desea dar de baja de esta clase: ";
            cin >> dniSocio;

            // Buscar la inscripcion específica socio + clase
            int posIns = archivoclasesxsocio.BuscarPorSocioYClase(dniSocio, idClase);
            if (posIns < 0) {
                cout << "No se encontro una inscripcion ACTIVA de ese socio en esa clase." << endl;
                system("pause");
                break;
            }

            ClasexSocio reg;
            if (!archivoclasesxsocio.Leer(posIns, reg)) {
                cout << "Error al leer la inscripcion." << endl;
                system("pause");
                break;
            }

            cout << "\nInscripcion encontrada:" << endl;
            reg.Mostrar();

            cout << "\nConfirma eliminar esta inscripcion? (s/n): ";
            char conf;
            cin >> conf;
            if (conf != 's' && conf != 'S') {
                cout << "Operacion cancelada." << endl;
                system("pause");
                break;
            }

            reg.setEstado(false);
            if (archivoclasesxsocio.Sobrescribir(posIns, reg)) {
                cout << "Inscripcion dada de baja correctamente." << endl;
            } else {
                cout << "Error al actualizar la inscripcion." << endl;
            }

            system("pause");
            break;
        }

        case 0:
            cout << "Saliendo del menú de Clases..." << endl;
            break;
    }
}
    
