#include "Memoria.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include "DECODE.h"
#include "CPU.h"
#include "Registradores.h"
#include <thread>
#include <Windows.h>
#include "cache.h"

using namespace std;
using Word = int;
using Adress = unsigned int;

Memoria memoria;
DECODE decode;
vector<CPU> cores;

int loader(string nomeArquivo, Adress adress)
{
	ifstream file(nomeArquivo);
	string line = "";
	vector<Word> comandos;

	if (file.is_open())
	{
		while (!file.eof())
		{
			getline(file, line);
			comandos.push_back(atoi((const char*)line.c_str()));
		}
		file.close();
	}

	memoria.alocaComandos(adress, comandos);
	return (int)comandos.size();
}

void startCPU(CPU *cpu, Registradores *reg, Adress pc, int numberOfInstructions, Cache *cache)
{
	cpu->execute(&memoria, reg, pc, numberOfInstructions, decode, cache);
}


int main()
{
	vector<thread*> threads;
	vector<int> numberOfInstructions;

	numberOfInstructions.push_back(loader("Assembler/Codificacao.txt", 0));
	numberOfInstructions.push_back(loader("Assembler/Codificacao2.txt", 150));
	numberOfInstructions.push_back(loader("Assembler/Codificacao3.txt", 666));
	numberOfInstructions.push_back(loader("Assembler/Codificacao4.txt", 420));

	threads.push_back(new thread(startCPU, new CPU(0), new Registradores(), 0, numberOfInstructions.at(0), new Cache()));
	threads.push_back(new thread(startCPU, new CPU(1), new Registradores(), 150, numberOfInstructions.at(1), new Cache()));
	threads.push_back(new thread(startCPU, new CPU(2), new Registradores(), 666, numberOfInstructions.at(2), new Cache()));
	threads.push_back(new thread(startCPU, new CPU(3), new Registradores(), 420, numberOfInstructions.at(3), new Cache()));

	for (size_t i = 0; i < threads.size(); i++)
	{
		threads.at(i)->join();
	}

	system("pause");
	return 0;
}