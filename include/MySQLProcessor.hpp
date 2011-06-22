#include <mysql++/mysql++.h>
/**
 * Simple mySQL Processor implementing the ShiftNineProcessor class
 *
 * This file is part of Shift9.
 *
 * Shift9 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Shift9 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Shift9. If not, see <http://www.gnu.org/licenses/>.
 *
 */
class MySQLProcessor: public ShiftNineProcessor, public ShiftNineObservable {
	private:
		mysqlpp::Connection connection;

	public:
		MySQLProcessor( const char *database, const char *hostname, const char *username, const char *password );
		~MySQLProcessor();
		bool process( ShiftNineAsteriskEvent *event );
};
