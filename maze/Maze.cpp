//author: David Smith
//Class: cs 215s12 fall 2012
//Program: This program randomly genorates a recursive division maze. 
//The user must use the a,s,d,and w keys to navigate himself/herself to the hidden treasure. 
 
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include "Maze.h"
using namespace std;

Maze::Maze ()
{
	numRows = numCols = 0;
	grid = NULL;
	startRow = startCol = 0;
	endRow = endCol = 0;
	currentRow = currentCol = 0;
}

Maze::Maze (const Maze & other)
{
}

Maze::~Maze ()
{
}

Maze & Maze::operator = (const Maze & other)
{
}

void Maze::Init ()
{
	numRows = 21;
	numCols = 31;

	// grab a random time for the seed, so you wont always get the same maze.
	srand(time(NULL));

	grid = new char * [numRows];
	for (int r = 0; r < numRows; r++)
	{
	    grid[r] = new char [numCols+1];
	}

	strcpy (grid[0], "*******************************");
	strcpy (grid[1], "*                             *");
	for (int i=2; i<numRows-1; i++)
	  strcpy (grid[i], grid[1]);
	strcpy (grid[numRows-1], "*******************************");

	/*
	strcpy (grid[0],  "*******************************");
        strcpy (grid[1],  "* *       *   * ***    * * * **");
	strcpy (grid[2],  "* ** *** ** *       ** *      *");
	strcpy (grid[3],  "* *   *   * * * ** **    *** **");
	strcpy (grid[4],  "* * ********* *     *  * *    *");
	strcpy (grid[5],  "*     * * * * ************* ***");
	strcpy (grid[6],  "* * *         *     *   * * * *");
	strcpy (grid[7],  "* * * ** ** * *****   ***   * *");
	strcpy (grid[8],  "* * * *   * * *     *     *   *");
	strcpy (grid[9],  "* *** **************** ********");
	strcpy (grid[10], "* *     *   *  *        * *   *");
	strcpy (grid[11], "* * ******* ** ******** *   ***");
	strcpy (grid[12], "* * * *   * *             *   *");
	strcpy (grid[13], "* *     *   ******** ******** *");
	strcpy (grid[14], "* ******** **    * *    *     *");
	strcpy (grid[15], "* *   *     **** *   *  *     *");
	strcpy (grid[16], "* *** ***** * *  ***** **** ***");
	strcpy (grid[17], "* * * *  *    ** *  *  *    * *");
	strcpy (grid[18], "* * *   **  * ** *    ***** * *");
	strcpy (grid[19], "* *   *     *      **         *");
	strcpy (grid[20], "*******************************");
	for(int i=0; i < Rows; i++)
	  grid[i][0] = grid[i][Cols-1] = '*'; //verticle column walls
	for(int b=0; b < Cols; b++)
	  grid[b][0] = grid[b][Rows-1]
      
	*/

	Divide(0, 0, numRows - 1, numCols - 1);
       	startRow = 1;
	startCol = 1;

	//your moving a V around the maze which begins where the reccursion began.
	grid [startRow][startCol] = 'O';
	endRow = numRows-2;
	endCol = numCols-2;
	// this is the treasure located at the end of the reccursion. 
	grid [endRow][endCol] = '$';
	currentRow = startRow;
	currentCol = startCol;


}

void Maze::Instructions (ostream & outs, istream & ins)
{
	system ("clear");
	outs << "\nUse the a, w, d, and s keys to move yourself (O) through the\n";
	outs << "maze to find the treasure ($)!\n\n";
	outs << "\ta = left\n\tw = up\n\td = right\n\ts = down\n\tq = quit\n\ti = instructions\n\n";
	outs << "Press any key and enter to start.\n";
	char c;
	ins >> c;
}

void Maze::Display (ostream & outs)
{
	char esc = 0x1B;
	system ("clear");
	for (int r = 0; r < numRows; r++)
	{
	    for (int c = 0; c < numCols; c++)
		outs << grid[r][c] << ' ';
	    outs << endl;
	}
}

