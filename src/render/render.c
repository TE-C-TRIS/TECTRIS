#include "game.h"
#include <stdio.h>
#include <math.h>

void UpdateScreenConfig(GameContext *ctx) {
    ctx->screen.screenWidth = GetScreenWidth();
    ctx->screen.screenHeight = GetScreenHeight();
    
    // Design de referência: 800x700
    float scaleX = (float)ctx->screen.screenWidth / 800.0f;
    float scaleY = (float)ctx->screen.screenHeight / 700.0f;
    
    // Escala uniforme para não distorcer
    ctx->screen.scale = (scaleX < scaleY) ? scaleX : scaleY;
    
    // Tile size proporcional
    ctx->screen.cellSize = (int)(30 * ctx->screen.scale);
    
    // Centralização dinâmica
    float gridWidth = BOARD_WIDTH * ctx->screen.cellSize;
    float panelWidth = 220 * ctx->screen.scale;
    float totalWidth = gridWidth + panelWidth + (40 * ctx->screen.scale);
    
    ctx->screen.offset.x = (ctx->screen.screenWidth - totalWidth) / 2.0f;
    ctx->screen.offset.y = (ctx->screen.screenHeight - (BOARD_HEIGHT * ctx->screen.cellSize)) / 2.0f;
}

void DrawGame(GameContext *ctx, int menuIndex) {
    UpdateScreenConfig(ctx);
    float s = ctx->screen.scale;
    int cs = ctx->screen.cellSize;
    Vector2 off = ctx->screen.offset;

    ClearBackground(COLOR_BG);
    
    // Grid Background
    Rectangle boardRect = { off.x, off.y, (float)BOARD_WIDTH * cs, (float)BOARD_HEIGHT * cs };
    DrawRectangleRec(boardRect, (Color){5, 5, 12, 255});
    DrawRectangleLinesEx(boardRect, 3 * s, COLOR_BORDER);
    
    // Board Cells
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (ctx->board[y][x].a != 0) {
                DrawRectangle((int)(off.x + x * cs + 1), (int)(off.y + y * cs + 1), cs - 2, cs - 2, ctx->board[y][x]);
                DrawRectangleLines((int)(off.x + x * cs + 1), (int)(off.y + y * cs + 1), cs - 2, cs - 2, (Color){255,255,255,30});
            }
        }
    }  // ← fecha o for corretamente aqui
    
    // Current Piece
    if (ctx->state == STATE_GAME || ctx->state == STATE_QUESTION) {
        for (int y = 0; y < ctx->currentPiece.size; y++) {
            for (int x = 0; x < ctx->currentPiece.size; x++) {
                if (ctx->currentPiece.shape[y][x]) {
                    int px = (int)(off.x + (ctx->currentPiece.pos.x + x) * cs);
                    int py = (int)(off.y + (ctx->currentPiece.pos.y + y) * cs);
                    if (py >= off.y) {
                        DrawRectangle(px + 1, py + 1, cs - 2, cs - 2, ctx->currentPiece.color);
                        DrawRectangleLines(px + 1, py + 1, cs - 2, cs - 2, WHITE);
                    }
                }
            }
        }
    }
    
    // Kill Line
    int killY = (int)(off.y + (ctx->killLineY * cs));
    float pulse = (sinf(GetTime() * 8.0f) + 1.0f) / 2.0f;
    Color kColor = COLOR_KILLLINE;
    kColor.a = (unsigned char)(180 + (75 * pulse));
    DrawLineEx((Vector2){off.x, (float)killY}, (Vector2){off.x + BOARD_WIDTH * cs, (float)killY}, 4 * s, kColor);
    DrawText("KILL LINE", (int)(off.x - 90 * s), killY - (int)(10 * s), (int)(15 * s), kColor);
    
    // Side Panel
    int panelX = (int)(off.x + BOARD_WIDTH * cs + 30 * s);
    DrawRectangle(panelX, (int)off.y, (int)(200 * s), (int)(450 * s), COLOR_PANEL);
    DrawRectangleLinesEx((Rectangle){(float)panelX, off.y, 200 * s, 450 * s}, 2 * s, COLOR_TEXT);
    
    DrawText("SCORE", panelX + (int)(20 * s), (int)(off.y + 20 * s), (int)(20 * s), COLOR_TEXT);
    char scoreStr[16]; sprintf(scoreStr, "%06d", ctx->score);
    DrawText(scoreStr, panelX + (int)(20 * s), (int)(off.y + 50 * s), (int)(30 * s), WHITE);
    
    DrawText("LINES", panelX + (int)(20 * s), (int)(off.y + 110 * s), (int)(20 * s), COLOR_TEXT);
    char linesStr[16]; sprintf(linesStr, "%d", ctx->lines);
    DrawText(linesStr, panelX + (int)(20 * s), (int)(off.y + 140 * s), (int)(30 * s), WHITE);
    
    DrawText("LEVEL", panelX + (int)(20 * s), (int)(off.y + 200 * s), (int)(20 * s), COLOR_TEXT);
    char levelStr[16]; sprintf(levelStr, "%d", ctx->level);
    DrawText(levelStr, panelX + (int)(20 * s), (int)(off.y + 230 * s), (int)(30 * s), WHITE);
    
    DrawText("NEXT", panelX + (int)(20 * s), (int)(off.y + 300 * s), (int)(20 * s), COLOR_TEXT);
    int nextCs = (int)(18 * s);
    for (int y = 0; y < ctx->nextPiece.size; y++) {
        for (int x = 0; x < ctx->nextPiece.size; x++) {
            if (ctx->nextPiece.shape[y][x]) {
                DrawRectangle(panelX + (int)(50 * s) + x * nextCs, (int)(off.y + 350 * s) + y * nextCs, nextCs - 2, nextCs - 2, ctx->nextPiece.color);
            }
        }
    }

    // Menu
    int sw = (int)ctx->screen.screenWidth;
    int sh = (int)ctx->screen.screenHeight;

    if (ctx->state == STATE_MENU) {
        DrawRectangle(0, 0, sw, sh, (Color){0, 0, 0, 200});
        DrawText("TECTRIS", sw / 2 - MeasureText("TECTRIS", (int)(70 * s)) / 2, (int)(sh * 0.3f), (int)(70 * s), COLOR_TEXT);
        DrawText("Aprenda C Jogando", sw / 2 - MeasureText("Aprenda C Jogando", (int)(25 * s)) / 2, (int)(sh * 0.42f), (int)(25 * s), WHITE);

        const char* options[] = {"Jogar", "Analisar Historico", "Analisar Estatisticas", "Sair"};
        for (int i = 0; i < 4; i++) {
            Color textColor = (i == menuIndex) ? YELLOW : WHITE;
            DrawText(options[i], sw / 2 - MeasureText(options[i], (int)(30 * s)) / 2, (int)(sh * 0.55f + i * 40 * s), (int)(30 * s), textColor);
        }
    }

    else if (ctx->state == STATE_REPORT) {
        DrawRectangle(0, 0, sw, sh, (Color){15, 15, 30, 240});
        DrawText("RELATORIO ANALITICO", sw / 2 - MeasureText("RELATORIO ANALITICO", (int)(40 * s)) / 2, (int)(sh * 0.1f), (int)(40 * s), COLOR_TEXT);
        DrawText("Carregando dados...", sw / 2 - MeasureText("Carregando dados...", (int)(20 * s)) / 2, (int)(sh * 0.4f), (int)(20 * s), LIGHTGRAY);
        DrawText("Pressione ENTER ou ESC para voltar ao Menu", sw / 2 - MeasureText("Pressione ENTER ou ESC para voltar ao Menu", (int)(20 * s)) / 2, (int)(sh * 0.9f), (int)(20 * s), LIGHTGRAY);
    }

    else if (ctx->state == STATE_HISTORY) {
        for (int i = 0; i < ctx->historyCount; i++)
        DrawRectangle(0, 0, sw, sh, (Color){15, 15, 30, 240});
        DrawText("HISTORICO DE PARTIDAS", sw / 2 - MeasureText("HISTORICO DE PARTIDAS", (int)(40 * s)) / 2, (int)(sh * 0.1f), (int)(40 * s), COLOR_TEXT);

        if (ctx->historyCount == 0) {
            DrawText("Nenhuma partida registrada ainda.", sw / 2 - MeasureText("Nenhuma partida registrada ainda.", (int)(20 * s)) / 2, (int)(sh * 0.4f), (int)(20 * s), LIGHTGRAY);
        } else {
            for (int i = 0; i < ctx->historyCount; i++) {
                char historyEntry[128];
                sprintf(historyEntry, "Score: %d | Linhas: %d | Nivel: %d | Data: %ld",
                    ctx->history[i].score,
                    ctx->history[i].lines,
                    ctx->history[i].level,
                    ctx->history[i].timestamp);
                DrawText(historyEntry, sw / 2 - MeasureText(historyEntry, (int)(20 * s)) / 2, (int)(sh * 0.2f + i * 30 * s), (int)(20 * s), WHITE);
            }
        }
        DrawText("Pressione ENTER para voltar ao Menu", sw / 2 - MeasureText("Pressione ENTER para voltar ao Menu", (int)(20 * s)) / 2, (int)(sh * 0.9f), (int)(20 * s), LIGHTGRAY);
    }
} 