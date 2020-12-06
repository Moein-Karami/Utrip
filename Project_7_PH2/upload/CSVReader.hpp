#ifndef _CSVReader_hpp_
#define _CSVReader_hpp_

#include "LibrariesAndDefines.hpp"

class Utrip;
class Hotel;

class CSVReader
{
	private :
		Utrip* utrip;
	public :
		CSVReader(Utrip* _utrip);
		void readData(std::string file_path);
		void readOneHotelData(std::string merged_data);
		void readRatingData(std::string file_path);
		void readOneHotelRating(std::string merged_data);
};

#endif