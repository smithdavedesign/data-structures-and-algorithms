CFLAGS = -ggdb -std=c++11

OBJECTS = main.o largeNum.o

p2.x: $(OBJECTS)
	g++ $(CFLAGS) $(OBJECTS) -o p2.x

main.o: main.cpp largeNum.h
	g++ -c $(CFLAGS) -o main.o main.cpp

largeNum.o: largeNum.cpp largeNum.h
	g++ -c $(CFLAGS) -o largeNum.o largeNum.cpp

clean:
	rm *.o p2.x
