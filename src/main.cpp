#include "snake.h"
using namespace std;

int main(int argc, char *argv[]) {
  initscr();
  noecho();
  curs_set(0);

  //speed for each stage
  int speed1 =300;  

  start_color();
  init_pair(16,16,16);
  init_pair(100,18,18);

  init_pair(33,226,226); //yellow
  init_pair(44,202,202); //orange

  wbkgd(stdscr, COLOR_PAIR(16));
  Board b1;
  WINDOW *win = newwin(30,90,0,64);
  wbkgd(win,COLOR_PAIR(100));

  bool flag = false;
  int dir = 1;   //right
  int ch;
  list<Snake> snake1;
  list<Snake>::iterator it;
  
  //initialize snake length:3
  for (int i = 0; i < 3; i++) {
    snake1.push_back(Snake(15,15+i));
  }
  for (it = snake1.begin(); it !=snake1.end(); it++) {
    
    if (it == snake1.begin()) {
      b1.boardList[(*it).getX()][(*it).getY()*2] = 3;
    }
    else {
      b1.boardList[(*it).getX()][(*it).getY()*2] = 4;
    }
  }
  b1.printBoard();
  keypad(stdscr, TRUE);

  time_t item_time;
  item_time = time(NULL);
  time_t gate_time;
  gate_time = time(NULL);
  int item_cnt = 0;
  int gate_cnt = 0;
  int intogate = 0;//for displaying gate while going into the gate
  
  while(!flag) {   //while start
    usleep(speed1*1000);
    if(kbhit()) {  //if(kbhit) start
      ch = getch();
      switch(ch) {
      case 'a': //left
        dir = 1;
        break;
      case 'd': //right
        dir = 2;
        break;
      case 's': //down
        dir = 3;
        break;
      case 'w': //up
        dir = 4;
        break;
      default:
        flag = true;
        break;
      }
    }
    Snake head = snake1.front();
    int headX = head.getX();
    int headY = head.getY();
    if (dir == 1) headY--;
    else if (dir == 2) headY++;
    else if (dir == 3) headX++;
    else if (dir == 4) headX--;
    
    

    if (b1.boardList[headX][headY*2] == 1){  //collision wall
      flag = true;
    }
    if (b1.boardList[headX][headY*2] == 4){  //opposite way
      flag = true;
    }

    ////////////////////////////////////
    //INTO GATE
    if (b1.boardList[headX][headY*2]==7){ 
      gate_time--;
      intogate = snake1.size();
      int anotherX, anotherY;
      if (headX == b1.gateX1 && headY == b1.gateY1){
        anotherX = b1.gateX2;
        anotherY = b1.gateY2;
      }
      else{
        anotherX = b1.gateX1;
        anotherY = b1.gateY1;
      }

      if (b1.boardList[anotherX-1][anotherY*2]==9){ //gate on the upper wall
        dir = 3; // down
        headX = anotherX + 1;
        headY = anotherY;
      }
      else if (b1.boardList[anotherX+1][anotherY*2] == 9){ //gate on the lower wall
        dir = 4; //up
        headX = anotherX -1;
        headY = anotherY;
      }
      else if (b1.boardList[anotherX][(anotherY-1)*2] == 9){ //gate on the left wall
        dir = 2; //right
        headX = anotherX;
        headY = anotherY + 1;
      }
      else if (b1.boardList[anotherX][(anotherY+1)*2] == 9) { //gate on the right wall
        dir = 1; //left
        headX = anotherX;
        headY = anotherY - 1;
      }

      //gate not on the sidewall
      else{ 
        if (dir == 1){ //original dir = left
          headX = anotherX;
          headY = anotherY - 1;
          if (b1.boardList[anotherX][(anotherY-1)*2]==1){ //when blocked by wall
            dir = 4; //up
            headX = anotherX -1;
            headY = anotherY;
            if (b1.boardList[anotherX-1][anotherY*2]==1){ //when blocked by wall again
              dir = 3; //down
              headX = anotherX+1;
              headY = anotherY;
              if (b1.boardList[anotherX+1][anotherY*2]==1){ //blocked again..
                dir = 2; //right
                headX = anotherX;
                headY = anotherY + 1;
              } 
            }
          }
        }
        else if (dir == 2) { //original dir =right
          headX = anotherX;
          headY = anotherY + 1;
          if (b1.boardList[anotherX][(anotherY+1)*2]==1){ //when blocked by wall
            dir = 3; //down
            headX = anotherX + 1;
            headY = anotherY;
            if (b1.boardList[anotherX+1][anotherY*2]==1){ //when blocked by wall again
              dir = 4; //up
              headX = anotherX-1;
              headY = anotherY;
              if (b1.boardList[anotherX-1][anotherY*2]==1){ //blocked again..
                dir = 1; //left
                headX = anotherX;
                headY = anotherY - 1;
              } 
            }
          }
        }
        else if (dir == 3) { //original dir = down
          headX = anotherX + 1; 
          headY = anotherY;
          if (b1.boardList[anotherX + 1][(anotherY)*2]==1){ //when blocked by wall
            dir = 1; //left
            headX = anotherX;
            headY = anotherY-1;
            if (b1.boardList[anotherX][(anotherY-1)*2]==1){ //when blocked by wall again
              dir = 2; //right
              headX = anotherX;
              headY = anotherY+1;
              if (b1.boardList[anotherX][(anotherY+1)*2]==1){ //blocked again..
                dir = 4; //up
                headX = anotherX-1;
                headY = anotherY;
              } 
            }
          }
        }
        else if (dir == 4) { //original dir =up
          headX = anotherX-1;
          headY = anotherY;
          if (b1.boardList[anotherX-1][(anotherY)*2]==1){ //when blocked by wall
            dir = 2; //right
            headX = anotherX;
            headY = anotherY+1;
            if (b1.boardList[anotherX][(anotherY+1)*2]==1){ //when blocked by wall again
              dir = 1; //left
              headX = anotherX;
              headY = anotherY-1;
              if (b1.boardList[anotherX][(anotherY-1)*2]==1){ //blocked again..
                dir = 3; //down
                headX = anotherX+1;
                headY = anotherY;
              } 
            }
          }
        }
      }

    }
    /////////////////////////////////
    if (item_time % 16 == 0) {   //set item
      item_time++;
      for (int i=2; i<30; i++) {
        for (int j=2; j<30; j++) {
          if (b1.itemList[i][j*2] == 5 || b1.itemList[i][j*2] == 6) {
            b1.itemList[i][j*2] = 0;
            b1.boardList[i][j*2] = 0;
          }
        }
      }
      b1.setItem();
    }

    if (gate_time % 15 == 0) {   //set gate
      gate_time++;
      for (int i=1; i<31; i++) {
        for (int j=1; j<31; j++) {
          if (b1.boardList[i][j*2] == 7) b1.boardList[i][j*2] = 1;
        }
      }
      b1.setGate();
    }

    item_cnt++;  //item이 2개씩 떨어지는거 방지
    if (item_cnt == 2) {
      item_cnt = 0;
      item_time++;
    }

    gate_cnt++;  //gate가 4개씩 생기는거 방지
    if (gate_cnt == 2) {
      gate_cnt = 0;
      gate_time++;
    }

    if (intogate !=0){ //if snake is going through a gate 
      gate_time--;
      intogate--;
    }

    snake1.push_front(Snake(headX,headY));  //new head (moving forward)
    
    
    
    if (b1.itemList[headX][headY*2] == 6) { //eating poison item
      b1.itemList[headX][headY*2] = 0;
      b1.boardList[(snake1.back()).getX()][(snake1.back()).getY()*2] = 0; //erase last tail*2
      snake1.pop_back();
      b1.boardList[(snake1.back()).getX()][(snake1.back()).getY()*2] = 0; 
      snake1.pop_back();
    }
    else if (b1.itemList[headX][headY*2] == 5) { //eating growth item
      b1.itemList[headX][headY*2] = 0;
    }
    else{  //default moving
      b1.boardList[(snake1.back()).getX()][(snake1.back()).getY()*2] = 0; //erase last tail
      snake1.pop_back();
    }

    
    if (snake1.size() == 2){ //when snake size < 3 
      flag = true;
    }

    if (snake1.size() == 4) {   //change stage
      b1.changeBoard(b1.stage_3);
    }
    //draw snake1 on the board
    for (it = snake1.begin(); it !=snake1.end(); it++) { 
      
      if (it == snake1.begin()) { //snake head
        b1.boardList[(*it).getX()][(*it).getY()*2] = 3;
        }
      else { //snake tail
        if ((*it).getX()==headX && (*it).getY() == headY){  //collision with itself
          flag = true;
        }
        b1.boardList[(*it).getX()][(*it).getY()*2] = 4;
      }
      
    }
    
    

    



    clear();
    b1.printBoard();
    refresh();
  }  //while end
  refresh();
  wrefresh(win);
  endwin();
  return 0;
  }

