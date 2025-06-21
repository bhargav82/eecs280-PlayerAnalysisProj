EXECUTABLE = soccer_players
CC = g++
CFLAGS = -O0 -Wall -std=c++17 -pedantic
LIBS = -lm

GTEST = -I../googletest/googletest/include -pthread
GLIB = ../googletest/build/libgtest.a

all:
	$(CC) $(CFLAGS) -o $(EXECUTABLE) main.cpp player_stats.cpp

test:
	$(CC) $(CFLAGS) $(GTEST) ../tests/test.cpp player_stats.cpp $(GLIB) -o test 

clean:
	rm -f $(EXECUTABLE)

clean-test:
	rm -f test
