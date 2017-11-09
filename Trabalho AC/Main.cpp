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
Registradores reg;
DECODE decode;
Cache cache = *new Cache();
vector<CPU> cores(4);


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

void startCPU(CPU *cpu, Adress number, int numberOfInstructions)
{
	cpu->execute(&memoria, &reg, number, numberOfInstructions, decode, &cache);
}

int main()
{
	vector<thread> threads;

	int numberOfInstructions = 0;
	numberOfInstructions = loader("Assembler/Codificacao.txt", 0);

	for (int i = 0; i < 1; i++)
	{
		cores.at(i) = *new CPU(i);
		threads.push_back(thread(startCPU, &cores.at(i), i, numberOfInstructions));
	}

	for (int i = 0; i < threads.size(); i++)
	{
		threads.at(i).join();
	}

	system("pause");
	return 0;
}