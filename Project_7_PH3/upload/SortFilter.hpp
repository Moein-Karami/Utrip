#ifndef _SortFilter_hpp_
#define _SortFilter_hpp_

#include "LibrariesAndDefines.hpp"
#include "Filter.hpp"

class SortFilter : public Filter
{
	private :
		bool (*compare)(Hotel*, Hotel*);
	public :
		SortFilter(bool (*tmp)(Hotel*, Hotel*));
		std::vector<Hotel*> purification(const std::vector<Hotel*> hotels);
};

#endif