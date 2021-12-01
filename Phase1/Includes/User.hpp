#ifndef _User_hpp_
#define _User_hpp_

#include "LibrariesAndDefines.hpp"
#include "Rating.hpp"

class Hotel;
class Reservation;

class User
{
	private :
		std::string name;
		std::string email;
		long long int hashed_pass;
		double money;
		std::vector<double> transactions;
		std::vector<Reservation*> reserves;
		int last_reserve_id;
		std::map<Hotel*, Rating*> ratings;
	public :
		User(std::string _email = BLANK, std::string pass = BLANK, std::string username = BLANK);
		User(const User& user);
		User& operator=(const User& user);
		void copyData(const User& user);
		~User();
		void chargeWallet(double amount);
		std::stringstream printTransactions(int cnt);
		std::stringstream printReserves() ;
		void deleteReserve(int reserve_id);
		void addRate(Hotel* hotel, Rating rate);
		std::string getName();
		long long int getPass();
		std::stringstream reserve(Hotel* hotel, int quantity, std::string room_type,
		 int check_in, int check_out);
};



#endif