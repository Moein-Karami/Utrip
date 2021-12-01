#ifndef _Hotel_hpp_
#define _Hotel_hpp_

#include "LibrariesAndDefines.hpp"
#include "Comment.hpp"
#include "Rating.hpp"

class Room;
class Reservation;

class Hotel
{
	private :
		std::string id;
		std::string name;
		int star;
		std::string over_view;
		std::string amenities;
		std::string city;
		double latitude;
		double longitude;
		std::string image_url;
		std::vector<Room*> rooms[NUMBER_OF_ROOM_TYPE];
		double costs[NUMBER_OF_ROOM_TYPE];
		double average_cost;
		std::vector<Comment> comments;
		Rating rating;
		int num_of_ratings;
		int num_of_rooms;
	public :
		Hotel(std::string _id, std::string name, int _star, std::string _over_view,
			std::string _amenities, std::string _city, double _latitude,
			double _longitude, std::string _image_url, int number_of_std_room,
			int number_of_delux_room, int number_of_lux_room, int number_of_prm_room,
			double std_room_cost, double delux_room_cost, double lux_room_cost, double prm_room_cost);
		Hotel(const Hotel& hotel);
		Hotel& operator= (const Hotel& hotel);
		void copyData(const Hotel& hotel);
		void copyRooms(const Hotel& hotel);
		void deleteRooms();
		~Hotel();
		std::stringstream generalPrint();
		std::stringstream specialPrint();
		double getCost(std::string type);
		Reservation* reserve(std::string room_type, int quantity, int check_in, int check_out);
		bool canReserveRooms(std::string room_type, int quantity, int check_in, int check_out);
		void addComment(std::string username, std::string comment);
		std::stringstream printRates();
		double calculateAverageCost();
		std::string getId();
		std::string getCity();
		int getStar();
		double getAverageCost();
		void addRate(Rating rate);
		void deleteRate(Rating rate);
		std::stringstream printComments();
};

#endif