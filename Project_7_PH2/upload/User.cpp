#include "User.hpp"
#include "Hotel.hpp"
#include "Reservation.hpp"
#include "GeneralFunctions.hpp"
#define NUM first
#define EXPENCE second
using namespace std;

typedef pair<double, double> DoublePair;

User::User(string _email, string pass, string username)
	: email(_email), name(username)
{
	hashed_pass = GeneralFunctions::hashString(pass);
	money = ZERO;
	transactions.push_back(money);
	last_reserve_id = ZERO;
	is_manual_weights_active = false;
	is_estimated_weights_up_to_date = false;
}

User::User(const User& user)
{
	copyData(user);
}

User& User::operator=(const User& user)
{
	copyData(user);
	return *this;
}

void User::copyData(const User& user)
{
	name = user.name;
	email = user.email;
	hashed_pass = user.hashed_pass;
	money = user.money;
	transactions = user.transactions;
	reserves.clear();
	for(auto reserve : user.reserves)
	{
		Reservation* new_reserve = new Reservation;
		*new_reserve = *reserve;
		reserves.push_back(new_reserve);
	}
	last_reserve_id = user.last_reserve_id;
	ratings = user.ratings;
	is_manual_weights_active = user.is_manual_weights_active;
	manual_weights = user.manual_weights;
	is_estimated_weights_up_to_date = user.is_estimated_weights_up_to_date;
	estimated_weights = user.estimated_weights;
}

User::~User()
{
	for(int i = ZERO; i < reserves.size(); i++)
	{
		reserves[i] -> deleteReserve();
		delete reserves[i];
	}
}

void User::chargeWallet(double amount)
{
	money += amount;
	transactions.push_back(money);
}

stringstream User::printTransactions(int cnt)
{
	stringstream output;
	for(int i = transactions.size() - ONE; i >= max(ZERO, (int)transactions.size() - cnt); i--)
		output << fixed << setprecision(ZERO) << transactions[i] << endl;
	return output;
}

stringstream User::printReserves()
{
	if(reserves.size() == ZERO)
		throw runtime_error(EMPTY_ERR);
	stringstream output;
	string line;
	for(int i = reserves.size() - ONE; i >= ZERO; i--)
	{
		getline(reserves[i] -> printForUser(), line);	
		output << line << endl;
	}
	return output;
}

void User::deleteReserve(int reserve_id)
{
	for(int i = ZERO; i < reserves.size(); i++)
	{
		if(reserves[i] -> getId() == reserve_id)
		{
			chargeWallet(reserves[i] -> getTotalCost() / (double)TWO);
			reserves[i] -> deleteReserve();
			delete reserves[i];
			reserves.erase(reserves.begin() + i);
			return ;
		}
	}
	throw runtime_error(NOT_FOUND_ERR);
}

void User::addRate(Hotel* hotel, Rating rate)
{
	Rating* rating = new Rating;
	*rating = rate;
	ratings[hotel] = rating;
	is_estimated_weights_up_to_date = false;
}

string User::getName()
{
	return name;
}

long long int User::getPass()
{
	return hashed_pass;
}

stringstream User::reserve(Hotel* hotel, int quantity, string room_type,
		 int check_in, int check_out)
{
	double total_cost = hotel -> getCost(room_type) * quantity * (check_out - check_in + ONE);
	if(total_cost > money)
		throw runtime_error(CREDIT_ERR);
	Reservation* new_reserve;
	new_reserve = hotel -> reserve(room_type, quantity, check_in, check_out);
	chargeWallet(-total_cost);
	last_reserve_id++;
	new_reserve -> setId(last_reserve_id);
	reserves.push_back(new_reserve);
	return new_reserve -> printRooms();	
}

DoublePair User::getDefaultFilterPeriod()
{
	vector<double> reserved_rooms_cost = getReservedRoomsCost();
	double sum = ZERO;
	for_each(reserved_rooms_cost.begin(), reserved_rooms_cost.end(), [&](double x){sum += x;});
	double average = sum / (double)reserved_rooms_cost.size();
	double deviation = calculateDeviation(reserved_rooms_cost, average);
	return DoublePair(average - (double)TWO * deviation, average + (double)TWO * deviation);
}

