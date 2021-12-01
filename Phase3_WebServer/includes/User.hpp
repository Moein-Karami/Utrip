#ifndef _User_hpp_
#define _User_hpp_

#include "LibrariesAndDefines.hpp"
#include "Rating.hpp"
#include "Weights.hpp"

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
		bool is_manual_weights_active;
		Weights manual_weights;
		bool is_estimated_weights_up_to_date;
		Weights estimated_weights;
	public :
		User(std::string _email = BLANK, std::string pass = BLANK, std::string username = BLANK);
		User(const User& user);
		User& operator=(const User& user);
		void copyData(const User& user);
		~User();
		void chargeWallet(double amount);
		std::stringstream printTransactions(int cnt);
		double getCurrentMoney();
		std::stringstream printReserves() ;
		void deleteReserve(int reserve_id);
		void addRate(Hotel* hotel, Rating rate);
		std::string getName();
		long long int getPass();
		std::stringstream reserve(Hotel* hotel, int quantity, std::string room_type,
		 int check_in, int check_out);
		std::pair<double, double> getDefaultFilterPeriod();
		std::vector<double> getReservedRoomsCost();
		double calculateDeviation(std::vector<double> numbers, double average);
		int getNumOfReserves();
		void deactiveManualWeights();
		void setManualWeights(Weights weights);
		double calculateOverAllRating(Hotel* hotel);
		std::vector<double> getWeights();
		Weights getEstimatedWeights();
		void calculateEstimatedWeights();
		std::vector<double> fixEstimatedWeights(std::vector<double> weights);
		double calculateDifference(std::vector<double> weights, std::vector<double> rate);
		std::stringstream printManualWeights();
		std::stringstream printEstimatedWeights();
		std::string getUserName();
};



#endif