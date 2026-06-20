#ifndef GAME_H
#define GAME_H

#include "common.h"
#include "ranking.h"

#define MAX_HISTORY_RECORDS 100

typedef struct {
    Color board[BOARD_HEIGHT][BOARD_WIDTH];
    Tetromino currentPiece;
    Tetromino nextPiece;
    int score;
    int lines;
    int level;
    int killLineY;
    bool gameOver;
    float dropTimer;
    float dropInterval;
    GameState state;
    ScreenConfig screen;
    char playerName[24];

    MatchHistory history[MAX_HISTORY_RECORDS];
    int historyCount;
} GameContext;

// Inicialização e Loop
void InitGame(GameContext *ctx);
void UpdateGame(GameContext *ctx, float deltaTime);
void HandleInput(GameContext *ctx);

// Lógica de Tetris
bool CheckCollision(GameContext *ctx, Tetromino piece, int offsetX, int offsetY);
void RotatePiece(Tetromino *piece);
bool TryRotate(GameContext *ctx);
void MergePiece(GameContext *ctx);
void ClearLines(GameContext *ctx);
void SpawnPiece(GameContext *ctx);
void AddPenaltyLine(GameContext *ctx);
void RemovePenaltyLine(GameContext *ctx);
bool CheckKillLineViolation(GameContext *ctx);

// Perguntas
Question GetRandomQuestion(int level);
bool ValidateAnswer(const char* user, const Question* q);

// Renderização
void DrawGame(GameContext *ctx, int menuIndex);
void UpdateScreenConfig(GameContext *ctx);

// ===== Efeitos visuais (popups + flash de acerto/erro) =====
void InitPopupSystem(PopupSystem *ps);
void AddPopup(PopupSystem *ps, const char *text, Color color);
void UpdatePopups(PopupSystem *ps, float dt);
void DrawPopups(PopupSystem *ps, float anchorX, float anchorY);

void TriggerFlash(FlashEffect *fx, Color color, float duration);
void UpdateFlash(FlashEffect *fx, float dt);
void DrawFlashOverlay(FlashEffect *fx, Rectangle area);

// ===== Multiplayer =====
void DrawMultiplayerGame(GameContext *p1, GameContext *p2,
                          FlashEffect *flashP1, FlashEffect *flashP2,
                          PopupSystem *popsP1, PopupSystem *popsP2,
                          float nextQuestionIn);

void DrawMultiQuestionOverlay(MultiQuestionState *mq, GameContext *p1, GameContext *p2);

void DrawNameEntryScreen(const char *title, const char *input, bool isEasy);
void DrawMultiNameEntryScreen(const char *p1Name, const char *p2Name, int activeStep);
void DrawMultiGameOverScreen(GameContext *p1, GameContext *p2, bool p1Won);

// ===== Ranking geral =====
void DrawRankingScreen(RankingEntry *entries, int count);

#endif