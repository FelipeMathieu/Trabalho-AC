#include<iostream>
#include "Memoria.h"
#include "DECODE.h"
#include<vector>
#include<math.h>
#include <utility>
#include <algorithm>  
#include <limits>
#include <string>
#include <bitset>

using namespace std;
using Word = int;
using Adress = unsigned int;
using Tag = string;


#pragma once
class Cache
{
private:
	vector<pair<Tag, vector<pair<Tag, Word>>>> cache;
public:
	Cache();
	~Cache();

	Word consultCache(Memoria *memoria, Adress pc);
	Word updateCache(Memoria *memoria, Adress pc);
};

