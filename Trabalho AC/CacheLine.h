#include<iostream>

template<class Tag, class Dado>
static class CacheLine
{
public:
	Tag tag;
	Dado dado;

	CacheLine(Tag tag, Dado dado)
	{
		this->dado = dado;
		this->tag = tag;
	}

	Tag tag{ get; set; }
	Dado dado{ get; set; }
};
