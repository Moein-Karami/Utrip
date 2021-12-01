#ifndef _AvailableRoomFilter_hpp_
#define _AvailableRoomFilter_hpp_

#include "Filter.hpp"
#include "LibrariesAndDefines.hpp"

class AvailableRoomFilter : public Filter
{
	private :
		std::string type;
		int quantity;
		int check_in;
		int check_out;
	public :
		AvailableRoomFilter(std::string _type = BLANK, int _quantity = ZERO,
			int _check_in = ZERO, int _check_out= ZERO);
		std::vector<Hotel*> purification(const std::vector<Hotel*> hotels);          
};

#endif 