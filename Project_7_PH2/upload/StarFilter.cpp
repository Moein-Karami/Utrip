#include "StarFilter.hpp"
#include "Hotel.hpp"

using namespace std;

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
	return chosen_hotels;
}