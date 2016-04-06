#pragma once
/*
Klasa reprezentuj¹ca pojedynczy element wkladany do plecaka
*/
class Element
{
private:
	unsigned size; // waga elementu
	unsigned value; // wartosc elementu
	float factor; //wspolczynnik elementu
public:
	Element();
	Element(unsigned int s, unsigned int v);
	~Element();
	unsigned getSize();
	unsigned getValue();
	float getFactor();
};



