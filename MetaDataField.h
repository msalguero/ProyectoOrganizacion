#ifndef METADATAFIELD_H
#define METADATAFIELD_H
#include <string.h>
#include <stdlib.h>

class MetaDataField
{
    public:
        int tipoDato;
        char *nombreCampo;
        int tamanioCampo;
        static int const SIZE = 28;
        MetaDataField(int tipoDato, char *nombreCampo, int tamanio);
        MetaDataField();
        virtual ~MetaDataField();

        char* toBytes();
        void fromBytes(char *bytes);
    protected:
    private:
};

#endif // METADATAFIELD_H
