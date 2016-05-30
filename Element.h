#pragma once
/*
Backpack's element representation
*/
class Element
{
private:
	unsigned weight = 0;
	unsigned value = 0;
	float factor = 0;
public:
	Element();
	Element(unsigned int weight, unsigned int value);
	~Element();
	const unsigned getWeight();
	const unsigned getValue();
	const float getFactor();
};



