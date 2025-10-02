// Romano Serrizuela Julieta
// Tenuta Guerrero Felipe
// Machaca Celeste
// Zambrano Juan

//=========================================================================
// VERSION CORREGIDA
//=========================================================================
#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Aula.h"
#include "Burbuja.h"
#include "Lapiz.h" 

using namespace std;


//=========================================================
// ENUM
//=========================================================
enum class GameState { MENU, PLAYING, END, EXIT };

// MENÚ PRINCIPAL
void mostrarMenu() {
    clear();
    mvprintw(2, (COLS - 61) / 2, "+==========================================================+");
    mvprintw(3, (COLS - 61) / 2, "|eeeee  e   e eeeee  eeeee  e   e    e  eeeee              |");
    mvprintw(4, (COLS - 61) / 2, "|8   8  8   8 8   8  8   8  8   8    8  8   8              |");
    mvprintw(5, (COLS - 61) / 2, "|8eee8e 8e  8 8eee8e 8eee8e 8e  8    8e 8eee8              |");
    mvprintw(6, (COLS - 61) / 2, "|88   8 88  8 88   8 88   8 88  8 e  88 88  8              |");
    mvprintw(7, (COLS - 61) / 2, "|88eee8 88ee8 88   8 88eee8 88ee8 8ee88 88  8              |");
    mvprintw(8, (COLS - 61) / 2, "|eeeeeee eeeee eeeee eeee eeeeeee eeeee eeeee e  eeee eeeee|");
    mvprintw(9, (COLS - 61) / 2, "|8  8  8 8   8   8   8    8  8  8 8   8   8   8  8  8 8   8|");
    mvprintw(10, (COLS - 61) / 2, "|8e 8  8 8eee8   8e  8eee 8e 8  8 8eee8   8e  8e 8e   8eee8|");
    mvprintw(11, (COLS - 61) / 2, "|88 8  8 88  8   88  88   88 8  8 88  8   88  88 88   88  8|");
    mvprintw(12, (COLS - 61) / 2, "|88 8  8 88  8   88  88ee 88 8  8 88  8   88  88 88e8 88  8|");
    mvprintw(13, (COLS - 61) / 2, "+==========================================================+");

    mvprintw(16, (COLS - 12) / 2, "1. Iniciar juego");
    mvprintw(17, (COLS - 12) / 2, "2. Instrucciones"); // NUEVO, acerca de la jugabilidad.
    mvprintw(18, (COLS - 12) / 2, "3. Salir");
    mvprintw(19, (COLS - 12) / 2, "4. Participantes");
    refresh();
}

//=========================================================
//MENÚ -> INSTRUCCIONES / JUGABILIDAD
//=========================================================
void mostrarInstrucciones() {
    clear();
    mvprintw(2, (COLS - 28) / 2, "=== INSTRUCCIONES DEL JUEGO ===");

    int y = 4; 
    int x = 2;

    mvprintw(y++, x, "El juego consta de 10 preguntas matematicas.");
    mvprintw(y++, x, "Para responder la pregunta utilice las flechas izquierda y derecha para moverse.");
    mvprintw(y++, x, "Alguna de las burbujas que aparece en pantalla contiene la respuesta correcta.");
    mvprintw(y++, x, "Una vez posicionado debajo de la burbuja, mantenga presionado ESPACIO para marcar la correcta.");
    mvprintw(y++, x, "Otra opcion para seleccionar la respuesta correcta es usando las teclas 1, 2 o 3");
    mvprintw(y++, x, "(segun el orden de las burbujas de izquierda a derecha).");
    mvprintw(y++, x, "El juego termina cuando se acaben las 3 vidas o conteste todas las preguntas.");
    mvprintw(y++, x, "Tambien puede salir del juego antes, presionando la tecla Q.");
    mvprintw(y + 1, x, "Presione cualquier tecla para volver al menu.");

    refresh();
    getch();
}

