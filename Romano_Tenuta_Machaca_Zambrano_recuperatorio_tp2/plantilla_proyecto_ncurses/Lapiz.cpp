#include "Lapiz.h"

Lapiz::Lapiz(int x, int y)
{
  m_x = x;
  m_y = y;
  flashFrames = 3; 
}

void Lapiz::update()
{
  if (m_y >= 1) m_y--;
  if (flashFrames > 0) flashFrames--;
}

void Lapiz::draw()
{
  attron(COLOR_PAIR(4)); // amarillo

  if (flashFrames > 0) {
    
    mvaddch(m_y, m_x, '*');
  } else {
    
    if (m_y > 0) mvaddch(m_y, m_x, '^');
    if (m_y > 1) mvaddch(m_y - 1, m_x, '^');
    if (m_y > 2) mvaddch(m_y - 2, m_x, '^');
  }

  attroff(COLOR_PAIR(4));
}