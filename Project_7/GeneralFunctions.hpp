#ifndef _GeneralFunctions_HPP_
#define _GeneralFunctions_HPP_

#include "LibrariesAndDefines.hpp"

class GeneralFunctions
{
	public :
		static std::vector<std::string> divideStringByChar(std::string input, char divider);
		static long long int hashString(std::string str);
};


#endif