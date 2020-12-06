#ifndef _GeneralFunctions_hpp_
#define _GeneralFunctions_hpp_

#include "LibrariesAndDefines.hpp"

class GeneralFunctions
{
	public :
		static std::vector<std::string> divideStringByChar(std::string input, char divider);
		static long long int hashString(std::string str);
};


#endif