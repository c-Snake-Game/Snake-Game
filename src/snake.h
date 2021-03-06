#include <iostream>
#include <ncurses.h>
#include <list>
#include <utility>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <ctime>   //setItem
#include <random>  //setItem

#ifndef SNAKE_H
#define SNAKE_H

int kbhit();     //key board hit 

class Board{
    public:
        Board();
        ~Board();
        int boardList[32][64];
        int itemList[32][64];
        int stage_1[32][64];
        int stage_2[32][64];
        int stage_3[32][64];
        void printBoard();
        void printPlay();
        void setItem();
        void setSpecial();
        void setGate();
        void changeBoard(int arr[32][64]);
        int gateX1,gateY1;
        int gateX2,gateY2;
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
