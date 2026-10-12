#include <iostream>
#include "Maze.h"
using namespace std;

int main ()
{
    char play = 'y';
    Maze maze;
    maze.Instructions (cout, cin);
    while (tolower (play) == 'y')
    {
	maze.Init();
	maze.Display (cout);
	bool finished = false, quitting = false;
	while (!finished && !quitting)
	{
		char key;
		cout << "\nEnter move (a = left, w = up, d = right, s = down,\n\tq = quit, i = instructions): ";
		if (!(cin >> key))
			key = 'q';  // input ended (Ctrl-D or a closed pipe): quit instead of looping forever
		if (key == 'q')
			quitting = true;
		else if (key == 'i')
			maze.Instructions (cout, cin);
		else
			maze.Move(key);
		finished = maze.Done();
		maze.Display (cout);
	}
	maze.Message (finished, cout);
	cout << "Please play again! (y/n) ";
	if (!(cin >> play))
		play = 'n';
	cin.clear ();;
    }
    cout << endl;
    return 0;
}
