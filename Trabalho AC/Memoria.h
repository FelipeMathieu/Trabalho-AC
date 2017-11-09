#pragma once
#include<iostream>
#include<vector>
#include<math.h>
#include <bitset>
#include <utility>
#include <algorithm>  
#include <limits>
#include <string>

using namespace std;

using Word = int;
using Adress = unsigned int;
using BIN = string;

class Memoria
{
private:
	vector<Word> memoria;
public:
	Memoria();
	~Memoria();

	vector<int> getMemoria()
	{
		return this->memoria;
	}

	void alocaComandos(Adress inicio, vector<int> comandos);
	Word getIntructions(Adress programCounter);
	bool alocaInstrucao(Adress adress, Word value);
	Adress getAdressOfInstruction(Word value, Adress valueOfProgramCounter);
	vector<pair<BIN, Word>> returnToCache(BIN t, Adress pc);
};

