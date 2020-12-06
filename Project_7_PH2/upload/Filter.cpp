#include "Filter.hpp"
#include "Hotel.hpp"

using namespace std;

Filter::Filter(string _type)
	: type(_type) {}

string Filter::getType()
{
	return type ;
}
