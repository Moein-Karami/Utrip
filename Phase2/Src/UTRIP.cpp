#include "UTRIP.hpp"
#include "User.hpp"
#include "Hotel.hpp"
#include "Filter.hpp"
#include "AvailableRoomFilter.hpp"
#include "CostFilter.hpp"
#include "StarFilter.hpp"
#include "CityFilter.hpp"
#include "GeneralFunctions.hpp"
#include "SortFilter.hpp"
#include "PersonalRatingSortFilter.hpp"
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

void Utrip::checkLoggedInUser()
{
	if(logged_in_user == NULL)\
		throw(runtime_error(PERMISSION_ERR));
}

void Utrip::signUp(string email, string username, string pass)
{
	if(logged_in_user != NULL || name_to_user[username] != NULL ||
	 email_to_user[email] != NULL)
		throw runtime_error(BAD_REQ_ERR);
	User* user = new User(email, pass, username);
	users.push_back(user);
	name_to_user[username] = user;
	email_to_user[email] = user;
	logged_in_user = user;
	is_default_filter_on = true;
}

void Utrip::logIn(string email, string pass)
{
	User* user = email_to_user[email];
	if(logged_in_user != NULL || user == NULL)
		throw runtime_error(BAD_REQ_ERR);
	if(user -> getPass() != GeneralFunctions::hashString(pass))
		throw runtime_error(BAD_REQ_ERR);
	logged_in_user = user;
	is_default_filter_on = true;
}

void Utrip::logOut()
{
	checkLoggedInUser();
	cleanFilters();
	deactiveManualWeights();
	logged_in_user = NULL;
}

void Utrip::chargeWallet(double amount)
{
	checkLoggedInUser();
	if(amount <= ZERO)
		throw runtime_error(BAD_REQ_ERR);
	logged_in_user -> chargeWallet(amount);
}

stringstream Utrip::printTransactions(int cnt)
{
	checkLoggedInUser();
	if(cnt <= ZERO)
		throw runtime_error(BAD_REQ_ERR);
	return logged_in_user -> printTransactions(cnt);
}

stringstream Utrip::printAllHotels()
{
	checkLoggedInUser();
	if(hotels.size() == ZERO)
		throw runtime_error(EMPTY_ERR);
	stringstream output;
	vector<Hotel*> chosen_hotels = filterHotels();
	if(canAddDefaultFilter())
	{
		chosen_hotels = defaultFilter(chosen_hotels);
		output << DEFAULT_FILTER_MSG;
	}
	if(chosen_hotels.size() == ZERO)
		throw runtime_error(EMPTY_ERR);
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
	checkLoggedInUser();
	Hotel* hotel = id_to_hotel[id];
	if(hotel == NULL)
		throw runtime_error(NOT_FOUND_ERR);
	return hotel->specialPrint();
}

void Utrip::addCityFilter(string city)
{
	checkLoggedInUser();
	deleteFilterType(CITY_FILTER);
	filters.push_back(new CityFilter(city));
}

void Utrip::addStarFilter(int min_star, int max_star)
{
	checkLoggedInUser();
	if(min_star < ONE || max_star > FIVE || min_star > max_star)
		throw runtime_error(BAD_REQ_ERR);
	deleteFilterType(STAR_FILTER);
	filters.push_back(new StarFilter(min_star, max_star));
}

void Utrip::addCostFilter(double min_price, double max_price)
{
	checkLoggedInUser();
	if(min_price < ONE || min_price > max_price)
		throw runtime_error(BAD_REQ_ERR);
	deleteFilterType(COST_FILTER);
	filters.push_back(new CostFilter(min_price, max_price));
}

void Utrip::addAvailableRoomFilter(string type, int quantity, int check_in, int check_out)
{
	checkLoggedInUser();
	if(checkValidRoomType(type) == false || quantity <= ZERO ||
		check_in < ONE || check_out > MONTH_DAYS || check_in > check_out)
		throw runtime_error(BAD_REQ_ERR);
	deleteFilterType(ROOM_FILTER);
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
	checkLoggedInUser();
	cleanFilters();
}

