#include <iostream>
#include <map>

using namespace std;
using Word = int;
using Adress = unsigned int;

#pragma once
class Registradores
{
private:
	map<Adress, int> registradores = {
		{ 0, 0 }, //AX
		{ 1, 0 }, //BX
		{ 2, 0 }, //CX
		{ 3, 0 } //DX
	};

public:
	Registradores();
	~Registradores();

	void setReg(Adress reg, int value);
	int getValueOfReg(Adress reg);
	string getNameOfReg(Adress reg);
};

