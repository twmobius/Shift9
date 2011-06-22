#include "ShiftNine.hpp"

bool RTCPFilter::valid( std::string event ) {
	if( event.find("RTPReceiverStat") != std::string::npos || event.find("RTPSenderStat") != std::string::npos )
		return 1;

	return 0;
}
