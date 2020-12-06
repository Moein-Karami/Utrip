#include "Filter.hpp"
#include "Hotel.hpp"

using namespace std;

Filter::Filter(string _type)
	: type(_type) {}

bool Filter::compareById(Hotel* hotel1, Hotel* hotel2)
{
	return hotel1 -> getId() < hotel2 ->getId(); 
}

vector<Hotel*> Filter::purification(const vector<Hotel*> hotels)
{
	vector<Hotel*> sorted_hotels = hotels;
	sort(sorted_hotels.begin(), sorted_hotels.end(), Filter::compareById);
	return sorted_hotels;
}

string Filter::getType()
{
	return type ;
}

CityFilter::CityFilter(string _city)
	: Filter(CITY_FILTER), city(_city) {}

vector<Hotel*> CityFilter::purification(const vector<Hotel*> hotels)
{
	vector<Hotel*> chosen_hotels ;
	for(auto hotel : hotels)
		if(hotel -> getCity() == city)
			chosen_hotels.push_back(hotel);
	return Filter::purification(chosen_hotels);
}

StarFilter::StarFilter(int _min_star, int _max_star)
	: Filter(STAR_FILTER), min_star(_min_star), max_star(_max_star) {}

vector<Hotel*> StarFilter::purification(const vector<Hotel*> hotels)
{
	vector<Hotel*> chosen_hotels;
	int hotel_star;
	for(auto hotel : hotels)
	{
		hotel_star = hotel -> getStar();
		if(min_star <= hotel_star && hotel_star <= max_star)
			chosen_hotels.push_back(hotel);
	}
	return Filter::purification(chosen_hotels);
}

CostFilter::CostFilter(double _min_cost, double _max_cost)
	: Filter(COST_FILTER), min_cost(_min_cost), max_cost(_max_cost) {}

vector<Hotel*> CostFilter::purification(const vector<Hotel*> hotels)
{
	vector<Hotel*> chosen_hotels;
	for(auto hotel : hotels)
	{
		double hotel_average_cost = hotel -> getAverageCost();
		if(min_cost <= hotel_average_cost && hotel_average_cost <= max_cost)
			chosen_hotels.push_back(hotel);
	}
	return Filter::purification(chosen_hotels);
}

AvailableRoomFilter::AvailableRoomFilter(string _type, int _quantity, int _check_in, int _check_out)
	: Filter(ROOM_FILTER), type(_type), quantity(_quantity), check_in(_check_in), check_out(_check_out) {}

vector<Hotel*> AvailableRoomFilter::purification(const vector<Hotel*> hotels)
{
	vector<Hotel*> chosen_hotels;
	for(auto hotel : hotels)
		if(hotel -> canReserveRooms(type, quantity, check_in, check_out))
			chosen_hotels.push_back(hotel);
	return Filter::purification(chosen_hotels);
}