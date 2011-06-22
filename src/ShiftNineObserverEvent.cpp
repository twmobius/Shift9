#include "ShiftNine.hpp"

ShiftNineObserverEvent::ShiftNineObserverEvent( int level, std::string message ) {
	this->level = level;
	this->message = message;
}

std::string ShiftNineObserverEvent::getMessage() {
	return this->message;
}

int ShiftNineObserverEvent::getLevel() {
	return this->level;
}

void ShiftNineObserverEvent::setMessage( std::string message ) {
	this->message = message;
}

void ShiftNineObserverEvent::setLevel( int level ) {
	this->level = level;
}

