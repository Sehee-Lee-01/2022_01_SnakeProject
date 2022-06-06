#include <ncurses.h>
int main()
{
    initscr();
    resize_term(21, 42);
    start_color();
    keypad(stdscr, TRUE);

    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_YELLOW, COLOR_GREEN);

    bkgd('0');
    
    attron(COLOR_PAIR(2));
    border('1', '1', '1', '1', '2', '2', '2', '2');
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    mvprintw(4,4,"3444");
    attroff(COLOR_PAIR(1));

    refresh();
    getch();
    endwin();
    return 0;
}