#include "stdafx.h"
#include "Element.h"

// konstruktor domyslny
Element::Element()
{
	this->size = 0;
	this->value = 0;
	this->factor = 0;
}


// argumenty konstruktora: s- waga elementu, v- wartosc elementu
Element::Element(unsigned int s, unsigned int v)
{
	this->size = s;
	this->value = v;
	this->factor = value / size; // wspolczynnik danego elementu wyliczany jako stosunek wartosci do wagi
}


Element::~Element() {}

// funkcja zwracajaca wage danego elementu
unsigned Element::getSize()
{
	return this->size;
}

// funkcja zwracajaca wartosc danego elementu
unsigned Element::getValue()
{
	return this->value;
}

// funkcja zwracajaca wspolczynnik danego elementu
float Element::getFactor()
{
	return this->factor;
}