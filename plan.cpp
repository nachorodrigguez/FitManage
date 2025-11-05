#include <iostream>
#include <cstring>
#include "Plan.h"

using namespace std;

int Plan::ultimoID = 0;
Plan::Plan(int id, const char* tip, const char* per, float pre, int dur){
  idPlan = ++ultimoID;
  strcpy(tipoPlan, "Indefinido");
  strcpy(periodo, "Mensual o anual");
  precio = pre;
  duracionMeses = dur;

  if (strcmp(tip, "Flex") == 0) strcpy(descripcion, "Gimnasio");
  else if (strcmp(tip, "Plus") == 0) strcpy(descripcion, "Gimnasio + 1 Clase");
  else if (strcmp(tip, "Total") == 0) strcpy(descripcion, "Todo Libre");
  else strcpy(descripcion, "Error");
}

void Plan::Cargar() {
    cout << "Cargando Plan #" << idPlan << endl;

    int opcionTipo;
    do {
    cout << "\nSeleccione el tipo de plan:" << endl;
    cout << "1 - Flex" << endl;
    cout << "2 - Plus" << endl;
    cout << "3 - Total" << endl;
    cout << "Opcion: ";
    cin >> opcionTipo;

    if (opcionTipo < 1 || opcionTipo > 3) {
            cout << "Opción inválida. Intente nuevamente.\n";
        }
} while (opcionTipo < 1 || opcionTipo > 3);

    switch (opcionTipo) {
        case 1:
            strcpy(tipoPlan, "Flex");
            strcpy(descripcion, "Gimnasio");
            break;
        case 2:
            strcpy(tipoPlan, "Plus");
            strcpy(descripcion, "Gimnasio + 1 Clase");
            break;
        case 3:
            strcpy(tipoPlan, "Total");
            strcpy(descripcion, "Todo Libre");
            break;
        default:
            strcpy(tipoPlan, "Desconocido");
            strcpy(descripcion, "Error");
            break;
    }

    int opcionPeriodo;
    do {
        cout << "\nSeleccione el periodo:" << endl;
        cout << "1 - Mensual" << endl;
        cout << "2 - Anual" << endl;
        cout << "Opcion: ";
        cin >> opcionPeriodo;

        if (opcionPeriodo < 1 || opcionPeriodo > 2) {
            cout << "Opcion invalida. Intente nuevamente.\n";
        }
    } while (opcionPeriodo < 1 || opcionPeriodo > 2);



    if (opcionPeriodo == 1) strcpy(periodo, "Mensual");
    else if (opcionPeriodo == 2) strcpy(periodo, "Anual");
    else strcpy(periodo, "Indefinido");

    cout << "\nIngrese precio: $";
    cin >> precio;

    cout << "Ingrese duracion (en meses): ";
    cin >> duracionMeses;
}


void Plan::Mostrar() const {
  cout << "ID Plan: " << idPlan << endl;
  cout << "Tipo: " << tipoPlan << endl;
  cout << "Descripcion: " << descripcion << endl;
  cout << "Periodo: " << periodo << endl;
  cout << "Precio: $" << precio << endl;
  cout << "Duracion: " << duracionMeses << " meses" << endl;
}

void Plan::setIdPlan(int id) { idPlan = id; }

void Plan::setTipoPlan (const char* tip) {
  strcpy(tipoPlan, tip);
  if (strcmp(tipoPlan, "Flex") == 0) strcpy(descripcion, "Gimnasio");
  else if (strcmp(tipoPlan, "Plus") == 0) strcpy(descripcion, "Clases");
  else if (strcmp(tipoPlan, "Total") == 0) strcpy(descripcion, "Gimnasio+Clases");
  else strcpy(descripcion, "Desconocido");
}

void Plan::setPeriodo(const char* per) { strcpy(periodo, per); }
void Plan::setPrecio(float pre) { precio = pre; }
void Plan::setDuracion(int dur) { duracionMeses = dur; }

int Plan::getIdPlan() const { return idPlan; }
const char* Plan::getTipo() const { return tipoPlan
; }
const char* Plan::getDescripcion() const { return descripcion; }
const char* Plan::getPeriodo() const { return periodo; }
float Plan::getPrecio() const { return precio; }
int Plan::getDuracion() const { return duracionMeses; }