vector<double> User::getReservedRoomsCost()
{
	vector<double> output;
	for(auto reserve : reserves)
	{
		DoublePair tmp = reserve -> getReserveInformation();
		for(int i = ZERO; i < tmp.NUM; i++)
			output.push_back(tmp.EXPENCE);
	}
	return output;
}

double User::calculateDeviation(vector<double> numbers, double average)
{
	double tmp = ZERO;
	for_each(numbers.begin(), numbers.end(), [&](double x){tmp += (x - average) * ( x - average);});
	tmp /= double(numbers.size() - ONE);
	tmp = sqrt(tmp);
	return tmp;
}

int User::getNumOfReserves()
{
	return reserves.size();
}

void User::deactiveManualWeights()
{
	is_manual_weights_active = false;
}

void User::setManualWeights(Weights weights)
{
	is_manual_weights_active = true;
	manual_weights = weights;
}

double User::calculateOverAllRating(Hotel* hotel)
{
	if(ratings[hotel])
		return ratings[hotel] -> getOverAllRating(ONE);
	ratings.erase(hotel);
	vector<double> weights = getWeights();
	vector<double> rating_values = hotel -> getRatingValues();
	double sum = ZERO, total_weight = ZERO;
	for(int i = ZERO; i < weights.size(); i++)
	{
		sum += weights[i] * rating_values[i];
		total_weight += weights[i]; 
	}
	return sum / total_weight;
}

vector<double> User::getWeights()
{
	if(is_manual_weights_active)
		return manual_weights.getValues();
	if(ratings.size() < FIVE)
		throw runtime_error(INSUFFICIENT_RATING_ERR);
	return getEstimatedWeights().getValues();
}

Weights User::getEstimatedWeights()
{
	if(is_estimated_weights_up_to_date)
		return estimated_weights;
	if(ratings.size() < FIVE)
		throw runtime_error(INSUFFICIENT_RATING_ERR);
	calculateEstimatedWeights();
	return estimated_weights;
}

void User::calculateEstimatedWeights()
{
	is_estimated_weights_up_to_date = true;
	estimated_weights = Weights();
	vector<double> weights = estimated_weights.getValues();
	for(int step = ZERO; step < ESTIMATE_STEPS ; step++)
		weights = fixEstimatedWeights(weights);
	estimated_weights = Weights(weights[ZERO], weights[ONE], weights[TWO],
		weights[THREE], weights[FOUR]);
}

vector<double> User::fixEstimatedWeights(vector<double> weights)
{
	double diff[FIVE];
	fill(diff, diff + FIVE, ZERO);
	vector<double> tmp;
	for(int i = ZERO; i < FIVE; i++)
	{
		tmp = weights;
		tmp[i] += EPSILON;
		auto rate = ratings.begin();
		while(rate != ratings.end())
		{
			diff[i] += (calculateDifference(tmp, (rate -> second) -> getValues(ONE)) -
				calculateDifference(weights, (rate -> second) -> getValues(ONE))) / EPSILON;
			rate++;
		}
	}
	for(int i = ZERO; i < FIVE; i++)
	{
		weights[i] -= diff[i] * ALPHA;
		weights[i] = max((double) ONE, weights[i]);
		weights[i] = min((double) FIVE, weights[i]);
	}
	return weights;
}

double User::calculateDifference(vector<double> weights, vector<double> rate)
{
	double my_overall_rating = ZERO, total_weight = ZERO;
	for(int i = ZERO; i < FIVE; i++)
	{
		my_overall_rating += weights[i] * rate[i];
		total_weight += weights[i];
	}
	my_overall_rating /= total_weight;
	return (my_overall_rating - rate[FIVE]) * (my_overall_rating - rate[FIVE]);
}

stringstream User::printManualWeights()
{
	if(is_manual_weights_active == false)
	{
		stringstream output;
		output << ACTIVE << SPACE << FALSE_MSG <<endl;
		return output;
	}
	return manual_weights.print();
}

stringstream User::printEstimatedWeights()
{
	return getEstimatedWeights().print(IS_ESTIMATED);
}