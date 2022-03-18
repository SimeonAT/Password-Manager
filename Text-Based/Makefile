CC = clang++ 
CFLAGS = -Wall -Werror -Wextra -Wpedantic 

interface: interface.o password.h
	$(CC) -o manager interface.o

interface.o: interface.cpp 
	$(CC) $(CFLAGS) -c interface.cpp -g

clean: 
	rm -f $(wildcard *.o) manager 

format:
	clang-format -i $(wildcard *.cpp) $(wildcard *.h)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all -s ./manager


