#pragma once
class Accommodation
{
	//shashmaps com datas no futuro que alteram o preço (2*, 0.5*), por enquanto preço base só
	double price;
public:
	/*Accommodation();*/
	Accommodation(double price);
	double getPrice() const;
};

