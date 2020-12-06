#ifndef _Rating_hpp_
#define _Rating_hpp_

#include "LibrariesAndDefines.hpp"

class Rating
{
	private :
		double location;
		double cleanliness;
		double staff;
		double facilities;
		double value_for_money;
		double overall_rating;
	public :
		Rating(double _location = ZERO, double _cleanliness = ZERO, double _staff = ZERO, 
			double _facilities = ZERO, double _value_for_money = ZERO, double _over_all_rating = ZERO);
		std::stringstream printAverage(double number_of_ratings);
		Rating operator+(const Rating& rating);
		Rating operator-(const Rating& rating);
};


#endif