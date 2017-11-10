#include "Cache.h"

Cache::Cache()
{
	this->cache = *new vector<pair<Tag, vector<pair<Tag, Word>>>>(128);

	for (int i = 0; i < 128; i++)
	{
		this->cache.at(i).second = *new vector<pair<Tag, Word>>(64);
	}
}

Cache::~Cache()
{
}

Word Cache::consultCache(Memoria *memoria, Adress pc)
{
	bitset<24> b = pc;
	string bin = b.to_string();

	string w = "";
	string t = "";
	string r = "";

	t = bin.substr(0, 11);
	r = bin.substr(11, 7);
	w = bin.substr(18, 6);

 	int linhaR = std::stoi(r, nullptr, 2);

	if (this->cache.at(linhaR).first == "")
	{
		cout << "Cache miss" << endl;
		vector<pair<Tag, Word>> c;
		c = memoria->returnToCache(t, pc);
		this->cache.at(linhaR).first = t;
		this->cache.at(linhaR).second = c;

		auto values = find_if(this->cache.at(linhaR).second.begin(), this->cache.at(linhaR).second.end(),
			[&w](const pair<Tag, Word>&p) { return p.first == w; });

		pair<Tag, Word> aux = *values._Ptr;
		return aux.second;
	}
	else
	{
		Adress tag = std::stoi(this->cache.at(linhaR).first, nullptr, 2);
		if (stoi(t, nullptr, 2) == tag)
		{
			cout << "Cache hit" << endl;
			auto values = find_if(this->cache.at(linhaR).second.begin(), this->cache.at(linhaR).second.end(),
				[&w](const pair<Tag, Word>&p) { return p.first == w; });

			pair<Tag, Word> aux = *values._Ptr;
			return aux.second;
		}
	}

	return 0;
}

Word Cache::updateCache(Memoria *memoria, Adress pc)
{
	bitset<24> b = pc;
	string bin = b.to_string();

	string w = "";
	string t = "";
	string r = "";

	t = bin.substr(0, 11);
	r = bin.substr(11, 7);
	w = bin.substr(18, 6);

	int linhaR = std::stoi(r, nullptr, 2);

	if (this->cache.at(linhaR).first == "")
	{
		return this->consultCache(memoria, pc);
	}
	else
	{
		Adress tag = std::stoi(this->cache.at(linhaR).first, nullptr, 2);
		if (stoi(t, nullptr, 2) == tag)
		{
			cout << "Cache hit" << endl;
			for (int i = 0; i < 64; i++)
			{
				if (this->cache.at(linhaR).second.at(i).first == w)
				{
					this->cache.at(linhaR).second.at(i).second = memoria->getIntructions(pc);
					return this->cache.at(linhaR).second.at(i).second;
				}
			}
		}
	}

	return 0;
}