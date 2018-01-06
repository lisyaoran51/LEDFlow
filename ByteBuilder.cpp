#include "ByteBuilder.h"


ByteBuilder* ByteBuilder::Set(int rReg, int cReg) {
	rowReg = rReg;
	colReg = cReg;
	return this;
}

ByteBuilder* ByteBuilder::Add(int key) {
	keys.add(key);
	return this;
}

Byte* ByteBuilder::Build() {

}