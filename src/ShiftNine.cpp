#include "ShiftNine.hpp"
#include "pugixml.hpp"
#include <string.h>

using namespace std;

ShiftNine::ShiftNine( string ajam, string username, string secret ) {
	this->ajam = ajam;
	this->username = username;
	this->secret = secret;

	this->share = curl_share_init();
	this->filter = NULL;

	curl_share_setopt(this->share, CURLSHOPT_SHARE, CURL_LOCK_DATA_COOKIE);
}

ShiftNine::~ShiftNine() {
	curl_share_cleanup(this->share);
}

string ShiftNine::getAjam() {
	return this->ajam;
}

void ShiftNine::setAjam( string ajam ) {
	this->ajam = ajam;
}

void ShiftNine::setUsername( string username ) {
	this->username = username;
}

void ShiftNine::setSecret( string secret ) {
	this->secret = secret;
}

void ShiftNine::login() {
	map<string, string> parameters;

	parameters["Username"] = this->username;
	parameters["Secret"]   = this->secret;
	parameters["Action"]   = "login";

	this->send(parameters);
}

void ShiftNine::ping() {
	map<string, string> parameters;

	parameters["Action"] = "ping";
	this->send(parameters);
}

void ShiftNine::logoff() {
	map<string, string> parameters;

	parameters["Action"] = "logoff";
	this->send(parameters);
}

void ShiftNine::waitEvent() {
	map<string, string> parameters;
	parameters["Action"] = "WaitEvent";

	this->send(parameters);
}

void ShiftNine::setFilter( ShiftNineFilter *filter ) {
	this->filter = filter;
}

void ShiftNine::setProcessor( ShiftNineProcessor *processor ) {
	this->processor = processor;
}

bool ShiftNine::send( map<string, string> parameters ) {
	CURL *curl;
	CURLcode curlCode;

	map<string, string>::iterator curr, end;
	string url = this->ajam + "?";

	for( curr = parameters.begin(), end = parameters.end();  curr != end;  curr++ ) {
		url += curr->first +  "=" + this->urlencode(curr->second) + "&";
	}

	this->notifyObservers( new ShiftNineObserverEvent(ShiftNineObserver::LEVEL_DEBUG, "Sending to URL: " + url) );
	curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(curl, CURLOPT_HEADER, 0);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ShiftNine::curl_writer);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	curl_easy_setopt(curl, CURLOPT_SHARE, this->share);
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

	curlCode = curl_easy_perform(curl);

	if( curlCode == CURLE_OK) {
		this->notifyObservers( new ShiftNineObserverEvent(ShiftNineObserver::LEVEL_DEBUG, "Retrieved data: ") );
		this->notifyObservers( new ShiftNineObserverEvent(ShiftNineObserver::LEVEL_DEBUG, this->buffer) );
		this->parse_result();

		this->buffer = "";
	}
	else {
		this->notifyObservers( new ShiftNineObserverEvent(ShiftNineObserver::LEVEL_ERROR, "Unable to retrieve data") );
		return 0;
	}

	curl_easy_cleanup(curl);
	return 1;
}

string ShiftNine::urlencode(const string &c) {
	string escaped = "";
	int max = c.length();

	for( int i = 0; i < max; i++ ) {
		if ( (48  <= c[i] && c[i] <= 57) ||//0-9
			(65 <= c[i] && c[i] <= 90) ||//abc...xyz
				(97 <= c[i] && c[i] <= 122) || //ABC...XYZ
					(c[i]=='~' || c[i]=='!' || c[i]=='*' || c[i]=='(' || c[i]==')' || c[i]=='\'') //~!*()'
		) {
			escaped.append(&c[i], 1);
		}
		else {
			escaped.append("%");
			escaped.append(this->char2hex(c[i])); //converts char 255 to string "ff"
		}
	}
	return escaped;
}

string ShiftNine::char2hex( char dec ) {
	char dig1 = (dec&0xF0)>>4;
	char dig2 = (dec&0x0F);

	if ( 0<= dig1 && dig1<= 9) dig1+=48;    //0,48inascii
	if (10<= dig1 && dig1<=15) dig1+=97-10; //a,97inascii
	if ( 0<= dig2 && dig2<= 9) dig2+=48;
	if (10<= dig2 && dig2<=15) dig2+=97-10;

	string r;
	r.append( &dig1, 1);
	r.append( &dig2, 1);

	return r;
}

std::vector<ShiftNineAsteriskEvent *> ShiftNine::parse_result() {
	pugi::xml_document xml;
	std::vector <ShiftNineAsteriskEvent *> events;

	bool success = 0;

	if( xml.load(this->buffer.c_str()) ) {
		pugi::xml_node ajaxResponse = xml.child("ajax-response");
		for( pugi::xml_node response = ajaxResponse.child("response"); response; response = response.next_sibling("response") ) {
			for( pugi::xml_node generic = response.child("generic"); generic; generic = generic.next_sibling("generic") ) {
				if( !success ) {
					if( strlen(generic.attribute("response").value()) != 0 && !strcmp(generic.attribute("response").value(), "Success") ) {
						success = 1;
					}
					else {
						throw ShiftNineException(generic.attribute("message").value());
					}
				}

				std::map<string, string> attributes;
				//this->listener->message(ShiftNineListener::LEVEL_DEBUG, "Received event: " + generic.attribute("event").value());
				if( (this->filter != NULL) ) {
					if( this->filter->valid(generic.attribute("event").value()) ) {
						// Process all events that match the filter specified
						this->notifyObservers( new ShiftNineObserverEvent(ShiftNineObserver::LEVEL_DEBUG, "Matched event by filter") );
						attributes = this->extract_attributes(generic);

						ShiftNineAsteriskEvent event( generic.attribute("event").value(), attributes);

						this->processor->process(&event);
						events.push_back(&event);
					}
					else {
						continue;
					}
				}
				else {
					// Process all events since there is no filter defined
					this->notifyObservers( new ShiftNineObserverEvent(ShiftNineObserver::LEVEL_DEBUG, "No filter attached. Matching event") );
					ShiftNineAsteriskEvent event( generic.attribute("event").value(), attributes);

					this->processor->process(&event);
					events.push_back(&event);
				}
			}
		}
	}
	else {
		throw ShiftNineException("Unable to parse response from remote asterisk server");
	}

	return events;
}

map<string, string> ShiftNine::extract_attributes( pugi::xml_node node ) {
	map<string, string> attributes;

	for( pugi::xml_node::attribute_iterator iattr = node.attributes_begin(); iattr != node.attributes_end(); ++iattr) {
		//this->listener->message(ShiftNineListener::LEVEL_DEBUG, string("Attribute: " + iattr->name() + " Value: " + iattr->value()));
		attributes[iattr->name()] = iattr->value();
	}
	return attributes;
}

int ShiftNine::curl_writer(char *data, size_t size, size_t nmemb, std::string *buffer) {
	int result = 0;

	if (buffer != NULL) {
		buffer->append(data, size * nmemb);
		result = size * nmemb;
	}

	return result;
}
