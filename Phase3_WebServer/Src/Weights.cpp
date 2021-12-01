#include "Weights.hpp"

using namespace std;

Weights::Weights(double _location, double _cleanliness, double _staff,
	double _facilities, double _value_for_money)
	: location(_location), cleanliness(_cleanliness), staff(_staff),
		facilities(_facilities), value_for_money(_value_for_money) 
{
	if(location < ONE || location > FIVE)
		throw runtime_error(BAD_REQ_ERR);
	if(cleanliness < ONE || cleanliness > FIVE)
		throw runtime_error(BAD_REQ_ERR);
	if(staff < ONE || staff > FIVE)
		throw runtime_error(BAD_REQ_ERR);
	if(facilities < ONE || facilities > FIVE)
		throw runtime_error(BAD_REQ_ERR);
	if(value_for_money < ONE || value_for_money > FIVE)
		throw runtime_error(BAD_REQ_ERR);
}

Weights::Weights()
{
	srand(time(ZERO));
	location = rand() % FIVE + ONE;
	cleanliness = rand() % FIVE + ONE;
	staff = rand() % FIVE + ONE;
	facilities = rand() % FIVE + ONE;
	value_for_money = rand() % FIVE + ONE;
}

vector<double> Weights::getValues()
{
	return {location, cleanliness, staff, facilities, value_for_money};
}

stringstream Weights::print(bool is_manual)
{
	stringstream output;
	if(is_manual)
		output << ACTIVE << SPACE << TRUE_MSG << SPACE;
	output << fixed << setprecision(DIGITS_AFTER_POINT)<< LOCATION 
		<< SPACE << floor(location * HUNDRED) / HUNDRED << SPACE;
	output << CLEANLINESS << SPACE << floor(cleanliness * HUNDRED) / HUNDRED << SPACE;
	output << STAFF << SPACE << floor(staff * HUNDRED) / HUNDRED << SPACE;
	output << FACILITIES << SPACE << floor(facilities * HUNDRED) / HUNDRED << SPACE;
	output << GET_VALUE_FOR_MONEY << SPACE << floor(value_for_money * HUNDRED) / HUNDRED << SPACE;
	return output;
}
