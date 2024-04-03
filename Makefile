FLAGS = -Werror -std=c++11

main.exe : main.o database.h
	g++ -o main.exe main.o

main.o: main.cpp database.h
	g++ ${FLAGS} -c main.cpp

clean:
	rm *.o
	rm main
