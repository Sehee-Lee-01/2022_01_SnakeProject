#include <ncurses.h>
#include <string.h>
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
	int row, col;
	row = 4;
	col = 4;
	char arr[10] = "34444";
    mvprintw(row,col,arr);

    attroff(COLOR_PAIR(2));
    refresh();
    getch();
    endwin();
    return 0;
}