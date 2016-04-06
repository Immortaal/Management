#include "stdafx.h"
#include "Element.h"

// konstruktor domyslny
Element::Element()
{
	this->purchaseCost = 0.0;
	this->sellingPrice = 0.0;
	this->profitOnSale = 0.0;
}


// argumenty konstruktora: s- waga elementu, v- wartosc elementu
Element::Element(float purchaseCost, float sellingPrice)
{
	this->purchaseCost = purchaseCost;
	this->sellingPrice = sellingPrice;
	this->profitOnSale = sellingPrice - purchaseCost; // wspolczynnik danego elementu wyliczany jako stosunek wartosci do wagi
}


Element::~Element() {}
