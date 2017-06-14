PROGNAME = main
SRC = main.cpp
CC = g++
CCFLAGS = -std=c++11

$(PROGNAME) : $(SRC)
	$(CC) $(CCFLAGS) -o $@ $<

.PHONY: clean

clean:
	-rm -f $(PROGNAME) *.o *~
