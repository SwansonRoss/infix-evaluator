proj5: proj5main.o proj5tokens.o proj5stacks.o
	g++ -o proj5 proj5main.o proj5tokens.o proj5stacks.o

proj5Main.o: proj5main.cpp proj5.h
	g++ -c proj5main.cpp

proj5Tokens.o: proj5tokens.cpp proj5.h
	g++ -c proj5tokens.cpp

proj5stacks.o: proj5stacks.cpp proj5.h
	g++ -c proj5stacks.cpp

clean:
	rm proj5 proj5Main.o proj5Tokens.o proj5stacks.o
