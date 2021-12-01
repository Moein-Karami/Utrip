#include "CSVReader.hpp"
#include "Hotel.hpp"
#include "UTRIP.hpp"
#include "GeneralFunctions.hpp"
#include "Rating.hpp"

using namespace std;

CSVReader::CSVReader(Utrip* _utrip)
	: utrip(_utrip) {}

void CSVReader::readData(string file_path)
{
	fstream input;
	input.open(file_path);
	string data, to_be_ignored;
	getline(input, to_be_ignored);
	while(getline(input, data))
		readOneHotelData(data);
	input.close();
}

void CSVReader::readOneHotelData(string merged_data)
{
	vector<string> data = GeneralFunctions::divideStringByChar(merged_data, COMMA);
	Hotel* hotel = new Hotel(data[HOTEL_ID_IN_FILE], data[HOTEL_NAME_IN_FILE], 
		stoi(data[HOTEL_STAR_IN_FILE]), data[HOTEL_OVERVIEW_IN_FILE], data[HOTEL_AMENITIES_IN_FILE],
		data[HOTEL_CITY_IN_FILE], stod(data[HOTEL_LATITUDE_IN_FILE]), stod(data[HOTEL_LONGITUDE_IN_FILE]),
		data[HOTEL_IMG_URL_IN_FILE], stoi(data[HOTEL_NUM_OF_STD_ROOM_IN_FILE]),
		stoi(data[HOTEL_NUM_OF_DELUX_ROOM_IN_FILE]), stoi(data[HOTEL_NUM_OF_LUX_ROOM_IN_FILE]),
		stoi(data[HOTEL_NUM_OF_PRM_ROOM_IN_FILE]), stod(data[HOTEL_STD_ROOM_PRICE_IN_FILE]),
		stod(data[HOTEL_DELUX_ROOM_PRICE_IN_FILE]), stod(data[HOTEL_LUX_ROOM_PRICE_IN_FILE]),
		stod(data[HOTEL_PRM_ROOM_PRICE_IN_FILE]));
	utrip -> addHotel(hotel);
}

void CSVReader::readRatingData(string file_path)
{
	fstream input;
	input.open(file_path);
	string line, to_be_ignored;
	getline(input, to_be_ignored);
	while(getline(input, line))
		readOneHotelRating(line);
	input.close();
}

void CSVReader::readOneHotelRating(string merged_data)
{
	vector<string> data = GeneralFunctions::divideStringByChar(merged_data, COMMA);
	Rating rate(stod(data[ONE]), stod(data[TWO]), stod(data[THREE]), stod(data[FOUR]), stod(data[FIVE]), stod(data[SIX]));
	utrip -> setHotelRating(data[ZERO], rate);
}