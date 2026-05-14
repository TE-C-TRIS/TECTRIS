#ifndef GAME_H
#define GAME_H

#include "common.h"

typedef struct {
    Color board[BOARD_HEIGHT][BOARD_WIDTH];
    Tetromino currentPiece;
    Tetromino nextPiece;
    int score;
    int lines;
    int level;
    int killLineY; // Linha limite (índice de 0 a BOARD_HEIGHT)
    bool gameOver;
    float dropTimer;
    float dropInterval;
    GameState state;
    ScreenConfig screen;
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

#endif