bool Maze::Done () const
{
	if (currentRow == endRow && currentCol == endCol)
	{
		grid[currentRow][currentCol] = '#';
		return true;
	}
	return false;
}
// This function helps your character move around the maze and makes sure you dont walk 
// through walls. if the typed in character is legal it moves your character in the desired direction. 
void Maze::Move (char direction)
{
  bool mademove = false;
  int arow = currentRow;
  int acol = currentCol;
	switch (tolower(direction))
	{
		case 'a':
		  if (currentCol-1>=0&&(grid[currentRow][currentCol-1] !='*'))
		    {
		      currentCol --;
		      mademove = true;
		    }
		      break;
		    
		case 'w':
		  if (currentRow-1>=0&&(grid[currentRow-1][currentCol] !='*'))
		    {
		      currentRow --;
		      mademove = true;
		    }
		      break;
		    

		case 'd':
		  if (currentCol+1 <numCols-1&&(grid[currentRow][currentCol+1] !='*'))
                    {
                      currentCol ++;
                      mademove = true;
		    }
		      break;
                    
		case 's':
		  if (currentRow+1 <numRows-1&&(grid[currentRow+1][currentCol] !='*'))
                    {
                      currentRow ++;
                      mademove = true;
                    }
		      break;
	}                    
		  if (mademove == true)
		    grid[arow][acol]= ' ';
		  grid[currentRow][currentCol]='@';

}	

void Maze::Message (bool completed, ostream & outs)
{
	if (completed)
		outs << "\nWOOT! You found the treasure!\n\n";
	else
		outs << "\nGame Over :( \n\n";
}

//build the walls and doors for the maze. in a recursive way.
void Maze::Divide (int left, int top, int right, int bottom /* int level*/)
{
  //debug tool
  /*  Display(cout);
    char c;
    cin >> c;
  */
  int height;
  int width;
  height = bottom -top;
  width = right - left;

  if (height < 4 || width < 4)
    return;




  //these are random integers chosen so that the walls can be created between left right top and bottom.

  int vert =  2 *((rand()%((height)/2-1))+1) + top;//a random even # N; left < N <right
  int horz =  2 *((rand()%((width)/2-1))+1) + left;//a random even # M; top< M <bottom


  //**************************************************
  /*    for( int i = 0; i < level; i++) 
      cout << " " << left << right << vert << horz << endl;
  */
  //*****************************************************

// generate the '*' walls.
  for(int r = top + 1; r < bottom; r++)
    grid[horz][r] = '*';
  for (int c = left + 1; c <right; c++)
  grid[c][vert] = '*';

  //debug
  cout << left <<  " " << top << " " <<  bottom << " " <<  right << endl;
//this takes a random number between the walls so that the walls can be created.
int d1 =  2 *(rand()%((vert - top)/2))+1 + top;// a random odd #; left < D1 < vert

int d2 =  2 *(rand()%((horz - left)/2))+1 + left;// a random odd #; top < D2 < horz

int d3 =  2 *(rand()%((bottom - vert)/2))+1 + vert;// a random odd #; vert < D3 < right

int d4 =  2 *(rand()%((right - horz)/2))+1 + horz;// a random odd #; Vert < D4 < bottom


//select 4 doors and randomly skip one of them. its a random integer between 0 and 3.
int skip = rand()%4;
if (skip !=0) 
  grid[horz][d1] = ' ';
if (skip!=1)
  grid[horz][d3] = ' ';
if (skip!=2)
  grid[d2][vert] = ' ';
if (skip!=3)
  grid[d4][vert] = ' ';

// debuging!!!! 
cout << d1 << d2 << d3 << d4 << endl;

Divide(left, top, horz, vert);
Divide(horz, top, right, vert);
Divide(left, vert, horz, bottom);
Divide(horz, vert, right, bottom);



}

/*

}

//return an even integer between low and high
void maze :: EvenRand(int low, int high)
{
  int even;
  even =

    return even;
}

//return an odd integer between low and high
void Maze :: OddRand(int low, int high)
{

}


low = 6 high = 18
int possible; 5 because we have 8,10,12,14,16
int both = rand()% possible;
both*=2; 
even low + both +2;
6+0+2=8
6+2+2=10
6+4+2=12
6+6+2=14
6+8+2=16
*/
