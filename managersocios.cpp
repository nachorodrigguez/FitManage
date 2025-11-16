#include <iostream>
#include <limits>
#include <cstring>
#include "archivoClasexSocio.h"
#include "clasexsocio.h"
#include "fecha.h"
#include "ManagerSocios.h"
#include "rlutil.h"

using namespace std;

ManagerSocios::ManagerSocios(std::string nombreArchivo): archivoSocios(nombreArchivo){
    _cantidadOpcines = 5 ;
}

void ManagerSocios::run(){
    int opcion;
    do{
        rlutil::cls();
        opcion = seleccionOpcion();
        rlutil::cls();
        ejecutarOpcion(opcion);
    }while(opcion!=0);
}

void ManagerSocios::mostrarOpciones(){
    rlutil::setColor(rlutil::LIGHTGREEN);
    rlutil::locate(60, 10);
    rlutil::locate(60, 11); cout << "MENU PRINCIPAL";
    rlutil::locate(60, 12); cout << "=====================";
    rlutil::locate(60, 13); cout << "1 - CARGAR SOCIO";      //test ultimo commit
    rlutil::locate(60, 14); cout << "2 - MODIFICAR SOCIO";
    rlutil::locate(60, 15); cout << "3 - LISTADO DE SOCIOS"  ;
    rlutil::locate(60, 16); cout << "4 - ASIGNAR PLAN A SOCIO";
    rlutil::locate(60, 17); cout << "5 - ELIMINAR SOCIO";
    rlutil::locate(60, 18); cout << "0 - SALIR";
    rlutil::locate(60, 19); cout << "======================";
}

int ManagerSocios::seleccionOpcion(){
    int opcion;
    mostrarOpciones();
    rlutil::locate(60, 21); cout << "Opcion: ";
    cin >> opcion;

    while (opcion < 0 || opcion > _cantidadOpcines){
        rlutil::setColor(rlutil::RED);
        rlutil::locate(60, 23); cout << "Opcion incorrecta..." << endl;
        rlutil::setColor(rlutil::LIGHTGREEN);
        rlutil::locate(60, 24); cout << "Opcion: ";
        cin  >> opcion;
    }
    return opcion;
}

/* Helpers para inscripciones Socio y Clase (Plan 2 y 3) */
static int pedirIdClase(){
    int id;
    rlutil::locate(60, 10); cout << "Ingrese ID de clase (1-7): ";
    while(!(cin >> id) || id < 1 || id > 7){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        rlutil::setColor(rlutil::RED);
        rlutil::locate(60, 11); cout << "Valor invalido.";

        rlutil::setColor(rlutil::LIGHTGREEN);
        rlutil::locate(60, 12); cout << "Ingrese 1..7: ";
    }
    return id;
}


static bool existeInscripcionActiva(ArchivoClasexSocio& arc, int idSocio, int idClase){
    return arc.BuscarPorSocioYClase(idSocio, idClase) >= 0;
}

static bool crearInscripcion(ArchivoClasexSocio& arc, int idSocio, int idClase){
    // Crea y persiste una inscripción socio→clase con fecha y estado activo
    ClasexSocio reg;
    int nuevoID = arc.BuscarUltimoID() + 1;
    reg.setIDClasexSocio(nuevoID);
    reg.setIdSocio(idSocio);
    reg.setIDClase(idClase);

    Fecha f;
    rlutil::locate(60, 13);
    cout << "\nFecha de inscripcion:\n";
    f.Cargar();
    reg.setFechaInscripcion(f);
    reg.setEstado(true);

    if(arc.Guardar(reg)){
        rlutil::locate(60, 15); cout << "Inscripcion creada (ID " << nuevoID << ").\n";
        return true;
    } else {
        rlutil::locate(60, 15); cout << "Error al guardar la inscripcion.\n";
        return false;
    }
}

