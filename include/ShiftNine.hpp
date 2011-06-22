#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <exception>

#include <curl/curl.h>

#include "ShiftNineAsteriskEvent.hpp"
#include "ShiftNineFilter.hpp"
#include "ShiftNineProcessor.hpp"
#include "ShiftNineObserver.hpp"
#include "ShiftNineException.hpp"
#include "pugixml.hpp"

using namespace std;

class ShiftNine : public ShiftNineObservable {
	private:
		string ajam;
		string username;
		string secret;
		string buffer;

		CURLSH *share;
		ShiftNineFilter *filter;
		ShiftNineProcessor *processor;

		/**
		 * Handles all the proxying of requests to the remote asterisk server.
		 *
		 * @param map<string, string> parameters The parameters to pass to the remote asterisk
		 */
		bool send( map<string, string> parameters );

		/**
		 * Internal function responsible for url encoding a string
		 *
		 * @param string c The string to urlencode
		 *
		 * @return string
		 */
		string urlencode(const string &c);

		/**
		 * Converts a char to hexadecimal value and returns a string representation
		 *
		 */
		string char2hex( char dec );

		std::vector<ShiftNineAsteriskEvent *> parse_result();

		/**
		 * Internal function responsible for extracting all the attributes from the xml_node returning them as a map<string, string>
		 * for further processing
		 *
		 * \param pugi::xml_node node
		 *
		 * \return map<string, string>
		 */
		map<string, string> extract_attributes( pugi::xml_node node );

		/**
		 * Privately declared function used by libcurl to save the data retrieved from the remote URL into the
		 * internal ShiftNine class buffer
		 */
		static int curl_writer(char *data, size_t size, size_t nmemb, std::string *buffer);
	public:
		ShiftNine( string ajam, string username, string secret );
		~ShiftNine();

		string getAjam();
		void setAjam( string ajam );
		void setUsername( string username );

		/**
		 * Sets the username's secret
		 *
		 * @param string secret
		 *
		 * @return void
		 */
		void setSecret( string secret );

		/**
		 * Logs in to the remote asterisk
		 */
		void login();

		/**
		 * Pings the remote asterisk server. Keeps the remote connection alive
		 *
		 * @return
		 */
		void ping();

		/**
		 * Logs off from the remote asterisk
		 */
		void logoff();

		/**
		 * Waits for the remote asterisk to send an event
		 */
		void waitEvent();

		/**
		 * Sets the filter for the processor of events
		 *
		 * @param ShiftNineFilter filter
		 *
		 */
		void setFilter( ShiftNineFilter *filter );

		void setProcessor( ShiftNineProcessor *processor );
};

#define PROXY_VERSION 		"0.1"
#define RTCP_COLLECTOR_VERSION	"0.1"
