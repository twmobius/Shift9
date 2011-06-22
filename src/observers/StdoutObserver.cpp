#include "ShiftNine.hpp"

StdoutObserver::StdoutObserver( int level ): ShiftNineObserver( level ) {
	this->level = level;
}

void StdoutObserver::event( ShiftNineObserverEvent *event ) {
	if( this->level >= event->getLevel() ) {
		switch( event->getLevel() ) {
			case ShiftNineObserver::LEVEL_ERROR:
				std::cout << "[Error]: ";
			break;
			case ShiftNineObserver::LEVEL_VERBOSE:
				std::cout << "[Verbose]: ";
			break;
			case ShiftNineObserver::LEVEL_DEBUG:
				std::cout << "[Debug]: ";
			break;
		}

		std::cout << event->getMessage() << endl;
	}
}
