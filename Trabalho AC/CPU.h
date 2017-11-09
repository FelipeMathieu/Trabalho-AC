#include <iostream>
#include "Registradores.h"
#include "Memoria.h"
#include <vector>
#include "DECODE.h"
#include <string>
#include "cache.h"

using namespace std;
using Adress = unsigned int;
using Word = int;

#pragma once
class CPU
{
private:
	Adress programCounter = 0;
	int flag = 0;
	Adress CPUnumber = 0;

public:
	CPU();
	CPU(Adress CPUnumber);
	~CPU();

	void execute(Memoria *memoria, Registradores *reg, Adress inicio, int instrucoes, DECODE decode, Cache *cache);
	void mov_rr(Memoria *memoria, Registradores *reg, Cache *cache);
	void mov_rm(Memoria *memoria, Registradores *reg, int instructions, Cache *cache);
	void mov_mr(Memoria *memoria, Registradores *reg, int instructions, Cache *cache);
	void mov_ri(Memoria *memoria, Registradores *reg, Cache *cache);
	void mov_mi(Memoria *memoria, int instructions, Cache *cache);
	void add(Memoria *memoria, Registradores *reg, Cache *cache);
	void sub(Memoria *memoria, Registradores *reg, Cache *cache);
	void cmp(Memoria *memoria, Registradores *reg, Cache *cache);
	void jmp(Memoria *memoria, Cache *cache);
	void jz(Memoria *memoria, Cache *cache);
	void jg(Memoria *memoria, Cache *cache);
	void jl(Memoria *memoria, Cache *cache);
	void out(Memoria *memoria, Registradores *reg, Cache *cache);
	void inc(Memoria *memoria, Registradores *reg, Cache *cache);
	void dec(Memoria *memoria, Registradores *reg, Cache *cache);
	void mul(Memoria *memoria, Registradores *reg, Cache *cache);
	void div(Memoria *memoria, Registradores *reg, Cache *cache);
};