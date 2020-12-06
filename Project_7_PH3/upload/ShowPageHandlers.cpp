#include "LogicHandlers.hpp"
#include <exception>
#include "ShowPageHandlers.hpp"
#include "GeneralFunctions.hpp"

using namespace std;

LogInPage::LogInPage(string file_path)
	: TemplateHandler(file_path) {}

map<string, string> LogInPage::handle(Request *req) {
	map<string, string> context;
	context["massage"] = req -> getQueryParam("msg");
	return context;
}

SignUpPage::SignUpPage(string file_path)
	: TemplateHandler(file_path) {}

map<string, string> SignUpPage::handle(Request *req) {
	map<string, string> context;
	context["massage"] = req -> getQueryParam("msg");
	return context;
}

HomePage::HomePage(Utrip* _utrip, SessionManager* _session_manager)
	: utrip(_utrip), session_manager(_session_manager) {}

Response *HomePage::callback(Request* req)
{
	string session_id = req -> getSessionId();
	if(session_manager -> isSessionActive(session_id) == false)
		return Response::redirect("/?msg=Please login first!");
	int min_star = ONE , max_star = FIVE;
	if(req -> getQueryParam("min") != BLANK)
		min_star = stoi(req -> getQueryParam("min"));
	if(req -> getQueryParam("max") != BLANK)
		max_star = stoi(req -> getQueryParam("max"));
	string massage = req -> getQueryParam("msg");
	string email = session_manager-> getEmailFromSessionId(session_id);
	utrip -> fastLogIn(email);
	Response* res = new Response;
	string name = utrip -> getLoggedInUserName();
	try
	{
		utrip -> addStarFilter(min_star, max_star);
	}
	catch(exception error)
	{
		utrip -> logOut();
		res = Response::redirect("/home?min=1&max=5&msg=Your input is wrong dear " + name + "! We set default star rating filter ");
		return res;
	}
	res -> setHeader("Content-Type", "text/html");
	vector<vector<string>> hotels = utrip -> printAllHotels();
	utrip -> logOut();
	ostringstream body;
	body
	<< "<html>" << endl
	<< "	<head>" << endl
	<< "		<title> Home </title>" << endl
	<< "		<style>" << endl
	<< "			lable" << endl
	<< "			{" << endl
	<< "				font-size: 30px;" << endl
	<< "			}" << endl
	<< "			select" << endl
	<< "			{" << endl
  	<< "				width: 60px;" << endl
  	<< "				padding: 5px 10px;" << endl
	<< "				border: 1;" << endl
  	<< "				border-radius: 20px;" << endl
  	<< "				background-color: #f1f1f1;" << endl
  	<< "				font-size: 20px;" << endl
	<< "			}" <<endl
	<< "		    input[type=button], input[type=submit], input[type=reset]" << endl
	<< "	      		{" << endl
  	<< "	    			background-color: #4CAF50;" << endl
    << "				    border: 1;" << endl
	<< "			        color: white;" << endl
	<< "			        padding: 10px 15px;" << endl
	<< "			        text-decoration: none;" << endl
	<< "			        font-size: 20px;" << endl
 	<< "			    	margin: 4px 2px;" << endl
	<< "			        cursor: pointer;" << endl
	<< "					border-radius: 20px;" << endl
	<< "			    }"
	<< "			body" <<endl
	<< "			{" <<endl
	<< "				background-color: pink;" << endl
	<< "			}" << endl
	<< "			div" << endl
	<< "			{" << endl
	<< "		        width: 1300px;" << endl
    << "  				background-color: lightblue;" << endl
    << "			    border: 10px solid blue;" << endl
    << "			    margin: auto;" << endl
    << "  				text-align: center;" << endl
    << "				image-align: center;" << endl
    << "				border-radius: 20px;" << endl
   	<< "				border-radius: 20px;" << endl
    << "				padding: 50px;" << endl
    << "			}" << endl
    << "			input" << endl
    << "			{" << endl
    << " 				color: black;" << endl
    << "				text-align:center;" << endl
    << " 			}" << endl
    << "			#massage" << endl
    << " 			{" << endl
    << "   				color: purple;" << endl
    << "   				text-align:center;" << endl
    << " 			}" << endl
    << "			h2" << endl
    << " 			{" << endl
    << "   				color: black;" << endl
    << "   				text-align:center;" << endl
    << " 			}" << endl
    << " 			a:link, a:visited " << endl
    << " 			{" << endl
    << "   				background-color: gray;" << endl
    << "   				color: white;" << endl
    << "   				padding: 15px 25px;" << endl
    << "   				text-align: center;" << endl
    << "  				text-decoration: none;" << endl
    << "   				display: inline-block;" << endl
    << "   				margin: auto;" << endl
    << "				font-size: 20px;" << endl
   	<< "				border-radius: 20px;" << endl
    << " 			}" << endl
	<< "			h1" << endl
	<< "			{" << endl
	<< "				color: green;" << endl
	<< "				text-align: center;" << endl
	<< "			}" << endl
	<< "			img" << endl
	<< "			{" << endl
	<< "				border-radius: 20px;" << endl
	<< "			}" << endl
	<< "		</style>" << endl
	<< "	</head>" <<endl
	<< "	<body>" << endl
	<< " 		<h1>HOME PAGE</h1>" <<endl;
	if(massage != BLANK)
		body << "		<h2 id='massage'>" << massage << "</h2><br>" << endl;
	body
	<< " 		<a href='/exit'>EXIT</a><br><br>" << endl
	<< "		<a href='/charge'> CHARGE WALLET</a><br><br><br><br>" << endl
	<< "		<form action='/home' method='get'>" << endl
	<< "			<input type='hidden' value='We set your star rating filter dear "+ name + "' name=msg><br>"
	<< "			<lable>Min Star Rating: </lable>" << endl
	<< "			<select name='min'>" <<endl
	<< "			<option value='" << min_star << "'>" << min_star << "</option>" <<endl;
	for(int i = ONE; i <= FIVE; i++)
		if(i != min_star)
			body<<"			 <option value='" << i << "'>" << i<< "</option>" <<endl;
	body
	<< "			</select><br>"
	<< "			<lable>Max Star Rating: </lable>" << endl
	<< "			<select name='max'>" <<endl;
	body<<"			 <option value='" << max_star << "'>" << max_star << "</option>" <<endl;
	for(int i = ONE; i <= FIVE; i++)
		if(i != max_star)
			body<<"			 <option value='" << i << "'>" << i<< "</option>" <<endl;
	body
	<< "			</select><br>"
	<< "			<input type='submit' value='FILTER'><br><br><br><br>" << endl
	<< "		</form><br><br>" << endl;
	for(int i = ZERO; i < hotels.size(); i++)
	{
		body
		<< "		<div><br>" << endl
		<< "			<img src='" << hotels[i][ZERO] << "'>" << endl
		<< "			<h2> Name : " << hotels[i][ONE] << "</h2>" <<endl
		<< "			<h2> Star rating : " << hotels[i][TWO] << "</h2>" <<endl
		<< "			<h2> City : " << hotels[i][THREE] << "</h2>" <<endl
		<< "			<a href='/showHotel?id=" << hotels[i][FOUR] << "'> View Hotel </a><br><br><br>" << endl
		<< "		</div><br><br><br>" <<endl;
	}
	body
	<< "	</body>" << endl
	<< "</htmp>" <<endl;
	res -> setBody(body.str());
	return res;
}

