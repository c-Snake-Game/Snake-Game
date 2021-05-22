#include <iostream>
#include <ncurses.h>

#ifndef SNAKE_H
#define SNAKE_H

class board{
public:
    board();
    ~board();
    int boardlist[21][21];
    void printboard();
};

#endif