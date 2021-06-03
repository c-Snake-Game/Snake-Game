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
    init_pair(7, COLOR_MAGENTA, COLOR_MAGENTA);  // 7 gate purple
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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(2,29);    //2, 29
    int x = dis(gen);
    int y = dis(gen);
    int item = dis(gen);
    while (true) {  //snake가 있는 곳에는 item생성 x
        if (boardList[x][y*2] == 3 || boardList[x][y*2] == 4) {
            x = dis(gen);
            y = dis(gen);
            item = dis(gen);
        }
        else break;
    }
    if (item % 2 == 0) {
        itemList[x][y*2] = 5;   // Growth Item
    }
    else {
        itemList[x][y*2] = 6;   // Poison Item
    }
}

void Board::setGate() {
    // x = 1~30  y*2 = 2 ~ 29
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis_0(1,30);    //version
    std::uniform_int_distribution<int> dis_1(1,30);   //x1,x2
    std::uniform_int_distribution<int> dis_2(2,29);   // x= 1 , y
    std::uniform_int_distribution<int> dis_4(1,2);   // x = 2~29 , y
    std::uniform_int_distribution<int> dis_5(1,2);   // x = 2~29 , y
    int arrY[] = {0,1,30,0};
    int x1;
    int y1;
    int x2;
    int y2;
    int ver = dis_0(gen);
    if (ver % 2 == 0) {  // x먼저 뽑을경우 맨왼쪽 맨오른쪽 나올 확률이 높음
        x1 = dis_1(gen);
        x2 = dis_1(gen);
        if ( x1 == 1 ) {
        y1 = dis_2(gen);
        }
        else if ( x1 == 30) {
            y1 = dis_2(gen);
        }
        else {
            y1 = arrY[dis_4(gen)];
        }

        if ( x2 == 1 ) {
            y2 = dis_2(gen);
        }
        else if ( x2 == 30) {
            y2 = dis_2(gen);
        }
        else {
            y2 = arrY[dis_5(gen)];
        }
    }
    else {  // y먼저 뽑을경우 맨위 맨아래 나올 확률이 높음
        y1 = dis_1(gen);
        y2 = dis_1(gen);
        if ( y1 == 1 ) {
        x1 = dis_2(gen);
        }
        else if ( y1 == 30 ) {
            x1 = dis_2(gen);
        }
        else {
            x1 = arrY[dis_4(gen)];
        }

        if ( y2 == 1 ) {
            x2 = dis_2(gen);
        }
        else if ( y2 == 30 ) {
            x2 = dis_2(gen);
        }
        else {
            x2 = arrY[dis_5(gen)];
        }
    }
    boardList[x1][y1*2] = 7;
    boardList[x2][y2*2] = 7;
}

Snake::~Snake() {
}







//class snake