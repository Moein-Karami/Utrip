#include "LibrariesAndDefines.hpp"
#include "UTRIP.hpp"
#include "CSVReader.hpp"
#include "Interface.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	string file_path(argv[ONE]);

	Utrip* utrip = new Utrip();
	CSVReader reader(utrip);
	reader.readData(file_path);
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