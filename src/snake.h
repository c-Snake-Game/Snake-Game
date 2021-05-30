#include <iostream>
#include <ncurses.h>
#include <list>
#include <stdlib.h>
#include <string>
#include <time.h>

#ifndef SNAKE_H
#define SNAKE_H

class board1{
public:
    board1();
    ~board1();
    int boardlist1[30][60];
    void printboard1();
};

class snake{
private:
    int x;
    int y;
public:
    snake(int headx, int heady){
        x = headx;
        y = heady;
    }
    int getX(){return x;}
    int getY(){return y;}
    
};



#endif