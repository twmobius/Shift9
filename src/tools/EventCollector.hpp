#include "ShiftNine.hpp"
#include "MySQLProcessor.hpp"

#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <iostream>
#include <unistd.h>

namespace po = boost::program_options;
using namespace std;

void signalHandler( int param );

#define DEFAULT_CONFIGURATION_FILE "/etc/event-collector.conf"
