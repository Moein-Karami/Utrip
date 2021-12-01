#include "Room.hpp"
#include "Reservation.hpp"

using namespace std;

Room::Room(string _name, double _price, string _type)
	: name(_name), price(_price), type(_type) 
{
	for(int i = ZERO; i <= MONTH_DAYS ; i++)
		isReservedOnDay[i] = false;
}

bool Room::isFreeInPeriod(int start, int finish)
{
	for(int i = start; i <= finish; i++)
		if(isReservedOnDay[i])
			return false; 
	return true;
}

void Room::deleteReserve(Reservation* reserve)
{
	for(int i = reserve -> getBegin() ;i <= reserve -> getEnd(); i++)
		isReservedOnDay[i] = false;
}

string Room::getName()
{
	return name;
}

string Room::getType()
{
	return type;
}

void Room::addReserve(Reservation* reserve)
{
	for(int i = reserve -> getBegin(); i <= reserve -> getEnd(); i++)
		isReservedOnDay[i] = true;
}

double Room::getPrice()
{
	return price;
}