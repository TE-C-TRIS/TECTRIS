#include "game.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

static const int TETROMINO_SHAPES[7][4][4] = {
    {{0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0}}, // I
    {{1,1,0,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}}, // O
    {{0,1,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}, // T
    {{0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}}, // S
    {{1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}}, // Z
    {{1,0,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}, // J
    {{0,0,1,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}  // L
};

static const Color TETROMINO_COLORS[7] = {
    {0, 245, 255, 255},  // Cyan
    {255, 255, 0, 255},  // Yellow
    {255, 0, 255, 255},  // Magenta
    {0, 255, 65, 255},   // Green
    {255, 0, 0, 255},    // Red
    {0, 0, 255, 255},    // Blue
    {255, 165, 0, 255}   // Orange
};

static Tetromino CreateRandomPiece() {
    int type = rand() % 7;
    Tetromino p;
    memcpy(p.shape, TETROMINO_SHAPES[type], sizeof(p.shape));
    p.color = TETROMINO_COLORS[type];
    p.size = (type == 0) ? 4 : (type == 1 ? 2 : 3);
    p.pos.x = BOARD_WIDTH / 2 - p.size / 2;
    p.pos.y = 0;
    return p;
}

void InitGame(GameContext *ctx) {
    memset(ctx->board, 0, sizeof(ctx->board));
    ctx->score = 0;
    ctx->lines = 0;
    ctx->level = 1;
    ctx->killLineY = 4; // Linha limite superior (índice 4)
    ctx->gameOver = false;
    ctx->dropTimer = 0;
    ctx->dropInterval = 1.0f;
    ctx->state = STATE_MENU;
    
    srand(time(NULL));
    ctx->currentPiece = CreateRandomPiece();
    ctx->nextPiece = CreateRandomPiece();
    UpdateScreenConfig(ctx);
}

bool CheckCollision(GameContext *ctx, Tetromino piece, int offsetX, int offsetY) {
    for (int y = 0; y < piece.size; y++) {
        for (int x = 0; x < piece.size; x++) {
            if (piece.shape[y][x]) {
                int newX = piece.pos.x + x + offsetX;
                int newY = piece.pos.y + y + offsetY;
                
                if (newX < 0 || newX >= BOARD_WIDTH || newY >= BOARD_HEIGHT) return true;
                if (newY >= 0 && ctx->board[newY][newX].a != 0) return true;
            }
        }
    }
    return false;
}

void RotatePiece(Tetromino *piece) {
    int temp[4][4] = {0};
    for (int y = 0; y < piece->size; y++) {
        for (int x = 0; x < piece->size; x++) {
            temp[x][piece->size - 1 - y] = piece->shape[y][x];
        }
    }
    memcpy(piece->shape, temp, sizeof(temp));
}

bool TryRotate(GameContext *ctx) {
    Tetromino rotated = ctx->currentPiece;
    RotatePiece(&rotated);
    
    int kicks[] = {0, -1, 1, -2, 2};
    for (int i = 0; i < 5; i++) {
        if (!CheckCollision(ctx, rotated, kicks[i], 0)) {
            rotated.pos.x += kicks[i];
            ctx->currentPiece = rotated;
            return true;
        }
    }
    return false;
}

bool CheckKillLineViolation(GameContext *ctx) {
    // Verifica se há qualquer bloco fixo na região da Kill Line ou acima dela
    for (int y = 0; y < ctx->killLineY; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (ctx->board[y][x].a != 0) return true;
        }
    }
    return false;
}

void MergePiece(GameContext *ctx) {
    for (int y = 0; y < ctx->currentPiece.size; y++) {
        for (int x = 0; x < ctx->currentPiece.size; x++) {
            if (ctx->currentPiece.shape[y][x]) {
                int boardX = ctx->currentPiece.pos.x + x;
                int boardY = ctx->currentPiece.pos.y + y;
                if (boardY >= 0 && boardY < BOARD_HEIGHT) {
                    ctx->board[boardY][boardX] = ctx->currentPiece.color;
                }
            }
        }
    }
    
    // ATIVAÇÃO REAL DO GAME OVER NA KILL LINE
    if (CheckKillLineViolation(ctx)) {
        ctx->gameOver = true;
        ctx->state = STATE_GAMEOVER;
        return;
    }
    
    ClearLines(ctx);
    SpawnPiece(ctx);
}

void ClearLines(GameContext *ctx)
{
    int linesCleared = 0;

    for (int y = BOARD_HEIGHT - 1; y >= 0; y--)
    {
        bool full = true;
        bool isPenaltyLine = false; // Identifica linha de penalidade

        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            // Verifica se existe alguma célula vazia
            if (ctx->board[y][x].a == 0)
            {
                full = false;
            }

            // Verifica se é um bloco de penalidade (cinza)
            if (ctx->board[y][x].r == 100 &&
                ctx->board[y][x].g == 100 &&
                ctx->board[y][x].b == 100 &&
                ctx->board[y][x].a == 255)
            {
                isPenaltyLine = true;
            }
        }

        // Remove apenas linhas cheias que NÃO sejam penalidades
        if (full && !isPenaltyLine)
        {
            linesCleared++;

            for (int yy = y; yy > 0; yy--)
            {
                memcpy(
                    ctx->board[yy],
                    ctx->board[yy - 1],
                    sizeof(ctx->board[yy])
                );
            }

            memset(ctx->board[0], 0, sizeof(ctx->board[0]));

            y++; // Reavalia a linha após deslocamento
        }
    }

    if (linesCleared > 0)
    {
        int points[] = {0, 100, 300, 500, 800};

        ctx->score += points[linesCleared] * ctx->level;
        ctx->lines += linesCleared;
        ctx->level = 1 + (ctx->lines / 10);

        ctx->dropInterval =
            1.0f * powf(0.85f, (float)(ctx->level - 1));
    }
}

void SpawnPiece(GameContext *ctx) {
    ctx->currentPiece = ctx->nextPiece;
    ctx->nextPiece = CreateRandomPiece();
    if (CheckCollision(ctx, ctx->currentPiece, 0, 0)) {
        ctx->gameOver = true;
        ctx->state = STATE_GAMEOVER;
    }
}

void AddPenaltyLine(GameContext *ctx) {
    for (int y = 0; y < BOARD_HEIGHT - 1; y++) {
        memcpy(ctx->board[y], ctx->board[y+1], sizeof(ctx->board[y]));
    }
    int hole = rand() % BOARD_WIDTH;
    for (int x = 0; x < BOARD_WIDTH; x++) {
        if (x != hole) ctx->board[BOARD_HEIGHT-1][x] = (Color){100, 100, 100, 255};
        else ctx->board[BOARD_HEIGHT-1][x] = (Color){0,0,0,0};
    }
    // Kill line desce (fica mais difícil)
    if (ctx->killLineY < BOARD_HEIGHT - 2) ctx->killLineY++;
}

void RemovePenaltyLine(GameContext *ctx) {
    // Kill line sobe (fica mais fácil)
    if (ctx->killLineY > 2) ctx->killLineY--;
}

void UpdateGame(GameContext *ctx, float deltaTime) {
    if (ctx->state != STATE_GAME) return;
    
    ctx->dropTimer += deltaTime;
    if (ctx->dropTimer >= ctx->dropInterval) {
        if (!CheckCollision(ctx, ctx->currentPiece, 0, 1)) {
            ctx->currentPiece.pos.y++;
        } else {
            MergePiece(ctx);
        }
        ctx->dropTimer = 0;
    }
}
