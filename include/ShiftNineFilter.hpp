/**
 * Abstract class defining the Filter object. By implementing a ShiftNineFilter class
 * you can control the events that should be sent to the Processor for further
 * manipulation
 */
class ShiftNineFilter {
	public:
		virtual bool valid( std::string event ) = 0;
};

/**
 * RTCP Filter
 */
class RTCPFilter: public ShiftNineFilter {
	public:
		bool valid( std::string event );
};

/**
 * Generic String Filter
 */
class StringFilter: public ShiftNineFilter {
	private:
		std::string _string;

	public:
		StringFilter( std::string _string );
		bool valid( std::string event );
};
