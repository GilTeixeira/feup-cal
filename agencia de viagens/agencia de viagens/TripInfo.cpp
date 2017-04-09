#include "TripInfo.h"


TripInfo::TripInfo(string type, int time_in_minutes, double price_in_euros)
{
	this->type = type;
	this->time_in_minutes = time_in_minutes;
	this->price_in_euros = price_in_euros;
}

string TripInfo::getType() const
{
	return type;
}

unsigned int TripInfo::getTime() const
{
	return time_in_minutes;
}

double TripInfo::getPrice() const
{
	return price_in_euros;
}

ostream& operator<<(ostream& out, const TripInfo & trip) {
	out << "Tipo de transporte: " << trip.type << endl;
	out << std::fixed << std::setprecision(2) <<"Preco: " << trip.price_in_euros << "€" << endl;
	out << "Tempo de viagem: " << trip.time_in_minutes << " min" << endl;
	return out;
}


