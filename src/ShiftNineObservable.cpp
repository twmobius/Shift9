#include "ShiftNine.hpp"

void ShiftNineObservable::addObserver( ShiftNineObserver *observer ) {
	this->observers.push_back(observer);
	return;
}

void ShiftNineObservable::notifyObservers( ShiftNineObserverEvent *event ) {
	std::vector<ShiftNineObserver *>::iterator ob;

	for ( ob = this->observers.begin() ; ob < this->observers.end(); ob++ ) {
		(*ob)->event(event);
	}
}

void ShiftNineObservable::clearObservers() {
	this->observers.clear();
	return;
}

int ShiftNineObservable::getObserversCount() {
	return this->observers.size();
}
