#include "DECODE.h"

DECODE::DECODE()
{
}

DECODE::~DECODE()
{
}

string DECODE::getInstruction(Word i)
{
	return this->instrucoes[i];
}