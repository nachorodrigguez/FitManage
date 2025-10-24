#include <iostream>
using namespace std;

#include "Examen.h"
#include "OrdenProduccion.h"
#include "ArchivoOrdenProduccion.h"

void Examen::EjemploDeListado(){
   ArchivoOrdenProduccion archivo("ordenes_produccion.dat");
   OrdenProduccion registro;

   int i, cantidadRegistros = archivo.CantidadRegistros();
   for(i = 0; i < cantidadRegistros; i++){
      registro = archivo.Leer(i);
      cout << registro.toCSV() << endl;
   }
}

void Examen::Punto1(){
    ArchivoOrdenProduccion archivo("ordenes_produccion.dat");
    OrdenProduccion registro;

    int i, cantidadRegistros = archivo.CantidadRegistros();
    float mayorTiempo [15]={0};

    for (i = 0; i < cantidadRegistros; i++){
        registro = archivo.Leer(i);
        if (registro.getFecha().getAnio() == 2024 and registro.getFecha().getMes() <=6){
            mayorTiempo[registro.getIDMaquina()-1] +=registro.getTiempoEnHoras();
        }
    }

    float maximo = mayorTiempo[0];
    int maximoHoras = 1;

    for (int i=1; i<15; i++){
        if(mayorTiempo[i] > maximo){
            maximo = mayorTiempo[i];
            maximoHoras = i + 1;
        }
    }

    cout <<"La maquina con mas tiempo de trabajo en el segundo semestre de 2024 es: "
    << maximoHoras<< endl;
}

void Examen::Punto2(){
    ArchivoOrdenProduccion archivo("ordenes_produccion.dat");
    OrdenProduccion registro;

    int i, cantidadRegistros = archivo.CantidadRegistros();
    float mayorGasto [15]={0};

    for (i = 0; i < cantidadRegistros; i++){
        registro = archivo.Leer(i);
        if (registro.getIDTipoPieza() == 15){
            mayorGasto[registro.getIDMaquina() - 1] += registro.getCosto();
        }
    }

    int contador = 0;
    for (int i=0; i <15; i++){
        if (mayorGasto[i] > 90000){
            contador++;
        }
    }

    cout << "La cantidad de maquinas que gastaron mas de $90.000 en la pieza 15 son: "
    << contador << endl;
}

void Examen::Punto3(){
    ArchivoOrdenProduccion archivo("ordenes_produccion.dat");
    OrdenProduccion registro;

    int i, cantidadRegistros = archivo.CantidadRegistros();
    int anioMateriaPrima[15]={0};
    float mayorMateriaPrima[15]={0};
    float maquinas2025[15]={0};

    for (i = 0; i < cantidadRegistros; i++){
        registro = archivo.Leer(i);
        mayorMateriaPrima[registro.getIDMaquina() - 1] += registro.getCantidadMateriaPrima();
        anioMateriaPrima[registro.getIDMaquina() - 1] = registro.getFecha().getAnio();
        if(anioMateriaPrima[registro.getIDMaquina()-1] != registro.getFecha().getAnio() and mayorMateriaPrima[registro.getIDMaquina()-1] > registro.getCantidadMateriaPrima
           ()){
            maquinas2025[registro.getIDMaquina() - 1] = registro.getIDMaquina();
           }
    }

    if (maquinas2025[registro.getIDMaquina()-1] !=0){
        cout << "Las maquinas que gastaron mas materia prima en 2025 que en 2024 son: "<< endl;
        for (i=0; i<15; i++){
            cout << "Maquina #" << maquinas2025[i];
        }
    }
}
