CC = g++
CFLAGS = -O3 -I../../include -I/usr/include/mysql -I/usr/include/mysql++ -fPIC -L../
LIBS = -lshiftnine -lboost_program_options-mt
MAKE=/usr/bin/make

# first target entry is the target invoked when typing 'make'
default: EventCollector

EventCollector: EventCollector.cpp
	@echo -n '[C] EventCollector.cpp... '
	@$(CC) $(CFLAGS) -o event-collector EventCollector.cpp $(LIBS)
	@echo Done.


