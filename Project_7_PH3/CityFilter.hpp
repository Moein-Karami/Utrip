#ifndef _CityFilter_hpp_
#define _CityFilter_hpp_

#include "LibrariesAndDefines.hpp"
#include "Filter.hpp"

class CityFilter : public Filter
{
	private :
		std::string city;
	public :
		CityFilter(std::string _city = BLANK);
		std::vector<Hotel*> purification(const std::vector<Hotel*> hotels);
};


#endif