#ifndef _UTRIP_hpp_
#define _UTRIP_hpp_

#include "LibrariesAndDefines.hpp"
#include "Rating.hpp"
#include "Weights.hpp"

class User;
class Hotel;
class Filter;

class Utrip
{
	private :
		std::vector<Hotel*> hotels;
		std::vector<User*> users;
		std::map<std::string, Hotel*> id_to_hotel;
		std::map<std::string, User*> name_to_user;
		std::map<std::string, User*> email_to_user;
		User* logged_in_user;
		std::vector<Filter*> filters;
		bool is_default_filter_on;
	public :
		Utrip();
		~Utrip();
		void addHotel(Hotel* hotel);
		void signUp(std::string email, std::string username, std::string pass);
		void checkLoggedInUser();
		void logIn(std::string email, std::string pass);
		void fastLogIn(std::string email);
		void logOut();
		void chargeWallet(double amount);
		std::stringstream printTransactions(int cnt);
		double getCurrentMoney();
		std::vector<std::vector<std::string> > printAllHotels();
		std::vector<Hotel*> filterHotels();
		std::stringstream printOneHotel(std::string id);
		void addCityFilter(std::string city);
		void addStarFilter(int min_star, int max_star);
		void addCostFilter(double min_price, double max_price);
		void addAvailableRoomFilter(std::string type, int quantity, int check_in, int check_out);
		bool checkValidRoomType(std::string type);
		void deleteFilter();
		std::stringstream reserve(std::string hotel_id,std::string type, int quantity, int check_in, int check_out);
		std::stringstream printReserves();
		void deleteReserve(int id);
		void addComment(std::string hotel_id, std::string comment);
		void addRate(std::string hotel_id, Rating rate);
		std::stringstream printComments(std::string id);
		std::stringstream printRates(std::string id);
		void cleanFilters();
		void deleteFilterType(std::string type);
		void setHotelRating(std::string hotel_id, Rating rating);
		bool canAddDefaultFilter();
		std::vector<Hotel*> defaultFilter(std::vector<Hotel*> chosen_hotels);
		void setDefaultFilter(std::string situation);
		void addSortFilter(std::string type, std::string order);
		void addIdSortFilter(bool is_ascending);
		void addNameSortFilter(bool is_ascending);
		void addStarSortFilter(bool is_ascending);
		void addCitySortFilter(bool is_ascending);
		void addStdRoomCostSortFilter(bool is_ascending);
		void addDeluxRoomCostSortFilter(bool is_ascending);
		void addLuxRoomCostSortFilter(bool is_ascending);
		void addPrmRoomCostSortFilter(bool is_ascending);
		void addAverageRoomCostSortFilter(bool is_ascending);
		void addRatingOverAllSortFilter(bool is_ascending);
		void deactiveManualWeights();
		void setManualWeights(Weights weight);
		std::stringstream printManualWeights();
		std::stringstream printEstimatedWeights();
		void addRatingPersonalSortFilter(bool is_ascending);
		std::string getLoggedInUserName();
};

#endif