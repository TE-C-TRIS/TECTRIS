#include "game.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

// ---------------------------------------------------------------------
// Fundo ambiente: uma grade bem sutil + leve vinheta nas bordas, so pra
// a tela nao ficar com preto vazio atras do tabuleiro. Discreto de
// proposito, pra nao atrapalhar a leitura do jogo.
// ---------------------------------------------------------------------
static void DrawAmbientBackground(int sw, int sh) {
    Color gridColor = (Color){0, 255, 65, 12};
    int step = 42;
    for (int x = 0; x < sw; x += step) DrawLine(x, 0, x, sh, gridColor);
    for (int y = 0; y < sh; y += step) DrawLine(0, y, sw, y, gridColor);

    Color vig = (Color){0, 0, 0, 70};
    int vSize = 50;
    DrawRectangle(0, 0, sw, vSize, vig);
    DrawRectangle(0, sh - vSize, sw, vSize, vig);
    DrawRectangle(0, 0, vSize, sh, vig);
    DrawRectangle(sw - vSize, 0, vSize, sh, vig);
}

// ---------------------------------------------------------------------
// Peca fantasma: simula a queda da peca atual ate colidir, pra mostrar
// ao jogador onde ela vai pousar (igual ao Tetris moderno).
// ---------------------------------------------------------------------
static Tetromino GetGhostPiece(GameContext *ctx) {
    Tetromino ghost = ctx->currentPiece;
    while (!CheckCollision(ctx, ghost, 0, 1)) {
        ghost.pos.y++;
    }
    return ghost;
}

