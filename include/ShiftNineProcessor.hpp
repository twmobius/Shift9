/**
 * Abstract class defining the Processor object. By implementing a ShiftNineProcessor class
 * you can specify how the events retrieved from the remote Asterisk can be further
 * manipulated
 */
class ShiftNineProcessor {
	public:
		virtual bool process( ShiftNineAsteriskEvent *event ) = 0;
};
