#pragma once
class Accommodation
{
	//shashmaps com datas no futuro que alteram o pre�o (2*, 0.5*), por enquanto pre�o base s�
	double price;
public:
	/*Accommodation();*/
	Accommodation(double price);
	double getPrice() const;
};

