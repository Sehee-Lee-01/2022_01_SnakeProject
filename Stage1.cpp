#include <iostream>
#include <ncurses.h>
#include <string.h>
using namespace std;

char map[21][42]; // Map

// Show Map
void show_map()
{
    for (int i=0; i<21; i++)
    {
        for(int j=0; j<21; j++)
            cin >> map[i][j];
            // set color
    }
}


int main()
{
    initscr(); // Curses mode start
    resize_term(21, 42);
    start_color(); // Use color
    keypad(stdscr, TRUE);
    
// Color Palette
// 1) Map
    init_pair(1, COLOR_WHITE, COLOR_WHITE); // 0 (background)
    init_pair(2, COLOR_BLACK, COLOR_BLACK); // 1 (wall)
    init_pair(3, COLOR_BLACK, COLOR_BLACK); // 2 (Immune Wall)
    init_pair(4, COLOR_MAGENTA, COLOR_MAGENTA); // Gate A, Gate B
    init_pair(6, COLOR_CYAN, COLOR_CYAN); // Growth Item
    init_pair(7, COLOR_RED, COLOR_RED); // Poison Item

// 2) Snake
    init_pair(8, COLOR_YELLOW, COLOR_YELLOW); // Snake Head
    init_pair(9, COLOR_GREEN, COLOR_GREEN); // Snake body

// Make & Show Map
    show_map();    

    // bkgd('0');
    // attron(COLOR_PAIR(2));
    // border('1', '1', '1', '1', '2', '2', '2', '2');
    // attroff(COLOR_PAIR(2));
    // attron(COLOR_PAIR(1));
    // mvprintw(4,4,"3444");
    // attroff(COLOR_PAIR(1));

    refresh(); // Show screen
    getch(); // Waiting user input
    endwin(); // Exit Curses mode

    return 0;
}