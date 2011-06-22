#include "ShiftNine.hpp"

StringFilter::StringFilter( std::string _string ) {
	this->_string = _string;
}

bool StringFilter::valid( std::string event ) {
	if( event.find(this->_string) != std::string::npos )
		return 1;

	return 0;
}
