#ifndef _Comment_hpp_
#define _Comment_hpp_

#include "LibrariesAndDefines.hpp"

class Comment
{
	private :
		std::string username;
		std::string comment;
	public :
		Comment(std::string _username, std::string _comment);
		std::stringstream print();
};

#endif