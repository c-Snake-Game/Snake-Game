#include <iostream>
#include <ncurses.h>
#include <list>
#include <stdlib.h>
#include <string>
#include <time.h>

#ifndef SNAKE_H
#define SNAKE_H

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
    Snake(int headx, int heady){
        x = headx;
        y = heady;
    }
    int getX(){return x;}
    int getY(){return y;}
    
};



#endif