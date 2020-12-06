#include "Reservation.hpp"
#include "Room.hpp"

using namespace std;

Reservation::Reservation(vector<Room*> _rooms, string _hotel_id, int _check_in,
			int _check_out, double _total_cost)
	: rooms(_rooms), hotel_id(_hotel_id), check_in(_check_in), check_out(_check_out),
		total_cost(_total_cost) {}

stringstream Reservation::printRooms()
{
	stringstream output;
	for(auto room : rooms)
		output<<room -> getName()<<SPACE;
	return output;
}

stringstream Reservation::printForUser()
{
	stringstream output;
	output << ID << COLON << SPACE << id << SPACE;
	output << HOTEL << COLON << SPACE << hotel_id << SPACE;
	output << ROOM << COLON << SPACE << rooms.back() -> getType() << SPACE;
	output << QUANTITY << COLON << SPACE << rooms.size() << SPACE;
	output << COST << COLON << SPACE << fixed << setprecision(ZERO) << total_cost << SPACE;
	output << CHECK_IN << SPACE << check_in << SPACE;
	output << CHECK_OUT << SPACE << check_out << SPACE;
	return output;
}

void Reservation::deleteReserve()
{
	for(auto room : rooms)
		room -> deleteReserve(this);
}

bool Reservation::isFreeInPeriod(int start, int finish)
{
	if(start >= check_in && start <= check_out)
		return false;
	if(finish >= check_in && finish <= check_out)
		return false;
	return true;
}

int Reservation::getBegin()
{
	return check_in;
}

int Reservation::getEnd()
{
	return check_out;
}

void Reservation::setId(int _id)
{
	id = _id;
}

int Reservation::getId()
{
	return id;
}

double Reservation::getTotalCost()
{
	return total_cost;
}

void Reservation::getRooms()
{
	for(auto room : rooms)
		room -> addReserve(this);
}

pair<int, int> Reservation::getReserveInformation()
{
	return pair<int,int>(rooms.size(), rooms.back() -> getPrice());
}
