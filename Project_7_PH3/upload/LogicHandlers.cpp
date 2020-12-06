#include "LogicHandlers.hpp"
#include <exception>
#include "ShowPageHandlers.hpp"

using namespace std;

SignUpLogic::SignUpLogic(Utrip* _utrip)
	: utrip(_utrip) {}

Response *SignUpLogic::callback(Request *req)
{
	Response* res = new Response;
	string username, email, password, rep_password;
	username = req -> getBodyParam("username");
	password = req -> getBodyParam("pass");
	rep_password = req -> getBodyParam("rep_pass");
	email = req -> getBodyParam("email");
	if(password != rep_password)
		return Response::redirect("/signup?msg=The repeated password is wrong!");
	try
	{
		utrip -> signUp(email, username, password);
	}
	catch (exception err)
	{
		return Response::redirect("/signup?msg=Email or username is unavailable!");
	}
	return Response::redirect("/?msg=Signup is succesfull dear " + username);
}

LogInLogic::LogInLogic(Utrip* _utrip, SessionManager *_session_manager)
	: utrip(_utrip), session_manager(_session_manager) {}

Response *LogInLogic::callback(Request* req)
{
	Response* res = new Response;
	string email, password;
	email = req -> getBodyParam("email");
	password = req -> getBodyParam("password");
	try
	{
		utrip -> logIn(email, password);
		string session_id = session_manager-> getUniqueSessionId(email);
		session_manager -> activeSession(session_id);
		res = Response::redirect("/home?min=1&max=5");
		res -> setSessionId(session_id);
		utrip -> logOut();
		return res;
	}
	catch (exception error)
	{
		return Response::redirect("/?msg=Your input is wrong!");
	}
}

Exit::Exit(Utrip* _utrip, SessionManager* _session_manager)
	: utrip(_utrip) , session_manager(_session_manager) {}

Response *Exit::callback(Request* req)
{
	session_manager -> deactiveSession(req -> getSessionId());
	return Response::redirect("/");
}

ChargeWalletLogic::ChargeWalletLogic(Utrip* _utrip, SessionManager* _session_manager)
	: utrip(_utrip), session_manager(_session_manager) {}

Response *ChargeWalletLogic::callback(Request* req)
{
	string session_id = req -> getSessionId();
	if(session_manager -> isSessionActive(session_id) == false)
		return Response::redirect("/?msg=Please login first!");
	string email = session_manager-> getEmailFromSessionId(session_id);
	utrip -> fastLogIn(email);
	string name = utrip -> getLoggedInUserName();
	string money = req -> getBodyParam("money");
	int amount = -ONE;
	if(money != BLANK)
		amount = stod(req -> getBodyParam("money"));
	try
	{
		utrip -> chargeWallet(amount);
		utrip -> logOut();
		return Response::redirect("/charge?msg=Your transaction is succesfull dear " + name);
	}
	catch(exception ex)
	{
		utrip -> logOut();
		return Response::redirect("/charge?msg=Something is wrong! Please try again dear " + name);
	}
}