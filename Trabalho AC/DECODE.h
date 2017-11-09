#include<iostream>
#include<map>

using namespace std;
using Word = int;

#pragma once
class DECODE
{
private:
	map<int, string> instrucoes = {
		{0, "NOP"},
		{1, "HALT"},
		{2, "MOV_RR"},
		{3, "MOV_RM"},
		{4, "MOV_MR"},
		{5, "MOV_RI"},
		{6, "MOV_MI"},
		{7, "ADD" },
		{8, "SUB" },
		{9, "CMP" },
		{10, "JMP" },
		{11, "JZ" },
		{12, "JG" },
		{13, "JL" },
		{14, "OUT"},
		{15, "INC"},
		{16, "DEC"},
		{17, "MUL"},
		{18, "DIV"}
	};

public:
	DECODE();
	~DECODE();

	string getInstruction(Word i);
};

