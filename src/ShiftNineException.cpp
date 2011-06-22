#include "ShiftNine.hpp"

ShiftNineException::ShiftNineException(const char* message): m_message(message) {

}

const char* ShiftNineException::what() const throw() {
	return m_message;
}
