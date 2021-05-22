#include "snake.h"

board::board(){
  for (int i=0; i<21; i++) {
      for (int j=0; j<21; j++) {
          boardlist[i][j] = 0;
      }
  }
  for (int i=0; i<21; i++) {
      for (int j=0; j<21; j++) {
          if ((i==0) && (j>=1 && j<= 19)) boardlist[i][j] = 1;
          else if ((j==0) && (i>=1 && i<=19)) boardlist[i][j] = 1;
          else if ((i==20) && (j>=1 && j<=19)) boardlist[i][j] = 1;
          else if ((j==20) && (i>=1 && i<=19)) boardlist[i][j] = 1;
      }
  }
  boardlist[10][10] = 3;
  boardlist[10][11] = 4;
  boardlist[10][12] = 4;
  boardlist[0][0] = 2;
  boardlist[0][20] = 2;
  boardlist[20][0] = 2;
  boardlist[20][20] = 2;
}

board::~board(){
}

void board::printboard(){
    init_pair(0, 15,15);      // 0 white
    init_pair(1, 8, 8);  // 1 gray
    init_pair(2, COLOR_BLACK,COLOR_BLACK);    // 2 black
    init_pair(3, 11, 11);  // 3 yellow head
    init_pair(4, COLOR_YELLOW, COLOR_YELLOW);  // 4 orange tail
    for (int i=0; i<21; i++) {
        for (int j=0; j<21; j++) {
            if (boardlist[i][j] == 0) {
                move(i,j);
                attron(COLOR_PAIR(0));
                addch('a');
                attroff(COLOR_PAIR(0));
            }
            else if (boardlist[i][j] == 1) {
                move(i,j);
                attron(COLOR_PAIR(1));
                addch('a');
                attroff(COLOR_PAIR(1));
            }
            else if (boardlist[i][j] == 2) {
                move(i,j);
                attron(COLOR_PAIR(2));
                addch('a');
                attroff(COLOR_PAIR(2));
            }
            else if (boardlist[i][j] == 3) {
                move(i,j);
                attron(COLOR_PAIR(3));
                addch('a');
                attroff(COLOR_PAIR(3));
            }
            else if (boardlist[i][j] == 4) {
                move(i,j);
                attron(COLOR_PAIR(4));
                addch('a');
                attroff(COLOR_PAIR(4));
            }
        }
    }
}
