#include "Hotel.hpp"
#include "Room.hpp"
#include "Reservation.hpp"
#include "GeneralFunctions.hpp"

using namespace std;

const string TYPES[] = {STD, DELUX, LUX, PRM};
const string ROOM_CODS []= {STD_CODE, DELUX_CODE, LUX_CODE, PRM_CODE};
map<string, int> type_map = {{STD, STD_ROOM_ID}, {DELUX, DELUX_ROOM_ID},
	{LUX, LUX_ROOM_ID}, {PRM, PRM_ROOM_ID}};

Hotel::Hotel(string _id, string _name, int _star, string _over_view, string _amenities,
	string _city, double _latitude, double _longitude, string _image_url, int number_of_std_room,
	int number_of_delux_room, int number_of_lux_room, int number_of_prm_room, double std_room_cost,
	double delux_room_cost, double lux_room_cost, double prm_room_cost)
	: id(_id), name(_name), star(_star), over_view(_over_view), amenities(_amenities), city(_city), latitude(_latitude),
	longitude(_longitude), image_url(_image_url)
{
	costs[STD_ROOM_ID] = std_room_cost;
	costs[DELUX_ROOM_ID] = delux_room_cost;
	costs[LUX_ROOM_ID] = lux_room_cost;
	costs[PRM_ROOM_ID] = prm_room_cost;
	int tmp[] = {number_of_std_room, number_of_delux_room, number_of_lux_room, number_of_prm_room};
	num_of_rooms = ZERO ;
	for(int i = ZERO; i < NUMBER_OF_ROOM_TYPE; i++)
	{
		num_of_rooms += tmp[i];
		for(int j = ONE; j <= tmp[i]; j++)
			rooms[i].push_back(new Room(ROOM_CODS[i] + to_string(j), costs[i], TYPES[i]));
		
	}
	average_cost = calculateAverageCost();
	num_of_ratings = ZERO;
}

void Hotel::copyData(const Hotel& hotel)
{
	id = hotel.id;
	name = hotel.name;
	star = hotel.star;
	over_view = hotel.over_view;
	amenities = hotel.amenities;
	city = hotel.city;
	latitude = hotel.latitude;
	longitude = hotel.longitude;
	image_url = hotel.image_url;
	for(int i = ZERO; i < NUMBER_OF_ROOM_TYPE; i++)
		costs[i] = hotel.costs[i];
	average_cost = hotel.average_cost;
	comments = hotel.comments;
	rating = hotel.rating;
	num_of_ratings = hotel.num_of_ratings;
	copyRooms(hotel);
	num_of_rooms = hotel.num_of_rooms;
}

void Hotel::copyRooms(const Hotel& hotel)
{
	deleteRooms();
	for(int i = ZERO; i < NUMBER_OF_ROOM_TYPE; i++)
	{
		for(int j = ZERO; j < hotel.rooms[i].size(); j++)
		{
			Room* room = new Room;
			*room = *(hotel.rooms[i][j]);
			rooms[i].push_back(room);
		}
	}
}

Hotel::Hotel(const Hotel& hotel)
{
	copyData(hotel);
}

Hotel& Hotel::operator= (const Hotel& hotel)
{
	copyData(hotel);
	return *this;
}

Hotel::~Hotel()
{
	deleteRooms();
}

void Hotel::deleteRooms()
{
	for(int i = ZERO; i < NUMBER_OF_ROOM_TYPE; i++)
	{
		for(int j = ZERO; j < rooms[i].size(); j++)
			delete rooms[i][j];
		rooms[i].clear();
	}
}

vector<string> Hotel::generalPrint()
{
	return {image_url, name, to_string(star), city, id};
}

stringstream Hotel::specialPrint()
{
	stringstream output;
	output << image_url << endl;
	output << NAME_FOR_SITE << COLON << endl <<name << endl;
	output << OVERVIEW_FOR_SITE << COLON << endl << SPACE << over_view << endl;
	output << STAR_FOR_SITE << COLON << endl << star << endl;
	output << CITY_FOR_SITE << COLON << endl << city << endl;
	output << amenities << endl;
	for(int i = ZERO; i < NUMBER_OF_ROOM_TYPE; i++)
		output << rooms[i].size() << SPACE;
	for(int i = ZERO; i < NUMBER_OF_ROOM_TYPE; i++)
		output << setprecision(ZERO) << costs[i] << SPACE;
	output << endl;
	return output;
}

double Hotel::getCost(string type)
{
	return costs[type_map[type]];
}

Reservation* Hotel::reserve(string room_type, int quantity,	int check_in, int check_out)
{
	int type = type_map[room_type];
	if(canReserveRooms(room_type, quantity, check_in, check_out) == false)
		throw runtime_error(ROOM_ERR);
	vector<Room*> chosen_rooms;
	for(auto room : rooms[type])
	{
		if(room -> isFreeInPeriod(check_in, check_out))
			chosen_rooms.push_back(room);
		if(chosen_rooms.size() == quantity)
			break;
	}
	Reservation* new_reservation = new Reservation(chosen_rooms, id, check_in, check_out, quantity * costs[type] * (check_out - check_in + ONE));
	new_reservation -> getRooms();
	return new_reservation;
}

bool Hotel::canReserveRooms(string room_type, int quantity, int check_in, int check_out)
{
	int type = type_map[room_type];
	int cnt = ZERO;
	for(auto room : rooms[type])
		if(room -> isFreeInPeriod(check_in, check_out))
			cnt++;
	return (cnt >= quantity);
}

void Hotel::addComment(string username, string comment)
{
	comments.push_back(Comment(username, comment));
}

stringstream Hotel::printRates()
{
	if(num_of_ratings == ZERO)
		throw runtime_error(RATING_ERR);
	return rating.printAverage(num_of_ratings);
}

double Hotel::calculateAverageCost()
{
	double cnt = ZERO, total_cost = ZERO;
	for(int i = ZERO; i < NUMBER_OF_ROOM_TYPE; i++)
		if(costs[i])
			cnt++, total_cost += costs[i];
	if( cnt == ZERO)
		return ZERO;
	return total_cost / cnt;
}

string Hotel::getId()
{
	return id;
}

string Hotel::getCity()
{
	return city;
}

int Hotel::getStar()
{
	return star;
}

double Hotel::getAverageCost()
{
	return average_cost;
}

void Hotel::addRate(Rating rate)
{
	rating = rating + rate;
	num_of_ratings++;
}

void Hotel::deleteRate(Rating rate)
{
	rating = rating - rate;
	num_of_ratings--;
}

stringstream Hotel::printComments()
{
	stringstream output;
	string line;
	for(auto comment : comments)
	{
		getline(comment.print(), line);
		output << line << endl;
	}
	return output;
}

string Hotel::getName()
{
	return name;
}

double Hotel::getStdRoomCost()
{
	return costs[STD_ROOM_ID];
}

double Hotel::getDeluxRoomCost()
{
	return costs[DELUX_ROOM_ID];
}

double Hotel::getLuxRoomCost()
{
	return costs[LUX_ROOM_ID];
}

double Hotel::getPrmRoomCost()
{
	return costs[PRM_ROOM_ID];
}

double Hotel::getOverAllRating()
{
	return rating.getOverAllRating(num_of_ratings);
}

vector<double> Hotel::getRatingValues()
{
	return rating.getValues(num_of_ratings);
}