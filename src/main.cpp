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
  for (int i = 0; i < 3; i++) {
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

  time_t item_time;
  item_time = time(NULL);
  int item_cnt = 0;
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
    
    if (item_time % 5 == 0) {
      item_time++;
      for (int i=1; i<30; i++) {
        for (int j=1; j<30; j++) {
          if (b1.itemList[i][j*2] == 5 || b1.itemList[i][j*2] == 6) b1.itemList[i][j*2] = 0;
        }
      }
      b1.setItem();
    }
    
    item_cnt++;  //item이 2개씩 떨어지는거 방지
    if (item_cnt == 2) {
      item_cnt = 0;
      item_time++;
    }

    it = snake1.begin();
    if (b1.itemList[(*it).getX()][(*it).getY()*2] == 5) {
      b1.itemList[(*it).getX()][(*it).getY()*2] = 0;
      snake1.push_back(Snake((*it).getX(),(*it).getY()));
    }
    else if (b1.itemList[(*it).getX()][(*it).getY()*2] == 6) {
      b1.itemList[(*it).getX()][(*it).getY()*2] = 0;
      b1.boardList[(snake1.back()).getX()][(snake1.back()).getY()*2] = 0; //erase last tail
      snake1.pop_back();
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

