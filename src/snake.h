#include <iostream>
#include <ncurses.h>
#include <list>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <time.h>

#ifndef SNAKE_H
#define SNAKE_H

int kbhit();     //key board hit 

class Board{
    public:
        Board();
        ~Board();
        int boardList[32][64];
        void printBoard();
};

class Snake{
    private:
        int x;
        int y;
    public:
        Snake(int headx = 0, int heady = 0):x(headx), y(heady){}
        ~Snake();
        int getX(){return x;}
        int getY(){return y;}
};

#endif
