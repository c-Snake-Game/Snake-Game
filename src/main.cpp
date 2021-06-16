#include "snake.h"
using namespace std;

int main(int argc, char *argv[]) {
  initscr();
  noecho();
  curs_set(0);
  start_color();
  init_pair(16,16,16);
  
  init_pair(21,COLOR_WHITE,16);//white letter
  init_pair(22,COLOR_YELLOW,16);//yellow letter
  init_pair(23,90,16);//purple letter
  init_pair(24,COLOR_YELLOW,234);
  init_pair(25,90,234);
  init_pair(26,COLOR_GREEN,16);//green
  init_pair(27,COLOR_RED,16);//purple
  init_pair(28,11,16);//light yellow
  init_pair(29,50,16);//special
  
  wbkgd(stdscr, COLOR_PAIR(16));
  Board b1;
  
  bool flag = false;
  bool flag_special = false;
  int dir = 1;   //right
  int ch;
  list<Snake> snake1;
  list<Snake>::iterator it;
  int success = false;
  int growth_cnt =0;
  int poison_cnt =0;
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
  time_t start_time;  
  start_time = time(NULL);
  while(!start_time % 5 == 0) {
    start_time++;
    if (start_time % 5 == 0) {
      break;
    }
  }
  int gate_cnt = 0;
  bool changeBoard_1 = true;
  bool changeBoard_2 = true;
  bool changeBoard_3 = true;
  int intogate = 0;//for displaying gate while going into the gate
  //speed for each stage
  int speedArr[] = {300,220,140,100};
  int speedIndex = 0;
  time_t control_time;
  int temp_time = 0;
  bool set_lock = false;
  while(!flag) {   //while start

    control_time = time(NULL);
    if (control_time == temp_time) {
      set_lock = true;
    }
    else {
      set_lock = false;
    }
    temp_time = control_time; 
    usleep(speedArr[speedIndex]*1000);
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
          if ((b1.boardList[anotherX][(anotherY-1)*2]==1)||(b1.boardList[anotherX][(anotherY-1)*2]==2)){ //when blocked by wall
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
          if ((b1.boardList[anotherX][(anotherY+1)*2]==1)||(b1.boardList[anotherX][(anotherY+1)*2]==2)){ //when blocked by wall
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
          if ((b1.boardList[anotherX + 1][(anotherY)*2]==1)||(b1.boardList[anotherX + 1][(anotherY)*2]==2)){ //when blocked by wall
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
          if ((b1.boardList[anotherX-1][(anotherY)*2]==1)||(b1.boardList[anotherX-1][(anotherY)*2]==2)){ //when blocked by wall
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
    if (((control_time - start_time) % 5 == 0)) {   //set item
      if (!set_lock) {
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
    }

    if (intogate !=0){ //if snake is going through a gate 
      intogate--;
      if (intogate == 0){
        gate_cnt++;
      }
    }

    if (((control_time - start_time) % 15 == 0)&&(!intogate)&&(control_time-start_time>=20)) {   //set gate
      if (!set_lock) {
        for (int i=1; i<31; i++) {
        for (int j=1; j<31; j++) {
          if (b1.boardList[i][j*2] == 7) b1.boardList[i][j*2] = 1;
          }
        }
        b1.setGate();
      }
    }
    if (flag_special) {
      if (((control_time - start_time) % 3 == 0)) {   //set item
        if (!set_lock && snake1.size()>=9) {
          for (int i=2; i<30; i++) {
          for (int j=2; j<30; j++) {
            if (b1.itemList[i][j*2] == 8) {
              b1.itemList[i][j*2] = 0;
              b1.boardList[i][j*2] = 0;
            }
            }
          }
          b1.setSpecial();
        }
      }
    }

    

    snake1.push_front(Snake(headX,headY));  //new head (moving forward)
    
    if (b1.itemList[headX][headY*2] == 8){
      success = true;
      flag =true;
    }
    
    if (b1.itemList[headX][headY*2] == 6) { //eating poison item
      poison_cnt++;
      b1.itemList[headX][headY*2] = 0;
      b1.boardList[(snake1.back()).getX()][(snake1.back()).getY()*2] = 0; //erase last tail*2
      snake1.pop_back();
      b1.boardList[(snake1.back()).getX()][(snake1.back()).getY()*2] = 0; 
      snake1.pop_back();
    }
    else if (b1.itemList[headX][headY*2] == 5) { //eating growth item
      growth_cnt++;
      b1.itemList[headX][headY*2] = 0;
    }
    else{  //default moving
      b1.boardList[(snake1.back()).getX()][(snake1.back()).getY()*2] = 0; //erase last tail
      snake1.pop_back();
    }

    
    if (snake1.size() == 2){ //when snake size < 3 
      flag = true;
    }
    if (snake1.size() == 5 && changeBoard_1) {   //change stage
      b1.changeBoard(b1.stage_1);
      changeBoard_1 = false;
      speedIndex = 1;
      gate_cnt = 0;
      growth_cnt=0;
      poison_cnt=0;
      int tempSize_1 = snake1.size();
      for (int i=0; i<tempSize_1; i++) {
        snake1.pop_back();
      }
      for (int i=0; i<tempSize_1; i++) {
        snake1.push_back(Snake(15,15+i));
      }
      dir = 1;
      while(!start_time % 5 == 0) {
        start_time++;
        if (start_time % 5 == 0) {
          break;
        }
      }
    }
    
    if (snake1.size() >= 7 && gate_cnt>=1 && changeBoard_2 && poison_cnt>=1 && growth_cnt>=3) {
      b1.changeBoard(b1.stage_2);
      changeBoard_2 = false;
      speedIndex = 2;
      gate_cnt = 0;
      growth_cnt=0;
      poison_cnt=0;
      int tempSize_2 = snake1.size();
      for (int i=0; i<tempSize_2; i++) {
        snake1.pop_back();
      }
      for (int i=0; i<tempSize_2; i++) {
        snake1.push_back(Snake(19,14+i));
      }
      dir = 1;
      while(!start_time % 5 == 0) {
        start_time++;
        if (start_time % 5 == 0) {
          break;
        }
      }
    }
    if (snake1.size() >= 9 && gate_cnt>=2 && changeBoard_3 && poison_cnt>=2 && growth_cnt>=4) {
      b1.changeBoard(b1.stage_3);
      changeBoard_3 = false;
      flag_special = true;
      speedIndex = 3;
      gate_cnt = 0;
      growth_cnt=0;
      poison_cnt=0;
      int tempSize_3 = snake1.size();
      for (int i=0; i<tempSize_3; i++) {
        snake1.pop_back();
      }
      for (int i=0; i<tempSize_3; i++) {
        snake1.push_back(Snake(22,12+i));
      }
      dir = 1;
      while(!start_time % 5 == 0) {
        start_time++;
        if (start_time % 5 == 0) {
          break;
        }
      }
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
    //play board
    if(!changeBoard_3){
      attron(COLOR_PAIR(21));
      mvprintw(3,68,"*******LAST STAGE*******");
      mvprintw(6,69,"   **YOUR MISSION**   ");
      attroff(COLOR_PAIR(21));
      attron(COLOR_PAIR(29));
      mvprintw(8,70,"-EAT SPECIAL ITEM ");
      attroff(COLOR_PAIR(29));
    }
    else if (!changeBoard_2){
      attron(COLOR_PAIR(21));
      mvprintw(3,68,"*******3rd  STAGE*******");
      mvprintw(4,69,"   **YOUR MISSION**   ");
      attroff(COLOR_PAIR(21));
      attron(COLOR_PAIR(22));
      mvprintw(6,70,"-Snake length > 8     ");
      if (snake1.size()>8) mvprintw(6,90,"o");
      attroff(COLOR_PAIR(22));
      attron(COLOR_PAIR(26));
      mvprintw(7,70,"-Eat 4 Growth items   ");
      if (growth_cnt>=4) mvprintw(7,90,"o");
      attroff(COLOR_PAIR(26));
      attron(COLOR_PAIR(27));
      mvprintw(8,70,"-Eat 2 Poison item   ");
      if (poison_cnt>=2) mvprintw(8,90,"o");
      attroff(COLOR_PAIR(27));
      attron(COLOR_PAIR(23));
      mvprintw(9,70,"-Passing gate 2 times ");
      if (gate_cnt>=2) mvprintw(9,90,"o");
      attroff(COLOR_PAIR(23));
    }
    else if(!changeBoard_1){
      attron(COLOR_PAIR(21));
      mvprintw(3,68,"*******2nd  STAGE*******");
      mvprintw(4,69,"   **YOUR MISSION**   ");
      attroff(COLOR_PAIR(21));
      attron(COLOR_PAIR(22));
      mvprintw(6,70,"-Snake length > 6     ");
      if (snake1.size()>6) mvprintw(6,90,"o");
      attroff(COLOR_PAIR(22));
      attron(COLOR_PAIR(26));
      mvprintw(7,70,"-Eat 3 Growth items   ");
      if (growth_cnt>=3) mvprintw(7,90,"o");
      attroff(COLOR_PAIR(26));
      attron(COLOR_PAIR(27));
      mvprintw(8,70,"-Eat 1 Poison item   ");
      if (poison_cnt>=1) mvprintw(8,90,"o");
      attroff(COLOR_PAIR(27));
      attron(COLOR_PAIR(23));
      mvprintw(9,70,"-Passing gate 1 time  ");
      if (gate_cnt>=1) mvprintw(9,90,"o");
      attroff(COLOR_PAIR(23));
    }
    else {
      attron(COLOR_PAIR(21));
      mvprintw(3,68,"*******1st  STAGE*******");
      mvprintw(4,69,"   **YOUR MISSION**   ");
      attroff(COLOR_PAIR(21));
      attron(COLOR_PAIR(22));
      mvprintw(6,70,"-Snake length : 5     ");
      if (snake1.size()>=5) mvprintw(6,90,"o");
      attroff(COLOR_PAIR(22));
    }
    attron(COLOR_PAIR(24));
    mvprintw(13,70," Current length: %d   ", snake1.size());
    mvprintw(14,70," Growth item: %d   ", growth_cnt);
    mvprintw(15,70," Poison item: %d   ", poison_cnt);
    attroff(COLOR_PAIR(24));
    attron(COLOR_PAIR(25));
    mvprintw(16,70," Passed gate   : %d   ", gate_cnt);
    attroff(COLOR_PAIR(25));
    b1.printPlay();
    refresh();
  }  //while end
  clear();
  attron(COLOR_PAIR(21));
  if (success){
    mvprintw(10,20,"*******CONGRATULATIAON*******");
    mvprintw(13,20,"        **YOU WIN!!!**   ");
  }
  else {
    mvprintw(10,20,"*******   YOU FAILED  *******");
    mvprintw(13,20,"        **TRY AGAIN**   ");
  }
  
  attroff(COLOR_PAIR(21));
  refresh();
  sleep(3);
  endwin();
  return 0;
  }

