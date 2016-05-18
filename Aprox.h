#pragma once

#include <vector>
#include "Backpack.h"

class Aprox
{
private:
	float scale;
	float errorLimiter;
	Backpack backpack;

	std::vector<Element *> products;

public:
	Aprox(Backpack backpack, float errorLimiter);
	void calculate();
	~Aprox();
};

