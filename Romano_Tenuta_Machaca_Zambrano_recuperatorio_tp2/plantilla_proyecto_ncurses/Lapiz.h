#pragma once
#include <ncurses.h>

class Lapiz
{
public:
  Lapiz(int x, int y);

  void update();
  void draw();

  int getX() { return m_x; }
  int getY() { return m_y; }

private:
  int m_x, m_y;
  int flashFrames; 
};