#pragma once
class Accommodation
{
	//shashmaps com datas no futuro que alteram o preço (2*, 0.5*), por enquanto preço base só
	float price;
public:
	Accommodation();
	Accommodation(float price);
	float getPrice();
};