ChargeWalletPage::ChargeWalletPage(Utrip * _utrip, SessionManager* _session_manager)
	: utrip(_utrip), session_manager(_session_manager) {}

Response* ChargeWalletPage::callback(Request* req)
{
	string session_id = req -> getSessionId();
	if(session_manager -> isSessionActive(session_id) == false)
		return Response::redirect("/?msg=Please login first!");
	string email = session_manager-> getEmailFromSessionId(session_id);
	utrip -> fastLogIn(email);
	Response* res = new Response;
	res -> setHeader("Content-Type", "text/html");
	string massage = req -> getQueryParam("msg");
	double current_cash = utrip -> getCurrentMoney();
	utrip -> logOut();
	ostringstream body;
	body
	<< "<html>" << endl
	<< "	<head>" << endl
	<< "		<title> Charge Wallet </title>" << endl
	<< "		<style>" << endl
	<< "			input[type=number]" << endl
	<< "				{" << endl
  	<< "	    			background-color: #f1f1f1;" << endl
 	<< "					width: 20%;" << endl
  	<< "					padding: 12px 20px;" << endl
	<< "				 	margin: 8px 0;" << endl
  	<< "					box-sizing: border-box;" << endl
  	<< "					font-size: 20px;" << endl
	<< "					border-radius: 20px;" << endl
	<< "				}" << endl
	<< "			lable" << endl
	<< "			{" << endl
	<< "				font-size: 30px;" << endl
	<< "			}" << endl
	<< "			select" << endl
	<< "			{" << endl
  	<< "				width: 8%;" << endl
  	<< "				padding: 5px 10px;" << endl
	<< "				border: 1;" << endl
  	<< "				border-radius: 20px;" << endl
  	<< "				background-color: #f1f1f1;" << endl
  	<< "				font-size: 20px;" << endl
	<< "			}" <<endl
	<< "		    input[type=button], input[type=submit], input[type=reset]" << endl
	<< "	      		{" << endl
  	<< "	    			background-color: #4CAF50;" << endl
    << "				    border: 1;" << endl
	<< "			        color: white;" << endl
	<< "			        padding: 10px 15px;" << endl
	<< "			        text-decoration: none;" << endl
	<< "			        font-size: 20px;" << endl
 	<< "			    	margin: 4px 2px;" << endl
	<< "			        cursor: pointer;" << endl
	<< "					border-radius: 20px;" << endl
	<< "			    }"
	<< "			body" <<endl
	<< "			{" <<endl
	<< "				background-color: pink;" << endl
	<< "			}" << endl
	<< "			div" << endl
	<< "			{" << endl
	<< "		        width: 1000px;" << endl
    << "  				background-color: lightblue;" << endl
    << "			    border: 10px solid blue;" << endl
    << "			    margin: auto;" << endl
    << "  				text-align: center;" << endl
    << "				image-align: center;" << endl
    << "				padding: 20px;" << endl
    << "				border-radius: 20px;" << endl
   	<< "				border-radius: 20px;" << endl
    << "			}" << endl
    << "			input" << endl
    << "			{" << endl
    << " 				color: black;" << endl
    << "				text-align:center;" << endl
    << " 			}" << endl
    << "			#massage" << endl
    << " 			{" << endl
    << "   				color: purple;" << endl
    << "   				text-align:center;" << endl
    << " 			}" << endl
    << "			h2" << endl
    << " 			{" << endl
    << "   				color: black;" << endl
    << "				font-size: 30px;" << endl
    << "   				text-align:center;" << endl
    << " 			}" << endl
    << " 			a:link, a:visited " << endl
    << " 			{" << endl
    << "   				background-color: gray;" << endl
    << "   				color: white;" << endl
    << "   				padding: 15px 25px;" << endl
    << "   				text-align: center;" << endl
    << "  				text-decoration: none;" << endl
    << "   				display: inline-block;" << endl
    << "   				margin: auto;" << endl
    << "				font-size: 20px;" << endl
   	<< "				border-radius: 20px;" << endl
    << " 			}" << endl
	<< "			h1" << endl
	<< "			{" << endl
	<< "				color: green;" << endl
	<< "				text-align: center;" << endl
	<< "			}" << endl
	<< "		</style>" << endl
	<< "	</head>" <<endl
	<< "	<body>" << endl
	<< "		<h1> CHARGE WALLET </h1>" << endl
	<< "		<a href='/exit'>EXIT</a><br><br>" << endl
	<< "		<a href='/home?min=1&max=5'>HOME PAGE</a><br><br><br><br><br>" <<endl
	<< "		<div>" << endl
	<< "			<h2> Current cash : " << fixed << setprecision(TWO) << current_cash << setprecision(ZERO) << "</h2>" << endl
	<< " 			<form action='/chargeWalletLogic' method='post'>" << endl
	<< "				<lable>Increase cash</lable><br>" << endl 
	<< "				<input type='number' name='money'><br>" << endl
	<< "				<input type='submit' value='CHARGE'> " << endl
	<< "			</form>" << endl;
	if(massage != BLANK)
	{
		body
		<< "			<h2 id='massage'>" << massage << "</h2" <<endl;
	} 
	body
	<< "		</div>" << endl 
	<< "	</body>" << endl
	<< "</html>" << endl;
	res -> setBody(body.str());
	return res;
}

