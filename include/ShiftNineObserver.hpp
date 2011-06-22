/**
 * An Observer event
 */
class ShiftNineObserverEvent {
	public:
		ShiftNineObserverEvent( int level, std::string message );

		std::string getMessage();
		int getLevel();

		void setMessage( std::string message );
		void setLevel( int level );

	protected:
		int level;
		std::string message;
};

/**
 * Abstract class defining the Observer object. The Observer object is used to trap
 * events from the ShiftNine Library and derived objects (such as the Processors)
 */
class ShiftNineObserver {
	public:
		static const int LEVEL_ERROR    = 1;
		static const int LEVEL_VERBOSE  = 2;
		static const int LEVEL_DEBUG    = 3;

		ShiftNineObserver( int level );
		virtual void event( ShiftNineObserverEvent *event ) = 0;

	protected:
		int level;
};

/**
 * Abstract class defining a Observable class. A class that inherits this class can be added a Observer
 * object for messages
 */
class ShiftNineObservable {
	public:
		void addObserver( ShiftNineObserver *observer );
		void notifyObservers( ShiftNineObserverEvent *event );
		void clearObservers();
		int getObserversCount();

	private:
		std::vector<ShiftNineObserver *> observers;
};

/**
 * Stdout Observer
 */
class StdoutObserver: public ShiftNineObserver {
	public:
		StdoutObserver( int level );
		void event( ShiftNineObserverEvent *event );
};

/**
 * Syslog Observer
 */
class SyslogObserver: public ShiftNineObserver {
	public:
		SyslogObserver( int level );
		void event( ShiftNineObserverEvent *event );
};

