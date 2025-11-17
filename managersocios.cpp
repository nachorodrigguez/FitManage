#include <iostream>
#include <limits>
#include <cstring>
#include "archivoClasexSocio.h"
#include "clasexsocio.h"
#include "fecha.h"
#include "ManagerSocios.h"

using namespace std;

ManagerSocios::ManagerSocios(std::string nombreArchivo): archivoSocios(nombreArchivo){
    _cantidadOpcines = 8 ;
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
    cout << "MENU SOCIOS"<<endl;
    cout << "====================="<< endl;
    cout << "1 - CARGAR SOCIO"<< endl;
    cout << "2 - MODIFICAR SOCIO" << endl;    //test rama backup
    cout << "3 - LISTADO DE SOCIOS" << endl;
    cout << "4 - ASIGNAR PLAN A SOCIO" << endl;
    cout << "5 - ASIGNAR CLASE A SOCIO" << endl;
    cout << "6 - ELIMINAR CLASE DE SOCIO" << endl;
    cout << "7 - ELIMINAR SOCIO" << endl;
    cout << "8 - CONSULTAS DE SOCIOS" << endl;
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

/* Helpers para inscripciones Socio y Clase (Plan 2 y 3) */
static int pedirIdClase(){
    int id;
    cout << "Ingrese ID de clase (1-7): ";
    while(!(cin >> id) || id < 1 || id > 7){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Valor invalido. Ingrese 1..7: ";
    }
    return id;
}

static bool existeInscripcionActiva(ArchivoClasexSocio& arc, int idSocio, int idClase){
    return arc.BuscarPorSocioYClase(idSocio, idClase) >= 0;
}

static bool crearInscripcion(ArchivoClasexSocio& arc, int idSocio, int idClase){
    // Crea y persiste una inscripcion socio a clase con fecha y estado activo
    ClasexSocio reg;
    int nuevoID = arc.BuscarUltimoID() + 1;
    reg.setIDClasexSocio(nuevoID);
    reg.setIdSocio(idSocio);
    reg.setIDClase(idClase);

    Fecha f;
    cout << "\nFecha de inscripcion:\n";
    f.Cargar();
    reg.setFechaInscripcion(f);
    reg.setEstado(true);

    if(arc.Guardar(reg)){
        cout << "Inscripcion creada (ID " << nuevoID << ").\n";
        return true;
    } else {
        cout << "Error al guardar la inscripcion.\n";
        return false;
    }
}

/// lo de abajo es nuevo 16/11 2da modificacion
// Lista las clases activas de un socio. Devuelve true si encuntra al menos una.
static bool listarClasesDeSocio(ArchivoClasexSocio& arc, int idSocio){
    int n = arc.CantidadRegistros();
    ClasexSocio reg;
    bool alguno = false;

    cout << "\nClases activas del socio " << idSocio << ":\n";

    for(int i = 0; i < n; i++){
        if(arc.Leer(i, reg)){
            if(reg.getIdSocio() == idSocio && reg.getEstado()){
                cout << " - ID Clase: " << reg.getIDClase()
                     << " (ID Inscripcion: " << reg.getIDClasexSocio() << ")\n";
                alguno = true;
            }
        }
    }

    if(!alguno){
        cout << "   (No tiene clases activas)\n";
    }

    return alguno;
}
/// ---------- LO DE ABAJO ES LO AGREGADO 16/11 ------ ///
// Devuelve cu├íntas clases puede tener el socio segun el tipo de plan.
// 0  = no puede inscribirse a clases
// 1  = puede tener una sola clase activa
// -1 = ilimitadas (mientras exista la clase)
static int maxClasesPorPlan(const char* tipoPlan){
    if (tipoPlan == nullptr || std::strcmp(tipoPlan, "Sin asignar") == 0) {
        return 0;
    }

    // nombres segun planes en ManagerPlanes
    if (std::strstr(tipoPlan, "FLEX") != nullptr) {
        // Solo gimnasio
        return 0;
    }
    if (std::strstr(tipoPlan, "PLUS") != nullptr) {
        // Gimnasio + 1 clase
        return 1;
    }
    if (std::strstr(tipoPlan, "TOTAL") != nullptr) {
        // Gimnasio + todas las clases
        return -1;
    }

    // Si el nombre no matchea nada conocido, por seguridad NO se le da clase
    return 0;
}

// Cuenta cuantas inscripciones activas tiene un socio
static int contarClasesActivas(ArchivoClasexSocio& arc, int idSocio){
    int n = arc.CantidadRegistros();
    ClasexSocio reg;
    int cont = 0;

    for (int i = 0; i < n; i++) {
        if (arc.Leer(i, reg)) {
            if (reg.getIdSocio() == idSocio && reg.getEstado()) {
                cont++;
            }
        }
    }
    return cont;
}

//---------------------LO DE ARRIBA ES LO AGREGADO 16/11----------
/// ABAJO NUEVO
// Compara dos fechas: devuelve true si a < b (más antigua)
static bool fechaMenor(const Fecha& a, const Fecha& b){
    if (a.getAnio() != b.getAnio()) return a.getAnio() < b.getAnio();
    if (a.getMes()  != b.getMes())  return a.getMes()  < b.getMes();
    return a.getDia() < b.getDia();
}

// Ordena el vector de socios alfabéticamente por apellido (A..Z)
static void ordenarSociosPorApellido(Socio* vec, int n){
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            const char* apeI = vec[i].getApellido();
            const char* apeJ = vec[j].getApellido();
            if (std::strcmp(apeI, apeJ) > 0) {
                Socio aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;
            }
        }
    }
}

