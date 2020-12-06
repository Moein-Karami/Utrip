#ifndef _CostFilter_hpp_
#define _CostFilter_hpp_

#include "LibrariesAndDefines.hpp"
#include "Filter.hpp"

class CostFilter : public Filter
{
	private :
		double min_cost;
		double max_cost;
	public :
		CostFilter(double _min_cost = ZERO, double _max_cost = ZERO);
		std::vector<Hotel*> purification(const std::vector<Hotel*> hotels);
};

#endif