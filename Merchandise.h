#pragma once
/*
Klasa reprezentuj¹ca pojedynczy Merchandise wkladany do plecaka
*/
class Merchandise
{
private:
//PurchaseCost, ProfitOnSale,  sellingPrice

	unsigned purchaseCost;		//Koszt zakupu
	unsigned sellingPrice;		//Cena przy sprzeda¿y
	unsigned profitOnSale;		//Zarobek ze sprzeda¿y

public:
	Merchandise();
	Merchandise(float purchaseCost, float sellingPrice);
	~Merchandise();

	unsigned getPurchaseCost() const { return this->purchaseCost; }
	unsigned getSellingPrice() const { return this->sellingPrice; }
	unsigned getProfitOnSale() const { return this->profitOnSale; }

};



