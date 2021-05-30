#include "snake.h"

board1::board1(){
  
  for (int y=0; y<30; y++) { 
      for (int x=0; x<60; x++) {
          if ((y==0||y==29)&&(x==0||x==59)){//immune wall
              boardlist1[y][x] = 2;
          }
          else if ((y==0||y==29)||(x==0||x==59)){
              boardlist1[y][x] = 1;
          }
          else boardlist1[y][x] = 0;

      }

  }
  
}

board1::~board1(){
    for (int y=0; y<30; y++) {
      for (int x=0; x<60; x++) {
          boardlist1[y][x] = 0;
      }
  }
}

void board1::printboard1(){
    init_pair(9, 16, 16);      // 0 black
    init_pair(1, 8, 8);  // 1 gray
    init_pair(2, COLOR_WHITE,COLOR_WHITE);    // 2 white
    init_pair(3, 11, 11);  // 3 yellow head
    init_pair(4, COLOR_YELLOW, COLOR_YELLOW);  // 4 orange tail
    for (int y=0; y<30; y++) {
        for (int x=0; x<60; x++) {
            if (boardlist1[y][x] == 0) {
                attron(COLOR_PAIR(9));
                mvprintw(y,x,"a");
                attroff(COLOR_PAIR(9));
            }
            else if (boardlist1[y][x] == 1) {
                
                attron(COLOR_PAIR(1));
                mvprintw(y,x,"a");
                attroff(COLOR_PAIR(1));
            }
            else if (boardlist1[y][x] == 2) {
                attron(COLOR_PAIR(2));
                mvprintw(y,x,"a");
                attroff(COLOR_PAIR(2));
            }
            else if (boardlist1[y][x] == 3) {
                attron(COLOR_PAIR(3));
                mvprintw(y,x,"a");
                attroff(COLOR_PAIR(3));
            }
            else if (boardlist1[y][x] == 4) {
                attron(COLOR_PAIR(4));
                mvprintw(y,x,"a");
                attroff(COLOR_PAIR(4));
            }
        }
    }
}









//class snake