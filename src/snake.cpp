#include "snake.h"
using namespace std;

random_device rd;
mt19937 gen(rd());

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
            itemList[i][j] = 0;
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
    init_pair(5, COLOR_GREEN, COLOR_GREEN);  // 5 Growh item green
    init_pair(6, COLOR_RED, COLOR_RED);  // 6 Poison item red
    init_pair(7, 90, 90);  // 7 gate purple
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
                else if (boardList[x][y] == 7) {
                    attron(COLOR_PAIR(7));
                    mvprintw(x,y,"aa");
                    attroff(COLOR_PAIR(7));
                }
                if (itemList[x][y] == 5) {   //Growth Item
                    attron(COLOR_PAIR(5));
                    mvprintw(x,y,"aa");
                    attroff(COLOR_PAIR(5));
                }
                else if (itemList[x][y] == 6) {   //Poison Item
                    attron(COLOR_PAIR(6));
                    mvprintw(x,y,"aa");
                    attroff(COLOR_PAIR(6));
                }
            }
        }
    }
}

void Board::setItem() {
    pair<int,int> xy;
    list<pair<int,int>> pairList;
    for (int i=2; i<29; i++) {
        for (int j=2; j<29; j++) {
                if ( boardList[i][j*2] == 0) {
                    xy.first = i;
                    xy.second = j;
                    pairList.push_back(xy);
                }
        }
    }
    int size = pairList.size();

    uniform_int_distribution<int> dis(0,size-1);
    int ranNum = dis(gen);
    int item = dis(gen);
    int x = 0;
    int y = 0;
    for ( int i=0; i<ranNum; i++ ) {
        xy = pairList.front();
        pairList.pop_front();
        pairList.push_back(xy);    
    }
    xy = pairList.front();
    x = xy.first;
    y = xy.second;
    if (item % 2 == 0) {
        itemList[x][y*2] = 5;   // Growth Item
    }
    else {
        itemList[x][y*2] = 6;   // Poison Item
    }
}

void Board::setGate() {
    // x = 1~30  y*2 = 2 ~ 29
    int x1;
    int y1;
    int x2;
    int y2;

    pair<int,int> xy;
    list<pair<int,int>> pairList;
    for (int i=0; i<32; i++) {
        for (int j=0; j<32; j++) {
            if ( boardList[i][j*2] == 1 ) {
                xy.first = i;
                xy.second = j;
                pairList.push_back(xy);
            }
        }
    }

    int size = pairList.size();
    uniform_int_distribution<int> dis(0,size-1);   
    int ranNum_1 = dis(gen);
    int ranNum_2 = dis(gen);
    
    for ( int i=0; i<ranNum_1; i++ ) {
        xy = pairList.front();
        pairList.pop_front();
        pairList.push_back(xy);    
    }
    xy = pairList.front();
    x1 = xy.first;
    y1 = xy.second;
    pairList.pop_front();

    for ( int i=0; i<ranNum_2; i++ ) {
        xy = pairList.front();
        pairList.pop_front();
        pairList.push_back(xy);    
    }
    xy = pairList.front();
    x2 = xy.first;
    y2 = xy.second;
    
    gateX1=x1; gateY1 = y1;
    gateX2=x2; gateY2 = y2; 
    boardList[x1][y1*2] = 7;
    boardList[x2][y2*2] = 7;
}

Snake::~Snake() {
}







//class snake