#ifndef _CommandFixer_hpp_
#define _CommandFixer_hpp_

#include "LibrariesAndDefines.hpp"

class CommandFixer
{
	public :
		std::vector<std::string> readInput(std::stringstream& input);
		std::vector<std::pair<std::string, std::string>> makePairWords(std::vector<std::string>);
		std::vector<std::string> fixSignUpArgumans(std::stringstream& input);
		bool isValidArgumansSingUp(std::vector<std::pair<std::string, std::string>>);
		std::vector<std::string> fixLogInArgumans(std::stringstream& input);
		std::vector<std::pair<std::string, std::string> > fixFilterArgumans(std::stringstream& input);
		std::vector<std::pair<std::string, std::string> > fixCityFilterArgumans(std::vector<std::string> words);
		std::vector<std::pair<std::string, std::string> > fixStarFilterArgumans(std::vector<std::string> words);
		std::vector<std::pair<std::string, std::string> > fixCostFilterArgumans(std::vector<std::string> words);
		std::vector<std::pair<std::string, std::string> > fixRoomFilterArgumans(std::vector<std::string> words);
		bool isValidArgumansRoomFilter(std::vector<std::pair<std::string, std::string> > argumans);
		std::vector<std::string> fixReserveArgumans(std::stringstream& input);
		bool isValidArgumansReserve(std::vector<std::pair<std::string, std::string> > argumans);
		std::vector<std::string> fixCommentsArgumans(std::stringstream& input);
		std::vector<std::string> fixPostRatingArgumans(std::stringstream& input);
		bool isValidArgumansRating(std::vector<std::pair<std::string, std::string> > argumans);
		std::vector<std::string> fixSortArgumans(std::stringstream& input);
		std::vector<std::string> fixSetManualWeightArgumans(std::stringstream& input);
		void checkSetManualWeightsValidArgumans(std::vector<std::pair<std::string, std::string>>);
};

#endif