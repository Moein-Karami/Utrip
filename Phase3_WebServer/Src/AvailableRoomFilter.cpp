#include "AvailableRoomFilter.hpp"
#include "Hotel.hpp"

using namespace std;

AvailableRoomFilter::AvailableRoomFilter(string _type, int _quantity, int _check_in, int _check_out)
	: Filter(ROOM_FILTER), type(_type), quantity(_quantity), check_in(_check_in), check_out(_check_out) {}

vector<Hotel*> AvailableRoomFilter::purification(const vector<Hotel*> hotels)
{
	vector<Hotel*> chosen_hotels;
	for(auto hotel : hotels)
		if(hotel -> canReserveRooms(type, quantity, check_in, check_out))
			chosen_hotels.push_back(hotel);
	return chosen_hotels;
}