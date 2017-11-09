#include "Memoria.h"

Memoria::Memoria()
{
	this->memoria = *new vector<Word>(pow(2, 24));
}

Memoria::~Memoria()
{
}

void Memoria::alocaComandos(Adress inicio, vector<Word> comandos)
{
	for (int i = 0; i < comandos.size(); i++)
	{
		this->memoria[inicio] = comandos.at(i);
		inicio++;
	}
}

Word Memoria::getIntructions(Adress programCounter)
{
	if (programCounter < (int)this->memoria.size())
	{
		return this->memoria.at(programCounter);
	}
	
	cout << "ENDERECO DE MEMORIA INVALIDO" << endl;
}

bool Memoria::alocaInstrucao(Adress adress, Word value)
{
	if (adress < (int)this->memoria.size())
	{
		this->memoria.at(adress) = value;
		return true;
	}

	return false;
}

Adress Memoria::getAdressOfInstruction(Word value, Adress valueOfProgramCounter)
{
	for (int i = 0; i < this->memoria.size(); i++)
	{
		if (value == this->memoria.at(i) && i != valueOfProgramCounter)
		{
			return i;
		}
	}

	return value;
}

vector<pair<BIN, Word>> Memoria::returnToCache(BIN t, Adress pc)
{
	string tMem = "";
	string bin = "";
	string wMem = "";

	bitset<24> binMem;

	vector<pair<BIN, Word>> c(64);
	int j = 0;

	for (int i = pc; i < (int)this->memoria.size(); i++)
	{
		binMem = i;
		bin = binMem.to_string();
		wMem = bin.substr(bin.length() - 6);
		tMem = bin.substr(0, 11);

		if (t.compare(tMem) == 0)
		{
			c.at(j) = *new pair<BIN, Word>(wMem, this->memoria.at(i));
			j++;
		}
		if (j == 64)
		{
			break;
		}

		bin = "";
		wMem = "";
		tMem = "";
	}

	return c;
}