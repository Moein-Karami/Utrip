#include "PersonalRatingSortFilter.hpp"
#include "User.hpp"
#include "Hotel.hpp"

using namespace std;

typedef pair<double, Hotel*> HotelPair;

PersonalRatingSortFilter::PersonalRatingSortFilter(User* _user, bool _is_ascending)
	: Filter(SORT_FILTER), user(_user), is_ascending(_is_ascending) {}

vector<Hotel*> PersonalRatingSortFilter::purification(const vector<Hotel*> hotels)
{
	vector<HotelPair> paired_hotels;
	for_each(hotels.begin(), hotels.end(), [&](Hotel* hotel){paired_hotels.push_back(HotelPair(user -> calculateOverAllRating(hotel), hotel));});
	if(is_ascending == false)
		for_each(paired_hotels.begin(), paired_hotels.end(), [](HotelPair& tmp){tmp.first *= -ONE;});
	sort(paired_hotels.begin(), paired_hotels.end(), PersonalRatingSortFilter::compare);
	vector<Hotel*> sorted_hotels;
	for_each(paired_hotels.begin(), paired_hotels.end(), [&](HotelPair tmp){sorted_hotels.push_back(tmp.second);});
	return sorted_hotels;
}

bool PersonalRatingSortFilter::compare(HotelPair hotel_pair1, HotelPair hotel_pair2)
{
	if(hotel_pair1.first != hotel_pair2.first)
		return hotel_pair1.first < hotel_pair2.first;
	return hotel_pair1.second -> getId() < hotel_pair2.second -> getId();
}