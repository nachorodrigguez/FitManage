#include <iostream>
#include <cstring>
#include <string>
#include "Plan.h"

using namespace std;

//CONSTRUCTOR
int Plan::ultimoID = 0;
Plan::Plan(int id, const char* tip, const char* per, float pre, int dur){
  idPlan = ++ultimoID;
  strcpy(tipoPlan, "Indefinido");
  strcpy(descripcion, "Indefinido");
  strcpy(periodo, "Indefinido");
  precio = pre;
  duracionMeses = dur;

}

void Plan::Mostrar() const {
  cout << "ID Plan: " << idPlan << endl;
  cout << "Tipo: " << tipoPlan << endl;
  cout << "Descripcion: " << descripcion << endl;
  cout << "Periodo: " << periodo << endl;
  cout << "Precio: $" << precio << endl;
  cout << "Duracion: " << duracionMeses << " meses" << endl;
}

//SETTERS
void Plan::setIdPlan(int id) { idPlan = id; }
void Plan::setTipoPlan (const char* tip) {strcpy(tipoPlan, tip);}
void Plan::setPeriodo(const char* per) { strcpy(periodo, per); }
void Plan::setPrecio(float pre) { precio = pre; }
void Plan::setDuracion(int dur) { duracionMeses = dur; }

//GETTERS
int Plan::getIdPlan() const { return idPlan; }
const char* Plan::getTipo() const { return tipoPlan; }
const char* Plan::getDescripcion() const { return descripcion; }
const char* Plan::getPeriodo() const { return periodo; }
float Plan::getPrecio() const { return precio; }
int Plan::getDuracion() const { return duracionMeses; }

void Plan::Cargar() {
    cout << "Cargando Plan #" << idPlan << endl;

    cin.ignore();
    string tipoDePlan;
    cout << "INGRESE EL NOMBRE DEL PLAN: ";
    getline(cin, tipoDePlan);
    strncpy(tipoPlan, tipoDePlan.c_str(), sizeof(tipoPlan) - 1);
    tipoPlan[sizeof(tipoPlan) - 1] = '\0';

    string descripcionDelPlan;
    cout << "INGRESE LA DESCRIPCION DEL PLAN: ";
    getline(cin, descripcionDelPlan);
    strncpy(descripcion, descripcionDelPlan.c_str(), sizeof(descripcion) - 1);
    descripcion[sizeof(descripcion) - 1] = '\0';

    int opcionDePeriodo = 0;
    do {
        cout << "\nSeleccione el periodo:" << endl;
        cout << "1 - Mensual" << endl;
        cout << "2 - Anual" << endl;
        cout << "Opcion: ";
        cin >> opcionDePeriodo;

        if (opcionDePeriodo < 1 || opcionDePeriodo > 2) {
            cout << "Opcion invalida. Intente nuevamente.\n";
        }
    } while (opcionDePeriodo < 1 || opcionDePeriodo > 2);
    if (opcionDePeriodo == 1) strcpy(periodo, "Mensual");
    else strcpy(periodo, "Anual");

    cout << "\nIngrese el precio del plan: $";
    cin >> precio;

    cout << "Ingrese la duracion del plan (en meses): ";
    cin >> duracionMeses;
}
