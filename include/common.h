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
    STATE_GAME_EASY,      // NOVO: Jogo no modo fácil
    STATE_PAUSE,
    STATE_QUESTION,
    STATE_QUESTION_EASY, // NOVO: Tela de pergunta de curiosidades
    STATE_HISTORY,
    STATE_HISTORY_EASY, // NOVO: Histórico do modo fácil
    STATE_REPORT,
    STATE_GAMEOVER,

    // ===== Multiplayer / Ranking geral =====
    STATE_NAME_ENTRY,        // Tela de digitar nome (modos single-player, antes de jogar)
    STATE_MULTI_NAME_ENTRY,  // Tela de digitar os dois nomes (multiplayer)
    STATE_MULTI_GAME,        // Partida multiplayer local (2 tabuleiros simultâneos)
    STATE_MULTI_QUESTION,    // Pergunta no multiplayer (entrada alternada por jogador)
    STATE_MULTI_GAMEOVER,    // Fim da partida multiplayer (mostra vencedor)
    STATE_RANKING            // Pódio + ranking geral (todos os modos)
} GameState;

// Cores dos jogadores no modo multiplayer
#define COLOR_P1 (Color){ 0, 245, 255, 255 }    // Ciano (mesmo tom do COLOR_TEXT)
#define COLOR_P2 (Color){ 255, 140, 0, 255 }    // Laranja vibrante (alto contraste com P1)
#define COLOR_GOLD   (Color){ 255, 215, 70, 255 }
#define COLOR_SILVER (Color){ 200, 207, 224, 255 }
#define COLOR_BRONZE (Color){ 222, 142, 80, 255 }

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

// Estrutura de Pergunta do Modo Easy
typedef struct {
    char pergunta[256];
    char alternativas[4][100];
    int alternativaCorreta;
} PerguntaEasy;

// Histórico de Partidas
#define HISTORY_FILE "history.txt"
#define HISTORY_EASY_FILE "history_easy.txt" // novo
#define MAX_HISTORY_RECORDS 100

// ===================================================================
// Efeitos visuais (popups flutuantes de pontuação + flash de acerto/erro)
// ===================================================================
#define MAX_POPUPS 12

typedef struct {
    char text[24];
    float life;     // tempo restante (segundos)
    float maxLife;  // duração total, usada para calcular o fade e o deslocamento
    Color color;
    bool active;
} Popup;

typedef struct {
    Popup items[MAX_POPUPS];
} PopupSystem;

typedef struct {
    Color color;
    float timer;   // > 0 enquanto o flash estiver visível
    float maxTimer;
} FlashEffect;

// ===================================================================
// Estado de UI da pergunta no modo multiplayer (entrada alternada)
// ===================================================================
typedef enum {
    TURN_NONE = 0,
    TURN_P1,
    TURN_P2
} AnswerTurn;

typedef struct {
    Question question;
    AnswerTurn activeTurn;     // quem está com a caixa de resposta aberta agora
    bool p1Done, p2Done;       // já responderam (ou levaram timeout)
    bool p1Correct, p2Correct;
    char p1Input[64];
    char p2Input[64];
    int p1Letters, p2Letters;
    float questionTimer;
    float questionTimeMax;
    bool showFeedback;
    float feedbackTimer;
} MultiQuestionState;

#endif