#include "CPU.h"

CPU::CPU()
{
}

CPU::CPU(Adress CPUnumber)
{
	this->CPUnumber = CPUnumber;
}

CPU::~CPU()
{
}

void CPU::execute(Memoria *memoria, Registradores *reg, Adress inicio, int instrucoes, DECODE decode, Cache *cache)
{
	Word s = 0;
	this->programCounter = inicio;
	string instToDo = "";
	while (this->programCounter < instrucoes)
	{
		//s = memoria->getIntructions(this->programCounter);
		s = cache->consultCache(memoria, &this->programCounter);
		instToDo = decode.getInstruction(s);

		//NOP
		if (instToDo == "NOP")
		{
			//NOP
			this->programCounter++;
		}
		//HALT
		else if (instToDo == "HALT")
		{
			//HALT
			this->programCounter++;
			cout << "CPU: " << this->CPUnumber << " processes stopped by HALT" << endl;
			break;
		}
		//MOV_RR
		else if (instToDo == "MOV_RR")
		{
			this->programCounter++;
			this->mov_rr(memoria, reg, cache);
		}
		//MOV_RM
		else if (instToDo == "MOV_RM")
		{
			this->programCounter++;
			this->mov_rm(memoria, reg, instrucoes, cache);
		}
		//MOV_MR
		else if (instToDo == "MOV_MR")
		{
			this->programCounter++;
			this->mov_mr(memoria, reg, instrucoes, cache);
		}
		//MOV_RI
		else if (instToDo == "MOV_RI")
		{
			this->programCounter++;
			this->mov_ri(memoria, reg, cache);
		}
		//MOV_MI
		else if (instToDo == "MOV_MI")
		{
			this->programCounter++;
			this->mov_mi(memoria, instrucoes, cache);
		}
		//ADD
		else if (instToDo == "ADD")
		{
			this->programCounter++;
			this->add(memoria, reg, cache);
		}
		//SUB
		else if (instToDo == "SUB")
		{
			this->programCounter++;
			this->sub(memoria, reg, cache);
		}
		//CMP
		else if (instToDo == "CMP")
		{
			this->programCounter++;
			this->cmp(memoria, reg, cache);
		}
		//JMP
		else if (instToDo == "JMP")
		{
			this->programCounter++;
			this->jmp(memoria, cache);
		}
		//JZ
		else if (instToDo == "JZ")
		{
			this->programCounter++;
			this->jz(memoria, cache);
		}
		//JG
		else if (instToDo == "JG")
		{
			this->programCounter++;
			this->jg(memoria, cache);
		}
		//JL
		else if (instToDo == "JL")
		{
			this->programCounter++;
			this->jl(memoria, cache);
		}
		//OUT
		else if (instToDo == "OUT")
		{
			this->programCounter++;
			this->out(memoria, reg, cache);
		}
		//INC
		else if (instToDo == "INC")
		{
			this->programCounter++;
			this->inc(memoria, reg, cache);
		}
		//DEC
		else if (instToDo == "DEC")
		{
			this->programCounter++;
			this->dec(memoria, reg, cache);
		}
		//MUL
		else if (instToDo == "MUL")
		{
			this->programCounter++;
			this->mul(memoria, reg, cache);
		}
		//DIV
		else if (instToDo == "DIV")
		{
			this->programCounter++;
			this->div(memoria, reg, cache);
		}
		else
		{
			this->programCounter++;
		}
	}

	cout << "CPU: " << this->CPUnumber << " finished!" << endl;
}

//move Rx <- Ry
void CPU::mov_rr(Memoria *memoria, Registradores *reg, Cache *cache)
{
	Adress registrador = 0, registrador1 = 0;

	registrador = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	registrador1 = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	reg->setReg(registrador, reg->getValueOfReg(registrador1));
}

//move Rx <- M
void CPU::mov_rm(Memoria *memoria, Registradores *reg, int instructions, Cache *cache)
{
	Adress registrador = 0;
	Adress mem = 0;

	registrador = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	mem = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	if (mem > instructions)
	{
		reg->setReg(registrador, cache->updateCache(memoria, &mem));
	}
	else
	{
		cout << "ERRO AO ALOCAR MEMORIA" << endl;
		cout << "MEMORIA INACESSIVEL" << endl;
	}
}

//move M <-Rx
void CPU::mov_mr(Memoria *memoria, Registradores *reg, int instructions, Cache *cache)
{
	Adress registrador = 0;
	Adress mem = 0;

	mem = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	registrador = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	if (mem > instructions)
	{
		if (!memoria->alocaInstrucao(mem, reg->getValueOfReg(registrador)))
		{
			cout << "ERRO AO ALOCAR VALOR DE REGISTRADOR NA MEMORIA!!!" << endl;
			cout << "MOV_MR" << endl;
		}
	}
	else
	{
		cout << "ERRO AO ALOCAR MEMORIA" << endl;
		cout << "MEMORIA INACESSIVEL" << endl;
	}
}

