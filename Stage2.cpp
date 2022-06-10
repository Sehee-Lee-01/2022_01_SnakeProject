#include <ncurses.h>
int main()
{
    initscr();
    resize_term(21, 42);
    start_color();
    keypad(stdscr, TRUE);

    init_pair(1, COLOR_BLACK, COLOR_YELLOW);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);

    // bkgd('0');
    
    attron(COLOR_PAIR(2));
    border('|', '|', '-', '-', '+', '+', '+', '+');
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    mvprintw(4,4,"^000");
    attroff(COLOR_PAIR(1));

    refresh();
    getch();
    endwin();
    return 0;
}