#ifndef _Room_hpp_
#define _Room_hpp_

#include "LibrariesAndDefines.hpp"

class Reservation;

class Room
{
	private :
		std::string name;
		double price;
		bool isReservedOnDay[MONTH_DAYS + TWO];
		std::string type;
	public :
		Room(std::string _name = BLANK, double _price = ZERO, std::string _type = BLANK);
		bool isFreeInPeriod(int start, int finis);
		void deleteReserve(Reservation* reserve);
		std::string getName();
		std::string getType();
		void addReserve(Reservation* reserve);
};

#endif