//move Rx <-I
void CPU::mov_ri(Memoria *memoria, Registradores *reg, Cache *cache)
{
	Adress registrador = 0, imediato = 0;

	registrador = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	imediato = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	reg->setReg(registrador, imediato);
}

//move M <-I
void CPU::mov_mi(Memoria *memoria, int instrucitons, Cache *cache)
{
	Word imediato = 0;
	Adress mem = 0;

	mem = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	imediato = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	if (mem > instrucitons)
	{
		if (!memoria->alocaInstrucao(mem, imediato))
		{
			cout << "ERRO AO ALOCAR VALOR DE REGISTRADOR NA MEMORIA!!!" << endl;
			cout << "MOV_MR" << endl;
		}
	}
	else
	{
		cout << "ERRO AO ALOCAR MEMORIA" << endl;
		cout << "MEMORIA INACESSIVEL" << endl;
	}
}

//Rx <- Rx + Ry
void CPU::add(Memoria *memoria, Registradores *reg, Cache *cache)
{
	Adress registrador = 0, registrador1 = 0;
	Word value = 0;

	registrador = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	registrador1 = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	value = reg->getValueOfReg(registrador) + reg->getValueOfReg(registrador1);

	reg->setReg(registrador, value);
}

//Rx <-Rx - Ry
void CPU::sub(Memoria *memoria, Registradores *reg, Cache *cache)
{
	Adress registrador = 0, registrador1 = 0;
	Word value = 0;

	registrador = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	registrador1 = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	value = reg->getValueOfReg(registrador) - reg->getValueOfReg(registrador1);

	reg->setReg(registrador, value);
}

//FL <-Rx - Ry
void CPU::cmp(Memoria *memoria, Registradores *reg, Cache *cache)
{
	Adress registrador = 0, registrador1 = 0;

	registrador = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	registrador1 = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	this->flag = reg->getValueOfReg(registrador) - reg->getValueOfReg(registrador1);
}

//I = absolute address
void CPU::jmp(Memoria *memoria, Cache *cache)
{
	Adress mem = 0;

	mem = cache->consultCache(memoria, &this->programCounter);
	this->programCounter = memoria->getAdressOfInstruction(mem, this->programCounter);
}

//I = relative jump if FL == 0
void CPU::jz(Memoria *memoria, Cache *cache)
{
	if (this->flag == 0)
	{
		Adress mem = 0;

		mem = cache->consultCache(memoria, &this->programCounter);
		this->programCounter = memoria->getAdressOfInstruction(mem, this->programCounter);
	}
	else
	{
		this->programCounter++;
	}
}

//I = relative jump if FL > 0
void CPU::jg(Memoria *memoria, Cache *cache)
{
	if (this->flag > 0)
	{
		Adress mem = 0;

		mem = cache->consultCache(memoria, &this->programCounter);
		this->programCounter = memoria->getAdressOfInstruction(mem, this->programCounter);
	}
	else
	{
		this->programCounter++;
	}
}

//I = relative jump if FL < 0
void CPU::jl(Memoria *memoria, Cache *cache)
{
	if (this->flag < 0)
	{
		Adress mem = 0;

		mem = cache->consultCache(memoria, &this->programCounter);
		this->programCounter = memoria->getAdressOfInstruction(mem, this->programCounter);
	}
	else
	{
		this->programCounter++;
	}
}

//prints out Rx value
void CPU::out(Memoria *memoria, Registradores *reg, Cache *cache)
{
	Adress registrador = 0;
	string value = "";
	string name = "";

	registrador = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	value = to_string(reg->getValueOfReg(registrador));
	name = reg->getNameOfReg(registrador);

	cout << name << ": " << value << endl;
}

//Rx <- Rx + 1
void CPU::inc(Memoria *memoria, Registradores *reg, Cache *cache)
{
	Adress registrador = 0;
	Word value = 0;

	registrador = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	value = reg->getValueOfReg(registrador) + 1;

	reg->setReg(registrador, value);
}

//Rx <- Rx - 1
void CPU::dec(Memoria *memoria, Registradores *reg, Cache *cache)
{
	Adress registrador = 0;
	Word value = 0;

	registrador = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	value = reg->getValueOfReg(registrador) - 1;

	reg->setReg(registrador, value);
}

//Rx <-Rx * Ry
void CPU::mul(Memoria *memoria, Registradores *reg, Cache *cache)
{
	Adress registrador = 0, registrador1 = 0;
	Word value = 0;

	registrador = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	registrador1 = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	value = reg->getValueOfReg(registrador) * reg->getValueOfReg(registrador1);

	reg->setReg(registrador, value);
}

//Rx <-Rx / Ry
void CPU::div(Memoria *memoria, Registradores *reg, Cache *cache)
{
	Adress registrador = 0, registrador1 = 0;
	Word value = 0, rest = 0;

	registrador = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	registrador1 = cache->consultCache(memoria, &this->programCounter);
	this->programCounter++;

	value = reg->getValueOfReg(registrador) / reg->getValueOfReg(registrador1);
	rest = reg->getValueOfReg(registrador) % reg->getValueOfReg(registrador1);

	reg->setReg(registrador, value);
	reg->setReg(registrador1, rest);
}