#include "Interface.hpp"
#include "UTRIP.hpp"
#include "Rating.hpp"
#include "CommandFixer.hpp"

using namespace std;
CommandFixer fixer;

typedef pair<string, string> StringPair;

Interface::Interface(Utrip* _utrip)
	: utrip(_utrip) {}

stringstream Interface::commandDone()
{
	stringstream output;
	output << OK << endl;
	return output;
}

void Interface::checkQuestionMark(stringstream& input)
{
	string word;
	double arguman;
	input >> word;
	if(word != QUESTION_MARK)
		throw runtime_error(BAD_REQ_ERR);
}

stringstream Interface::doCommand(string unorderd_command)
{
	stringstream input;
	input << unorderd_command;
	string word;
	input >> word;
	if(word == POST)
		return doPostCommand(input);
	else if(word == GET)
		return doGetCommand(input);
	else if(word == DELETE)
		return doDeleteCommand(input);
	else 
		throw runtime_error(BAD_REQ_ERR);
}

stringstream Interface::doPostCommand(stringstream& input)
{
	string word;
	input >> word;
	if(word == SIGNUP)
		return doSignUpCommand(input);
	else if (word == LOGIN)
		return doLogInCommand(input);
	else if(word == LOGOUT)
		return doLogOutCommand();
	else if(word == WALLET)
		return doPostWalletCommand(input);
	else if(word == FILTERS)
		return doFiltersCommand(input);
	else if(word == RESERVES)
		return doPostReserveCommand(input);
	else if(word == COMMENTS)
		return doPostCommentsCommand(input);
	else if(word == RATINGS)
		return doPostRaitingsCommand(input);
	else 
		throw runtime_error(NOT_FOUND_ERR);
}

stringstream Interface::doSignUpCommand(stringstream& input)
{
	checkQuestionMark(input);
	vector<string> argumans = fixer.fixSignUpArgumans(input);
	utrip -> signUp(argumans[ZERO], argumans[ONE], argumans[TWO]);
	return commandDone();
}

stringstream Interface::doLogInCommand(stringstream& input)
{
	string word;
	string arguman;
	checkQuestionMark(input);
	vector<string> argumans = fixer.fixLogInArgumans(input);
	utrip -> logIn(argumans[ZERO], argumans[ONE]);
	return commandDone();
}

stringstream Interface::doLogOutCommand()
{
	utrip -> logOut();
	return commandDone();
}

stringstream Interface::doPostWalletCommand(stringstream& input)
{
	string word;
	double arguman;
	checkQuestionMark(input);
	input >> word >> arguman;
	if(word != AMOUNT)
		throw runtime_error(BAD_REQ_ERR);
	utrip -> chargeWallet(arguman);
	return commandDone();
}

stringstream Interface::doFiltersCommand(stringstream& input)
{
	checkQuestionMark(input);
	vector<StringPair> argumans = fixer.fixFilterArgumans(input);
	if(argumans[ZERO].first == CITY)
		utrip -> addCityFilter(argumans[ZERO].second);
	else if(argumans[ZERO].first == MIN_STAR)
		utrip -> addStarFilter(stoi(argumans[ZERO].second), stoi(argumans[ONE].second));
	else if(argumans[ZERO].first == MIN_PRICE) 
		utrip -> addCostFilter(stod(argumans[ZERO].second), stod(argumans[ONE].second));
	else if (argumans[ZERO].first == TYPE)
		utrip -> addAvailableRoomFilter(argumans[ZERO].second, stoi(argumans[ONE].second),
			stoi(argumans[TWO].second), stoi(argumans[THREE].second));
	else
		throw runtime_error(BAD_REQ_ERR);
	return commandDone();
}

stringstream Interface::doPostReserveCommand(stringstream& input)
{
	checkQuestionMark(input);
	vector<string> argumans = fixer.fixReserveArgumans(input);
	return utrip -> reserve(argumans[ZERO], argumans[ONE], stoi(argumans[TWO]),
		stoi(argumans[THREE]), stoi(argumans[FOUR]));
}

stringstream Interface::doPostCommentsCommand(stringstream& input)
{
	checkQuestionMark(input);
	vector<string> argumans = fixer.fixCommentsArgumans(input);
	utrip -> addComment(argumans[ZERO], argumans[ONE]);
	return commandDone();
}

stringstream Interface::doPostRaitingsCommand(stringstream& input)
{
	checkQuestionMark(input);
	vector<string> argumans = fixer.fixPostRatingArgumans(input);
	Rating rate(stod(argumans[ONE]), stod(argumans[TWO]), stod(argumans[THREE]),
		stod(argumans[FOUR]), stod(argumans[FIVE]), stod(argumans[SIX]));
	utrip -> addRate(argumans[ZERO], rate);
	return commandDone();
}

stringstream Interface::doGetCommand(stringstream& input)
{
	string word;
	input >> word;
	if(word == WALLET)
		return doGetWalletCommand(input);
	else if(word == HOTELS)
		return doGetHotelCommand(input);
	else if(word == RESERVES)
		return utrip->printReserves();
	else if(word == COMMENTS)
		return doGetCommentsCommand(input);
	else if(word == RATINGS)
		return doGetRatingsCommand(input);
	else
		throw runtime_error(NOT_FOUND_ERR);
}

stringstream Interface::doGetWalletCommand(stringstream& input)
{
	checkQuestionMark(input);
	string word;
	int cnt;
	input >> word >> cnt;
	if(word != COUNT)
		throw runtime_error(BAD_REQ_ERR);
	return utrip -> printTransactions(cnt);
}

stringstream  Interface::doGetHotelCommand(stringstream& input)
{
	string word;
	input >> word;
	if(word == QUESTION_MARK)
		return doGetSpecialHotelCommand(input);
	return utrip -> printAllHotels();
}

stringstream Interface::doGetSpecialHotelCommand(stringstream& input)
{
	string word,id;
	input >> word >> id;
	if(word != ID)
		throw runtime_error(BAD_REQ_ERR);
	return utrip -> printOneHotel(id);
}

stringstream Interface::doGetCommentsCommand(stringstream& input)
{
	checkQuestionMark(input);
	string word, hotel_id;
	input >> word >> hotel_id;
	if(word != HOTEL)
		throw runtime_error(BAD_REQ_ERR);
	return utrip -> printComments(hotel_id);
}

stringstream Interface::doGetRatingsCommand(stringstream& input)
{
	checkQuestionMark(input);
	string word, hotel_id;
	input >> word >> hotel_id;
	if(word != HOTEL)
		throw runtime_error(BAD_REQ_ERR);
	return utrip -> printRates(hotel_id);
}

stringstream Interface::doDeleteCommand(stringstream& input)
{
	string word;
	input >> word;
	if(word == FILTERS) 
		utrip -> deleteFilter();
	else if(word == RESERVES) 
		doDeleteReservesCommand(input);
	else 
		throw runtime_error(NOT_FOUND_ERR);
	return commandDone();
}

void Interface::doDeleteReservesCommand(stringstream& input)
{
	checkQuestionMark(input);
	string word;
	int id;
	input >> word >> id;
	if(word != ID)
		throw runtime_error(BAD_REQ_ERR);
	utrip -> deleteReserve(id);
}