L08.out : Lab08app.o LList.o
	g++ -o L08.out Lab08app.o LList.o -g

Lab08app.o : Lab08app.cpp LList.h
	g++ -c Lab08app.cpp -g

LList.o : LList.cpp LList.h
	g++ -c LList.cpp -g

clean :
	rm -f *.o L08.out

