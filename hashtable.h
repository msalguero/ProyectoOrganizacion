#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "ManejadorArchivos.h"
#include "MetaDataReg.h"
#include "Register.h"

class HashTable
{
public:
    ManejadorArchivos* bloqueTablaHash;
    MetaDataReg* metaData;
    HashTable(ManejadorArchivos* archivo, MetaDataReg* metaData);

    int hash(char * llave);
    int tam;
    int Agregar(char *llave, int valor);
    Register *Buscar( char * llave);
    void Eliminar(char* llave);
};

#endif // HASHTABLE_H
