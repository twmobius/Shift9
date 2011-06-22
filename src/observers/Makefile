CC = g++

# first target entry is the target invoked when typing 'make'
default: observers

observers: StdoutObserver.o

StdoutObserver.o: observers/StdoutObserver.cpp
	@echo -n 'Observer: [C] StdoutObserver.cpp... '
	@$(CC) $(CFLAGS) -o observers/StdoutObserver.o -c observers/StdoutObserver.cpp
	@echo Done.