stringstream Utrip::reserve(string hotel_id, string room_type, int quantity, int check_in, int check_out)
{
	checkLoggedInUser();
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
	checkLoggedInUser();
	return logged_in_user -> printReserves();
}

void Utrip::deleteReserve(int id)
{
	checkLoggedInUser();
	logged_in_user -> deleteReserve(id);
}

void Utrip::addComment(string hotel_id, string comment)
{
	checkLoggedInUser();
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
	checkLoggedInUser();
	Hotel* hotel = id_to_hotel[id];
	if(hotel == NULL)
		throw runtime_error(NOT_FOUND_ERR);
	return hotel -> printComments();
}

stringstream Utrip::printRates(string id)
{
	checkLoggedInUser();
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
	addIdSortFilter(true);
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

void Utrip::setHotelRating(string hotel_id, Rating rate)
{
	Hotel* hotel = id_to_hotel[hotel_id];
	hotel -> addRate(rate);
}

bool Utrip::canAddDefaultFilter()
{
	if(is_default_filter_on == false)
		return false;
	if(any_of(filters.begin(), filters.end(), [](Filter* filter){return (filter -> getType() == COST_FILTER);}))
		return false;
	if(logged_in_user -> getNumOfReserves() < TEN)
		return false;
	return true;
}

vector<Hotel*> Utrip::defaultFilter(vector<Hotel*> chosen_hotels)
{
	pair<double, double> cost_period = logged_in_user -> getDefaultFilterPeriod();
	CostFilter filter(cost_period.first, cost_period.second);
	return filter.purification(chosen_hotels);
}

void Utrip::setDefaultFilter(string situation)
{
	checkLoggedInUser();
	if(situation == TRUE_MSG)
		is_default_filter_on = true;
	else if(situation == FALSE_MSG)
		is_default_filter_on = false;
	else
		throw runtime_error(BAD_REQ_ERR);
}

void Utrip::addSortFilter(string type, string order)
{
	checkLoggedInUser();
	bool is_ascending;
	if(order == DESCENDING)
		is_ascending = false;
	else if(order == ASCENDING)
		is_ascending = true;
	else 
		throw(runtime_error(BAD_REQ_ERR));
	if(type == ID)
		addIdSortFilter(is_ascending);
	else if(type == NAME)
		addNameSortFilter(is_ascending);
	else if(type == STAR_RATING)
		addStarSortFilter(is_ascending);
	else if(type == CITY)
		addCitySortFilter(is_ascending);
	else if(type == STD_ROOM_COST)
		addStdRoomCostSortFilter(is_ascending);
	else if(type == DELUX_ROOM_COST)
		addDeluxRoomCostSortFilter(is_ascending);
	else if(type == LUX_ROOM_COST)
		addLuxRoomCostSortFilter(is_ascending);
	else if(type == PRM_ROOM_COST)
		addPrmRoomCostSortFilter(is_ascending);
	else if(type == AVERAGE_ROOM_PRICE)
		addAverageRoomCostSortFilter(is_ascending);
	else if(type == RATING_OVERALL)
		addRatingOverAllSortFilter(is_ascending);
	else if(type == RATING_PERSONAL)
		addRatingPersonalSortFilter(is_ascending);
	else
		throw runtime_error(BAD_REQ_ERR);
}

void Utrip::addIdSortFilter(bool is_ascending)
{
	Filter* new_filter;
	if(is_ascending)
		new_filter = new SortFilter([](Hotel* hotel1, Hotel* hotel2)
			{return (hotel1 -> getId() < hotel2 -> getId()) ;});
	else
		new_filter = new SortFilter([](Hotel* hotel1, Hotel* hotel2)
			{return (hotel1 -> getId() > hotel2 -> getId()) ;});
	deleteFilterType(SORT_FILTER);
	filters.push_back(new_filter);
}

void Utrip::addNameSortFilter(bool is_ascending)
{
	Filter* new_filter ;
	if(is_ascending)
		new_filter = new SortFilter([](Hotel* hotel1, Hotel* hotel2)
			{return ((hotel1 -> getName() != hotel2 -> getName()) ? (hotel1 -> getName() < hotel2 -> getName())
				: (hotel1 -> getId() < hotel2 -> getId()));});
	else
		new_filter = new SortFilter([](Hotel* hotel1, Hotel* hotel2)
			{return ((hotel1 -> getName() != hotel2 -> getName()) ? (hotel1 -> getName() > hotel2 -> getName())
				: (hotel1 -> getId() < hotel2 -> getId()));});
	deleteFilterType(SORT_FILTER);
	filters.push_back(new_filter);
}

void Utrip::addStarSortFilter(bool is_ascending)
{
	Filter* new_filter;
	if(is_ascending) 
		new_filter = new SortFilter([](Hotel* hotel1, Hotel* hotel2){return ((hotel1 -> getStar() != hotel2 -> getStar()) ? 
			(hotel1 -> getStar() < hotel2 -> getStar() ) : (hotel1 -> getId() < hotel2 -> getId()));});
	else
		new_filter = new SortFilter([](Hotel* hotel1, Hotel* hotel2){return ((hotel1 -> getStar() != hotel2 -> getStar()) ? 
			(hotel1 -> getStar() > hotel2 -> getStar() ) : (hotel1 -> getId() < hotel2 -> getId()));});
	deleteFilterType(SORT_FILTER);
	filters.push_back(new_filter);
}

void Utrip::addCitySortFilter(bool is_ascending)
{
	Filter* new_filter;
	if(is_ascending)
		new_filter = new SortFilter([](Hotel* hotel1, Hotel* hotel2){return ((hotel1 -> getCity() != hotel2 -> getCity()) ?
			(hotel1 -> getCity() < hotel2 -> getCity()) : (hotel1 -> getId() < hotel2 -> getId()));});
	else
		new_filter = new SortFilter([](Hotel* hotel1, Hotel* hotel2){return ((hotel1 -> getCity() != hotel2 -> getCity()) ?
			(hotel1 -> getCity() > hotel2 -> getCity()) : (hotel1 -> getId() < hotel2 -> getId()));});
	deleteFilterType(SORT_FILTER);
	filters.push_back(new_filter);
}

void Utrip::addStdRoomCostSortFilter(bool is_ascending)
{
	Filter* new_filter;
	if(is_ascending) 
		new_filter = new SortFilter([](Hotel* hotel1, Hotel* hotel2){return ((hotel1 -> getStdRoomCost() != hotel2 -> getStdRoomCost()) ?
			(hotel1 -> getStdRoomCost() < hotel2 -> getStdRoomCost()) : (hotel1 -> getId() < hotel2 -> getId() ) );});
	else
		new_filter = new SortFilter([](Hotel* hotel1, Hotel* hotel2){return ((hotel1 -> getStdRoomCost() != hotel2 -> getStdRoomCost()) ?
			(hotel1 -> getStdRoomCost() > hotel2 -> getStdRoomCost()) : (hotel1 -> getId() < hotel2 -> getId() ) );});
	deleteFilterType(SORT_FILTER);
	filters.push_back(new_filter);
}

void Utrip::addDeluxRoomCostSortFilter(bool is_ascending)
{
	Filter* new_filter;
	if(is_ascending)
		new_filter = new SortFilter([](Hotel* hotel1, Hotel* hotel2){return ((hotel1 -> getDeluxRoomCost() != hotel2 -> getDeluxRoomCost()) ?
			(hotel1 -> getDeluxRoomCost() < hotel2 -> getDeluxRoomCost()) : (hotel1 -> getId() < hotel2 -> getId() ) );});
	else
		new_filter = new SortFilter([](Hotel* hotel1, Hotel* hotel2){return ((hotel1 -> getDeluxRoomCost() != hotel2 -> getDeluxRoomCost()) ?
			(hotel1 -> getDeluxRoomCost() > hotel2 -> getDeluxRoomCost()) : (hotel1 -> getId() < hotel2 -> getId() ) );});
	deleteFilterType(SORT_FILTER);
	filters.push_back(new_filter);
}

void Utrip::addLuxRoomCostSortFilter(bool is_ascending)
{
	Filter* new_filter;
	if(is_ascending) 
		new_filter = new SortFilter([](Hotel* hotel1, Hotel* hotel2){return ((hotel1 -> getLuxRoomCost() != hotel2 -> getLuxRoomCost()) ?
			(hotel1 -> getLuxRoomCost() < hotel2 -> getLuxRoomCost()) : (hotel1 -> getId() < hotel2 -> getId() ) );});
	else
		new_filter = new SortFilter([](Hotel* hotel1, Hotel* hotel2){return ((hotel1 -> getLuxRoomCost() != hotel2 -> getLuxRoomCost()) ?
			(hotel1 -> getLuxRoomCost() > hotel2 -> getLuxRoomCost()) : (hotel1 -> getId() < hotel2 -> getId() ) );});
	deleteFilterType(SORT_FILTER);
	filters.push_back(new_filter);
}

void Utrip::addPrmRoomCostSortFilter(bool is_ascending)
{
	Filter* new_filter;
	if(is_ascending)
		new_filter = new SortFilter([](Hotel* hotel1, Hotel* hotel2){return ((hotel1 -> getPrmRoomCost() != hotel2 -> getPrmRoomCost()) ?
			(hotel1 -> getPrmRoomCost() < hotel2 -> getPrmRoomCost()) : (hotel1 -> getId() < hotel2 -> getId() ) );});
	else
		new_filter = new SortFilter([](Hotel* hotel1, Hotel* hotel2){return ((hotel1 -> getPrmRoomCost() != hotel2 -> getPrmRoomCost()) ?
			(hotel1 -> getPrmRoomCost() > hotel2 -> getPrmRoomCost()) : (hotel1 -> getId() < hotel2 -> getId() ) );});
	deleteFilterType(SORT_FILTER);
	filters.push_back(new_filter);
}

void Utrip::addAverageRoomCostSortFilter(bool is_ascending)
{
	Filter* new_filter;
	if(is_ascending)
		new_filter = new SortFilter([](Hotel* hotel1, Hotel* hotel2){return ((hotel1 -> getAverageCost() != hotel2 -> getAverageCost() ) ?
			(hotel1 -> getAverageCost() < hotel2 -> getAverageCost()) : (hotel1 -> getId() < hotel2 -> getId() ));});
	else
		new_filter = new SortFilter([](Hotel* hotel1, Hotel* hotel2){return ((hotel1 -> getAverageCost() != hotel2 -> getAverageCost() ) ?
			(hotel1 -> getAverageCost() > hotel2 -> getAverageCost()) : (hotel1 -> getId() < hotel2 -> getId() ));});
	deleteFilterType(SORT_FILTER);
	filters.push_back(new_filter);
}

void Utrip::addRatingOverAllSortFilter(bool is_ascending)
{
	Filter* new_filter;
	if(is_ascending)
		new_filter = new SortFilter([](Hotel* hotel1, Hotel* hotel2){return ((hotel1 -> getOverAllRating() != hotel2 ->getOverAllRating()) ?
			(hotel1 -> getOverAllRating() < hotel2 -> getOverAllRating()) : (hotel1 -> getId() < hotel2 -> getId()));});
	else
		new_filter = new SortFilter([](Hotel* hotel1, Hotel* hotel2){return ((hotel1 -> getOverAllRating() != hotel2 ->getOverAllRating()) ?
			(hotel1 -> getOverAllRating() > hotel2 -> getOverAllRating()) : (hotel1 -> getId() < hotel2 -> getId()));});
	deleteFilterType(SORT_FILTER);
	filters.push_back(new_filter);
}

void Utrip::deactiveManualWeights()
{
	checkLoggedInUser();
	logged_in_user -> deactiveManualWeights();
}

void Utrip::setManualWeights(Weights weights)
{
	checkLoggedInUser();
	logged_in_user -> setManualWeights(weights);
}

stringstream Utrip::printManualWeights()
{
	checkLoggedInUser();
	return logged_in_user -> printManualWeights();
}

stringstream Utrip::printEstimatedWeights()
{
	checkLoggedInUser();
	return logged_in_user -> printEstimatedWeights();
}

void Utrip::addRatingPersonalSortFilter(bool is_ascending)
{
	Filter* new_filter = new PersonalRatingSortFilter(logged_in_user, is_ascending);
	deleteFilterType(SORT_FILTER);
	filters.push_back(new_filter);
}