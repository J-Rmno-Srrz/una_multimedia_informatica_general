#pragma once
#include <ncurses.h>

class Aula {
public:
    Aula();
    void mover(int dx);
    void dibujar();
    int getX();
    void setX(int x);
    int getY();          
    void setY(int y);    

private:
    int x, y;
};