#ifndef _Weights_hpp_
#define _Weights_hpp_

#include "LibrariesAndDefines.hpp"


class Weights
{
	private :
		double location;
		double cleanliness;
		double staff;
		double facilities;
		double value_for_money;
	public :
		Weights(double _location, double _cleanliness, double _staff,
			double _facilities, double value_for_money);
		Weights();
		std::vector<double> getValues();
		std::stringstream print(bool is_manual = true);
};

#endif