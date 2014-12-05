#ifndef METADATAREG_H
#define METADATAREG_H
#include "MetaDataField.h"
#include "Lista.h"
#include <stdlib.h>
#include <string.h>

class MetaDataReg
{
    public:
        Lista<MetaDataField*>* metaDataFields;
        int idTabla;
        char* nombre;
        int blqDataI, blqDataF;
        int blqMeta;
        int cantRegistros;
        static int const SIZE = 44;

        MetaDataReg(char* nombre);
        virtual ~MetaDataReg();
        int getSizeRegistro();
        int cantitdadCampos();
        void setName(char* nombre);

        char* toBytes();
        void fromBytes(char *bytes);
        void newField(int tipoDato, char *nombreCampo, int tamanio);
        char* getMetaDataBytes();
        void setMetaDataBytes(char* bytes);
    protected:
    private:
        int cantCampos;
};

#endif // METADATAREG_H
