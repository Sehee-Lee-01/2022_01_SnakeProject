#include <clocale> // 혹은 <locale.h>
#include <ncurses.h>
#include <iostream>
int main()
{
setlocale(LC_ALL, "");
//...
mvprintw(3,4,"\u2B1B \u2B1C"); // 화면에 ■ □ 인쇄
}