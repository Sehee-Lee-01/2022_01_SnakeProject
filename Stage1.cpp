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
        {
            cin >> map[i][j];
            // Set & Print color
            switch (map[i][j])
            {
                case '0':
                    attron(COLOR_PAIR(0));
                    printw("0");
                    attroff(COLOR_PAIR(0));
                    break;
                case '1':
                    /* code */
                    break;
                case '2':
                    /* code */
                    break;
                default:
                    break;
            }
        }
    }
}

int main()
{
    initscr(); // Curses mode start
    resize_term(21, 42); // Size
    start_color(); // Use color
    keypad(stdscr, TRUE);
    
// Color Palette
// 1) Map
    init_pair(0, COLOR_WHITE, COLOR_WHITE); // 0: background
    init_pair(1, COLOR_BLACK, COLOR_BLACK); // 1: wall
    init_pair(2, COLOR_BLACK, COLOR_BLACK); // 2: Immune Wall

    init_pair(3, COLOR_MAGENTA, COLOR_MAGENTA); // 3: Gate A, Gate B
    init_pair(4, COLOR_CYAN, COLOR_CYAN); // 4: Growth Item
    init_pair(5, COLOR_RED, COLOR_RED); // 5: Poison Item
// 2) Snake
    init_pair(6, COLOR_YELLOW, COLOR_YELLOW); // 6: Snake Head
    init_pair(7, COLOR_GREEN, COLOR_GREEN); // 7: Snake body

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