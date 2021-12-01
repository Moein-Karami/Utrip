#include "UTRIP.hpp"
#include "User.hpp"
#include "Hotel.hpp"
#include "Filter.hpp"
#include "GeneralFunctions.hpp"

using namespace std;

const string ROOM_TYPES[]={STD, DELUX, LUX, PRM};

Utrip::Utrip()
{
	logged_in_user = NULL;
	cleanFilters();
}

Utrip::~Utrip()
{
	for(auto hotel : hotels)
		delete hotel;
	hotels.clear();
	for(auto user : users)
		delete user;
	users.clear();
	cleanFilters();
	delete filters.back();
}

void Utrip::addHotel(Hotel* hotel)
{
	id_to_hotel[hotel -> getId()] = hotel;
	hotels.push_back(hotel);
}

void Utrip::signUp(string email, string pass, string username)
{
	if(logged_in_user != NULL || name_to_user[username] != NULL ||
	 email_to_user[email] != NULL)
		throw runtime_error(BAD_REQ_ERR);
	User* user = new User(email, pass, username);
	users.push_back(user);
	name_to_user[username] = user;
	email_to_user[email] = user;
	logged_in_user = user;
}

void Utrip::logIn(string email, string pass)
{
	User* user = email_to_user[email];
	if(logged_in_user != NULL || user == NULL)
		throw runtime_error(BAD_REQ_ERR);
	if(user -> getPass() != GeneralFunctions::hashString(pass))
		throw runtime_error(BAD_REQ_ERR);
	logged_in_user = user;
}

void Utrip::logOut()
{
	if(logged_in_user == NULL)
		throw runtime_error(PERMISSION_ERR);
	logged_in_user = NULL;
	cleanFilters();
}

void Utrip::chargeWallet(double amount)
{
	if(logged_in_user == NULL)
		throw runtime_error(PERMISSION_ERR);
	if(amount <= ZERO)
		throw runtime_error(BAD_REQ_ERR);
	logged_in_user -> chargeWallet(amount);
}

stringstream Utrip::printTransactions(int cnt)
{
	if(logged_in_user == NULL)
		throw runtime_error(PERMISSION_ERR);
	if(cnt <= ZERO)
		throw runtime_error(BAD_REQ_ERR);
	return logged_in_user -> printTransactions(cnt);
}

stringstream Utrip::printAllHotels()
{
	if(logged_in_user == NULL)
		throw runtime_error(PERMISSION_ERR);
	if(hotels.size() == ZERO)
		throw runtime_error(EMPTY_ERR);
	stringstream output;
	vector<Hotel*> chosen_hotels = filterHotels();
	for(auto hotel : chosen_hotels)
	{
		stringstream tmp = hotel -> generalPrint();
		string word;
		while(tmp >> word)
			output << word << SPACE;
		output << endl;
	}
	return output;
}

vector<Hotel*> Utrip::filterHotels()
{
	vector<Hotel*> chosen_hotels = hotels;
	for(auto filter : filters)
		chosen_hotels = filter -> purification(chosen_hotels);
	return chosen_hotels;
}

stringstream Utrip::printOneHotel(string id)
{
	if(logged_in_user == NULL)
		throw runtime_error(PERMISSION_ERR);
	Hotel* hotel = id_to_hotel[id];
	if(hotel == NULL)
		throw runtime_error(NOT_FOUND_ERR);
	return hotel->specialPrint();
}

void Utrip::addCityFilter(string city)
{
	if(logged_in_user == NULL)
		throw runtime_error(PERMISSION_ERR);
	deleteFilterType(CITY_FILTER);
	filters.push_back(new CityFilter(city));
}

void Utrip::addStarFilter(int min_star, int max_star)
{
	if(logged_in_user == NULL)
		throw runtime_error(PERMISSION_ERR);
	if(min_star < ONE || max_star > FIVE || min_star > max_star)
		throw runtime_error(BAD_REQ_ERR);
	deleteFilterType(STAR_FILTER);
	filters.push_back(new StarFilter(min_star, max_star));
}

