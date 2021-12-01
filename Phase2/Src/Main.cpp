#include "LibrariesAndDefines.hpp"
#include "UTRIP.hpp"
#include "CSVReader.hpp"
#include "Interface.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	string data_file_path(argv[ONE]), rates_file_path(argv[TWO]);
	Utrip* utrip = new Utrip();
	CSVReader reader(utrip);
	reader.readData(data_file_path);
	reader.readRatingData(rates_file_path);
	Interface interface(utrip);
	string line;
	while(getline(cin, line))
	{
		try
		{
			stringstream output = interface.doCommand(line);
			while(getline(output, line))
				cout << line << endl;
		}
		catch(runtime_error& err)
		{
			cout << err.what();
		}
	}
}