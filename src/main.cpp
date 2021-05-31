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

  bool flag =false;
  char dir = 'l';
  char ch;
  keypad(stdscr, TRUE);

  int headX = 15;
  int headY = 15;
  b1.boardList[headX][headY*2] = 3;
  b1.boardList[headX][(headY+1)*2] = 4;
  b1.boardList[headX][(headY+2)*2] = 4;
  b1.printBoard();
  while(!flag){
    ch = getch();
    switch(ch) {
      case 'a': //left
        dir = 'l';
        break;
      case 'd': //right
        dir = 'r';
        break;
      case 's': //down
        dir = 'd';
        break;
      case 'w': //up
        dir = 'u';
        break;
      default:
        flag =true;
        break;
    }

    if (dir == 'l') headY--;
    else if (dir == 'r') headY++;
    else if (dir == 'd') headX++;
    else if (dir == 'u') headX--;

    if (b1.boardList[headX][headY*2] != 9){
      flag = true;
    }


    

    
  }
  
  
  refresh();
  wrefresh(win);
  getch();



  endwin();
  return 0;
}
