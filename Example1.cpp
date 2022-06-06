#include<ncurses.h>
#include<iostream>
using namespace std;
int main()
{
	int row, col;

	cin >> row >> col;
	
    initscr();
	resize_term(row, col);
	mvprintw(4,4,"C++ programming with ncurses");
	
    refresh();
	getch();
	endwin();

	return 0;
}

// g++ -std=c++11 -o ex1 Example1.cpp -lncursesw