#ifndef _ShowPageHandlers_hpp_
#define _ShowPageHandlers_hpp_

#include "LibrariesAndDefines.hpp"
#include "./server/server.hpp"
#include "UTRIP.hpp"
#include "SessionManager.hpp"

class LogInPage : public TemplateHandler
{
	public :
		LogInPage(std::string file_path);
  		std::map<std::string, std::string> handle(Request *req);
};

class SignUpPage : public TemplateHandler
{
	public :
		SignUpPage(std::string file_path);
  		std::map<std::string, std::string> handle(Request *req);
};

class HomePage : public RequestHandler
{
	private :
		Utrip* utrip;
		SessionManager* session_manager;
	public :
		HomePage(Utrip* _utrip, SessionManager* _session_manager);
		Response* callback(Request*);
};

class ChargeWalletPage : public RequestHandler
{
	private :
		Utrip* utrip;
		SessionManager* session_manager;
	public :
		ChargeWalletPage(Utrip* _utrip, SessionManager* _session_manager);
		Response* callback(Request*);
};

class ShowHotelPage : public RequestHandler
{
	private :
		Utrip* utrip;
		SessionManager* session_manager;
	public :
		ShowHotelPage(Utrip* _utrip, SessionManager* _session_manager);
		Response* callback(Request*);
};

#endif