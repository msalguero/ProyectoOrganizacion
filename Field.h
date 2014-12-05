#ifndef FIELD_H
#define FIELD_H
#include "MetaDataField.h"
#include "string.h"

class Field
{
    public:
        MetaDataField *metaData;
        char *valor;

        Field(MetaDataField *metaData, char *valor);
        virtual ~Field();

        int toBytes(char* bytes);
    protected:
    private:
};

#endif // FIELD_H
