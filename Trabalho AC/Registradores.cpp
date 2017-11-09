#include "Registradores.h"

Registradores::Registradores()
{
}

Registradores::~Registradores()
{
}

void Registradores::setReg(Adress reg, int value)
{
	registradores[reg] = value;
}

int Registradores::getValueOfReg(Adress reg)
{
	return registradores[reg];
}

string Registradores::getNameOfReg(Adress reg)
{
	if (reg == 0)
	{
		return "AX";
	}
	if (reg == 1)
	{
		return "BX";
	}
	if (reg == 2)
	{
		return "CX";
	}
	if (reg == 3)
	{
		return "DX";
	}

	return "ERRO, REGISTRADOR NAO EXISTE";
}