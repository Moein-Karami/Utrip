#include "CommandFixer.hpp"

using namespace std;

typedef pair<string, string> StringPair;

vector<string> CommandFixer::readInput(stringstream& input)
{
	string word;
	vector<string> words;
	while(input >> word)
		words.push_back(word);
	return words;
}

vector<StringPair> CommandFixer::makePairWords(vector<string> words)
{
	vector<StringPair> argumans;
	for(int i = ZERO; i < words.size(); i += TWO)
		argumans.push_back(StringPair(words[i], words[i + ONE]));
	sort(argumans.begin(), argumans.end());
	return argumans;
}

vector<string> CommandFixer::fixSignUpArgumans(stringstream& input)
{
	vector<string> words = readInput(input);
	if(words.size() != SIX)
		throw runtime_error(BAD_REQ_ERR);
	vector<StringPair> argumans = makePairWords(words);
	if(isValidArgumansSingUp(argumans) == false)
		throw runtime_error(BAD_REQ_ERR);
	vector<string> output = {argumans[ZERO].second, argumans[TWO].second, argumans[ONE].second};
	return output;
}

bool CommandFixer::isValidArgumansSingUp(vector<StringPair> argumans)
{
	string valids[] = {EMAIL, PASSWORD, USERNAME};
	for(int i = ZERO; i < argumans.size(); i++)
		if(argumans[i].first != valids[i])
			return false;
	return true;
}

vector<string> CommandFixer::fixLogInArgumans(stringstream& input)
{
	vector<string> words = readInput(input);
	if(words.size() < FOUR)
		throw runtime_error(BAD_REQ_ERR);
	vector<StringPair> argumans = makePairWords(words);
	if(argumans[ZERO].first != EMAIL || argumans[ONE].first != PASSWORD)
		throw runtime_error(BAD_REQ_ERR);
	vector<string> output = {argumans[ZERO].second, argumans[ONE].second};
	return output;
}

vector<StringPair> CommandFixer::fixFilterArgumans(stringstream& input)
{
	vector<string> words = readInput(input);
	if(words[ZERO] == CITY)
		return fixCityFilterArgumans(words);
	else if(find(words.begin(), words.end(), MIN_STAR) != words.end())
		return fixStarFilterArgumans(words);
	else if(find(words.begin(), words.end(), MIN_PRICE) != words.end())
		return fixCostFilterArgumans(words);
	else if(find(words.begin(), words.end(), TYPE) != words.end())
		return fixRoomFilterArgumans(words);
	else
		throw runtime_error(BAD_REQ_ERR);
}

vector<StringPair> CommandFixer::fixCityFilterArgumans(vector<string> words)
{
	string city;
	if(words.size() < TWO)
		throw runtime_error(BAD_REQ_ERR);
	for(int i = ONE; i < words.size(); i++)
		city += words[i];
	vector<StringPair> output={StringPair(CITY, city)};
	return output;
}

vector<StringPair> CommandFixer::fixStarFilterArgumans(vector<string> words)
{
	if(words.size() != FOUR)
		throw runtime_error(BAD_REQ_ERR);
	vector<StringPair> argumans = makePairWords(words);
	if(argumans[ZERO].first != MAX_STAR || argumans[ONE].first != MIN_STAR)
		throw runtime_error(BAD_REQ_ERR);
	vector<StringPair> output = {argumans[ONE], argumans[ZERO]};
	return output;
}

vector<StringPair> CommandFixer::fixCostFilterArgumans(vector<string> words)
{
	if(words.size() != FOUR)
		throw runtime_error(BAD_REQ_ERR);
	vector<StringPair> argumans = makePairWords(words);
	if(argumans[ZERO].first != MAX_PRICE || argumans[ONE].first != MIN_PRICE)
		throw runtime_error(BAD_REQ_ERR);
	vector<StringPair> output = {argumans[ONE], argumans[ZERO]};
	return output;
}

vector<StringPair> CommandFixer::fixRoomFilterArgumans(vector<string> words)
{
	if(words.size() != EIGHT)
		throw runtime_error(BAD_REQ_ERR);
	vector<StringPair> argumans = makePairWords(words);
	if(isValidArgumansRoomFilter(argumans) == false)
		throw runtime_error(BAD_REQ_ERR);
	vector<StringPair> output = {argumans[THREE], argumans[TWO], argumans[ZERO], argumans[ONE]};
	return output;
}

bool CommandFixer::isValidArgumansRoomFilter(vector<StringPair> argumans)
{
	string valids[] = {CHECK_IN, CHECK_OUT, QUANTITY, TYPE};
	for(int i = ZERO; i < argumans.size(); i++)
		if(argumans[i].first != valids[i])
			return false;
	return true; 
}

vector<string> CommandFixer::fixReserveArgumans(stringstream& input)
{
	vector<string> words = readInput(input);
	if(words.size() != TEN)
		throw runtime_error(BAD_REQ_ERR);
	vector<StringPair> argumans = makePairWords(words);
	if(isValidArgumansReserve(argumans) == false)
		throw runtime_error(BAD_REQ_ERR);
	vector<string> output = {argumans[TWO].second, argumans[FOUR].second,
		argumans[THREE].second, argumans[ZERO].second, argumans[ONE].second};
	return output;
}

bool CommandFixer::isValidArgumansReserve(vector<StringPair> argumans)
{
	string valids[]={CHECK_IN, CHECK_OUT, HOTEL, QUANTITY, TYPE};
	for(int i = ZERO; i < argumans.size(); i++)
		if(valids[i] != argumans[i].first)
			return false;
	return true;
}

vector<string> CommandFixer::fixCommentsArgumans(stringstream& input)
{
	vector<string> words = readInput(input);
	if(words.size() != FOUR )
		throw runtime_error(BAD_REQ_ERR);
	vector<StringPair> argumans = makePairWords(words);
	if(argumans[ZERO].first != COMMENT || argumans[ONE].first != HOTEL)
		throw runtime_error(BAD_REQ_ERR);
	vector<string> output = {argumans[ONE].second, argumans[ZERO].second};
	return output;
}

vector<string> CommandFixer::fixPostRatingArgumans(stringstream& input)
{
	vector<string> words = readInput(input);
	if(words.size() != FOURTEEN)
		throw runtime_error(BAD_REQ_ERR);
	vector<StringPair> argumans = makePairWords(words);
	if(isValidArgumansRating(argumans) == false)
		throw runtime_error(BAD_REQ_ERR);
	vector<string> output = {argumans[TWO].second, argumans[THREE].second,
		argumans[ZERO].second, argumans[FIVE].second, argumans[ONE].second,
		argumans[SIX].second, argumans[FOUR].second};
	return output;
}

bool CommandFixer::isValidArgumansRating(vector<StringPair> argumans)
{
	string valids[]={CLEANLINESS, FACILITIES, HOTEL, LOCATION, GET_OVERALL_RATING,
		STAFF, GET_VALUE_FOR_MONEY};
	for(int i = ZERO; i < argumans.size(); i++)
		if(argumans[i].first != valids[i])
			return false;
	return true;
}
