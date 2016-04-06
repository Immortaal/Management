#include "stdafx.h"
#include "Merchandise.h"

// konstruktor domyslny
Merchandise::Merchandise()
{
	this->purchaseCost = 0;
	this->sellingPrice = 0;
	this->profitOnSale = 0;
}

Merchandise::Merchandise(float purchaseCost, float sellingPrice)
{
	this->purchaseCost = purchaseCost;
	this->sellingPrice = sellingPrice;
	this->profitOnSale = sellingPrice - purchaseCost;
}

Merchandise::~Merchandise() {}
