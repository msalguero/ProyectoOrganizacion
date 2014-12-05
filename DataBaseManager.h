#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include "Table.h"
#include "ManejadorArchivos.h"

class DataBaseManager
{
    public:
        int bloqueDisponible;
        int cantTablas;
        ManejadorArchivos* archivo;
        Lista<Table*>* tablas;
        static int const SIZE_BLOQUE = 1024;

        DataBaseManager(const char *archivo);
        virtual ~DataBaseManager();

        Table* crearNuevaTabla(char* nombre);
        Table* buscarTabla(int idTabla);
        Table* buscarTabla(const char *nombre);

        void guardarMetaDataTablas();
        void leerMetaDataTablas();

        void guardarRegistrosTabla(int idTabla);
        void leerRegistrosTabla(int idTabla);
    protected:
    private:
        void guardarMetaDataCampos(Table* tabla);
        void leerMetaDataCampos(Table* tabla);
};

#endif // DATABASEMANAGER_H
