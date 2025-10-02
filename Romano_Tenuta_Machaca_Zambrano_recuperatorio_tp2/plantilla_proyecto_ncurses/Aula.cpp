#include "Aula.h"

Aula::Aula() {
    x = 10;
    y = 20;
}

void Aula::mover(int dx) {
    x += dx;
}

void Aula::dibujar() {
    attron(COLOR_PAIR(1));
    mvprintw(y,     x + 2, "A  ");
    mvprintw(y + 1, x + 1, "/|\\ ");
    mvprintw(y + 2, x,     "/ | \\");
    mvprintw(y + 3, x,     "I___I");
    attroff(COLOR_PAIR(1));
}

int Aula::getX() {
    return x;
}

void Aula::setX(int newX) {
    x = newX;
}

int Aula::getY() {       
    return y;
}

void Aula::setY(int newY) {  
    y = newY;
}