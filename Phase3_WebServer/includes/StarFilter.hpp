#ifndef _StarFilter_hpp_
#define _StarFilter_hpp_

#include "LibrariesAndDefines.hpp"
#include "Filter.hpp"

class StarFilter : public Filter
{
	private :
		int min_star;
		int max_star;
	public :
		StarFilter(int _min_star = ZERO, int _max_star = ZERO);
		std::vector<Hotel*> purification(const std::vector<Hotel*> hotels);
};

#endif 