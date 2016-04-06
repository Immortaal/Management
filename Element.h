#pragma once
/*
Klasa reprezentuj¹ca pojedynczy element wkladany do plecaka
*/
class Element
{
private:
//PurchaseCost, ProfitOnSale,  sellingPrice

	float purchaseCost;		//Koszt zakupu
	float sellingPrice;		//Cena przy sprzeda¿y
	float profitOnSale;		//Zarobek ze sprzeda¿y

public:
	Element();
	Element(float s, float v);
	~Element();

	float getPurchaseCost() const { return this->purchaseCost; }
	float getSellingPrice() const { return this->sellingPrice; }
	float getProfitOnSale() const { return this->profitOnSale; }

};



