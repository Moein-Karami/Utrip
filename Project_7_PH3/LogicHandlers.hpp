#ifndef _LogicHandlers_hpp_
#define _LogicHandlers_hpp_

#include "LibrariesAndDefines.hpp"
#include "./server/server.hpp"
#include "UTRIP.hpp"
#include "SessionManager.hpp"

class SignUpLogic : public RequestHandler
{
	private :
		Utrip* utrip;
	public :
		SignUpLogic(Utrip* _utrip);
		Response *callback(Request *);
};

class LogInLogic : public RequestHandler
{
	private :
		Utrip* utrip;
		SessionManager* session_manager;
	public :
		LogInLogic(Utrip* _utrip, SessionManager* _session_manager);
		Response * callback(Request*);
};

class Exit : public RequestHandler
{
	private :
		Utrip* utrip;
		SessionManager* session_manager;
	public :
		Exit(Utrip* _utrip, SessionManager* _session_manager);
		Response *callback(Request*);
};

class ChargeWalletLogic : public RequestHandler
{
	private :
		Utrip* utrip;
		SessionManager* session_manager;
	public :
		ChargeWalletLogic(Utrip* _utrip,SessionManager* _session_manager);
		Response *callback(Request*);
};

#endif