void Utrip::addCostFilter(double min_price, double max_price)
{
	if(logged_in_user == NULL)
		throw runtime_error(PERMISSION_ERR);
	if(min_price < ONE || min_price > max_price)
		throw runtime_error(BAD_REQ_ERR);
	deleteFilterType(COST_FILTER);
	filters.push_back(new CostFilter(min_price, max_price));
}

void Utrip::addAvailableRoomFilter(string type, int quantity, int check_in, int check_out)
{
	if(logged_in_user == NULL)
		throw runtime_error(PERMISSION_ERR);
	if(checkValidRoomType(type) == false || quantity <= ZERO ||
		check_in < ONE || check_out > MONTH_DAYS || check_in > check_out)
		throw runtime_error(BAD_REQ_ERR);
	deleteFilterType(COST_FILTER);
	filters.push_back(new AvailableRoomFilter(type, quantity, check_in, check_out));
}

bool Utrip::checkValidRoomType(string type)
{
	for(int i = ZERO; i < NUMBER_OF_ROOM_TYPE; i++)
		if(type == ROOM_TYPES[i])
			return true;
	return false;
}

void Utrip::deleteFilter()
{
	if(logged_in_user == NULL)
		throw runtime_error(PERMISSION_ERR);
	cleanFilters();
}

stringstream Utrip::reserve(string hotel_id, string room_type, int quantity, int check_in, int check_out)
{
	if(logged_in_user == NULL)
		throw runtime_error(PERMISSION_ERR);
	Hotel* hotel = id_to_hotel[hotel_id];
	if(hotel == NULL)
		throw runtime_error(NOT_FOUND_ERR);
	if(quantity <= ZERO || checkValidRoomType(room_type) == false || check_in > check_out ||
		check_in < ONE || check_out > MONTH_DAYS)
		throw runtime_error(BAD_REQ_ERR);
	return logged_in_user -> reserve(hotel, quantity, room_type, check_in, check_out);
}

stringstream Utrip::printReserves()
{
	if(logged_in_user == NULL)
		throw runtime_error(PERMISSION_ERR);
	return logged_in_user -> printReserves();
}

void Utrip::deleteReserve(int id)
{
	if(logged_in_user == NULL)
		throw runtime_error(PERMISSION_ERR);
	logged_in_user -> deleteReserve(id);
}

void Utrip::addComment(string hotel_id, string comment)
{
	if(logged_in_user == NULL)
		throw runtime_error(PERMISSION_ERR);
	Hotel* hotel = id_to_hotel[hotel_id];
	if(hotel == NULL)
		throw runtime_error(NOT_FOUND_ERR);
	hotel -> addComment(logged_in_user -> getName(), comment);
}

void Utrip::addRate(string hotel_id, Rating rate)
{
	if(logged_in_user ==NULL )
		throw runtime_error(PERMISSION_ERR);
	Hotel* hotel = id_to_hotel[hotel_id];
	if(hotel == NULL)
		throw runtime_error(NOT_FOUND_ERR);
	logged_in_user -> addRate(hotel, rate);
}

stringstream Utrip::printComments(string id)
{
	if(logged_in_user == NULL)
		throw runtime_error(PERMISSION_ERR);
	Hotel* hotel = id_to_hotel[id];
	if(hotel == NULL)
		throw runtime_error(NOT_FOUND_ERR);
	return hotel -> printComments();
}

stringstream Utrip::printRates(string id)
{
	if(logged_in_user == NULL)
		throw runtime_error(PERMISSION_ERR);
	Hotel* hotel = id_to_hotel[id];
	if(hotel == NULL)
		throw runtime_error(NOT_FOUND_ERR);
	return hotel -> printRates();
}

void Utrip::cleanFilters()
{
	for(auto filter : filters)
		delete filter;
	filters.clear();
	filters.push_back(new Filter);
}

void Utrip::deleteFilterType(string type)
{
	for(int i = ZERO; i < filters.size(); i++)
	{
		if(filters[i] -> getType() == type)
		{
			delete filters[i];
			filters.erase(filters.begin()+i);
		}
	}
}