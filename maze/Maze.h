#ifndef MAZE_H
#define MAZE_H

#include <iostream>
using namespace std;

class Maze
{
    public:
	Maze ();
	Maze (const Maze & other);
	~Maze ();
	Maze & operator = (const Maze & other);
	void Init ();
	void Instructions (ostream & outs, istream & ins);
	void Display (ostream & outs);
	bool Done () const;
	void Move (char direction);
	void Message (bool completed, ostream & outs);
    private:
//	void calc_even_rand (int, int, int, int, int);
//	void calc_odd_rand (int, int, int, int, int);
	void Divide (int, int, int, int/*,int*/);
	char ** grid;
	int numRows, numCols;
	int currentRow, currentCol;
	int startRow, startCol;
	int endRow, endCol;
};

#endif
