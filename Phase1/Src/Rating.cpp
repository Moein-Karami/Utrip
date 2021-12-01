#include "Rating.hpp"

using namespace std;

Rating::Rating(double _location, double _cleanliness, double _staff, 
	double _facilities, double _value_for_money, double _over_all_rating)
	: location(_location), cleanliness(_cleanliness), staff(_staff), facilities(_facilities),
		value_for_money(_value_for_money), overall_rating(_over_all_rating) {}

stringstream Rating::printAverage(double number_of_ratings)
{
	stringstream output;
	output << fixed << setprecision(DIGITS_AFTER_POINT);
	output << LOCATION << COLON << SPACE << location / number_of_ratings << endl;
	output << CLEANLINESS << COLON << SPACE << cleanliness / number_of_ratings << endl;
	output << STAFF << COLON << SPACE << staff / number_of_ratings << endl;
	output << FACILITIES << COLON << SPACE << facilities / number_of_ratings << endl;
	output << VALUE_FOR_MONEY << COLON << SPACE << value_for_money / number_of_ratings << endl;
	output << OVERALL_RATING << COLON << SPACE << overall_rating / number_of_ratings << endl;
	return output;
}

Rating Rating::operator+(const Rating& rating)
{
	Rating new_rating;
	new_rating.location = location + rating.location;
	new_rating.cleanliness = cleanliness + rating.cleanliness;
	new_rating.staff = staff + rating.staff;
	new_rating.facilities = facilities + rating.facilities;
	new_rating.value_for_money = value_for_money + rating.value_for_money;
	new_rating.overall_rating = overall_rating + rating.overall_rating;
	return new_rating;
}

Rating Rating::operator-(const Rating& rating)
{
	Rating new_rating;
	new_rating.location = location - rating.location;
	new_rating.cleanliness = cleanliness - rating.cleanliness;
	new_rating.staff = staff - rating.staff;
	new_rating.facilities = facilities - rating.facilities;
	new_rating.value_for_money = value_for_money - rating.value_for_money;
	new_rating.overall_rating = overall_rating - rating.overall_rating;
	return new_rating;
}