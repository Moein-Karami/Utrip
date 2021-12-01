#include "SessionManager.hpp"

using namespace std;

SessionManager::SessionManager()
	: last_id(ZERO) {}

void SessionManager::activeSession(string session)
{
	is_sessions_active[session] = true;
}

void SessionManager::deactiveSession(string session)
{
	is_sessions_active[session] = false;
}

bool SessionManager::isSessionActive(string session)
{
	return is_sessions_active[session];
}

string SessionManager::getUniqueSessionId(string id)
{
	string session_id = to_string(last_id) + UNDER_LINE + id;
	last_id ++;
	return session_id; 
}

string SessionManager::getEmailFromSessionId(string session_id)
{
	string email;
	bool is_part_of_email = false;
	for(int i = ZERO; i < session_id.size(); i++)
	{
		if(is_part_of_email)
			email += session_id[i];
		if(session_id[i] == UNDER_LINE)
			is_part_of_email = true;
	}
	return email;
}
