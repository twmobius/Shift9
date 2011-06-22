CC = g++

# first target entry is the target invoked when typing 'make'
default: filters

filters: RTCPFilter.o StringFilter.o

RTCPFilter.o: filters/RTCPFilter.cpp
	@echo -n 'Filter: [C] RTCPFilter.cpp... '
	@$(CC) $(CFLAGS) -o filters/RTCPFilter.o -c filters/RTCPFilter.cpp
	@echo Done.

StringFilter.o: filters/StringFilter.cpp
	@echo -n 'Filter: [C] StringFilter.cpp... '
	@$(CC) $(CFLAGS) -o filters/StringFilter.o -c filters/StringFilter.cpp
	@echo Done.


