#include "Burbuja.h"

Burbuja::Burbuja(int x, int y, const std::string& texto)
    : x(x), y(y), texto(texto) {}

void Burbuja::dibujar(int color_pair) {
    attron(COLOR_PAIR(color_pair)); // attron
    mvprintw(y,     x, "  _______ ");
    mvprintw(y + 1, x, " /       \\");
    mvprintw(y + 2, x, "|  %-5s  |", texto.c_str());
    mvprintw(y + 3, x, " \\_______/");
    attroff(COLOR_PAIR(color_pair)); // attroff 
}

int Burbuja::getX() { return x; }
int Burbuja::getY() { return y; }
std::string Burbuja::getTexto() { return texto; }

// NUEVOS MÉTODOS
int Burbuja::getWidth() {
    int base = 9; // ------> ancho mínimo del marco
    int textWidth = texto.size() + 6; // --------> margen dentro del marco
    return (textWidth > base) ? textWidth : base;
}

int Burbuja::getHeight() {
    return 4; // siempre 4 líneas
}