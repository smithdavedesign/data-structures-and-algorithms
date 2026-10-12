P2.out: DFA_Generator.o main.o
	g++ -std=c++11 DFA_Generator.o main.o -o P2.out -g

DFA_Generator.o: DFA_Generator.h DFA_Generator.cpp
	g++ -std=c++11 -c -o DFA_Generator.o DFA_Generator.cpp -g

main.o: DFA_Generator.h main.cpp
	g++ -std=c++11 -c -o main.o main.cpp -g

clean:
	rm *~ P2.out 
