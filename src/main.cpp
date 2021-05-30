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
  board1 b1;
  WINDOW *win = newwin(30,90,0,60);
  wbkgd(win,COLOR_PAIR(100));
  b1.printboard1();

  //snake not working...>>
/*
  list<snake> snake1;
  list<snake>::iterator it;
  bool fail =false;
  char dir = 'l';
  char ch;

  for (int i =0;i<3;i++){
    snake1.push_front(snake(45+i,15));

  }
  

  while(!fail){
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
        fail =true;
        break;
    }

      snake head = snake1.front();
    int x = head.getX();
    int y = head.getY();
    if (dir == 'l') x--;
    else if (dir == 'r') x++;
    else if (dir == 'd') y--;
    else if (dir == 'u') y++;

    if (y>29 || y<1 || x>59 || x<1){
      fail = true;
    }


    //print snake
    erase();
    for (it = snake1.begin(); it!=snake1.end();it++){
      if (it == snake1.begin()){
        attron(COLOR_PAIR(33));
        mvprintw(y,x,"@"); 
        attroff(COLOR_PAIR(33));
      }
      else{
        attron(COLOR_PAIR(44));
        mvprintw(y,x,"S"); 
        attroff(COLOR_PAIR(44));
      }
      if (((*it).getX()==x) && ((*it).getY() == y)){  //collision with itself
        fail = true;
      }
    }

    refresh();
    
  }
  
  erase();
  */
  refresh();
  wrefresh(win);
  getch();



  endwin();
  return 0;
}
