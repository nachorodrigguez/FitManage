#pragma once

class ManagerReportes{
    public:
        ManagerReportes(std::string nombreArchivoCobranzas);
        void run();

    protected:
        void mostrarOpciones();
        int seleccionOpcion();
        void ejecutarOpcion(int opcion);

    private:
        int _cantidadOpciones;
};
