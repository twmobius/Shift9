#include "ShiftNine.hpp"

ShiftNineAsteriskEvent::ShiftNineAsteriskEvent( std::string event, std::map<std::string, std::string> attributes ) {
	this->event = event;
	this->attributes = attributes;
}

bool ShiftNineAsteriskEvent::hasAttribute( std::string attribute ) {
//	if( this->attributes.find(attribute) != std::map::end )
		return 1;

	return 0;
}

bool ShiftNineAsteriskEvent::isEvent( std::string event ) {
	if( !this->event.compare(event) )
		return 1;

	return 0;
}

std::string ShiftNineAsteriskEvent::getAttribute( std::string attribute ) {
	if( this->hasAttribute(attribute) )
		return this->attributes[attribute];

	return NULL;
}

std::map<std::string, std::string> ShiftNineAsteriskEvent::getAttributes() {
	return this->attributes;
}
