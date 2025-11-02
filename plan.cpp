#include <iostream>
#include <cstring>
#include "Plan.h"

using namespace std;


Plan::Plan(int id, const char* tip, const char* per, float pre, int dur){
  idPlan = id;
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
  cout << "Ingrese ID del plan: ";
  cin >> idPlan;
  cin.ignore();

  cout << "Ingrese tipo de plan (Flex / Plus / Total): ";
  cin.getline(tipoPlan, 30);

  if (strcmp(tipoPlan, "Flex") == 0) strcpy(descripcion, "Gimnasio");
  else if (strcmp(tipoPlan, "Plus") == 0) strcpy(descripcion, "Gimnasio + 1 Clase");
  else if (strcmp(tipoPlan, "Total") == 0) strcpy(descripcion, "Todo Libre");
  else strcpy(descripcion, "Error");

  cout << "Ingrese periodo (Mensual / Anual): ";
  cin.getline(periodo, 20);

  cout << "Ingrese precio: $";
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
  cout << "Duración: " << duracionMeses << " meses" << endl;
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

