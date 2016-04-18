CC=g++
CC_FLAGS = -wall

# Main target
test: test.o
	$(CC) test.o -o test

test.o: test.cpp graph.h
	$(CC) $(CC_FLAGS) -c test.cpp

clean:
	rm -f test test.o
