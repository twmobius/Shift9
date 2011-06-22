#include "ShiftNine.hpp"
#include "MySQLProcessor.hpp"

using namespace std;

MySQLProcessor::MySQLProcessor( const char *database, const char *hostname, const char *username, const char *password ) {
	this->connection.connect(database, hostname, username, password);
}

MySQLProcessor::~MySQLProcessor() {

}

bool MySQLProcessor::process( ShiftNineAsteriskEvent *event ) {
	map<string, string>::iterator curr, end;
	map<string, string> attributes = event->getAttributes();

	string query;
	string tableName;

	string columns = "(`id`, `date_added`, ";
	string values  = "(NULL, NOW(), ";

	for( curr = attributes.begin(), end = attributes.end();  curr != end;  curr++ ) {
		if( !curr->first.compare("event") )
			tableName = curr->second;

		columns += "`" + curr->first  + "`,";
		values  += "'" + curr->second + "',";
	}

	// Remove the last comma from both string
	columns.erase(columns.length()-1);
	values.erase(values.length()-1);

	columns += ")";
	values += ")";

	query = "INSERT INTO " + tableName + " "  + columns + " VALUES " + values;

	this->notifyObservers( new ShiftNineObserverEvent( ShiftNineObserver::LEVEL_DEBUG, query ) );

	mysqlpp::Query _query = this->connection.query();
        _query << query;

	try {
        	mysqlpp::SimpleResult res = _query.execute();
	} catch( const mysqlpp::BadQuery &er ) {
		this->notifyObservers( new ShiftNineObserverEvent( ShiftNineObserver::LEVEL_ERROR, "Unable to execute query (" + (string) er.what() + ")" ) );
		return 0;
	} catch( exception &er ) {
		this->notifyObservers( new ShiftNineObserverEvent( ShiftNineObserver::LEVEL_ERROR, "Unexpected mySQL Error (" + (string) er.what() + ")" ) );
		return 0;
	}

	return 1;
}
