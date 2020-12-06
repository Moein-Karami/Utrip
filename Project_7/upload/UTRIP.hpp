#ifndef _UTRIP_hpp_
#define _UTRIP_hpp_

#include "LibrariesAndDefines.hpp"
#include "Rating.hpp"

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
	public :
		Utrip();
		~Utrip();
		void addHotel(Hotel* hotel);
		void signUp(std::string email, std::string pass, std::string username);
		void logIn(std::string email, std::string pass);
		void logOut();
		void chargeWallet(double amount);
		std::stringstream printTransactions(int cnt);
		std::stringstream printAllHotels();
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
};

#endif