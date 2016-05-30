#include "Element.h"


Element::Element(unsigned int weight, unsigned int value) : weight(weight),
    value(value)
{
	factor = value / weight;
}

Element::Element() {}

Element::~Element() {}

const unsigned Element::getWeight()
{
	return weight;
}

const unsigned Element::getValue()
{
	return value;
}

const float Element::getFactor()
{
	return factor;
}
