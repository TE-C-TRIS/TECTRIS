#ifndef COMMON_H
#define COMMON_H

#include "raylib.h"
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

// Configurações do Grid
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

// Cores e Estética
#define COLOR_BG (Color){ 10, 10, 15, 255 }
#define COLOR_PANEL (Color){ 26, 26, 46, 255 }
#define COLOR_BORDER (Color){ 0, 255, 65, 255 }
#define COLOR_TEXT (Color){ 0, 245, 255, 255 }
#define COLOR_KILLLINE (Color){ 255, 0, 85, 255 }

// Estados do Jogo
typedef enum {
    STATE_MENU,
    STATE_GAME,
    STATE_PAUSE,
    STATE_QUESTION,
    STATE_HISTORY,
    STATE_REPORT,
    STATE_GAMEOVER
} GameState;

// Estrutura de Posição
typedef struct {
    int x;
    int y;
} Pos;

// Estrutura de Histórico de Partida
typedef struct {
    int score;
    int lines;
    int level;
    time_t timestamp;
} MatchHistory;

// Estrutura de Tetromino
typedef struct {
    int shape[4][4];
    int size;
    Color color;
    Pos pos;
} Tetromino;

// Estrutura de Pergunta
typedef struct {
    char question[256];
    char* answers[5]; // Múltiplas respostas válidas
    int answerCount;
    int level;
} Question;

// Estrutura de Configuração de Tela (Responsividade)
typedef struct {
    int screenWidth;
    int screenHeight;
    float scale;
    Vector2 offset;
    int cellSize;
} ScreenConfig;

// Histórico de Partidas
#define HISTORY_FILE "history.txt"
#define MAX_HISTORY_RECORDS 100

#endif