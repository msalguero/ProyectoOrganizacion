#ifndef MANEJADORARCHIVOS_H
#define MANEJADORARCHIVOS_H
#include "stdio.h"
#include "string.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

class ManejadorArchivos
{
    public:
        int static const TAM_BLOQUE = 1024;
        FILE * Archivo;
        ManejadorArchivos();
        virtual ~ManejadorArchivos();

        void abrirArchivo(const char *archivo);
        void abrirArchivoLectura(char* archivo);
        void cerrarArchivo();
        char *leerBloque(int numBloque);
        void escribirBloque(int numBloque, char* bloque);
        int leerEncabezado(int numBloque);
        void leerArchivo(char * data, char* archivo);
        void escribirArchivo(char * data, int cant_bytes,char* archivo);

    protected:
    private:
};

#endif // MANEJADORARCHIVOS_H
