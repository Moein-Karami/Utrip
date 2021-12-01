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
		Rating(double _location , double _cleanliness , double _staff , 
			double _facilities , double _value_for_money , double _over_all_rating );
		Rating();
		std::stringstream printAverage(double number_of_ratings);
		Rating operator+(const Rating& rating);
		Rating operator-(const Rating& rating);
		double getOverAllRating(double number_of_ratings);
		std::vector<double> getValues(double number_of_ratings);
};


#endif