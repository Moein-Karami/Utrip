#ifndef _Filter_hpp_
#define _Filter_hpp_

#include "LibrariesAndDefines.hpp"

class Hotel;

class Filter 
{
	protected :
		std::string type;
	public :
		Filter(std::string _type = SORT_FILTER);
		virtual std::vector<Hotel*> purification(const std::vector<Hotel*> hotels) = ZERO;
		virtual std::string getType();
};

#endif