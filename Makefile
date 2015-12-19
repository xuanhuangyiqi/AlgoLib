CC=g++
CC_FLAGS = -w

# Main target
test: test.o
	$(CC) test.o -o test

test.o: test.cpp Graph.h
	$(CC) $(CC_FLAGS) -c test.cpp

clean:
	rm -f test test.o
