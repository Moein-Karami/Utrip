#include "Comment.hpp"

using namespace std;

Comment::Comment(string _username, string _comment)
	: username(_username), comment(_comment) {}

stringstream Comment::print()
{
	stringstream output;
	output << username << COLON << SPACE << comment << endl;
	return output;
}