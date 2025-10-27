#include <iostream>
#include "persona.h"

using namespace std;

int main()
{
    int opc;
    while(true){
        system("cls");
        cout<<"MENU PRINCIPAL"<<endl;
        cout<<"====================="<<endl;
        cout<<"1 - CARGAR CLIENTE"<<endl;
        cout<<"2 - REPORTES"<<endl;
        cout<<"3 - CONFIGURACIONES"<<endl;
        cout<<"0 - SALIR"<<endl;
        cout<<"======================"<<endl;
        cout<<"INGRESE UNA OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc){
            case 1:
                Persona per;
                per.Cargar();
                break;
                return 0;
        }
        system("pause");
    }
}
