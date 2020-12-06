#ifndef _Reservation_hpp_
#define _Reservation_hpp_

#include "LibrariesAndDefines.hpp" 

class Room;

class Reservation
{
	private :
		std::vector<Room*> rooms;
		int check_in;
		int check_out;
		double total_cost;
		int id;
		std::string hotel_id;
	public :
		Reservation(std::vector<Room*> _rooms = EMPTY, std::string _hotel_id = BLANK, int _check_in = ZERO,
			int _check_out = ZERO, double _total_cost = ZERO);
		std::stringstream printRooms();
		std::stringstream printForUser();
		void deleteReserve();
		bool isFreeInPeriod(int start, int finish);
		int getBegin();
		int getEnd();
		void setId(int _id);
		int getId();
		double getTotalCost();
		void getRooms();
		std::pair<int,int> getReserveInformation();
};


#endif