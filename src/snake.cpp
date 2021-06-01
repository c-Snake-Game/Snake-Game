#include "snake.h"
int kbhit () {  /* checks if key has been hit or not */  
    struct timeval tv;
    fd_set read_fd;
    tv.tv_sec=0;
    tv.tv_usec=0;
    FD_ZERO(&read_fd);
    FD_SET(0,&read_fd);
    if(select(1, &read_fd, NULL, NULL, &tv) == -1) return 0;
    if(FD_ISSET(0,&read_fd)) return 1;
    return 0;
  }

Board::Board(){
  
  
    for (int i=0; i<32; i++) {
        for (int j=0; j<64; j++) {
            boardList[i][j] = 0;
        }
    }
    for (int i=0; i<32; i++) {
        for (int j=0; j<64; j++) {
            if (i == 0) boardList[i][j] = 9;
            else if (i == 31) boardList[i][j] = 9;
            else if (j == 0 || j == 1 || j == 62 || j==63) boardList[i][j] = 9;
            else if (j == 2 || j == 60) {
                if (i == 1 || i == 30) boardList[i][j] = 2;
                else boardList[i][j] = 1;
            }
            else if (i == 1 || i == 30) {
                if ( j>= 2 && j<= 61) {
                    if(j % 2 == 0) boardList[i][j] = 1;
                }
            }
        }
    }
  
}

Board::~Board(){
  
}

void Board::printBoard(){
    init_pair(9, 16, 16);      // 0 black
    init_pair(1, 8, 8);  // 1 gray
    init_pair(2, COLOR_WHITE,COLOR_WHITE);    // 2 white
    init_pair(3, 11, 11);  // 3 yellow head
    init_pair(4, COLOR_YELLOW, COLOR_YELLOW);  // 4 orange tail
    for (int x=0; x<32; x++) {
        for (int y=0; y<64; y++) {
            if(y % 2 == 0) {
                if (boardList[x][y] == 0) {
                    attron(COLOR_PAIR(9));
                    mvprintw(x,y,"aa");
                    attroff(COLOR_PAIR(9));
                }
                else if (boardList[x][y] == 1) {
                    attron(COLOR_PAIR(1));
                    mvprintw(x,y,"aa");
                    attroff(COLOR_PAIR(1));
                }
                else if (boardList[x][y] == 2) {
                    attron(COLOR_PAIR(2));
                    mvprintw(x,y,"aa");
                    attroff(COLOR_PAIR(2));
                }
                else if (boardList[x][y] == 3) {
                    attron(COLOR_PAIR(3));
                    mvprintw(x,y,"aa");
                    attroff(COLOR_PAIR(3));
                }
                else if (boardList[x][y] == 4) {
                    attron(COLOR_PAIR(4));
                    mvprintw(x,y,"aa");
                    attroff(COLOR_PAIR(4));
                }
            }
        }
    }
}









//class snake