static void DrawGhostPiece(Tetromino *ghost, Vector2 off, int cs) {
    Color outline = ghost->color;
    outline.a = 140;
    for (int y = 0; y < ghost->size; y++) {
        for (int x = 0; x < ghost->size; x++) {
            if (ghost->shape[y][x]) {
                int px = (int)(off.x + (ghost->pos.x + x) * cs);
                int py = (int)(off.y + (ghost->pos.y + y) * cs);
                if (py >= off.y) {
                    DrawRectangleLines(px + 2, py + 2, cs - 4, cs - 4, outline);
                }
            }
        }
    }
}

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
    DrawAmbientBackground(ctx->screen.screenWidth, ctx->screen.screenHeight);

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
    } 
    
    // Peca Fantasma (preview de onde a peca vai pousar)
    if (ctx->state == STATE_GAME) {
        Tetromino ghost = GetGhostPiece(ctx);
        DrawGhostPiece(&ghost, off, cs);
    }

    // Current Piece
    if (ctx->state == STATE_GAME || ctx->state == STATE_QUESTION || ctx->state == STATE_QUESTION_EASY) {
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

    // Gerenciamento de Telas Extras (Menu, Relatórios, Perguntas)
    int sw = (int)ctx->screen.screenWidth;
    int sh = (int)ctx->screen.screenHeight;

    if (ctx->state == STATE_MENU) {
        DrawRectangle(0, 0, sw, sh, (Color){0, 0, 0, 200});
        DrawText("TECTRIS", sw / 2 - MeasureText("TECTRIS", (int)(60 * s)) / 2, (int)(sh * 0.12f), (int)(60 * s), COLOR_TEXT);
        DrawText("Aprenda C Jogando", sw / 2 - MeasureText("Aprenda C Jogando", (int)(22 * s)) / 2, (int)(sh * 0.23f), (int)(22 * s), WHITE);

        // Lista de opcoes do menu - precisa bater 1:1 com a maquina de estados em main.c
        const char* options[] = {
            "Jogar (Desafio de C)",
            "Modo Easy (Curiosidades)",
            "Multiplayer Local",
            "Ranking Geral",
            "Historico - Desafio de C",
            "Historico - Modo Easy",
            "Analisar Estatisticas",
            "Sair"
        };
        int totalOptions = 8;

        for (int i = 0; i < totalOptions; i++) {
            Color textColor = (i == menuIndex) ? YELLOW : WHITE;
            const char *prefix = (i == menuIndex) ? "> " : "  ";
            char label[64];
            sprintf(label, "%s%s", prefix, options[i]);
            DrawText(label, sw / 2 - MeasureText(label, (int)(24 * s)) / 2, (int)(sh * 0.34f + i * 32 * s), (int)(24 * s), textColor);
        }

        const char *audioHint = "M = Musica  |  N = Efeitos Sonoros";
        DrawText(audioHint, sw / 2 - MeasureText(audioHint, (int)(14 * s)) / 2, (int)(sh * 0.96f), (int)(14 * s), GRAY);
    }
    else if (ctx->state == STATE_REPORT) {
        DrawRectangle(0, 0, sw, sh, (Color){15, 15, 30, 240});
        DrawText("RELATORIO ANALITICO", sw / 2 - MeasureText("RELATORIO ANALITICO", (int)(40 * s)) / 2, (int)(sh * 0.1f), (int)(40 * s), COLOR_TEXT);
        DrawText("Carregando dados...", sw / 2 - MeasureText("Carregando dados...", (int)(20 * s)) / 2, (int)(sh * 0.4f), (int)(20 * s), LIGHTGRAY);
        DrawText("Pressione ENTER ou ESC para voltar ao Menu", sw / 2 - MeasureText("Pressione ENTER ou ESC para voltar ao Menu", (int)(20 * s)) / 2, (int)(sh * 0.9f), (int)(20 * s), LIGHTGRAY);
    }

    else if (ctx->state == STATE_HISTORY) {
        // CORREÇÃO AQUI: Removemos o "for" que estava multiplicando o fundo sem necessidade
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

/* ===================================================================
 * EFEITOS VISUAIS: popups flutuantes de pontuacao + flash de acerto/erro
 * =================================================================== */

void InitPopupSystem(PopupSystem *ps) {
    for (int i = 0; i < MAX_POPUPS; i++) {
        ps->items[i].active = false;
    }
}

void AddPopup(PopupSystem *ps, const char *text, Color color) {
    for (int i = 0; i < MAX_POPUPS; i++) {
        if (!ps->items[i].active) {
            strncpy(ps->items[i].text, text, sizeof(ps->items[i].text) - 1);
            ps->items[i].text[sizeof(ps->items[i].text) - 1] = '\0';
            ps->items[i].color = color;
            ps->items[i].maxLife = 1.1f;
            ps->items[i].life = 1.1f;
            ps->items[i].active = true;
            return;
        }
    }
    // Pool cheio: substitui o mais antigo (indice 0) para nao perder o evento mais recente
    strncpy(ps->items[0].text, text, sizeof(ps->items[0].text) - 1);
    ps->items[0].text[sizeof(ps->items[0].text) - 1] = '\0';
    ps->items[0].color = color;
    ps->items[0].maxLife = 1.1f;
    ps->items[0].life = 1.1f;
    ps->items[0].active = true;
}

void UpdatePopups(PopupSystem *ps, float dt) {
    for (int i = 0; i < MAX_POPUPS; i++) {
        if (ps->items[i].active) {
            ps->items[i].life -= dt;
            if (ps->items[i].life <= 0) ps->items[i].active = false;
        }
    }
}

void DrawPopups(PopupSystem *ps, float anchorX, float anchorY) {
    int slot = 0;
    for (int i = 0; i < MAX_POPUPS; i++) {
        if (!ps->items[i].active) continue;
        float t = 1.0f - (ps->items[i].life / ps->items[i].maxLife); // 0..1
        float yOff = -t * 36.0f - slot * 22.0f;
        unsigned char alpha = (unsigned char)(255 * (ps->items[i].life / ps->items[i].maxLife));
        Color c = ps->items[i].color;
        c.a = alpha;
        int fs = 22;
        int tw = MeasureText(ps->items[i].text, fs);
        DrawText(ps->items[i].text, (int)(anchorX - tw / 2), (int)(anchorY + yOff), fs, c);
        slot++;
    }
}

void TriggerFlash(FlashEffect *fx, Color color, float duration) {
    fx->color = color;
    fx->timer = duration;
    fx->maxTimer = duration;
}

void UpdateFlash(FlashEffect *fx, float dt) {
    if (fx->timer > 0) {
        fx->timer -= dt;
        if (fx->timer < 0) fx->timer = 0;
    }
}

void DrawFlashOverlay(FlashEffect *fx, Rectangle area) {
    if (fx->timer <= 0) return;
    float t = fx->timer / fx->maxTimer; // 1..0
    Color c = fx->color;
    c.a = (unsigned char)(90 * t);
    DrawRectangleRec(area, c);
}

/* ===================================================================
 * MULTIPLAYER LOCAL
 * =================================================================== */

// Desenha um unico tabuleiro (board + peca atual + kill line) numa posicao
// arbitraria da tela, usado para montar a tela dividida do multiplayer.
// NOTA DE COMPATIBILIDADE: DrawRectangleRoundedLines() mudou de assinatura entre
// versoes do raylib (algumas pedem espessura da linha, outras nao). Para nao depender
// disso, desenhamos o contorno com DrawRectangleLinesEx (cantos retos), que e uma API
// estavel ha varias versoes do raylib.
static void DrawPanelOutline(Rectangle rec, float lineThick, Color color) {
    DrawRectangleLinesEx(rec, lineThick, color);
}

static void DrawBoardAt(GameContext *ctx, float x, float y, int cs, Color accent) {
    Rectangle boardRect = { x, y, (float)BOARD_WIDTH * cs, (float)BOARD_HEIGHT * cs };
    DrawRectangleRec(boardRect, (Color){5, 5, 12, 255});
    DrawRectangleLinesEx(boardRect, 3, accent);

    for (int yy = 0; yy < BOARD_HEIGHT; yy++) {
        for (int xx = 0; xx < BOARD_WIDTH; xx++) {
            if (ctx->board[yy][xx].a != 0) {
                DrawRectangle((int)(x + xx * cs + 1), (int)(y + yy * cs + 1), cs - 2, cs - 2, ctx->board[yy][xx]);
                DrawRectangleLines((int)(x + xx * cs + 1), (int)(y + yy * cs + 1), cs - 2, cs - 2, (Color){255,255,255,30});
            }
        }
    }

    // Peca Fantasma
    if (ctx->state == STATE_GAME) {
        Tetromino ghost = ctx->currentPiece;
        while (!CheckCollision(ctx, ghost, 0, 1)) ghost.pos.y++;
        Color outline = ghost.color;
        outline.a = 140;
        for (int yy = 0; yy < ghost.size; yy++) {
            for (int xx = 0; xx < ghost.size; xx++) {
                if (ghost.shape[yy][xx]) {
                    int px = (int)(x + (ghost.pos.x + xx) * cs);
                    int py = (int)(y + (ghost.pos.y + yy) * cs);
                    if (py >= y) DrawRectangleLines(px + 2, py + 2, cs - 4, cs - 4, outline);
                }
            }
        }
    }

    if (ctx->state == STATE_GAME) {
        for (int yy = 0; yy < ctx->currentPiece.size; yy++) {
            for (int xx = 0; xx < ctx->currentPiece.size; xx++) {
                if (ctx->currentPiece.shape[yy][xx]) {
                    int px = (int)(x + (ctx->currentPiece.pos.x + xx) * cs);
                    int py = (int)(y + (ctx->currentPiece.pos.y + yy) * cs);
                    if (py >= y) {
                        DrawRectangle(px + 1, py + 1, cs - 2, cs - 2, ctx->currentPiece.color);
                        DrawRectangleLines(px + 1, py + 1, cs - 2, cs - 2, WHITE);
                    }
                }
            }
        }
    }

    // Kill line
    int killY = (int)(y + (ctx->killLineY * cs));
    float pulse = (sinf(GetTime() * 8.0f) + 1.0f) / 2.0f;
    Color kColor = COLOR_KILLLINE;
    kColor.a = (unsigned char)(180 + (75 * pulse));
    DrawLineEx((Vector2){x, (float)killY}, (Vector2){x + BOARD_WIDTH * cs, (float)killY}, 3, kColor);

    if (ctx->state == STATE_GAMEOVER) {
        DrawRectangleRec(boardRect, (Color){20, 5, 5, 170});
        const char *over = "DERROTA";
        int fs = (int)(cs * 0.9f);
        DrawText(over, (int)(x + boardRect.width/2 - MeasureText(over, fs)/2), (int)(y + boardRect.height/2 - fs/2), fs, RED);
    }
}

void DrawMultiplayerGame(GameContext *p1, GameContext *p2,
                          FlashEffect *flashP1, FlashEffect *flashP2,
                          PopupSystem *popsP1, PopupSystem *popsP2,
                          float nextQuestionIn) {
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();
    float scale = fminf(sw / 1100.0f, sh / 760.0f);
    if (scale < 0.55f) scale = 0.55f;
    int cell = (int)(22 * scale);

    float boardW = BOARD_WIDTH * cell;
    float boardH = BOARD_HEIGHT * cell;
    float centerW = 240 * scale;
    float margin = 26 * scale;
    float totalW = boardW * 2 + centerW + margin * 2;
    float startX = (sw - totalW) / 2.0f;
    float boardY = (sh - boardH) / 2.0f + 14 * scale;
    float headerY = boardY - 64 * scale;

    float p1X = startX;
    float centerX = startX + boardW + margin;
    float p2X = centerX + centerW + margin;

    ClearBackground(COLOR_BG);
    DrawAmbientBackground(sw, sh);

    DrawText("TECTRIS - MULTIPLAYER LOCAL",
        sw / 2 - MeasureText("TECTRIS - MULTIPLAYER LOCAL", (int)(22 * scale)) / 2,
        (int)(14 * scale), (int)(22 * scale), COLOR_TEXT);

    // ---- Cabecalhos (nome + score) ----
    DrawText(p1->playerName[0] ? p1->playerName : "Jogador 1",
        (int)p1X, (int)headerY, (int)(22 * scale), COLOR_P1);
    char scoreStr1[32]; sprintf(scoreStr1, "%06d", p1->score);
    DrawText(scoreStr1, (int)p1X, (int)(headerY + 26 * scale), (int)(24 * scale), WHITE);

    const char *p2Name = p2->playerName[0] ? p2->playerName : "Jogador 2";
    int p2NameW = MeasureText(p2Name, (int)(22 * scale));
    DrawText(p2Name, (int)(p2X + boardW - p2NameW), (int)headerY, (int)(22 * scale), COLOR_P2);
    char scoreStr2[32]; sprintf(scoreStr2, "%06d", p2->score);
    int p2ScoreW = MeasureText(scoreStr2, (int)(24 * scale));
    DrawText(scoreStr2, (int)(p2X + boardW - p2ScoreW), (int)(headerY + 26 * scale), (int)(24 * scale), WHITE);

    // ---- Tabuleiros ----
    DrawBoardAt(p1, p1X, boardY, cell, COLOR_P1);
    DrawBoardAt(p2, p2X, boardY, cell, COLOR_P2);

    DrawFlashOverlay(flashP1, (Rectangle){ p1X, boardY, boardW, boardH });
    DrawFlashOverlay(flashP2, (Rectangle){ p2X, boardY, boardW, boardH });

    DrawPopups(popsP1, p1X + boardW / 2, boardY + boardH * 0.4f);
    DrawPopups(popsP2, p2X + boardW / 2, boardY + boardH * 0.4f);

    // ---- Rodape de cada tabuleiro: nivel / linhas / proxima peca ----
    char infoStr1[64]; sprintf(infoStr1, "Nivel %d  |  Linhas %d", p1->level, p1->lines);
    DrawText(infoStr1, (int)p1X, (int)(boardY + boardH + 8 * scale), (int)(16 * scale), LIGHTGRAY);
    char infoStr2[64]; sprintf(infoStr2, "Nivel %d  |  Linhas %d", p2->level, p2->lines);
    DrawText(infoStr2, (int)p2X, (int)(boardY + boardH + 8 * scale), (int)(16 * scale), LIGHTGRAY);

    // ---- Coluna central ----
    Rectangle centerPanel = { centerX, boardY, centerW, boardH };
    DrawRectangleRounded(centerPanel, 0.08f, 8, COLOR_PANEL);
    DrawPanelOutline(centerPanel, 2, COLOR_TEXT);

    float cy = boardY + 18 * scale;
    const char *vsLabel = "VS";
    DrawText(vsLabel, (int)(centerX + centerW/2 - MeasureText(vsLabel, (int)(34*scale))/2), (int)cy, (int)(34*scale), COLOR_BORDER);
    cy += 50 * scale;

    DrawText("PROXIMA", (int)(centerX + 20*scale), (int)cy, (int)(13*scale), GRAY);
    cy += 18*scale;
    // peca "next" de cada jogador, lado a lado
    int nextCs = (int)(14 * scale);
    for (int yy = 0; yy < p1->nextPiece.size; yy++)
        for (int xx = 0; xx < p1->nextPiece.size; xx++)
            if (p1->nextPiece.shape[yy][xx])
                DrawRectangle((int)(centerX + 24*scale) + xx*nextCs, (int)cy + yy*nextCs, nextCs-2, nextCs-2, p1->nextPiece.color);
    for (int yy = 0; yy < p2->nextPiece.size; yy++)
        for (int xx = 0; xx < p2->nextPiece.size; xx++)
            if (p2->nextPiece.shape[yy][xx])
                DrawRectangle((int)(centerX + centerW - 90*scale) + xx*nextCs, (int)cy + yy*nextCs, nextCs-2, nextCs-2, p2->nextPiece.color);
    cy += 70 * scale;

    DrawLineEx((Vector2){centerX + 16*scale, cy}, (Vector2){centerX + centerW - 16*scale, cy}, 1, (Color){80,80,110,255});
    cy += 16 * scale;

    DrawText("PROXIMA PERGUNTA EM", (int)(centerX + 20*scale), (int)cy, (int)(12*scale), GRAY);
    cy += 16*scale;
    char qTimer[16];
    if (nextQuestionIn < 0) nextQuestionIn = 0;
    sprintf(qTimer, "%ds", (int)nextQuestionIn);
    DrawText(qTimer, (int)(centerX + 20*scale), (int)cy, (int)(28*scale), COLOR_TEXT);
    cy += 46*scale;

    DrawLineEx((Vector2){centerX + 16*scale, cy}, (Vector2){centerX + centerW - 16*scale, cy}, 1, (Color){80,80,110,255});
    cy += 16 * scale;

    DrawText("CONTROLES", (int)(centerX + 20*scale), (int)cy, (int)(12*scale), GRAY);
    cy += 18*scale;
    int fsCtrl = (int)(13*scale);
    DrawText("J1: A D mover | W girar", (int)(centerX + 20*scale), (int)cy, fsCtrl, COLOR_P1); cy += fsCtrl + 5*scale;
    DrawText("    S responder | ESPACO queda", (int)(centerX + 20*scale), (int)cy, fsCtrl, COLOR_P1); cy += fsCtrl + 10*scale;
    DrawText("J2: setas mover/girar", (int)(centerX + 20*scale), (int)cy, fsCtrl, COLOR_P2); cy += fsCtrl + 5*scale;
    DrawText("    BAIXO responder | ENTER queda", (int)(centerX + 20*scale), (int)cy, fsCtrl, COLOR_P2); cy += fsCtrl + 10*scale;

    DrawText("P para pausar", (int)(centerX + 20*scale), (int)(boardY + boardH - 22*scale), (int)(12*scale), GRAY);
}

void DrawMultiQuestionOverlay(MultiQuestionState *mq, GameContext *p1, GameContext *p2) {
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();
    float s = fminf(sw / 1100.0f, sh / 760.0f);
    if (s < 0.55f) s = 0.55f;

    DrawRectangle(0, 0, sw, sh, (Color){10, 10, 25, 235});

    Rectangle qBox = { sw * 0.18f, sh * 0.08f, sw * 0.64f, sh * 0.28f };
    DrawRectangleRounded(qBox, 0.08f, 8, COLOR_PANEL);
    DrawPanelOutline(qBox, 2, COLOR_TEXT);

    const char *title = "DESAFIO DE C - MULTIPLAYER";
    DrawText(title, sw/2 - MeasureText(title, (int)(26*s))/2, (int)(qBox.y + 22*s), (int)(26*s), COLOR_TEXT);
    DrawText(mq->question.question, sw/2 - MeasureText(mq->question.question, (int)(20*s))/2,
        (int)(qBox.y + 70*s), (int)(20*s), WHITE);

    // barra de tempo compartilhada
    float pct = mq->questionTimer / mq->questionTimeMax;
    if (pct < 0) pct = 0;
    float barW = qBox.width * 0.8f;
    DrawRectangle((int)(sw/2 - barW/2), (int)(qBox.y + qBox.height - 24*s), (int)(barW*pct), (int)(6*s),
        (pct < 0.3f) ? RED : GREEN);

    // ---- Caixas de resposta lado a lado ----
    float boxW = sw * 0.36f;
    float boxH = sh * 0.42f;
    float boxY = qBox.y + qBox.height + 20*s;
    Rectangle p1Box = { sw/2 - boxW - 14*s, boxY, boxW, boxH };
    Rectangle p2Box = { sw/2 + 14*s, boxY, boxW, boxH };

    bool p1Active = (mq->activeTurn == TURN_P1);
    bool p2Active = (mq->activeTurn == TURN_P2);

    Color p1BorderColor = mq->p1Done ? (mq->p1Correct ? GREEN : RED) : (p1Active ? COLOR_P1 : (Color){80,80,110,255});
    Color p2BorderColor = mq->p2Done ? (mq->p2Correct ? GREEN : RED) : (p2Active ? COLOR_P2 : (Color){80,80,110,255});

    DrawRectangleRounded(p1Box, 0.06f, 8, COLOR_PANEL);
    DrawPanelOutline(p1Box, p1Active ? 4 : 2, p1BorderColor);
    DrawRectangleRounded(p2Box, 0.06f, 8, COLOR_PANEL);
    DrawPanelOutline(p2Box, p2Active ? 4 : 2, p2BorderColor);

    const char *p1Title = p1->playerName[0] ? p1->playerName : "Jogador 1";
    const char *p2Title = p2->playerName[0] ? p2->playerName : "Jogador 2";
    DrawText(p1Title, (int)(p1Box.x + 16*s), (int)(p1Box.y + 14*s), (int)(20*s), COLOR_P1);
    DrawText(p2Title, (int)(p2Box.x + 16*s), (int)(p2Box.y + 14*s), (int)(20*s), COLOR_P2);

    if (!mq->p1Done) {
        const char *hint;
        Color hintColor = GRAY;
        if (mq->showFeedback) {
            hint = "Jogador 2 acertou primeiro - sem penalidade";
            hintColor = LIGHTGRAY;
        } else if (p1Active) {
            hint = "Digite e pressione ENTER";
            hintColor = WHITE;
        } else if (mq->p2Done && !mq->p2Correct) {
            hint = "Sua vez! Pressione [S] para responder";
            hintColor = COLOR_P1;
        } else {
            hint = "Pressione [S] para responder";
        }
        DrawText(hint, (int)(p1Box.x + 16*s), (int)(p1Box.y + 46*s), (int)(14*s), hintColor);
        if (p1Active) {
            Rectangle iBox = { p1Box.x + 16*s, p1Box.y + 74*s, p1Box.width - 32*s, 44*s };
            DrawRectangleRec(iBox, (Color){5,5,12,255});
            DrawRectangleLinesEx(iBox, 2, WHITE);
            DrawText(mq->p1Input, (int)(iBox.x + 10*s), (int)(iBox.y + 12*s), (int)(20*s), COLOR_TEXT);
            if (((int)(GetTime()*2)) % 2 == 0) {
                int tw = MeasureText(mq->p1Input, (int)(20*s));
                DrawRectangle((int)(iBox.x + 10*s + tw + 2), (int)(iBox.y + 10*s), 2, (int)(22*s), COLOR_TEXT);
            }
        }
    } else {
        const char *fb = mq->p1Correct ? "RESPOSTA CORRETA! +150" : "RESPOSTA INCORRETA - linha de penalidade";
        DrawText(fb, (int)(p1Box.x + 16*s), (int)(p1Box.y + 60*s), (int)(15*s), mq->p1Correct ? GREEN : RED);
    }

    if (!mq->p2Done) {
        const char *hint;
        Color hintColor = GRAY;
        if (mq->showFeedback) {
            hint = "Jogador 1 acertou primeiro - sem penalidade";
            hintColor = LIGHTGRAY;
        } else if (p2Active) {
            hint = "Digite e pressione ENTER";
            hintColor = WHITE;
        } else if (mq->p1Done && !mq->p1Correct) {
            hint = "Sua vez! Pressione [BAIXO] para responder";
            hintColor = COLOR_P2;
        } else {
            hint = "Pressione [BAIXO] para responder";
        }
        DrawText(hint, (int)(p2Box.x + 16*s), (int)(p2Box.y + 46*s), (int)(14*s), hintColor);
        if (p2Active) {
            Rectangle iBox = { p2Box.x + 16*s, p2Box.y + 74*s, p2Box.width - 32*s, 44*s };
            DrawRectangleRec(iBox, (Color){5,5,12,255});
            DrawRectangleLinesEx(iBox, 2, WHITE);
            DrawText(mq->p2Input, (int)(iBox.x + 10*s), (int)(iBox.y + 12*s), (int)(20*s), COLOR_TEXT);
            if (((int)(GetTime()*2)) % 2 == 0) {
                int tw = MeasureText(mq->p2Input, (int)(20*s));
                DrawRectangle((int)(iBox.x + 10*s + tw + 2), (int)(iBox.y + 10*s), 2, (int)(22*s), COLOR_TEXT);
            }
        }
    } else {
        const char *fb = mq->p2Correct ? "RESPOSTA CORRETA! +150" : "RESPOSTA INCORRETA - linha de penalidade";
        DrawText(fb, (int)(p2Box.x + 16*s), (int)(p2Box.y + 60*s), (int)(15*s), mq->p2Correct ? GREEN : RED);
    }

    if (mq->p1Done && mq->p2Done) {
        const char *both = "Voltando ao jogo...";
        DrawText(both, sw/2 - MeasureText(both, (int)(16*s))/2, (int)(p1Box.y + p1Box.height + 14*s), (int)(16*s), LIGHTGRAY);
    }
}

/* ===================================================================
 * ENTRADA DE NOME (single + multiplayer)
 * =================================================================== */

void DrawNameEntryScreen(const char *title, const char *input, bool isEasy) {
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();
    float s = fminf(sw / 800.0f, sh / 700.0f);
    if (s < 0.6f) s = 0.6f;

    ClearBackground(COLOR_BG);
    DrawAmbientBackground(sw, sh);

    DrawText("TECTRIS", sw/2 - MeasureText("TECTRIS", (int)(50*s))/2, (int)(sh*0.22f), (int)(50*s), COLOR_TEXT);
    DrawText(title, sw/2 - MeasureText(title, (int)(22*s))/2, (int)(sh*0.34f), (int)(22*s), isEasy ? COLOR_P2 : COLOR_P1);

    DrawText("Digite seu nome:", sw/2 - MeasureText("Digite seu nome:", (int)(18*s))/2, (int)(sh*0.45f), (int)(18*s), LIGHTGRAY);

    Rectangle iBox = { sw/2 - 220*s, sh*0.52f, 440*s, 56*s };
    DrawRectangleRec(iBox, COLOR_PANEL);
    DrawRectangleLinesEx(iBox, 2, COLOR_TEXT);
    DrawText(input, (int)(iBox.x + 16*s), (int)(iBox.y + 14*s), (int)(28*s), WHITE);
    if (((int)(GetTime()*2)) % 2 == 0) {
        int tw = MeasureText(input, (int)(28*s));
        DrawRectangle((int)(iBox.x + 16*s + tw + 3), (int)(iBox.y + 12*s), 2, (int)(30*s), COLOR_TEXT);
    }

    DrawText("Pressione ENTER para confirmar  |  ESC para voltar",
        sw/2 - MeasureText("Pressione ENTER para confirmar  |  ESC para voltar", (int)(16*s))/2,
        (int)(sh*0.66f), (int)(16*s), GRAY);
}

void DrawMultiNameEntryScreen(const char *p1Name, const char *p2Name, int activeStep) {
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();
    float s = fminf(sw / 800.0f, sh / 700.0f);
    if (s < 0.6f) s = 0.6f;

    ClearBackground(COLOR_BG);
    DrawAmbientBackground(sw, sh);

    DrawText("TECTRIS", sw/2 - MeasureText("TECTRIS", (int)(46*s))/2, (int)(sh*0.14f), (int)(46*s), COLOR_TEXT);
    DrawText("MULTIPLAYER LOCAL", sw/2 - MeasureText("MULTIPLAYER LOCAL", (int)(20*s))/2, (int)(sh*0.25f), (int)(20*s), COLOR_BORDER);

    Rectangle box1 = { sw/2 - 230*s, sh*0.38f, 460*s, 56*s };
    Rectangle box2 = { sw/2 - 230*s, sh*0.52f, 460*s, 56*s };

    DrawText("Jogador 1 (WASD)", (int)box1.x, (int)(box1.y - 24*s), (int)(16*s), COLOR_P1);
    DrawRectangleRec(box1, COLOR_PANEL);
    DrawRectangleLinesEx(box1, 2, activeStep == 0 ? COLOR_P1 : (Color){80,80,110,255});
    DrawText(p1Name, (int)(box1.x + 16*s), (int)(box1.y + 14*s), (int)(26*s), WHITE);
    if (activeStep == 0 && ((int)(GetTime()*2)) % 2 == 0) {
        int tw = MeasureText(p1Name, (int)(26*s));
        DrawRectangle((int)(box1.x + 16*s + tw + 3), (int)(box1.y + 12*s), 2, (int)(28*s), COLOR_P1);
    }

    DrawText("Jogador 2 (Setas)", (int)box2.x, (int)(box2.y - 24*s), (int)(16*s), COLOR_P2);
    DrawRectangleRec(box2, COLOR_PANEL);
    DrawRectangleLinesEx(box2, 2, activeStep == 1 ? COLOR_P2 : (Color){80,80,110,255});
    DrawText(p2Name, (int)(box2.x + 16*s), (int)(box2.y + 14*s), (int)(26*s), activeStep >= 1 ? WHITE : GRAY);
    if (activeStep == 1 && ((int)(GetTime()*2)) % 2 == 0) {
        int tw = MeasureText(p2Name, (int)(26*s));
        DrawRectangle((int)(box2.x + 16*s + tw + 3), (int)(box2.y + 12*s), 2, (int)(28*s), COLOR_P2);
    }

    const char *hint = (activeStep == 0)
        ? "Jogador 1, digite seu nome e pressione ENTER"
        : "Jogador 2, digite seu nome e pressione ENTER";
    DrawText(hint, sw/2 - MeasureText(hint, (int)(16*s))/2, (int)(sh*0.68f), (int)(16*s), LIGHTGRAY);
    DrawText("ESC para voltar ao menu", sw/2 - MeasureText("ESC para voltar ao menu", (int)(14*s))/2, (int)(sh*0.74f), (int)(14*s), GRAY);
}

void DrawMultiGameOverScreen(GameContext *p1, GameContext *p2, bool p1Won) {
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();
    float s = fminf(sw / 800.0f, sh / 700.0f);
    if (s < 0.6f) s = 0.6f;

    DrawRectangle(0, 0, sw, sh, (Color){10, 5, 20, 240});

    const char *title = "FIM DE PARTIDA";
    DrawText(title, sw/2 - MeasureText(title, (int)(40*s))/2, (int)(sh*0.16f), (int)(40*s), COLOR_TEXT);

    GameContext *winner = p1Won ? p1 : p2;
    Color winColor = p1Won ? COLOR_P1 : COLOR_P2;
    const char *winnerName = winner->playerName[0] ? winner->playerName : (p1Won ? "Jogador 1" : "Jogador 2");

    char winText[64];
    sprintf(winText, "%s venceu!", winnerName);
    DrawText(winText, sw/2 - MeasureText(winText, (int)(34*s))/2, (int)(sh*0.30f), (int)(34*s), winColor);

    char scoreLine[96];
    sprintf(scoreLine, "%s: %d pts    x    %s: %d pts",
        p1->playerName[0] ? p1->playerName : "Jogador 1", p1->score,
        p2->playerName[0] ? p2->playerName : "Jogador 2", p2->score);
    DrawText(scoreLine, sw/2 - MeasureText(scoreLine, (int)(18*s))/2, (int)(sh*0.42f), (int)(18*s), WHITE);

    DrawText("Resultado salvo no Ranking Geral!", sw/2 - MeasureText("Resultado salvo no Ranking Geral!", (int)(16*s))/2,
        (int)(sh*0.52f), (int)(16*s), LIGHTGRAY);

    DrawText("Pressione ENTER para voltar ao menu", sw/2 - MeasureText("Pressione ENTER para voltar ao menu", (int)(18*s))/2,
        (int)(sh*0.85f), (int)(18*s), LIGHTGRAY);
}

/* ===================================================================
 * RANKING GERAL (podio + lista)
 * =================================================================== */

static Color ModeColor(const char *mode) {
    if (strcmp(mode, MODE_EASY) == 0) return COLOR_P2;
    if (strcmp(mode, MODE_MULTI) == 0) return COLOR_BORDER;
    return COLOR_P1;
}

void DrawRankingScreen(RankingEntry *entries, int count) {
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();
    float s = fminf(sw / 800.0f, sh / 700.0f);
    if (s < 0.6f) s = 0.6f;

    ClearBackground(COLOR_BG);
    DrawAmbientBackground(sw, sh);

    DrawText("RANKING GERAL", sw/2 - MeasureText("RANKING GERAL", (int)(38*s))/2, (int)(sh*0.04f), (int)(38*s), COLOR_TEXT);
    DrawText("C = Desafio de C   |   EASY = Curiosidades   |   MULTI = Multiplayer Local",
        sw/2 - MeasureText("C = Desafio de C   |   EASY = Curiosidades   |   MULTI = Multiplayer Local", (int)(13*s))/2,
        (int)(sh*0.10f), (int)(13*s), GRAY);

    if (count == 0) {
        const char *empty = "Nenhuma partida registrada ainda.";
        DrawText(empty, sw/2 - MeasureText(empty, (int)(20*s))/2, (int)(sh*0.4f), (int)(20*s), LIGHTGRAY);
    } else {
        // ---- Podio (top 3) ----
        int topCount = (count < 3) ? count : 3;
        float podiumBaseY = sh * 0.42f;
        float podiumW = 150 * s;
        float gap = 18 * s;
        float totalW = podiumW * 3 + gap * 2;
        float startX = sw/2 - totalW/2;
        // ordem visual: 2o (esquerda), 1o (centro), 3o (direita)
        int order[3] = {1, 0, 2};
        float heights[3] = {120*s, 160*s, 90*s};
        Color barColors[3] = {COLOR_SILVER, COLOR_GOLD, COLOR_BRONZE};
        const char *medals[3] = {"2o", "1o", "3o"};

        for (int slot = 0; slot < 3; slot++) {
            int rank = order[slot];
            float bx = startX + slot * (podiumW + gap);
            float bh = heights[slot];
            float by = podiumBaseY + (160*s - bh);

            if (rank < topCount) {
                RankingEntry *e = &entries[rank];
                Color mc = ModeColor(e->mode);

                char nameBuf[40]; sprintf(nameBuf, "%s", e->name);
                DrawText(nameBuf, (int)(bx + podiumW/2 - MeasureText(nameBuf, (int)(16*s))/2), (int)(by - 46*s), (int)(16*s), WHITE);

                char scoreBuf[24]; sprintf(scoreBuf, "%d pts", e->score);
                DrawText(scoreBuf, (int)(bx + podiumW/2 - MeasureText(scoreBuf, (int)(14*s))/2), (int)(by - 26*s), (int)(14*s), LIGHTGRAY);

                Rectangle bar = { bx, by, podiumW, bh };
                DrawRectangleRounded(bar, 0.12f, 8, barColors[slot]);
                DrawPanelOutline(bar, 2, mc);

                DrawText(medals[slot], (int)(bx + podiumW/2 - MeasureText(medals[slot], (int)(28*s))/2), (int)(by + 14*s), (int)(28*s), (Color){20,20,30,255});

                int modeW = MeasureText(e->mode, (int)(12*s));
                DrawRectangle((int)(bx + podiumW/2 - modeW/2 - 6*s), (int)(by + bh - 26*s), modeW + 12*s, (int)(18*s), mc);
                DrawText(e->mode, (int)(bx + podiumW/2 - modeW/2), (int)(by + bh - 24*s), (int)(12*s), (Color){10,10,15,255});
            } else {
                Rectangle bar = { bx, by, podiumW, bh };
                DrawRectangleRounded(bar, 0.12f, 8, (Color){40,40,55,255});
            }
        }

        // ---- Lista 4 em diante ----
        float listY = podiumBaseY + 160*s + 30*s;
        int maxList = (count < 13) ? count : 13;
        for (int i = 3; i < maxList; i++) {
            RankingEntry *e = &entries[i];
            Color mc = ModeColor(e->mode);
            char line[96];
            sprintf(line, "#%-2d  %-16s  %5d pts  [%s]", i+1, e->name, e->score, e->mode);
            DrawText(line, sw/2 - 220*s, (int)(listY + (i-3)*(22*s)), (int)(15*s), mc);
        }
    }

    DrawText("Pressione ENTER ou ESC para voltar", sw/2 - MeasureText("Pressione ENTER ou ESC para voltar", (int)(16*s))/2,
        (int)(sh*0.95f), (int)(16*s), GRAY);
}