void ManagerSocios::ejecutarOpcion(int opcion){
    switch(opcion){
        case 1: {
            rlutil::setColor(rlutil::LIGHTGREEN);
            rlutil::locate(60, 10); cout << "=== ALTA DE SOCIO ===";

            int idNuevo;
            bool idValido = false;

            // Validación de ID duplicado
            do {
                rlutil::locate(60, 12); cout << "Ingrese ID del socio (DNI): ";
                cin >> idNuevo;

                int posicionExistente = archivoSocios.Buscar(idNuevo);
                if (posicionExistente >= 0) {
                    rlutil::setColor(rlutil::RED);
                    rlutil::locate(60, 13); cout << "Error: ya existe un socio con ese ID. Intente con otro.";
                    rlutil::setColor(rlutil::LIGHTGREEN);
                } else {
                    idValido = true;
                }
            } while (!idValido);

            socio.Cargar(idNuevo);

            // Persistencia
            if (archivoSocios.Guardar(socio)) {
                rlutil::locate(60, 15); cout << "Socio guardado exitosamente!" ;
            } else {
                rlutil::locate(60, 15); cout << "Error al guardar el socio." ;
            }

            rlutil::anykey();
            break;
        }

        case 2 :{
            int idBuscado;
            rlutil::locate(60, 10); cout << "Ingrese el ID (DNI) del socio a modificar: ";
            cin >> idBuscado;

            int posicion = archivoSocios.Buscar(idBuscado);
            if (posicion < 0) {
                rlutil::locate(60, 12); cout << "No existe un socio con ese ID." << endl;
                rlutil::anykey();
                break;
            }

            // Mostrar datos actuales
            Socio socioActual = archivoSocios.Leer(posicion);
            rlutil::locate(60, 13); cout << "\n--- Datos actuales ---\n";
            socioActual.Mostrar();

            rlutil::locate(60, 14); cout << "\n=== Reingrese los datos del socio (se guardaran como nuevos datos) ===\n";
            Socio socioNuevo;
            socioNuevo.setId(idBuscado);
            socioNuevo.Modificar();

            if (archivoSocios.ModificarPorId(idBuscado, socioNuevo)) {
                rlutil::locate(60, 15); cout << "Socio modificado correctamente.";
            } else {
                rlutil::locate(60, 15); cout << "Error al modificar el socio.";
            }
            rlutil::anykey();
            break;
        }

        case 3: {
            int cantidad = archivoSocios.CantidadRegistros();
            if (cantidad == 0) {
                rlutil::locate(60, 10); cout << "No hay socios cargados.";
                rlutil::anykey();
                break;
            }

            int opcionListado;

            do {
                rlutil::cls();
                rlutil::locate(60, 10); cout << "1 - SOCIOS ACTIVOS";
                rlutil::locate(60, 11); cout << "2 - SOCIOS INACTIVOS";
                rlutil::locate(60, 12); cout << "3 - TODOS LOS SOCIOS";
                rlutil::locate(60, 13); cout << "0 - VOLVER AL MENU PRINCIPAL";
                rlutil::locate(60, 14); cout << "===============================";
                rlutil::locate(60, 15); cout << "OPCION: ";
                cin >> opcionListado;

                if (opcionListado == 0) break;

                while (opcionListado < 0 || opcionListado > 3) {
                    rlutil::setColor(rlutil::RED);
                    rlutil::locate(60, 15); cout << "Opcion incorrecta.";

                    rlutil::setColor(rlutil::LIGHTGREEN);
                    rlutil::locate(60, 16); cout << "Opcion: ";
                    cin >> opcionListado;
                }

                rlutil::cls();

                Socio* vectorSocios = new Socio[cantidad];
                archivoSocios.Leer(cantidad, vectorSocios);
                bool hayResultados = false;

                switch (opcionListado) {
                    case 1: {
                        rlutil::locate(60, 10); cout << "=== SOCIOS ACTIVOS ===";
                        for (int i = 0; i < cantidad; i++) {
                            if (vectorSocios[i].getEstado() == true) {
                                vectorSocios[i].Mostrar();
                                rlutil::locate(60, 11); cout << "------------------" << endl;
                                hayResultados = true;
                            }
                        }
                        if (!hayResultados)
                        rlutil::locate(60, 12); cout << "NO HAY SOCIOS ACTIVOS.";
                        break;
                    }

                    case 2: {
                        rlutil::locate(60, 10); cout << "=== SOCIOS INACTIVOS ===";
                        for (int i = 0; i < cantidad; i++) {
                            if (vectorSocios[i].getEstado() == false) {
                                vectorSocios[i].Mostrar();
                                rlutil::locate(60, 11);cout << "------------------";
                                hayResultados = true;
                            }
                        }
                        if (!hayResultados)
                            rlutil::locate(60, 12); cout << "NO HAY SOCIOS INACTIVOS.";
                        break;
                    }

                    case 3: {
                        rlutil::locate(60, 10); cout << "=== TODOS LOS SOCIOS ===";
                        for (int i = 0; i < cantidad; i++) {
                            vectorSocios[i].Mostrar();
                            rlutil::locate(60, 11); cout << "------------------";
                            hayResultados = true;
                        }
                        if (!hayResultados)
                            rlutil::locate(60, 15); cout << "NO HAY SOCIOS CARGADOS.";
                        break;
                    }
                }

                delete[] vectorSocios;
                cout << endl;
                rlutil::anykey();

            } while (opcionListado != 0);

            break;
        }

        case 4: {
            // Asignar plan a socio (valida existencia, estado e IDs de plan)
            int idBuscado;
            rlutil::locate(60, 10); cout << "Ingrese el ID (DNI) del socio: ";
            cin >> idBuscado;

            int posSocio = archivoSocios.Buscar(idBuscado);
            if (posSocio < 0) {
                rlutil::locate(60, 11); cout << "No existe un socio con ese ID." << endl;
                rlutil::anykey();
                break;
            }

            Socio s = archivoSocios.Leer(posSocio);

            if (!s.getEstado()) {
                rlutil::locate(60, 12); cout << "El socio esta inactivo. No se puede asignar un plan." << endl;
                rlutil::anykey();
                break;
            }

            // Confirmación de si ya tiene plan
            if (s.tienePlan()) {
                cout << "El socio ya tiene un plan activo asignado: "
                     << s.getTipoPlan() << endl;
                cout << "Desea reemplazarlo? (1=Si / 0=No): ";
                int conf;
                while(!(cin >> conf) || (conf != 0 && conf != 1)){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Ingrese 1 o 0: ";
                }
                if (conf == 0) {
                    cout << "Operacion cancelada." << endl;
                    rlutil::anykey();
                    break;
                }
            }

            // Listado de planes activos
            ArchivoPlanes repoPlanes("planes.dat");
            int cant = repoPlanes.CantidadRegistros();
            if (cant <= 0) {
                cout << "No hay planes cargados.\n";
                rlutil::anykey();
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
                         << " | Duracion: " << vec[i].getDuracion() << " meses\n" << endl;
                    hayActivos = true;
                }
            }

            if (!hayActivos) {
                cout << "No hay planes activos.\n";
                delete[] vec;
                rlutil::anykey();
                break;
            }

            // Elección de plan por ID (validación contra archivo)
            int idPlanSel;
            cout << "\nIngrese el ID del plan a asignar: ";
            cin >> idPlanSel;

            int posPlan = repoPlanes.Buscar(idPlanSel);
            if (posPlan < 0) {
                cout << "ID de plan inexistente.\n";
                delete[] vec;
                rlutil::anykey();
                break;
            }

            Plan elegido = repoPlanes.Leer(posPlan);
            if (!elegido.getEstado()) {
                cout << "El plan esta inactivo.\n";
                delete[] vec;
                rlutil::anykey();
                break;
            }

            // Asignar plan (se guarda el tipoPlan tal como está en el plan elegido)
            s.setTipoPlan(elegido.getTipo());

            // Persistir el socio modificado en su misma posición
            if (archivoSocios.Guardar(s, posSocio)) {
                cout << "Plan asignado correctamente al socio " << s.getId()
                     << " (tipoPlan = " << s.getTipoPlan() << ").\n";
            } else {
                cout << "Error al guardar el socio con el nuevo tipo de plan.\n";
                delete[] vec;
                rlutil::anykey();
                break;
            }

            // Inscribir clases según el plan (2 = una clase, 3 = múltiples)
            {
                ArchivoClasexSocio arcIns;

                if(idPlanSel == 2){
                    int idClase = pedirIdClase();
                    if(existeInscripcionActiva(arcIns, s.getId(), idClase)){
                        cout << "El socio ya tiene esa clase activa.\n";
                    } else {
                        crearInscripcion(arcIns, s.getId(), idClase);
                    }
                }
                else if(idPlanSel == 3){
                    char mas = 's';
                    do{
                        int idClase = pedirIdClase();
                        if(existeInscripcionActiva(arcIns, s.getId(), idClase)){
                            cout << "El socio ya tiene esa clase activa.\n";
                        } else {
                            crearInscripcion(arcIns, s.getId(), idClase);
                        }
                        cout << "Desea inscribir otra clase? (s/n): ";
                        cin >> mas;
                    } while(mas=='s' || mas=='S');
                }
                // idPlanSel == 1 -> Solo gimnasio (no inscribe clases)
            }

            delete[] vec;
            rlutil::anykey();
            break;
        }

        case 5: {
            // Baja lógica del socio (marca inactivo)
            int idBuscado;
            cout << "Ingrese el ID (DNI) del socio a eliminar: ";
            cin >> idBuscado;

            int posicion = archivoSocios.Buscar(idBuscado);
            if (posicion < 0) {
                cout << "No existe un socio con ese ID." << endl;
                rlutil::anykey();
                break;
            }

            Socio socioActual = archivoSocios.Leer(posicion);
            cout << "\n--- Datos del socio a eliminar ---\n";
            socioActual.Mostrar();

            cout << "\nConfirma que desea eliminar este socio? (s/n): ";
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

            rlutil::anykey();
            break;
        }

        case 0:{
            break;
        }
    }
}
