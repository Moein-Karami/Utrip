#ifndef _SessionManager_hpp_
#define _SessionManager_hpp_

#include "LibrariesAndDefines.hpp"

class SessionManager 
{
	private :
		std::map<std::string, bool> is_sessions_active;
		int last_id;
	public :
		SessionManager();
		void activeSession(std::string session);
		void deactiveSession(std::string session);
		bool isSessionActive(std::string session);
		std::string getUniqueSessionId(std::string id);
		std::string getEmailFromSessionId(std::string session_id);
};


#endif