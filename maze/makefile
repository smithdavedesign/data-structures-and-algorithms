P3.out: Proj3app.o Maze.o
	g++ -g -o P3.out Proj3app.o Maze.o

Proj3app.o: Proj3app.cpp Maze.h
	g++ -g -c Proj3app.cpp

Maze.o: Maze.cpp Maze.h
	g++ -g -c Maze.cpp

clean:
	rm *.o P3.out

run : P3.out
	clear
	P3.out

submit : Proj3app.cpp Maze.h Maze.cpp makefile
	rm -rf smithP3
	mkdir smithP3
	cp Proj3app.cpp smithP3
	cp Maze.h smithP3
	cp README.txt smithREADME.txt
	cp Maze.cpp smithP3
	cp makefile smithP3
	tar cfvz smithP3.tgz smithP3
	cp smithP3.tgz ~tiawatts/cs215drop
