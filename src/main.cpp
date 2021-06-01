#include "snake.h"
using namespace std;

int main(int argc, char *argv[]) {
  initscr();
  noecho();
  curs_set(0);
  

  start_color();
  init_pair(16,16,16);
  init_pair(100,18,18);

  init_pair(33,226,226); //yellow
  init_pair(44,202,202); //orange

  wbkgd(stdscr, COLOR_PAIR(16));
  Board b1;
  WINDOW *win = newwin(30,90,0,64);
  wbkgd(win,COLOR_PAIR(100));

  //snake not working...>>

  bool flag = false;
  int dir = 1;   //right
  int ch;
  list<Snake> snake1;
  list<Snake>::iterator it;

  //initialize snake length:10
  for (int i = 0; i < 10; i++) {
    snake1.push_back(Snake(15,15+i));
  }
  for (it = snake1.begin(); it !=snake1.end(); it++) {
    
    if (it == snake1.begin()) {
      b1.boardList[(*it).getX()][(*it).getY()*2] = 3;
    }
    else {
      b1.boardList[(*it).getX()][(*it).getY()*2] = 4;
    }
  }
  b1.printBoard();
  keypad(stdscr, TRUE);

  while(!flag) {   //while start
    usleep(500*1000);
    if(kbhit()) {  //if(kbhit) start
      ch = getch();
      switch(ch) {
      case 'a': //left
        dir = 1;
        break;
      case 'd': //right
        dir = 2;
        break;
      case 's': //down
        dir = 3;
        break;
      case 'w': //up
        dir = 4;
        break;
      default:
        flag = true;
        break;
      }
    }
    Snake head = snake1.front();
    int headX = head.getX();
    int headY = head.getY();
    if (dir == 1) headY--;
    else if (dir == 2) headY++;
    else if (dir == 3) headX++;
    else if (dir == 4) headX--;
    
    if (b1.boardList[headX][headY*2] == 1){  //collision wall
      flag = true;
    }
    
    snake1.push_front(Snake(headX,headY));  //new head
    b1.boardList[(snake1.back()).getX()][(snake1.back()).getY()*2] = 0; //erase last tail
    snake1.pop_back(); 

    for (it = snake1.begin(); it !=snake1.end(); it++) { //draw snake1 on the board
      
      if (it == snake1.begin()) { //snake head
        b1.boardList[(*it).getX()][(*it).getY()*2] = 3;
        }
      else { //snake tail
        if ((*it).getX()==headX && (*it).getY() == headY){  //collision with itself
          flag = true;
        }
        b1.boardList[(*it).getX()][(*it).getY()*2] = 4;
      }
      
    }
    
    
    clear();
    b1.printBoard();
    refresh();

    
  }  //while end
  refresh();
  wrefresh(win);
  endwin();
  return 0;
  }

