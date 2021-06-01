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

  int sl = 7;   //snake length
  for (int i = 0; i < sl; i++) {
    snake1.push_back(Snake(15,15+i));
  }
  for (int i = 0; i < sl; i++) {
    Snake temp = snake1.front();
    snake1.pop_front();
    snake1.push_back(temp);
    if (i == 0) {
      b1.boardList[temp.getX()][temp.getY()*2] = 3;
    }
    else {
      b1.boardList[temp.getX()][temp.getY()*2] = 4;
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
    Snake temp = snake1.back();
    b1.boardList[temp.getX()][temp.getY()*2] = 0;
    snake1.pop_back();

    for (int i = 0; i < sl; i++) {
      Snake temp = snake1.front();
      snake1.pop_front();
      snake1.push_back(temp);
      if (i == 0) {
        b1.boardList[temp.getX()][temp.getY()*2] = 3;
        }
      else {
        b1.boardList[temp.getX()][temp.getY()*2] = 4;
      }
    }
    Snake tempH = snake1.front();
    for (it = snake1.begin(); it != snake1.end(); it++) {  //collision with itself
      if ( it != snake1.begin() ) {
        if ((*it).getX() == tempH.getX() && (*it).getY() == tempH.getY() ) flag = true;
      }
    }  
    clear();
    b1.printBoard();
    refresh();
    } //if(kbhit) end
    else { //else start
      Snake head = snake1.front();
      int headX = head.getX();
      int headY = head.getY();
      if (dir == 1) headY--;
      else if (dir == 2) headY++;
      else if (dir == 3) headX++;
      else if (dir == 4) headX--;
      if (b1.boardList[headX][headY*2] == 1){
        flag = true;
      }
      snake1.push_front(Snake(headX,headY));  //new head
      Snake temp = snake1.back();
      b1.boardList[temp.getX()][temp.getY()*2] = 0;
      snake1.pop_back();
      for (int i = 0; i < sl; i++) {
        Snake temp = snake1.front();
        snake1.pop_front();
        snake1.push_back(temp);
        if (i == 0) {
          b1.boardList[temp.getX()][temp.getY()*2] = 3;
        }
        else {
          b1.boardList[temp.getX()][temp.getY()*2] = 4;
        }
      }
      Snake tempH = snake1.front();
      for (it = snake1.begin(); it != snake1.end(); it++) {  //collision with itself
        if ( it != snake1.begin() ) {
          if ((*it).getX() == tempH.getX() && (*it).getY() == tempH.getY() ) flag = true;
      }
    }
      clear();
      b1.printBoard();
      refresh();
    }  //else end
  }  //while end
  refresh();
  wrefresh(win);
  endwin();
  return 0;
  }

