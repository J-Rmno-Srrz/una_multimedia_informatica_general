#pragma once
#include <string>
#include <ncurses.h>

class Burbuja {
public:
    Burbuja(int x, int y, const std::string& texto);
    void dibujar(int color_pair);
    int getX();
    int getY();
    std::string getTexto();

// NUEVO: AGREGADOS PARA CONTROLAR EL AREA DE BURBUJA
    int getWidth();   // NUEVO
    int getHeight();  // NUEVO

private:
    int x, y;
    std::string texto;
};