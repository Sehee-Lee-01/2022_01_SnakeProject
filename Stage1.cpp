#include <ncurses.h>
int main()
{
    initscr();
    resize_term(21, 21);
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_GREEN);

    bkgd('0');
    attron(COLOR_PAIR(1));
    attroff(COLOR_PAIR(1));
    
    attron(COLOR_PAIR(2));
    border('1', '1', '1', '1', '2', '2', '2', '2');
    mvprintw(4,4,"3444");

    attroff(COLOR_PAIR(2));
    refresh();
    getch();
    endwin();
    return 0;
}