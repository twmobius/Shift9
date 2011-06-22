#
# Makefile for ShiftNine library
#
# Type 'make' to create the binary.
# Type 'make clean' to delete all temporaries.
#

# build target specs
CC = g++
CFLAGS = -O3 -I../include -fPIC
LIBS = -lcurl -lmysqlpp
MAKE=/usr/bin/make

include filters/Makefile observers/Makefile processors/Makefile

# first target entry is the target invoked when typing 'make'
default: ShiftNine 

ShiftNine: filters pugixml.o pugixpath.o ShiftNineAsteriskEvent.o ShiftNine.o ShiftNineObservable.o ShiftNineObserver.o ShiftNineObserverEvent.o ShiftNineException.o
	@echo -n 'Build library... '
	@$(CC) $(CFLAGS) -shared -o libshiftnine.so pugixml.o pugixpath.o ShiftNineAsteriskEvent.o ShiftNine.o ShiftNineObservable.o ShiftNineObserver.o ShiftNineObserverEvent.o ShiftNineException.o filters/*.o processors/*.o observers/*.o $(LIBS)
	@echo Done.

pugixml.o: pugixml.cpp
	@echo -n 'Core: [C] pugixml.cpp... '
	@$(CC) $(CFLAGS) -o pugixml.o -c pugixml.cpp
	@echo Done.

pugixpath.o: pugixpath.cpp
	@echo -n 'Core: [C] pugixpath.cpp... '
	@$(CC) $(CFLAGS) -o pugixpath.o -c pugixpath.cpp
	@echo Done.

ShiftNineException.o: ShiftNineException.cpp
	@echo -n 'Core: [C] ShiftNineException.cpp... '
	@$(CC) $(CFLAGS) -o ShiftNineException.o -c ShiftNineException.cpp
	@echo Done.

ShiftNineAsteriskEvent.o: ShiftNineAsteriskEvent.cpp
	@echo -n 'Core: [C] ShiftNineAsteriskEvent.cpp... '
	@$(CC) $(CFLAGS) -o ShiftNineAsteriskEvent.o -c ShiftNineAsteriskEvent.cpp
	@echo Done.

ShiftNine.o: ShiftNine.cpp 
	@echo -n 'Core: [C] ShiftNine.cpp... '
	@$(CC) $(CFLAGS) -o ShiftNine.o -c ShiftNine.cpp
	@echo Done.

ShiftNineObservable.o: ShiftNineObservable.cpp
	@echo -n 'Core: [C] ShiftNineObservable.cpp... '
	@$(CC) $(CFLAGS) -o ShiftNineObservable.o -c ShiftNineObservable.cpp
	@echo Done.

ShiftNineObserver.o: ShiftNineObserver.cpp 
	@echo -n 'Core: [C] ShiftNineObserver.cpp... '
	@$(CC) $(CFLAGS) -o ShiftNineObserver.o -c ShiftNineObserver.cpp
	@echo Done.

ShiftNineObserverEvent.o: ShiftNineObserverEvent.cpp
	@echo -n 'Core: [C] ShiftNineObserverEvent.cpp... '
	@$(CC) $(CFLAGS) -o ShiftNineObserverEvent.o -c ShiftNineObserverEvent.cpp
	@echo Done.

clean:
	@echo -n 'Removing all temporary binaries... '
	@rm -f *.so
	@rm -f *.o
	@rm -f filters/*.o
	@rm -f observers/*.o
	@rm -f processors/*.o
	@echo Done.

