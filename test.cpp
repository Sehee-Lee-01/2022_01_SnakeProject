#include<ncurses.h>
#include <unistd.h>
#include<fstream>
#include<iostream>
#include <vector>
#include <time.h>


#define tick 100000 

using namespace std;
// Size define
#define map_height 21
#define map_width 42
ifstream map_file;
int map[map_height][map_width]; // Map
//snake
vector<int> snake_x;
vector<int> snake_y; 

void show_map()
{
    init_pair(1, COLOR_WHITE, COLOR_WHITE); // 0: background
    init_pair(2, COLOR_CYAN, COLOR_CYAN); // 1: wall
    init_pair(3, COLOR_BLACK, COLOR_BLACK); // 2: Immune Wall
    string filename = "./snakemap/snakemap1.txt";
    map_file.open(filename);
    string line;
    for (int i=0; i<map_height; i++)
    {
        getline(map_file,line);
        for(int j=0; j<map_width; j++)
        {
            map[i][j] = line.at(j) - '0'; // char to int: out of range
            // Set & Print color
            switch (map[i][j])
            {
                case 0: // background
                    attron(COLOR_PAIR(1));
                    mvprintw(i, j," ");
                    attroff(COLOR_PAIR(1));                    
                    break;
                case 1: // wall
                    attron(COLOR_PAIR(2));
                    mvprintw(i, j," ");
                    attroff(COLOR_PAIR(2));                    
                    break;
                case 2: // Immune Wall
                    attron(COLOR_PAIR(3));
                    mvprintw(i, j," ");
                    attroff(COLOR_PAIR(3));                    
                    break;
            }
        }
    }
    map_file.close();
    refresh();
}
void show_snake()
{
    init_pair(4, COLOR_YELLOW, COLOR_YELLOW); // snake head
    init_pair(5, COLOR_GREEN, COLOR_GREEN); // snake body
    // print head
    attron(COLOR_PAIR(4));
    mvprintw(snake_x[0], snake_y[0]," ");
    attroff(COLOR_PAIR(4));
 
    //print body 
    for(int i=1; i<snake_x.size();i++)
    {
        attron(COLOR_PAIR(5));
        mvprintw(snake_x[i], snake_y[i]," ");
        attroff(COLOR_PAIR(5));
    }
    refresh();
}
int main()
{
    int x = 11;
    int y = 11;
    // init snake place
    for (int i=0; i<4; i++)
    {    
        snake_x.push_back(11 + i); 
        snake_y.push_back(11);
    }

    
    initscr();
    start_color();

    show_map();
    // getch();

    show_snake();

    for(int i = 0; i < 9; i++)
    {
        show_map(); show_snake();
        for(int j = 0; j < 4; j++)
        {
            snake_x[j]--;
        }
        usleep(tick);
    }
	getch();
	endwin();

	return 0;
}

// g++ -std=c++11 -o ex1 Example1.cpp -lncursesw