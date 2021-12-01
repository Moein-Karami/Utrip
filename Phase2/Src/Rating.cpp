#include "Rating.hpp"

using namespace std;

Rating::Rating(double _location, double _cleanliness, double _staff, 
	double _facilities, double _value_for_money, double _over_all_rating)
	: location(_location), cleanliness(_cleanliness), staff(_staff), facilities(_facilities),
		value_for_money(_value_for_money), overall_rating(_over_all_rating) 
{
	if(location < ONE || location > FIVE)
		throw runtime_error(BAD_REQ_ERR);
	if(cleanliness < ONE ||	cleanliness > FIVE)
		throw runtime_error(BAD_REQ_ERR);
	if(staff < ONE || staff > FIVE)
		throw runtime_error(BAD_REQ_ERR);
	if(facilities < ONE || facilities > FIVE)
		throw runtime_error(BAD_REQ_ERR);
	if(value_for_money < ONE || value_for_money > FIVE)
		throw runtime_error(BAD_REQ_ERR);
	if(overall_rating < ONE || overall_rating > FIVE)
		throw runtime_error(BAD_REQ_ERR);
}

Rating::Rating()
{
	location = ZERO;
	cleanliness = ZERO;
	staff = ZERO;
	facilities = ZERO;
	value_for_money = ZERO;
	overall_rating = ZERO;
}

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

double Rating::getOverAllRating(double number_of_ratings)
{
	return overall_rating/number_of_ratings;
}

vector<double> Rating::getValues(double number_of_ratings)
{
	return {location / number_of_ratings, cleanliness / number_of_ratings, staff / number_of_ratings, 
		facilities / number_of_ratings, value_for_money / number_of_ratings, overall_rating / number_of_ratings};
}
