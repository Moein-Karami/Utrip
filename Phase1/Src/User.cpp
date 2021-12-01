#include "User.hpp"
#include "Hotel.hpp"
#include "Reservation.hpp"
#include "GeneralFunctions.hpp"

using namespace std;

User::User(string _email, string pass, string username)
	: email(_email), name(username)
{
	hashed_pass = GeneralFunctions::hashString(pass);
	money = ZERO;
	transactions.push_back(money);
	last_reserve_id = ZERO;
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
	if(ratings[hotel] != NULL)
		hotel -> deleteRate(*(ratings[hotel]));
	hotel -> addRate(rate);
	ratings[hotel] = rating;
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