//=========================================================
// MENÚ -> INTEGRANTES DEL GRUPO
//=========================================================
void mostrarCreditos() {
    clear();
    mvprintw(3, (COLS - 20) / 2, "=== INTEGRANTES DEL GRUPO ===");
    mvprintw(6, (COLS - 30) / 2, "Participantes:");
    mvprintw(7, (COLS - 30) / 2, "- Felipe Tenuta Guerrero");
    mvprintw(8, (COLS - 30) / 2, "- Julieta Romano Serrizuela");
    mvprintw(9, (COLS - 30) / 2, "- Celeste Aquino");
    mvprintw(10, (COLS - 30) / 2, "- Juan Zambrano");
    mvprintw(14, (COLS - 40) / 2, "Presiona cualquier tecla para volver.");
    refresh();
    getch();
}

// GENERADOR DE PREGUNTA
struct Pregunta {
    std::string texto;
    std::vector<std::string> opciones;
    int respuesta_correcta;
};

Pregunta generarPregunta(int ronda) {
    Pregunta p;
    int max_val = 10 + ronda * 5; 
    int a = rand() % max_val + 1;
    int b = rand() % max_val + 1;

    int op = rand() % 4; 
    int correcta = 0;
    switch (op) {
        case 0: p.texto = "¿Cuanto es " + std::to_string(a) + " + " + std::to_string(b) + "?"; correcta = a + b; break;
        case 1: if (a < b) std::swap(a, b);
                p.texto = "¿Cuanto es " + std::to_string(a) + " - " + std::to_string(b) + "?"; correcta = a - b; break;
        case 2: p.texto = "¿Cuanto es " + std::to_string(a) + " * " + std::to_string(b) + "?"; correcta = a * b; break;
        case 3: b = (b == 0) ? 1 : b;
                correcta = a - a % b;
                p.texto = "¿Cuanto es " + std::to_string(correcta) + " / " + std::to_string(b) + "?";
                correcta = correcta / b;
                break;
    }

    p.respuesta_correcta = rand() % 3;
    p.opciones.resize(3);

    for (int i = 0; i < 3; ++i) {
        if (i == p.respuesta_correcta)
            p.opciones[i] = std::to_string(correcta);
        else
            p.opciones[i] = std::to_string(correcta + (i + 1));
    }
    return p;
}

// MARCO DEL JUEGO
void dibujarMarcoJuego(int gameX, int gameY, int gameW, int gameH) {
    attron(COLOR_PAIR(2)); 
    for (int i = 0; i < gameW; i++) {
        mvaddch(gameY, gameX + i, '=');
        mvaddch(gameY + gameH, gameX + i, '=');
    }
    for (int i = 0; i < gameH; i++) {
        mvaddch(gameY + i, gameX, '|');
        mvaddch(gameY + i, gameX + gameW, '|');
    }
    mvaddch(gameY, gameX, '#');
    mvaddch(gameY, gameX + gameW, '#');
    mvaddch(gameY + gameH, gameX, '#');
    mvaddch(gameY + gameH, gameX + gameW, '#');
    attroff(COLOR_PAIR(2));
}

