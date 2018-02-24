#include "ByteBuilder.h"


ByteBuilder* ByteBuilder::Set(int lNum, int rReg, int cReg) {
	rowReg = rReg;
	colReg = cReg;
	totalReg = rowReg + colReg;
	ledNum = lNum;
	return this;
}

ByteBuilder* ByteBuilder::Add(int key) {
	keys.add(key);
	return this;
}

/*	
*	1o
*	2o |(1)
*	3o V
*	4o
*	 a b c d e f g
*	 | | | | | | | 
*		(2) ->
*
*	bytes : 1234abcdefg
*/

byte* ByteBuilder::Build() 
{

	/*	|         0 -> col       |0 -> row |
	*	|<--------ColReg-------->|< RowReg>|
	*	| b0 | b1 | b2 | b3 | b4 | b5 | b6 |
	*
	*/

	byte* bytes = new byte[totalReg];
	for (int i = 0; i < totalReg; i++) {
		bytes[i] = 0b00000000;
	}

	/*
	*	led = #11 (start from 0)   
	*
	*	                0 -> 11
	*	| b0 | b1 | b2 | b3 | b4 |
	*
	*	|<---- totalReg = 5 ---->|
	*/

	int ledByte = ledNum / 8;

	/*
	*	o 0
	*	o 1
	*	o 2
	*	o 3
	*	o 4
	*	o 5
	*	o 6
	*	o 7
	*
	*	o a
	*	o b
	*	o c
	*	o d
	*	o e
	*
	*	|<  Max Byte - 1 >|<    Max Byte   >|
	*	
	*	  0 1 2 3 4 5 6 7   a b c d e - - -
	*/

	int ledBit = ledNum % 8;
	//bytes[ totalReg - ledByte ] |= 1 << ledBit;
  bytes[ totalReg - (rowReg-ledByte) ] |= 1 << ledBit;
  
	int keyByte;
	int keyBit;
	/*
	*
	*	| | | | | | | | | | | 
	*	 0 1 2 3 4 5 6 7 8 9 
	*
	*				  0~7   8~15  16~23  ...
	*	| (RowReg) |  b0  |  b1  |  b2  |  b3  | b4 | b5 |
	*/

	for (int i = 0; i < keys.size(); i++) {
		//keyByte = keys.get(i) / 8 + rowReg;
    keyByte = keys.get(i) / 8;
		keyBit = keys.get(i) % 8;

		bytes[keyByte] |= 1 << keyBit;
	}

 return bytes;
}


