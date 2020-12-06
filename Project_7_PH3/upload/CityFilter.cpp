#include "CityFilter.hpp"
#include "Hotel.hpp"

using namespace std;

CityFilter::CityFilter(string _city)
	: Filter(CITY_FILTER), city(_city) {}

vector<Hotel*> CityFilter::purification(const vector<Hotel*> hotels)
{
	vector<Hotel*> chosen_hotels ;
	for(auto hotel : hotels)
		if(hotel -> getCity() == city)
			chosen_hotels.push_back(hotel);
	return chosen_hotels;
}