CC = g++
CFLAGS = -O3 -I../include -I/usr/include/mysql -I/usr/include/mysql++ -fPIC

# first target entry is the target invoked when typing 'make'
default: processors

processors: MySQLProcessor.o

MySQLProcessor.o: processors/MySQLProcessor.cpp
	@echo -n 'Processor: [C] MySQLProcessor.cpp... '
	@$(CC) $(CFLAGS) -o processors/MySQLProcessor.o -c processors/MySQLProcessor.cpp
	@echo Done.