// Ordena el vector de socios por fecha de inscripcion (de más vieja a más nueva)
static void ordenarSociosPorFechaInscripcion(Socio* vec, int n){
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            Fecha fi = vec[i].getInscripcion();
            Fecha fj = vec[j].getInscripcion();
            if (!fechaMenor(fi, fj)) {
                // si fi >= fj, los invertimos para dejar el más viejo primero
                Socio aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;
            }
        }
    }
}
///ARRIBA NUEVO
void ManagerSocios::ejecutarOpcion(int opcion){
    switch(opcion){
        case 1: {
            cout << "=== ALTA DE SOCIO ===" << endl;
            cout << endl;

            int idNuevo;
            bool idValido = false;

            // ValidaciΓö£Γöén de ID duplicado
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

            // Persistencia
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

            // Mostrar datos actuales
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
        ///CASE 3 NUEVO
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
        cout << "=== LISTADO DE SOCIOS ===" << endl;
        cout << "1 - LISTAR TODOS POR APELLIDO" << endl;
        cout << "2 - LISTAR TODOS POR FECHA DE INSCRIPCION" << endl;
        cout << "3 - LISTAR SOCIOS POR ESTADO (ACTIVO / INACTIVO)" << endl;
        cout << "0 - VOLVER AL MENU SOCIOS" << endl;
        cout << "===============================" << endl;
        cout << "OPCION: ";
        cin >> opcionListado;

        if (opcionListado == 0) break;

        while (opcionListado < 0 || opcionListado > 3) {
            cout << "OPCION INCORRECTA. INGRESE NUEVAMENTE: ";
            cin >> opcionListado;
        }

        system("cls");

        // Leer todos los socios en un vector nuevo
        Socio* vectorSocios = new Socio[cantidad];
        archivoSocios.Leer(cantidad, vectorSocios);
        bool hayResultados = false;

        switch (opcionListado) {
            case 1: {
                cout << "=== TODOS LOS SOCIOS (ORDENADOS POR APELLIDO) ===" << endl;
                ordenarSociosPorApellido(vectorSocios, cantidad);
                for (int i = 0; i < cantidad; i++) {
                    vectorSocios[i].Mostrar();
                    cout << "------------------" << endl;
                    hayResultados = true;
                }
                if (!hayResultados) {
                    cout << "NO HAY SOCIOS CARGADOS." << endl;
                }
                break;
            }

            case 2: {
                cout << "=== TODOS LOS SOCIOS (ORDENADOS POR FECHA DE INSCRIPCION) ===" << endl;
                ordenarSociosPorFechaInscripcion(vectorSocios, cantidad);
                for (int i = 0; i < cantidad; i++) {
                    vectorSocios[i].Mostrar();
                    cout << "------------------" << endl;
                    hayResultados = true;
                }
                if (!hayResultados) {
                    cout << "NO HAY SOCIOS CARGADOS." << endl;
                }
                break;
            }

            case 3: {
                int estadoBuscado;
                cout << "Ingrese estado a listar (1 = Activos, 0 = Inactivos): ";
                cin >> estadoBuscado;

                cout << "=== SOCIOS " << (estadoBuscado == 1 ? "ACTIVOS" : "INACTIVOS") << " ===" << endl;

                for (int i = 0; i < cantidad; i++) {
                    if (vectorSocios[i].getEstado() == (estadoBuscado == 1)) {
                        vectorSocios[i].Mostrar();
                        cout << "------------------" << endl;
                        hayResultados = true;
                    }
                }

                if (!hayResultados) {
                    cout << "No se encontraron socios con ese estado." << endl;
                }
                break;
            }
        }

        delete[] vectorSocios;
        cout << endl;
        system("pause");

    } while (opcionListado != 0);

    break;
} ///AGREGADO NUEVO CASE3

        /// AGREADO ABAJO 16/11 ///
        case 4: {
            // Asignar plan a socio
            int idBuscado;
            cout << "Ingrese el ID (DNI) del socio: ";
            cin >> idBuscado;

            int posSocio = archivoSocios.Buscar(idBuscado);
            if (posSocio < 0) {
                cout << "No existe un socio con ese ID." << endl;
                system("pause");
                break;
            }

            Socio s = archivoSocios.Leer(posSocio);

            if (!s.getEstado()) {
                cout << "El socio esta inactivo. No se puede asignar un plan." << endl;
                system("pause");
                break;
            }

            // Confirmacion de si ya tiene plan
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
                    system("pause");
                    break;
                }
            }

            // Listado de planes activos
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

            // Eleccion de plan por ID
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
                cout << "El plan esta inactivo.\n";
                delete[] vec;
                system("pause");
                break;
            }

            // Asignar plan (se guarda el tipoPlan tal como esta en el plan elegido)
            s.setTipoPlan(elegido.getTipo());

            // Persistir el socio modificado
            if (archivoSocios.Guardar(s, posSocio)) {
                cout << "Plan asignado correctamente al socio " << s.getId()
                     << " (tipoPlan = " << s.getTipoPlan() << ").\n";
            } else {
                cout << "Error al guardar el socio con el nuevo tipo de plan.\n";
                delete[] vec;
                system("pause");
                break;
            }

            delete[] vec;
            system("pause");
            break;
        }

        /// LO DE ARRIBA ES NUEVO 16/11
        /// LO DE ABAJO TAMBIEN NUEVA OPCION

        case 5: {
            // Asignar clase(s) a socio segun su plan
            cout << "=== ASIGNAR CLASE A SOCIO ===" << endl;

            int idBuscado;
            cout << "Ingrese el ID (DNI) del socio: ";
            cin >> idBuscado;

            int posSocio = archivoSocios.Buscar(idBuscado);
            if (posSocio < 0) {
                cout << "No existe un socio con ese ID." << endl;
                system("pause");
                break;
            }

            Socio s = archivoSocios.Leer(posSocio);

            if (!s.getEstado()) {
                cout << "El socio esta inactivo. No se puede asignar clases." << endl;
                system("pause");
                break;
            }

            if (!s.tienePlan()) {
                cout << "El socio no tiene un plan asignado. Asigne un plan primero." << endl;
                system("pause");
                break;
            }

            const char* tipoPlan = s.getTipoPlan();
            int maxClases = maxClasesPorPlan(tipoPlan);

            if (maxClases == 0) {
                cout << "El plan actual (" << tipoPlan << ") no permite inscribirse a clases." << endl;
                system("pause");
                break;
            }

            ArchivoClasexSocio arcIns;
            int clasesActuales = contarClasesActivas(arcIns, s.getId());

            if (maxClases > 0 && clasesActuales >= maxClases) {
                cout << "El socio ya tiene " << clasesActuales
                     << " clase(s) activa(s), que es el m├íximo permitido para su plan." << endl;
                system("pause");
                break;
            }

            cout << "Plan del socio: " << tipoPlan << endl;
            cout << "Clases activas actuales: " << clasesActuales << endl;

            char mas = 's';
            do {
                int idClase = pedirIdClase();

                if (existeInscripcionActiva(arcIns, s.getId(), idClase)) {
                    cout << "El socio ya tiene esa clase activa.\n";
                } else {
                    // Si el plan tiene limite, validar antes de crear una nueva
                    if (maxClases > 0 && clasesActuales >= maxClases) {
                        cout << "Se alcanzo el limite de clases para este socio.\n";
                        break;
                    }

                    if (crearInscripcion(arcIns, s.getId(), idClase)) {
                        clasesActuales++;
                    }
                }

                // Si es TOTAL (maxClases < 0) puede seguir
                if (maxClases < 0 || clasesActuales < maxClases) {
                    cout << "Desea inscribir otra clase? (s/n): ";
                    cin >> mas;
                } else {
                    cout << "Se alcanzo el limite de clases para este socio.\n";
                    mas = 'n';
                }

            } while (mas == 's' || mas == 'S');

            system("pause");
            break;
        }

        /// LO DE ARRIBA NUEVO 16/11
        // case 6 nuevo 16/11 2da ver
        case 6: {
            // Eliminar (baja logica) una clase de un socio
            cout << "=== ELIMINAR CLASE DE SOCIO ===" << endl;

            int idBuscado;
            cout << "Ingrese el ID (DNI) del socio: ";
            cin >> idBuscado;

            int posSocio = archivoSocios.Buscar(idBuscado);
            if (posSocio < 0) {
                cout << "No existe un socio con ese ID." << endl;
                system("pause");
                break;
            }

            Socio s = archivoSocios.Leer(posSocio);

            if (!s.getEstado()) {
                cout << "El socio esta inactivo. No se puede modificar sus clases." << endl;
                system("pause");
                break;
            }

            ArchivoClasexSocio arcIns;
            int totalIns = arcIns.CantidadRegistros();
            if (totalIns <= 0) {
                cout << "No hay inscripciones cargadas en el sistema." << endl;
                system("pause");
                break;
            }

            // Mostrar las clases activas de ese socio
            bool tieneClases = listarClasesDeSocio(arcIns, s.getId());
            if (!tieneClases) {
                cout << "El socio no tiene clases activas para eliminar." << endl;
                system("pause");
                break;
            }

            int idClase;
            cout << "\nIngrese el ID de la clase que desea dar de baja: ";
            cin >> idClase;

            // Buscar esa inscripcion especifica
            int posIns = arcIns.BuscarPorSocioYClase(s.getId(), idClase);
            if (posIns < 0) {
                cout << "No se encontro una inscripcion ACTIVA de ese socio a esa clase." << endl;
                system("pause");
                break;
            }

            ClasexSocio reg;
            if (!arcIns.Leer(posIns, reg)) {
                cout << "Error al leer la inscripcion." << endl;
                system("pause");
                break;
            }

            cout << "\nInscripcion encontrada:\n";
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
            if (arcIns.Sobrescribir(posIns, reg)) {
                cout << "Inscripcion dada de baja correctamente." << endl;
            } else {
                cout << "Error al actualizar la inscripcion." << endl;
            }

            system("pause");
            break;
        }
        //arriba nuevo 16/11 ver2
        case 7: {
            // Baja logica del socio (marca inactivo)
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

            system("pause");
            break;
        }

        //NUEVO
        case 8: {
            int opcionConsulta;
            do {
                system("cls");
                cout << "=== CONSULTAS DE SOCIOS ===" << endl;
                cout << "1 - BUSCAR SOCIO POR DNI" << endl;
                cout << "2 - BUSCAR SOCIOS POR NOMBRE Y APELLIDO" << endl;
                cout << "3 - LISTAR SOCIOS POR ESTADO (ACTIVOS / INACTIVOS)" << endl;
                cout << "4 - LISTAR SOCIOS POR TIPO DE PLAN" << endl;
                cout << "0 - VOLVER AL MENU SOCIOS" << endl;
                cout << "===============================" << endl;
                cout << "OPCION: ";
                cin >> opcionConsulta;

                if (opcionConsulta == 0) break;

                while (opcionConsulta < 0 || opcionConsulta > 4) {
                    cout << "OPCION INCORRECTA. INGRESE NUEVAMENTE: ";
                    cin >> opcionConsulta;
                }

                system("cls");

                int cantidad = archivoSocios.CantidadRegistros();
                if (cantidad == 0) {
                    cout << "No hay socios cargados." << endl;
                    system("pause");
                    break;
                }

                Socio* vectorSocios = new Socio[cantidad];
                archivoSocios.Leer(cantidad, vectorSocios);

                ArchivoClasexSocio arcIns; // para mostrar sus clases si queremos
                bool hayResultados = false;

                switch (opcionConsulta) {
                    case 1: {   // Buscar por DNI
                        int dniBuscado;
                        cout << "Ingrese DNI del socio a buscar: ";
                        cin >> dniBuscado;

                        int pos = archivoSocios.Buscar(dniBuscado);
                        if (pos < 0) {
                            cout << "No se encontro un socio con ese DNI." << endl;
                        } else {
                            Socio s = archivoSocios.Leer(pos);
                            s.Mostrar();
                            if (s.getEstado()) {
                                listarClasesDeSocio(arcIns, s.getId());
                            }
                        }
                        break;
                    }

                    case 2: {   // Buscar por nombre y apellido
                        char nombreBuscado[50], apellidoBuscado[50];
                        cout << "Ingrese NOMBRE (sin espacios): ";
                        cin >> nombreBuscado;
                        cout << "Ingrese APELLIDO (sin espacios): ";
                        cin >> apellidoBuscado;

                        cout << "=== SOCIOS QUE COINCIDEN CON " << nombreBuscado
                             << " " << apellidoBuscado << " ===" << endl;

                        for (int i = 0; i < cantidad; i++) {
                            if (std::strcmp(vectorSocios[i].getNombre(), nombreBuscado) == 0 &&
                                std::strcmp(vectorSocios[i].getApellido(), apellidoBuscado) == 0) {
                                vectorSocios[i].Mostrar();
                                if (vectorSocios[i].getEstado()) {
                                    listarClasesDeSocio(arcIns, vectorSocios[i].getId());
                                }
                                cout << "------------------" << endl;
                                hayResultados = true;
                            }
                        }

                        if (!hayResultados) {
                            cout << "No se encontraron socios con ese nombre y apellido." << endl;
                        }
                        break;
                    }

                    case 3: {   // Listar por estado
                        int estadoBuscado;
                        cout << "Ingrese estado a listar (1 = Activos, 0 = Inactivos): ";
                        cin >> estadoBuscado;

                        cout << "=== SOCIOS " << (estadoBuscado == 1 ? "ACTIVOS" : "INACTIVOS") << " ===" << endl;

                        for (int i = 0; i < cantidad; i++) {
                            if (vectorSocios[i].getEstado() == (estadoBuscado == 1)) {
                                vectorSocios[i].Mostrar();
                                if (vectorSocios[i].getEstado()) {
                                    listarClasesDeSocio(arcIns, vectorSocios[i].getId());
                                }
                                cout << "------------------" << endl;
                                hayResultados = true;
                            }
                        }
                        if (!hayResultados) {
                            cout << "No se encontraron socios con ese estado." << endl;
                        }
                        break;
                    }

                    case 4: {   // Listar por tipo de plan
                        char tipoPlanBuscado[50];
                        cout << "Ingrese el TIPO DE PLAN a buscar (texto exacto): ";
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cin.getline(tipoPlanBuscado, 50);

                        cout << "=== SOCIOS CON PLAN: " << tipoPlanBuscado << " ===" << endl;

                        for (int i = 0; i < cantidad; i++) {
                            if (std::strcmp(vectorSocios[i].getTipoPlan(), tipoPlanBuscado) == 0) {
                                vectorSocios[i].Mostrar();
                                if (vectorSocios[i].getEstado()) {
                                    listarClasesDeSocio(arcIns, vectorSocios[i].getId());
                                }
                                cout << "------------------" << endl;
                                hayResultados = true;
                            }
                        }

                        if (!hayResultados) {
                            cout << "No se encontraron socios con ese tipo de plan." << endl;
                        }
                        break;
                    }
                }

                delete[] vectorSocios;
                cout << endl;
                system("pause");

            } while (opcionConsulta != 0);

            break;
        }
        //nuevo mostrar
        case 0:{
            break;
        }
    }
}

