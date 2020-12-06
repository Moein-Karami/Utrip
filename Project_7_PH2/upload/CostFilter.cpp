#include "CostFilter.hpp"
#include "Hotel.hpp"

using namespace std;

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
	return chosen_hotels;
}