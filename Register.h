#ifndef REGISTER_H
#define REGISTER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Lista.h"
#include "Field.h"
#include "MetaDataField.h"
#include "MetaDataReg.h"

class Register
{
    public:
        Lista<Field*>* campos;
        MetaDataReg *metaDatareg;

        Register(MetaDataReg *metaDatareg);
        virtual ~Register();
        void fromBytes(char* bytes);
        int toBytes(char* bytes);
    protected:
    private:
};

#endif // REGISTER_H
