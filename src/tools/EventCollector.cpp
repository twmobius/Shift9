#include "EventCollector.hpp"

int main (int ac, char* av[]) {
	string configFile;

	signal(SIGINT, signalHandler);
	signal(SIGTERM, signalHandler);

	try {
		po::options_description desc("General Options");
		desc.add_options()
			("config,c",	po::value<string>(&configFile)->default_value(DEFAULT_CONFIGURATION_FILE), "Specify the configuration file")
			("nofork,f",	"Do not fork")
			("debug,d",	"Turn debugging on")
			("version,v",	"Displays version information")
			("help,h",	"This help message")
		;

		po::variables_map vm;
		po::store(po::parse_command_line(ac, av, desc), vm);
		po::notify(vm);

		po::options_description astConfig("Asterisk Manager Options");
		astConfig.add_options()
			("ajam",	po::value<string>(), "AJAM URL")
			("username",	po::value<string>(), "The Asterisk Manager's username")
			("password",	po::value<string>(), "The Asterisk Manager's password")
		;

		po::options_description dbConfig("mySQL Processor Options");
		dbConfig.add_options()
			("database",	po::value<string>(), "The database to use")
			("hostname",	po::value<string>(), "The hostname the database runs at")
			("dbuser",	po::value<string>(), "The user to connect to the database")
			("dbpasswd",	po::value<string>(), "The password of the user to connect with")
		;

		if( vm.count("help") ) {
			std::cout << desc << endl;
			std::cout << astConfig << endl;
			std::cout << dbConfig << endl;
			return 1;
		}

		if( vm.count("version") ) {
			std::cout << "RTCP Information Collector. Version " << RTCP_COLLECTOR_VERSION << " By mobius" << endl;
			std::cout << "ShiftNine Library version: " << PROXY_VERSION  << endl;
			return 1;
		}

		po::options_description configFileOptions;
		configFileOptions.add(astConfig).add(dbConfig);

		ifstream ifs(configFile.c_str());
		if( !ifs ) {
			if( !vm.count("ajam") || !vm.count("username") || !vm.count("password")
                        	|| !vm.count("database") || !vm.count("hostname") || !vm.count("dbuser") || !vm.count("dbpasswd") ) {
					cout << "[Error]: Unable to open config file: " << configFile << endl;

					return 0;
			}
		}
		else {
			store(parse_config_file(ifs, configFileOptions), vm);
			notify(vm);
		}

  		if( vm.count("ajam") && vm.count("username") && vm.count("password")
			&& vm.count("database") && vm.count("hostname") && vm.count("dbuser") && vm.count("dbpasswd") ) {

			int level = ShiftNineObserver::LEVEL_ERROR;

			if( vm.count("debug") ) {
				level = ShiftNineObserver::LEVEL_DEBUG;
			}

			if( !vm.count("nofork") ) {
				pid_t pid = fork();

				if( pid > 0 ) {
					exit(0);
				} else if (pid < 0) {
					std::cerr << "[Error]: Unable to fork." << endl;
					return 1;
				}
			}
//			else {
//				SyslogListener _listener(level);
//			}

			StdoutObserver *_observer = new StdoutObserver(level);

			ShiftNine _proxy(vm["ajam"].as<string>(), vm["username"].as<string>(), vm["password"].as<string>());

			RTCPFilter _filter;
			MySQLProcessor _processor(vm["database"].as<string>().c_str(), vm["hostname"].as<string>().c_str(), vm["dbuser"].as<string>().c_str(), vm["dbpasswd"].as<string>().c_str());

			_proxy.setFilter(&_filter);
			_proxy.setProcessor(&_processor);

			_proxy.addObserver(_observer);
			_processor.addObserver(_observer);

			try {
				_proxy.login();

				for( ;; ) {
					_proxy.waitEvent();
				}
			} catch( ShiftNineException &er ) {
				cout << "[Error]: ShiftNine Library error: " << er.what() << endl;
				return 1;
			}
		} else {
			cout << "[Error]: Please see help on how to invoke event collector" << endl;
		}
	}
	catch(exception& e) {
		std::cout << "[Error]: " << e.what() << ". Type " << av[0] << " --help to see command line options" << endl;
		return 1;
	}
	catch(...) {
		std::cout << "[Error]: Exception of unknown type!" << endl;
	}

	return 0;
}

void signalHandler( int param ) {
	cout << "Terminating signal has been received. Closing up..." << endl;

//	_proxy.logoff();
	exit(1);
}

