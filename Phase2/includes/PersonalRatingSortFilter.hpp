#ifndef _PersonalRatingSortFilter_hpp_
#define _PersonalRatingSortFilter_hpp_

#include "LibrariesAndDefines.hpp"
#include "Filter.hpp"

class User;
class Hotel;

typedef std::pair<double, Hotel*> HotelPair;

class PersonalRatingSortFilter : public Filter
{
	protected : 
		User* user;
		bool is_ascending;
	public :
		PersonalRatingSortFilter(User* _user, bool _is_ascending);
		std::vector<Hotel*> purification(const std::vector<Hotel*> hotels);
		static bool compare(HotelPair hotel_pair1, HotelPair hotel_pair2);
};

#endif