//=========================================================================
// MAIN
//=========================================================================
int main() {
    srand(time(0));
    initscr();
    cbreak();               
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    use_default_colors();   

    //=========================================================
    // Validación terminal 120x40
    //=========================================================
    if (COLS != 120 || LINES != 40) {
        endwin();
        printf("La terminal debe tener exactamente 120 columnas y 40 filas.\n");
        return 1;
    }

    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);

    GameState state = GameState::MENU;

    int ronda = 1;
    int puntaje = 0;
    int vidas = 3;

    //=====================================================
    //  PARA EL MENÚ
    //=====================================================

    while (state != GameState::EXIT) {
        switch(state) {
            case GameState::MENU: {
                mostrarMenu();
                int opcion = getch();
                if (opcion == '1') {
                    ronda = 1; puntaje = 0; vidas = 3;
                    state = GameState::PLAYING;
                } else if (opcion == '2') {
                    mostrarInstrucciones();
                } else if (opcion == '3') {
                    state = GameState::EXIT;
                } else if (opcion == '4') {
                    mostrarCreditos();
                }
                break;
            }

            

            //============================================================================
            // NUEVO gameState::PLAYING
            //============================================================================

            case GameState::PLAYING: {
                int gameX = 2, gameY = 2, gameW = COLS - 4, gameH = LINES - 6;
                Aula jugador; 
                jugador.setX(gameX + gameW / 2 - 4);
                jugador.setY(gameY + gameH - 4);
                Lapiz lapiz(0, 0);
                bool lapiz_activo = false;

                int numBurbujas = 3;
                std::vector<int> posicionesX;
                for (int i = 1; i <= numBurbujas; ++i)
                    posicionesX.push_back(gameX + i * gameW / (numBurbujas + 1));

                Pregunta pregunta = generarPregunta(ronda);
                std::vector<Burbuja> burbujas;
                for (int i = 0; i < numBurbujas; ++i)
                    burbujas.emplace_back(posicionesX[i], gameY + 3, pregunta.opciones[i]);

                bool juego_terminado = false;

                while (!juego_terminado) {
                    clear();

                    // Dibujar marco y HUD
                    dibujarMarcoJuego(gameX, gameY, gameW, gameH);
                    mvprintw(gameY - 2, gameX, "Pregunta %d: %s", ronda, pregunta.texto.c_str());
                    mvprintw(gameY + gameH + 1, gameX, "Vidas: %d | Puntaje: %d", vidas, puntaje);

                    // Dibujar burbujas
                    for (auto &b : burbujas) b.dibujar(1);

                    // Dibujar jugador
                    jugador.dibujar();

                    // Leer input
                    int input = getch();
                    switch(input) {
                        case KEY_LEFT: 
                            if (jugador.getX() > gameX + 1) jugador.mover(-1); 
                            break;
                        case KEY_RIGHT: 
                            if (jugador.getX() < gameX + gameW - 6) jugador.mover(1); 
                            break;
                        case ' ': 
                            if (!lapiz_activo) {
                                lapiz = Lapiz(jugador.getX() + 2, jugador.getY() - 1);
                                lapiz_activo = true;
                            }
                            break;

                        case '1': case '2': case '3': {
                            int idx = input - '1';
                            if (idx == pregunta.respuesta_correcta) puntaje++;
                            else vidas--;

                            ronda++;
                            juego_terminado = (vidas <= 0 || ronda > 10);

                            if (!juego_terminado) {
                                // Generar nueva pregunta
                                pregunta = generarPregunta(ronda);
                                burbujas.clear();
                                for (int i = 0; i < numBurbujas; ++i)
                                    burbujas.emplace_back(posicionesX[i], gameY + 3, pregunta.opciones[i]);
                                lapiz_activo = false;
                            }
                            break;
                        }

                        case 'q': case 'Q':
                            juego_terminado = true;
                            break;
                    }

                    // Lógica del Lapiz
                    if (lapiz_activo) {
                        lapiz.update();
                        lapiz.draw();

                        for (int i = 0; i < numBurbujas; ++i) {
                            if (lapiz.getX() >= burbujas[i].getX() &&
                                lapiz.getX() <= burbujas[i].getX() + burbujas[i].getWidth() &&
                                lapiz.getY() >= burbujas[i].getY() &&
                                lapiz.getY() <= burbujas[i].getY() + burbujas[i].getHeight()) {
                                
                                if (i == pregunta.respuesta_correcta) puntaje++;
                                else vidas--;

                                ronda++;
                                juego_terminado = (vidas <= 0 || ronda > 10);

                                if (!juego_terminado) {
                                    // Generar nueva pregunta
                                    pregunta = generarPregunta(ronda);
                                    burbujas.clear();
                                    for (int j = 0; j < numBurbujas; ++j)
                                        burbujas.emplace_back(posicionesX[j], gameY + 3, pregunta.opciones[j]);
                                }

                                lapiz_activo = false;
                                break;
                            }
                        }
                    }

                    refresh();
                    napms(50); // pequeño delay para animación
                }

                state = GameState::END;
                break;
            }

            //===============================================================
            // hasta aca.
            //===============================================================

            case GameState::END: {
                clear();
                mvprintw(8, 10, "Juego terminado!");
                mvprintw(9, 10, "Puntaje final: %d", puntaje);
                mvprintw(11, 10, "Presiona M para volver al menú o Q para salir.");
                refresh();
                bool elegido = false;
                while (!elegido) {
                    int c = getch();
                    if (c == 'q' || c == 'Q') { state = GameState::EXIT; elegido = true; }
                    else if (c == 'm' || c == 'M') { state = GameState::MENU; elegido = true; }
                }
                break;
            }
        }
    }

    endwin();
    return 0;
}