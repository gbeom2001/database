FLAGS = -Werror -std=c++11

main.exe : main.o database.h
	g++ $(FLAGS) -o main.exe main.o

main.o: main.cpp database.h
	g++ $(FLAGS) -c main.cpp

clean:
	rm -f *.o
	rm -f main.exe
