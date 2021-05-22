#include "snake.h"

int main(int argc, char *argv[]) {
  initscr();
  start_color();
  init_pair(100,COLOR_WHITE,COLOR_WHITE);
  attron(COLOR_PAIR(100));
  wbkgd(stdscr, COLOR_PAIR(100));
  board b1;
  WINDOW *win = newwin(21,21,0,0);
  b1.printboard();
  refresh();
  getch();
  endwin();
  return 0;
}
