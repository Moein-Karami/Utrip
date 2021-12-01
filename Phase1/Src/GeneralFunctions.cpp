#include "GeneralFunctions.hpp"

using namespace std;

vector<string> GeneralFunctions::divideStringByChar(string input, char divider)
{
	vector<string> output;
	input += divider;
	for(int i = ZERO; i < input.size(); i++)
	{
		string word;
		while(input[i] != divider)
		{
			word += input[i];
			i++;
		}
		if(word.size())
			output.push_back(word);
	}
	return output;
}

long long int GeneralFunctions::hashString(string str)
{
	long long int hash = ZERO;
	for(int i = ZERO; i < str.size(); i++)
		hash = ((hash * HASH_BASE) + str[i]) % HASH_MODE;
	return hash;
}