ShowHotelPage::ShowHotelPage(Utrip* _utrip, SessionManager* _session_manager)
	: utrip(_utrip), session_manager(_session_manager) {}

Response* ShowHotelPage::callback(Request* req)
{
	string session_id = req -> getSessionId();
	if(session_manager -> isSessionActive(session_id) == false)
		return Response::redirect("/?msg=Please login first!");
	string email = session_manager-> getEmailFromSessionId(session_id);
	Response* res = new Response;
	res -> setHeader("Content-Type", "text/html");
	ostringstream body;
	body
	<< "<html>" << endl
	<< "	<head>" << endl
	<< "		<title> Hotel Details </title>" << endl
	<< "		<style>" << endl
	<< "			lable" << endl
	<< "			{" << endl
	<< "				font-size: 30px;" << endl
	<< "			}" << endl
	<< "			select" << endl
	<< "			{" << endl
  	<< "				width: 8%;" << endl
  	<< "				padding: 5px 10px;" << endl
	<< "				border: 1;" << endl
  	<< "				border-radius: 20px;" << endl
  	<< "				background-color: #f1f1f1;" << endl
  	<< "				font-size: 20px;" << endl
	<< "			}" <<endl
	<< "		    input[type=button], input[type=submit], input[type=reset]" << endl
	<< "	      		{" << endl
  	<< "	    			background-color: #4CAF50;" << endl
    << "				    border: 1;" << endl
	<< "			        color: white;" << endl
	<< "			        padding: 10px 15px;" << endl
	<< "			        text-decoration: none;" << endl
	<< "			        font-size: 20px;" << endl
 	<< "			    	margin: 4px 2px;" << endl
	<< "			        cursor: pointer;" << endl
	<< "					border-radius: 20px;" << endl
	<< "			    }"
	<< "			body" <<endl
	<< "			{" <<endl
	<< "				background-color: pink;" << endl
	<< "			}" << endl
	<< "			div" << endl
	<< "			{" << endl
	<< "		        width: 1300px;" << endl
    << "  				background-color: lightblue;" << endl
    << "			    border: 10px solid blue;" << endl
    << "				padding: 50px;" << endl
    << "			    margin: auto;" << endl
    << "  				text-align: center;" << endl
    << "				table-align: center;" << endl
    << "				image-align: center;" << endl
    << "				border-radius: 20px;" << endl
   	<< "				border-radius: 20px;" << endl
    << "			}" << endl
    << "			input" << endl
    << "			{" << endl
    << " 				color: black;" << endl
    << "				text-align:center;" << endl
    << " 			}" << endl
    << "			#massage" << endl
    << " 			{" << endl
    << "   				color: purple;" << endl
    << "   				text-align:center;" << endl
    << " 			}" << endl
    << "			h2" << endl
    << " 			{" << endl
    << "   				color: black;" << endl
    << "   				text-align:center;" << endl
    << "				font-size: 30px;" << endl
    << " 			}" << endl
    << "			h3" << endl
    << " 			{" << endl
    << "   				color: black;" << endl
    << "   				text-align:center;" << endl
    << "				font-size: 23px;" << endl
    << " 			}" << endl   
    << "			#overview" << endl
    << " 			{" << endl
    << "   				color: black;" << endl
    << "   				text-align:left;" << endl
    << "				font-size: 23px;" << endl
    << " 			}" << endl 
    << " 			a:link, a:visited " << endl
    << " 			{" << endl
    << "   				background-color: gray;" << endl
    << "   				color: white;" << endl
    << "   				padding: 15px 25px;" << endl
    << "   				text-align: center;" << endl
    << "  				text-decoration: none;" << endl
    << "   				display: inline-block;" << endl
    << "   				margin: auto;" << endl
    << "				font-size: 20px;" << endl
   	<< "				border-radius: 20px;" << endl
    << " 			}" << endl
	<< "			h1" << endl
	<< "			{" << endl
	<< "				color: green;" << endl
	<< "				text-align: center;" << endl
	<< "			}" << endl
	<< "			table" << endl 
	<< "				{" << endl 
	<< "					border-collapse: collapse;" << endl 
  	<< "					width: 80%;" << endl 
  	<< "   					margin: auto;" << endl
	<< "				}" << endl 
	<< "			th, td " << endl 
	<< "			{" << endl 
  	<< "				text-align: center;" << endl 
  	<< "				padding: 10px;" << endl 
  	<< "				font-size: 25px;" << endl 
	<< "			}" << endl 
	<< "			tr:nth-child(even){background-color: #f2f2f2}" << endl 
	<< "			th " << endl 
	<< "			{" << endl 
  	<< "				background-color: #4CAF50;" << endl 
  	<< "				color: white;" << endl 
  	<< "				font-size: 25px;" << endl 
	<< "			}" << endl 
	<< "			ol " << endl 
	<< "			{" << endl 
  	<< "				list-style-type: number;" << endl 
  	<< "				list-style-position: inside;" << endl
  	<< "				font-size : 25px;" << endl
	<< "			}" << endl 
	<< "			img" << endl
	<< "			{" << endl
	<< "				border-radius: 20px;" << endl
	<< "			}" << endl
	<< "		</style>" << endl
	<< "	</head>" <<endl
	<< "	<body>" << endl
	<< "		<h1> Hotel Details</h1>"
	<< "		<a href='/exit'>EXIT</a><br><br>" << endl
	<< "		<a href='/home?min=1&max=5'>HOME PAGE</a><br><br><br><br>" << endl
	<< "		<div><br>" << endl;
	string hotel_id = req -> getQueryParam("id");
	utrip -> fastLogIn(email);
	stringstream hotel;
	try
	{
		hotel = utrip -> printOneHotel(hotel_id);
		utrip -> logOut();
	}
	catch(exception error)
	{
		return Response::redirect("/home");
	}
	string img_url;
	hotel >> img_url;
	body<< "			<img src='" << img_url << "'>"<<endl;
	string line;
	getline(hotel, line);
	for(int i = ZERO; i < FOUR; i++)
	{	
		getline(hotel, line);
		body<< "			<h2>" << line << "</h2>" <<endl;
		getline(hotel, line);
		if(i != ONE)
			body<< "			<h3>" << line << "</h3>" << endl;
		else
			body<< "			<h3 id='overview'>" << line << "</h3>" << endl;
	}
	body<< "			<h2>" << "Amentities : " << "</h2>" << endl;
	getline(hotel, line);
	vector<string> amentities = GeneralFunctions::divideStringByChar(line, VERTICAL_BAR);
	body<< "			<ol>" << endl;
	for(int i = ZERO; i < amentities.size(); i++)
		body<< "				<li>" << amentities[i] << "</li>" << endl;
	body
	<< "			</ol>" << endl
	<< "			<table border=5>" << endl
	<< "				<tr>" << endl
	<< "					<th>Room type</th>" << endl
	<< "					<th>Number of available rooms</th>" << endl
	<< "					<th>Price of room</th>" <<endl
	<< "				</tr>" << endl;
	string room_type[] ={STD , DELUX , LUX , PRM };
	double number_of_rooms[FOUR], rooms_cost[FOUR];
	for(int i = ZERO; i < FOUR; i++)
		hotel >> number_of_rooms[i];
	for(int i = ZERO; i < FOUR; i++)
		hotel >> rooms_cost[i];
	for(int i = ZERO; i < FOUR; i++)
	{
		body
		<< "				<tr>" << endl
		<< "					<td>" << room_type[i] << "</td>" << endl
		<< "					<td>" << number_of_rooms[i] << "</td>" << endl
		<< "					<td>" << rooms_cost[i] << "</td>" << endl
		<< "				</tr>" << endl;
	}
	body
	<< "			</table><br><br>" << endl
	<< "		</div>"
	<< "	</body>" << endl
	<< "</html>" << endl;
	res ->setBody(body.str());
	return res;
}