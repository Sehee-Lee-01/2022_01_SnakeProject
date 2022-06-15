#include <ncurses.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <time.h>


#define tick 100000 //0.1sec

using namespace std;
// Size define
#define map_height 21
#define map_width 42

WINDOW *score_board;
WINDOW *goal_board;

bool fail = false; // game over, init = false
int stage = 1;
// ifstream map_file;
int map[map_height][map_width]; // Map
//snaked
vector<int> snake_x;
vector<int> snake_y; 
int direction = 0; // 0: up, 1: right, 2: down, 3: left
int cur_x; int cur_y;
void get_item();
void in_gate();
void show_gate();

// item
int poison_x, poison_y, growth_x, growth_y;
int gate1_x, gate1_y, gate2_x, gate2_y;

int item_timer = 0;
int gate_timer = 0;

// score
int get_growth, get_poison, get_gate, max_length = 4;
int goal_growth = 1, goal_poison = 1, goal_gate = 0, goal_length = 5;
float play_time;

void show_map(int stage)
{
    init_pair(1, COLOR_WHITE, COLOR_WHITE); // 0: background
    init_pair(2, COLOR_CYAN, COLOR_CYAN); // 1: wall
    init_pair(3, COLOR_BLACK, COLOR_BLACK); // 2: Immune Wall
    ifstream map_file("./snakemap/snakemap" + to_string(stage) + ".txt");
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

bool move()
{
    int a =0;
    int key ;
    
        show_map(stage); show_snake(); get_item(); show_gate(); in_gate();

        cur_x = snake_x[0];
        cur_y = snake_y[0];
        
        if((map[cur_x][cur_y] == 1) || (snake_x.size() < 3)) {return true;}

    // 0: up, 1: right, 2: down, 3: left
        if (cur_x == growth_x && cur_y == growth_y){
            max_length++;
            get_growth++;
            int lastx = snake_x[-1];
            int lasty = snake_y[-1];
            if(direction == 0){snake_x.push_back(++lastx); snake_y.push_back(lasty);}
            else if(direction == 1){snake_x.push_back(lastx); snake_y.push_back(--lasty);}
            else if(direction == 2){snake_x.push_back(--lastx); snake_y.push_back(lasty);}
            else if(direction == 3){snake_x.push_back(lastx); snake_y.push_back(++lasty);}
        }
        else if (cur_x == poison_x && cur_y == poison_y)
        {
            get_poison++;
            snake_x.pop_back();snake_y.pop_back();
        }

        if(direction == 0){snake_x[0]--;}
        else if(direction == 1){snake_y[0]++;}
        else if(direction == 2){snake_x[0]++;}
        else if(direction == 3){snake_y[0]--;}


        key = getch();
        // 0: up, 1: right, 2: down, 3: left
        switch(key){    
			case KEY_RIGHT : // 오른쪽
                if (direction == 3) {return true;}// left
                else {direction = 1;}
			    break;
			case KEY_LEFT : // 왼쪽
                if(direction == 1){return true;} // right
                else {direction = 3;}// up
                break;
            case KEY_DOWN : // 아래 
                if(direction == 0){return true;} // up
                else {direction = 2;}
                break;
            case KEY_UP : //위
            if (direction == 2) {return true;}// left
                else {direction = 0;}
			    break;
            default:
                break;
            }

        for(int i = 1; i <= snake_y.size(); i++){
            
            int y =  snake_y[i];
            int x =  snake_x[i];
            
            snake_y[i] = cur_y;
            snake_x[i] = cur_x;

            cur_y = y; cur_x = x;
        }
        usleep(tick);

    return false;
}

void show_item()
{
    attron(COLOR_PAIR(6));
    mvprintw(poison_x, poison_y," ");
    attroff(COLOR_PAIR(6));    
    attron(COLOR_PAIR(7));
    mvprintw(growth_x, growth_y," ");
    attroff(COLOR_PAIR(7));  
}

void get_item()
{   
    init_pair(6, COLOR_RED, COLOR_RED); // poision
    init_pair(7, COLOR_BLUE, COLOR_BLUE); // growth
    
    srand(time(NULL));
    if(item_timer == 0){
        do{    
            poison_x = rand() % 18 + 2;
            poison_y = rand() % 39 + 2;
            do{
                growth_x = rand() % 18 + 2;
                growth_y = rand() % 39 + 2;
            }
            while(poison_x == growth_x && growth_x == poison_x );
        }
        while (map[poison_x][poison_y] == 1 || map[poison_x][poison_y] ==2 ||map[growth_x][growth_y] == 1 || map[growth_x][growth_y] == 2); // when value = 2 position

        item_timer = 50;
    }
    else {item_timer--;}

    // show Item
     show_item();
}


void in_gate()
{
    int cur_x = snake_x[0];
    int cur_y = snake_y[0];
    if((cur_x == gate1_x && cur_y  == gate1_y)||(cur_x == gate2_x && cur_y  == gate2_y))
    {
        get_gate++;
        if(cur_x == gate1_x) {cur_x = gate2_x; cur_y = gate2_y;}
        else {cur_x = gate1_x; cur_y = gate1_y;}
        
        switch (direction)
        {
        case 0:
            if(map[cur_x - 1][cur_y] ==0 && cur_x - 1 > 0 ){snake_x[0] = cur_x - 1 ;snake_y[0] = cur_y; direction = 0 ;}
            else if (map[cur_x][cur_y + 1] ==0 && cur_y + 1 < 42){snake_x[0] = cur_x ;snake_y[0] = cur_y + 1; direction = 1;}
            else if (map[cur_x][cur_y - 1]==0 && cur_y - 1> 0 ){snake_x[0] = cur_x ;snake_y[0] = cur_y - 1; direction = 3;}
            else if (map[cur_x + 1][cur_y ] ==0 && cur_x + 1< 21){snake_x[0] = cur_x + 1 ;snake_y[0] = cur_y; direction = 2;}
            break;
        case 1:
            if (map[cur_x][cur_y + 1] ==0 && cur_y + 1 <42){snake_x[0] = cur_x ;snake_y[0] = cur_y + 1; direction = 1;}
            else if (map[cur_x + 1][cur_y ] ==0 && cur_x + 1 < 21){snake_x[0] = cur_x+1 ;snake_y[0] = cur_y; direction = 2;}
            else if (map[cur_x - 1][cur_y] ==0 && cur_x - 1 > 0 ){snake_x[0] = cur_x - 1 ;snake_y[0] = cur_y; direction = 0 ;}
            else if (map[cur_x][cur_y - 1]==0 && cur_y - 1> 0 ){snake_x[0] = cur_x ;snake_y[0] = cur_y - 1; direction = 3;}
            break;
            
        case 2:
            if (map[cur_x + 1][cur_y ] ==0 && cur_x + 1< 21){snake_x[0] = cur_x + 1 ;snake_y[0] = cur_y; direction = 2;}
            else if (map[cur_x][cur_y - 1]==0 && cur_y - 1> 0 ){snake_x[0] = cur_x ;snake_y[0] = cur_y - 1; direction = 3;}
            else if (map[cur_x][cur_y + 1] ==0 && cur_y + 1 < 42){snake_x[0] = cur_x ;snake_y[0] = cur_y + 1; direction = 1;}
            else if (map[cur_x - 1][cur_y] ==0 && cur_x - 1 > 0 ){snake_x[0] = cur_x - 1 ;snake_y[0] = cur_y; direction = 0 ;}
            break;

        case 3:
            if (map[cur_x][cur_y - 1]==0 && cur_y - 1> 0 ){snake_x[0] = cur_x ;snake_y[0] = cur_y - 1; direction = 3;}
            else if (map[cur_x - 1][cur_y] ==0 && cur_x - 1 > 0 ){snake_x[0] = cur_x - 1 ;snake_y[0] = cur_y; direction = 0 ;}
            else if(map[cur_x + 1][cur_y ] ==0 && cur_x + 1< 21){snake_x[0] = cur_x + 1 ;snake_y[0] = cur_y; direction = 2;}
            else if (map[cur_x][cur_y + 1] ==0 && cur_y + 1 < 42){snake_x[0] = cur_x ;snake_y[0] = cur_y + 1; direction = 1;}
            break;
        }
    }
}

void show_gate()
{
    init_pair(8, COLOR_MAGENTA, COLOR_MAGENTA);
    srand(time(NULL));
    if(gate_timer == 0) // not immune wall
    {   
        do{
            gate1_x = rand() % 21;
            gate1_y = rand() % 42;
            do{
                gate2_x = rand() % 21;
                gate2_y = rand() % 42;
            }
            while(gate1_x == gate1_y && gate1_x == gate2_y);
        }
        while
        (map[gate1_x][gate1_y] == 2 || map[gate2_x][gate2_y] ==2); // when value = 2 position
        gate_timer = 50;
    }
    else {gate_timer--;}
    
    // show gate
    attron(COLOR_PAIR(8));
    mvprintw(gate1_x, gate1_y," ");
    mvprintw(gate2_x, gate2_y," ");
    attroff(COLOR_PAIR(8));          
}

void show_score(){
    init_pair(9, COLOR_BLACK, COLOR_WHITE);

    score_board = newwin(10, 20, 0, 43);
    goal_board = newwin(10, 20, 11, 43);
    wbkgd(score_board, COLOR_PAIR(9));
    wbkgd(goal_board, COLOR_PAIR(9));
    wattron(score_board, COLOR_PAIR(9));
    mvwprintw(score_board, 1, 1, "Score board");
    mvwprintw(score_board, 2, 1, "B: %d / %d", snake_x.size(), max_length);
    mvwprintw(score_board, 3, 1, "+: %d", get_growth);
    mvwprintw(score_board, 4, 1, "-: %d", get_poison);
    mvwprintw(score_board, 5, 1, "G: %d", get_gate);
    wborder(score_board, '@','@','@','@','@','@','@','@');
    wattroff(score_board, COLOR_PAIR(9));
    wrefresh(score_board);

    wattron(goal_board, COLOR_PAIR(9));
    mvwprintw(goal_board, 1, 1, "Mission");
    mvwprintw(goal_board, 2, 1, "B: %d", goal_length);
    if (max_length < goal_length) {wprintw(goal_board, " ( )");} else {wprintw(goal_board, " (V)");}
    mvwprintw(goal_board, 3, 1, "+: %d", goal_growth);
    if (get_growth < goal_growth) {wprintw(goal_board, " ( )");} else {wprintw(goal_board, " (V)");}
    mvwprintw(goal_board, 4, 1, "-: %d", goal_poison);
    if (get_poison > goal_poison) {wprintw(goal_board, " ( )");} else {wprintw(goal_board, " (V)");}
    mvwprintw(goal_board, 5, 1, "G: %d", goal_gate);
    if (get_gate < goal_gate) {wprintw(goal_board, " ( )");} else {wprintw(goal_board, " (V)");}
    wborder(goal_board, '@','@','@','@','@','@','@','@');
    wattroff(goal_board, COLOR_PAIR(9));
    wrefresh(goal_board);

    WINDOW * ck;
    ck = newwin(10, 20, 21, 43);
    wattron(ck, COLOR_PAIR(9));
    mvwprintw(ck, 1, 1, "%d", fail);
    wattroff(ck, COLOR_PAIR(9));
    wrefresh(ck);

}

void init(){

    while(snake_x.size() != 0)
    {
        snake_x.pop_back();
        snake_y.pop_back();
    }

    int init_x = 15;
    int init_y = 17;

    for (int i=0; i<4; i++)
    {    
        snake_x.push_back(init_x + i); 
        snake_y.push_back(init_y);
    }
    
    direction =0;

    get_growth=0; get_poison= 0; get_gate= 0; max_length= 4; 
    switch(stage){
        case 1:
            goal_growth = 2; 
            goal_poison = 0; 
            goal_gate = 2; 
            goal_length = 6;
            break;
        case 2:
            goal_growth = 3; 
            goal_poison = 0; 
            goal_gate = 3; 
            goal_length = 7;
            break;
        case 3:
            goal_growth = 4; 
            goal_poison = 1; 
            goal_gate = 4; 
            goal_length = 8;
            break;
        case 4:
            goal_growth = 7; 
            goal_poison = 2; 
            goal_gate = 6; 
            goal_length = 9;
            break;
    }

}
int main()
{
    initscr();
    resize_term(100, 100);
    start_color();
    nodelay(stdscr, true);
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    
for(; stage< 5; stage++)
{       
    init();
    show_map(stage);
	// show_score();

   while(!fail)
   {
        play_time += 0.1;
        fail = move();
        show_score();
        if ((max_length >= goal_length) && (get_growth >= goal_growth) && (get_poison <= goal_poison) && (get_gate >= goal_gate) ) {break;}
    }


    if(fail == 1)
        break;
        


    getch();
}
    sleep(4);
    clear();
    getch();
    
	endwin();
    if (fail){cout << "\n\nFailed!\nPlay time: "<< play_time <<" sec\n\n";}
    else{cout << "\n\nSuccessed!\nPlay time: "<< play_time <<" sec\n\n";}
	return 0;
}