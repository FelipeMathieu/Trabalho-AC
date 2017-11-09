#include "LerArquivo.h"

LerArquivo::LerArquivo()
{
}

LerArquivo::~LerArquivo()
{
}

vector<int> LerArquivo::lerArq_retornaVetor(string nomeArquivo)
{
	ifstream file(nomeArquivo);
	string line = "";
	vector<int> comandos = *new vector<int>();

	if (file.is_open())
	{
		while (!file.eof())
		{
			getline(file, line);
			comandos.push_back(atoi((const char*)line.c_str()));
		}
		file.close();
	}

	return comandos;
}
