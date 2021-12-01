#ifndef _Interface_hpp_
#define _Interface_hpp_

#include "LibrariesAndDefines.hpp"

class Utrip;

class Interface
{
	private :
		Utrip* utrip;
	public :
		Interface(Utrip* utrip);
		std::stringstream commandDone();
		void checkQuestionMark(std::stringstream& input);
		std::stringstream doCommand(std::string unorderd_command);
		std::stringstream doPostCommand(std::stringstream& input);
		std::stringstream doSignUpCommand(std::stringstream& input);
		std::stringstream doLogInCommand(std::stringstream& input);
		std::stringstream doLogOutCommand();
		std::stringstream doPostWalletCommand(std::stringstream& input);
		std::stringstream doFiltersCommand(std::stringstream& input);
		std::stringstream doPostReserveCommand(std::stringstream& input);
		std::stringstream doPostCommentsCommand(std::stringstream& input);
		std::stringstream doPostRaitingsCommand(std::stringstream& input);
		std::stringstream doGetCommand(std::stringstream& input);
		std::stringstream doGetWalletCommand(std::stringstream& input);
		std::stringstream doGetHotelCommand(std::stringstream& input);
		std::stringstream doGetSpecialHotelCommand(std::stringstream& input);
		std::stringstream doGetCommentsCommand(std::stringstream& input);
		std::stringstream doGetRatingsCommand(std::stringstream& input);
		std::stringstream doDeleteCommand(std::stringstream& input);
		void doDeleteReservesCommand(std::stringstream& input);
};



#endif