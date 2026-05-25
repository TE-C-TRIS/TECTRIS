#include "common.h"
#include "game.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "history.h"
#include <time.h>

int main()
{
    // Configuração de Janela Redimensionável
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(800, 700, "Tectris - Aprenda C Jogando");
    SetTargetFPS(60);

    GameContext game;
    InitGame(&game);
    int menuIndex = 0;
    MatchHistory history[10];
    int historyCount = 0;

    Question currentQuestion;
    char userInput[64] = "\0";
    int letterCount = 0;
    float questionTimer = 0;
    bool isCorrect = false;
    bool showFeedback = false;
    float feedbackTimer = 0;
    float nextQuestionTimer = 20.0f; // Tempo entre perguntas
    
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        
        // Máquina de Estados
        switch (game.state)
        {
        case STATE_MENU:
        if (IsKeyPressed(KEY_DOWN)) {
                menuIndex++;
                if (menuIndex > 3) menuIndex = 0;
            }
            
            if (IsKeyPressed(KEY_UP)) {
                menuIndex--;
                if (menuIndex < 0) menuIndex = 3;
            }

            if (IsKeyPressed(KEY_ENTER)) {
                
                if (menuIndex == 0) {
                    InitGame(&game);
                    game.state = STATE_GAME;
                }

                else if (menuIndex == 1) {
                    historyCount = LoadHistory(history, 10);
                    game.state = STATE_HISTORY;
                }

                else if (menuIndex == 2) {
                    game.state = STATE_REPORT;
                }
                else if (menuIndex == 3) {
                    CloseWindow();
                }
            }
            break;
            
            case STATE_HISTORY:
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE))
            game.state = STATE_MENU;
            break;
            
        case STATE_GAME:
        if (IsKeyPressed(KEY_P))
                game.state = STATE_PAUSE;
                
                // Controles de Gameplay
                if (IsKeyPressed(KEY_LEFT))
                {
                    if (!CheckCollision(&game, game.currentPiece, -1, 0))
                    game.currentPiece.pos.x--;
                }
                
                if (IsKeyPressed(KEY_RIGHT))
                {
                if (!CheckCollision(&game, game.currentPiece, 1, 0))
                    game.currentPiece.pos.x++;
            }

            if (IsKeyPressed(KEY_DOWN))
            {
                if (!CheckCollision(&game, game.currentPiece, 0, 1))
                    game.currentPiece.pos.y++;
                }
                
                if (IsKeyPressed(KEY_UP))
            {
                TryRotate(&game);
            }

            if (IsKeyPressed(KEY_SPACE))
            {
                // Hard Drop
                while (!CheckCollision(&game, game.currentPiece, 0, 1))
                game.currentPiece.pos.y++;
                
                MergePiece(&game);
            }
            
            UpdateGame(&game, dt);
            
            // Gerenciamento de Perguntas
            nextQuestionTimer -= dt;
            
            if (nextQuestionTimer <= 0)
            {
                game.state = STATE_QUESTION;
                currentQuestion = GetRandomQuestion(game.level);
                
                userInput[0] = '\0';
                letterCount = 0;
                questionTimer = 15.0f;
                showFeedback = false;
                
                nextQuestionTimer = 25.0f;
            }
            
            break;
            
            case STATE_PAUSE:
            if (IsKeyPressed(KEY_P))
            game.state = STATE_GAME;
            
            break;

            case STATE_QUESTION:
            
            if (!showFeedback)
            {
                questionTimer -= dt;
                
                if (questionTimer <= 0)
                {
                    isCorrect = false;
                    showFeedback = true;
                    feedbackTimer = 2.5f;
                    
                    AddPenaltyLine(&game);
                }
                
                // Captura de Input de Texto
                int key = GetCharPressed();
                
                while (key > 0)
                {
                    if ((key >= 32) && (key <= 125) && (letterCount < 63))
                    {
                        userInput[letterCount] = (char)key;
                        userInput[letterCount + 1] = '\0';
                        letterCount++;
                    }
                    
                    key = GetCharPressed();
                }
                
                if (IsKeyPressed(KEY_BACKSPACE))
                {
                    if (letterCount > 0)
                    {
                        letterCount--;
                        userInput[letterCount] = '\0';
                    }
                }
                
                if (IsKeyPressed(KEY_ENTER) && letterCount > 0)
                {
                    isCorrect = ValidateAnswer(userInput, &currentQuestion);
                    
                    showFeedback = true;
                    feedbackTimer = 2.5f;
                    
                    if (isCorrect)
                    {
                        game.score += 150;
                        RemovePenaltyLine(&game);
                    }
                    else
                    {
                        AddPenaltyLine(&game);
                    }
                }
            }
            else
            {
                feedbackTimer -= dt;
                
                if (feedbackTimer <= 0)
                {
                    game.state = STATE_GAME;
                }
            }
            
            break;
            
            case STATE_REPORT:
                DrawText("Estatisticas", 100, 100, 30, WHITE);

                if (IsKeyPressed(KEY_ESCAPE))
                {
                    game.state = STATE_MENU;
                }

            break;
            
            case STATE_GAMEOVER:
            
            if (IsKeyPressed(KEY_ENTER))
            {
                MatchHistory currentMatch;
                
                currentMatch.score = game.score;
                currentMatch.lines = game.lines;
                currentMatch.level = game.level;
                currentMatch.timestamp = time(NULL);
                
                SaveHistory(currentMatch);

                game.state = STATE_MENU;
                menuIndex = 0;
            }

            break;
        }

        // Renderização Centralizada
        BeginDrawing();

        DrawGame(&game, menuIndex);

        float s = game.screen.scale;
        int sw = game.screen.screenWidth;
        int sh = game.screen.screenHeight;

        // Overlays de Estado
        if (game.state == STATE_PAUSE)
        {
            DrawRectangle(0, 0, sw, sh, (Color){0, 0, 0, 160});

            DrawText(
                "PAUSA",
                sw / 2 - MeasureText("PAUSA", (int)(50 * s)) / 2,
                sh / 2 - (int)(40 * s),
                (int)(50 * s),
                WHITE
            );

            DrawText(
                "Pressione P para continuar",
                sw / 2 - MeasureText("Pressione P para continuar", (int)(20 * s)) / 2,
                sh / 2 + (int)(20 * s),
                (int)(20 * s),
                LIGHTGRAY
            );
        }

        else if (game.state == STATE_QUESTION)
        {
            DrawRectangle(0, 0, sw, sh, (Color){10, 10, 25, 240});

            Rectangle qBox = {
                sw * 0.1f,
                sh * 0.15f,
                sw * 0.8f,
                sh * 0.7f
            };

            DrawRectangleLinesEx(
                qBox,
                3 * s,
                showFeedback ? (isCorrect ? GREEN : RED) : COLOR_TEXT
            );

            DrawText(
                "DESAFIO DE C",
                sw / 2 - MeasureText("DESAFIO DE C", (int)(35 * s)) / 2,
                (int)(qBox.y + 40 * s),
                (int)(35 * s),
                COLOR_TEXT
            );

            DrawText(
                currentQuestion.question,
                sw / 2 - MeasureText(currentQuestion.question, (int)(22 * s)) / 2,
                (int)(qBox.y + 120 * s),
                (int)(22 * s),
                WHITE
            );

            // Input Box
            Rectangle iBox = {
                sw / 2 - 250 * s,
                qBox.y + 220 * s,
                500 * s,
                60 * s
            };

            DrawRectangleRec(iBox, COLOR_PANEL);

            DrawRectangleLinesEx(
                iBox,
                2 * s,
                showFeedback ? (isCorrect ? GREEN : RED) : WHITE
            );

            DrawText(
                userInput,
                (int)(iBox.x + 15 * s),
                (int)(iBox.y + 15 * s),
                (int)(30 * s),
                COLOR_TEXT
            );

            // Cursor piscante
            if (!showFeedback && ((int)(GetTime() * 2) % 2 == 0))
            {
                int textWidth = MeasureText(userInput, (int)(30 * s));

                DrawRectangle(
                    (int)(iBox.x + 15 * s + textWidth + 2 * s),
                    (int)(iBox.y + 15 * s),
                    (int)(2 * s),
                    (int)(30 * s),
                    COLOR_TEXT
                );
            }

            // Barra de Tempo
            float timerWidth = (questionTimer / 15.0f) * 500 * s;

            DrawRectangle(
                (int)(sw / 2 - 250 * s),
                (int)(iBox.y + 70 * s),
                (int)timerWidth,
                (int)(5 * s),
                (questionTimer < 5) ? RED : GREEN
            );

            if (showFeedback)
            {
                Color fColor = isCorrect ? GREEN : RED;

                const char *fText = isCorrect
                    ? "RESPOSTA CORRETA!"
                    : "RESPOSTA INCORRETA!";

                DrawText(
                    fText,
                    sw / 2 - MeasureText(fText, (int)(40 * s)) / 2,
                    (int)(qBox.y + 350 * s),
                    (int)(40 * s),
                    fColor
                );

                if (!isCorrect)
                {
                    char ans[128];

                    sprintf(ans, "A resposta era: %s", currentQuestion.answers[0]);

                    DrawText(
                        ans,
                        sw / 2 - MeasureText(ans, (int)(20 * s)) / 2,
                        (int)(qBox.y + 410 * s),
                        (int)(20 * s),
                        LIGHTGRAY
                    );
                }
            }
        }

        else if (game.state == STATE_GAMEOVER)
        {
            DrawRectangle(0, 0, sw, sh, (Color){20, 5, 5, 230});

            DrawText(
                "GAME OVER",
                sw / 2 - MeasureText("GAME OVER", (int)(80 * s)) / 2,
                (int)(sh * 0.35f),
                (int)(80 * s),
                RED
            );

            char finalScore[64];

            sprintf(finalScore, "PONTUACAO FINAL: %d", game.score);

            DrawText(
                finalScore,
                sw / 2 - MeasureText(finalScore, (int)(30 * s)) / 2,
                (int)(sh * 0.5f),
                (int)(30 * s),
                WHITE
            );

            DrawText(
                "Pressione ENTER para voltar ao menu",
                sw / 2 - MeasureText("Pressione ENTER para voltar ao menu", (int)(20 * s)) / 2,
                (int)(sh * 0.7f),
                (int)(20 * s),
                LIGHTGRAY
            );
        }
        
        else if (game.state == STATE_REPORT)
        {
            DrawRectangle(0, 0, sw, sh, (Color){15, 15, 30, 255});

            DrawText(
                "ESTATISTICAS",
                sw / 2 - MeasureText("ESTATISTICAS", (int)(35 * s)) / 2,
                (int)(sh * 0.1f),
                (int)(35 * s),
                COLOR_TEXT
            );

            DrawText(
                "Analise de desempenho em andamento...",
                sw / 2 - MeasureText("Analise de desempenho em andamento...", (int)(20 * s)) / 2,
                (int)(sh / 2),
                (int)(20 * s),
                WHITE
            );

            DrawText(
                "Pressione ENTER ou ESC para voltar",
                sw / 2 - MeasureText("Pressione ENTER ou ESC para voltar", (int)(18 * s)) / 2,
                (int)(sh * 0.9f),
                (int)(18 * s),
                LIGHTGRAY
            );
        }
       

        else if (game.state == STATE_HISTORY)
        {
            DrawRectangle(0, 0, sw, sh, (Color){10, 10, 25, 255});

            DrawText(
                "HISTORICO DE PARTIDAS",
                sw / 2 - MeasureText("HISTORICO DE PARTIDAS", (int)(35 * s)) / 2,
                (int)(sh * 0.08f),
                (int)(35 * s),
                COLOR_TEXT
            );

            if (historyCount == 0)
            {
                DrawText(
                    "Nenhuma partida registrada.",
                    sw / 2 - MeasureText("Nenhuma partida registrada.", (int)(20 * s)) / 2,
                    sh / 2,
                    (int)(20 * s),
                    LIGHTGRAY
                );
            }
            else
            {
                for (int i = 0; i < historyCount; i++)
                {
                    char line[128];
                    char dateStr[32];

                    struct tm *timeInfo = localtime(&history[i].timestamp);

                    strftime(
                        dateStr,
                        sizeof(dateStr),
                        "%d/%m/%Y %H:%M",
                        timeInfo
                    );

                    sprintf(
                        line,
                        "%d. Score: %d | Linhas: %d | Nivel: %d | %s",
                        i + 1,
                        history[i].score,
                        history[i].lines,
                        history[i].level,
                        dateStr
                    );

                    DrawText(
                        line,
                        sw / 2 - MeasureText(line, (int)(16 * s)) / 2,
                        (int)(sh * 0.2f) + i * (int)(35 * s),
                        (int)(16 * s),
                        WHITE
                    );
                }
            }

            DrawText(
                "Pressione ENTER ou ESC para voltar",
                sw / 2 - MeasureText("Pressione ENTER ou ESC para voltar", (int)(18 * s)) / 2,
                (int)(sh * 0.9f),
                (int)(18 * s),
                LIGHTGRAY
            );
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}