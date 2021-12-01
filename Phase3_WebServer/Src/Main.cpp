#include "LibrariesAndDefines.hpp"
#include "UTRIP.hpp"
#include "CSVReader.hpp"
#include "./server/server.hpp"
#include "LogicHandlers.hpp"
#include "ShowPageHandlers.hpp"
#include "SessionManager.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	string data_file_path(argv[ONE]), rates_file_path(argv[TWO]);
	Utrip* utrip = new Utrip();
	SessionManager*	session_manager = new SessionManager(); 
	CSVReader reader(utrip);
	reader.readData(data_file_path);
	reader.readRatingData(rates_file_path);
	try 
	{
	    Server server(PORT);
	    server.setNotFoundErrPage("static/404.html");
    	server.get("/", new LogInPage("template/LogInPage.html"));
    	server.get("/signup", new SignUpPage("template/SignUpPage.html"));
    	server.post("/signup_logic", new SignUpLogic(utrip));
    	server.post("/login_logic", new LogInLogic(utrip, session_manager));
    	server.get("/home", new HomePage(utrip, session_manager));
    	server.get("/exit", new Exit(utrip, session_manager));
    	server.get("/charge", new ChargeWalletPage(utrip, session_manager));
    	server.post("/chargeWalletLogic", new ChargeWalletLogic(utrip, session_manager));
    	server.get("/showHotel", new ShowHotelPage(utrip, session_manager));
   		server.run();
  	}
  	catch (Server::Exception error) 
  	{
    	cerr << error.getMessage() << endl;
  	}
  	catch (exception errror)
  	{
  		cerr << errror.what() << endl;
  	}
}