#include <iostream>
#include "managerClases.h"
#include "rlutil.h"
using namespace std;

ManagerClases::ManagerClases(string nombreArchivo) : archivoClases("clases.dat"), archivoclasesxsocio("clasexsocio.dat"),archivosocios("socios.dat")
{
    _cantidadOpciones = 5;
}

void ManagerClases::run() {
    int opcion;
    do {
        rlutil::cls();
        opcion = seleccionOpcion();
        rlutil::cls();
        ejecutarOpcion(opcion);
    } while (opcion != 0);
}

void ManagerClases::mostrarOpciones() {
    cout << "MENU CLASES" << endl;
    cout << "=====================" << endl;
    cout << "1 - AGREGAR CLASE" << endl;
    cout << "2 - LISTAR CLASES" << endl;
    cout << "3 - BUSCAR CLASE" << endl;
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
            rlutil::anykey();
            break;
        }
        case 2: {
            cout << "=== LISTADO DE CLASES ===" << endl;
            archivoClases.Listar();
            rlutil::anykey();
            break;
        }
        case 3: {
            cout << "=== BUSCAR CLASE ===" << endl;
            int id;
            cout << "Ingrese ID de clase: ";
            cin >> id;
            Clase c;
            if (archivoClases.LeerPorID(id, c)) {
                c.Mostrar();
            } else {
                cout << "No se encontró una clase con ese ID." << endl;
            }
            rlutil::anykey();
            break;
        }
        case 4:{
            int dni;
            bool idValido = false;

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

            if(socio.getEstado() == true){
                cout << "=== CLASES ==="<<endl;
                cout << "====================="<< endl;
                cout << "1) Spinning\n";
                cout << "2) Boxeo\n";
                cout << "3) Yoga\n";
                cout << "4) Crossfit\n";
                cout << "5) Pilates\n";
                cout << "6) Funcional\n";
                cout << "======================"<< endl;
            int opcion;
            cout << "Opcion: " << endl;
            cin >> opcion;

            switch(opcion){
                case 1:{
                        clasexsocio.setIDClase(opcion);
                        clasexsocio.setIdSocio(dni);
                        clasexsocio.Cargar();

                        int nuevoID = archivoclasesxsocio.CantidadRegistros() + 1;
                        clasexsocio.setIDClasexSocio(nuevoID);
                        if(archivoclasesxsocio.Guardar(clasexsocio)){
                            cout << endl;
                            cout << "Socio inscripto correctamente!" << endl;
                        }else{
                            cout << "Error al inscribir socio." << endl;
                        }
                    }
                }
            }else{
                cout << "Socio inactivo." << endl;
            }
            system("pause");
            break;
        }
        case 0:
            cout << "Saliendo del menú de Clases..." << endl;
            break;
    }
}
