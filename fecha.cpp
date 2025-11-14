#include "fecha.h"
#include <iostream>
#include <iomanip>   // setw, setfill (para imprimir en los cout con un ancho minimo de caracteres predeterminado)
#include <limits>    // numeric_limits (para limpiar buffer)
#include <ctime>
//helpers
bool Fecha::esBisiesto(int a) {
    return ( (a % 4 == 0 && a % 100 != 0) || (a % 400 == 0) );
}

int Fecha::diasDelMes(int m, int a) {
    switch (m) {
        case 1:  return 31;
        case 2:  return esBisiesto(a) ? 29 : 28;
        case 3:  return 31;
        case 4:  return 30;
        case 5:  return 31;
        case 6:  return 30;
        case 7:  return 31;
        case 8:  return 31;
        case 9:  return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: return 0;
    }
}

bool Fecha::esValida(int d, int m, int a) {
    if (a < 1900 || a > 2100) return false; // ajustable a lo que pida la cátedra
    if (m < 1 || m > 12)      return false;
    int dm = diasDelMes(m, a);
    if (dm == 0)              return false;
    if (d < 1 || d > dm)      return false;
    return true;
}

//Constructores
Fecha::Fecha() : dia(1), mes(1), anio(2000) {}

Fecha::Fecha(int d, int m, int a) {
    if (esValida(d, m, a)) { dia = d; mes = m; anio = a; }
    else { dia = 1; mes = 1; anio = 2000; }
}

//Getters
int Fecha::getDia()  const { return dia;  }
int Fecha::getMes()  const { return mes;  }
int Fecha::getAnio() const { return anio; }

//Setters
Fecha Fecha::FechaActual(){
    Fecha f;
    time_t t = time(NULL);
    struct tm *fecha = localtime(&t);
    f.dia = fecha->tm_mday;
    f.mes = fecha->tm_mon + 1;
    f.anio = fecha->tm_year + 1900;
    return f;
}

void Fecha::setDia(int d) {
    if (esValida(d, mes, anio)) {
        dia = d;
    } else {
        int dm = diasDelMes(mes, anio);
        if (dm > 0) dia = (d < 1 ? 1 : dm);
    }
}

void Fecha::setMes(int m) {
    if (m < 1) m = 1;
    if (m > 12) m = 12;
    mes = m;
    int dm = diasDelMes(mes, anio);
    if (dia > dm) dia = dm;
    if (dia < 1)  dia = 1;
}

void Fecha::setAnio(int a) {
    if (a < 1900) a = 1900;
    if (a > 2100) a = 2100;
    anio = a;
    int dm = diasDelMes(mes, anio);
    if (dia > dm) dia = dm;
    if (dia < 1)  dia = 1;
}

//I/O
void Fecha::Cargar() {
    int d, m, a;
    bool ok = false;

    do {
        std::cout << "Dia: ";
        while (!(std::cin >> d)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Valor invalido. Dia: ";
        }

        std::cout << "Mes: ";
        while (!(std::cin >> m)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Valor invalido. Mes: ";
        }

        std::cout << "Anio: ";
        while (!(std::cin >> a)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Valor invalido. Anio: ";
        }

        ok = esValida(d, m, a);
        if (!ok) {
            std::cout << "Fecha invalida. Reintente (anio 1900-2100, mes 1-12, dia acorde).\n";
        }
    } while (!ok);

    dia = d; mes = m; anio = a;

    // Limpia el resto de la línea para no interferir con lecturas siguientes
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Fecha::Mostrar() const {
    std::cout << std::setfill('0')
              << std::setw(2) << dia << '/'
              << std::setw(2) << mes << '/'
              << std::setw(4) << anio
              << std::setfill(' ');
}
