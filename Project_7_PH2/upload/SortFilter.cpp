#include "SortFilter.hpp"
#include "Hotel.hpp"

using namespace std;

SortFilter::SortFilter(bool (*tmp)(Hotel*, Hotel*))
	: Filter(SORT_FILTER), compare(tmp) {}

vector<Hotel*> SortFilter::purification(const vector<Hotel*> hotels)
{
	vector<Hotel*> sorted_hotels = hotels;
	sort(sorted_hotels.begin(), sorted_hotels.end(), compare);
	return sorted_hotels;
}