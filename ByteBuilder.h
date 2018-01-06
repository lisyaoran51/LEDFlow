#ifndef BYTE_BUILDER_H
#define BYTE_BUILDER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <string.h>
#include <LinkedList.h> 
#include "Pair.h"


class ByteBuilder
{
public:
	ByteBuilder* Set(int rReg, int cReg);
	ByteBuilder* Add(int key);
	Byte* Build();

private:
	int rowReg;
	int colReg;
	LinkedList<int> keys;
};

#endif //BYTE_CONVERTER_H