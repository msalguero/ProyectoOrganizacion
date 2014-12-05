#ifndef TABLE_H
#define TABLE_H
#include "MetaDataReg.h"
#include "Register.h"
#include "Lista.h"

class Table
{

    public:
        MetaDataReg* metaData;
        Lista<Register*>* registros;

        Table(char* nombre);
        virtual ~Table();

        void agregarRegistro(char* data);
        void agregarRegistro(Register* registro);
        void agregarCampo(int tipoDato, char *nombreCampo, int tamanio);

        void recibirBloqueRegistros(char * bloque);
        void recibirMetaDataTabla(char* data);
        void recibirMetaDataCampos(char* data);

        char* mandarRegistros();
        char* mandarMetaDataTabla();
        char* mandarMetaDataCampos();
    protected:
    private:

};

#endif // TABLE_H
