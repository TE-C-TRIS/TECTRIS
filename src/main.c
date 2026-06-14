#include "common.h"
#include "game.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "history.h"
#include "stats.h"
#include <time.h>

// ADICIONADO: Declaração externa da função do seu novo arquivo "questions_modo_easy.c"
Question GetRandomEasyQuestion();

int main()
{
    // Configuração de Janela Redimensionável
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(800, 700, "Tectris - Aprenda C Jogando");
    SetTargetFPS(60);

    GameContext game;
    InitGame(&game);
    int menuIndex = 0;
    bool isEasyMode = false; // ADICIONADO: Variável flag para saber se a partida atual é do modo fácil ou do modo C
    MatchHistory history[MAX_HISTORY_RECORDS];
    int historyCount = 0;
    GameStats stats;
    int scoresArr[MAX_HISTORY_RECORDS];

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
            if (IsKeyPressed(KEY_DOWN))
            {
                menuIndex++;
                if (menuIndex > 5) // MODIFICADO: O limite máximo subiu para 5 porque agora temos 6 opções no total do menu
                    menuIndex = 0;
            }

            if (IsKeyPressed(KEY_UP))
            {
                menuIndex--;
                if (menuIndex < 0)
                    menuIndex = 5; // MODIFICADO: Retorna para a última opção (5) se passar do topo
            }

            if (IsKeyPressed(KEY_ENTER))
            {

                if (menuIndex == 0)
                {
                    isEasyMode = false; // ADICIONADO: Define que a partida atual NÃO é modo fácil
                    InitGame(&game);
                    game.state = STATE_GAME;
                }

                else if (menuIndex == 1) // ADICIONADO: Nova opção no menu para iniciar o Modo Easy
                {
                    isEasyMode = true; // ADICIONADO: Define que a partida atual É do modo fácil
                    InitGame(&game); // ADICIONADO: Inicializa as configurações de jogo
                    game.state = STATE_GAME_EASY; // ADICIONADO: Modifica o estado do jogo para o loop do Modo Easy
                }

                else if (menuIndex == 2) // MODIFICADO: Antes era menuIndex == 1 (Histórico Normal)
                {
                    game.historyCount = LoadHistory(game.history, MAX_HISTORY_RECORDS, HISTORY_FILE); // MODIFICADO: Passa o arquivo padrão por parâmetro
                    game.state = STATE_HISTORY;
                }

                else if (menuIndex == 3) // ADICIONADO: Nova opção no menu para abrir o Histórico do Modo Easy
                {
                    game.historyCount = LoadHistory(game.history, MAX_HISTORY_RECORDS, HISTORY_EASY_FILE); // ADICIONADO: Carrega os registros salvos do arquivo fácil
                    game.state = STATE_HISTORY; // ADICIONADO: Direciona para a tela de exibição padrão de histórico
                }

                else if (menuIndex == 4) // MODIFICADO: Antes era menuIndex == 2 (Estatísticas)
                {
                    historyCount = LoadHistory(history, MAX_HISTORY_RECORDS, HISTORY_FILE); // MODIFICADO: Passa o arquivo padrão por parâmetro

                    stats.totalMatches = historyCount;
                    stats.averageScore = CalculateAverageScore(history, historyCount);
                    stats.bestScore = CalculateBestScore(history, historyCount);
                    stats.worstScore = CalculateWorstScore(history, historyCount);
                    stats.standardDeviation = CalculateStandardDeviation(history, historyCount, stats.averageScore);

                    for (int i = 0; i < historyCount; i++)
                    {
                        scoresArr[i] = history[i].score; // CORRIGIDO: de game.history para history para ler o arquivo recém-carregado
                    }

                    GenerateHeuristic(&stats);
                    game.state = STATE_REPORT;
                }

                else if (menuIndex == 5) // MODIFICADO: Antes era menuIndex == 3 (Sair)
                {
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

        case STATE_GAME_EASY: // ADICIONADO: Novo bloco de estado completo para gerenciar a partida no modo fácil
            if (IsKeyPressed(KEY_P)) // ADICIONADO
                game.state = STATE_PAUSE; // ADICIONADO

            // Controles de Gameplay idênticos ao modo normal // ADICIONADO
            if (IsKeyPressed(KEY_LEFT)) // ADICIONADO
            { // ADICIONADO
                if (!CheckCollision(&game, game.currentPiece, -1, 0)) // ADICIONADO
                    game.currentPiece.pos.x--; // ADICIONADO
            } // ADICIONADO

            if (IsKeyPressed(KEY_RIGHT)) // ADICIONADO
            { // ADICIONADO
                if (!CheckCollision(&game, game.currentPiece, 1, 0)) // ADICIONADO
                    game.currentPiece.pos.x++; // ADICIONADO
            } // ADICIONADO

            if (IsKeyPressed(KEY_DOWN)) // ADICIONADO
            { // ADICIONADO
                if (!CheckCollision(&game, game.currentPiece, 0, 1)) // ADICIONADO
                    game.currentPiece.pos.y++; // ADICIONADO
            } // ADICIONADO

            if (IsKeyPressed(KEY_UP)) // ADICIONADO
            { // ADICIONADO
                TryRotate(&game); // ADICIONADO
            } // ADICIONADO

            if (IsKeyPressed(KEY_SPACE)) // ADICIONADO
            { // ADICIONADO
                while (!CheckCollision(&game, game.currentPiece, 0, 1)) // ADICIONADO
                    game.currentPiece.pos.y++; // ADICIONADO
                MergePiece(&game); // ADICIONADO
            } // ADICIONADO

            // Hack técnico limpo: altera temporariamente o estado interno para rodar a física do game.c perfeitamente // ADICIONADO
            GameState previousState = game.state; // ADICIONADO
            game.state = STATE_GAME; // ADICIONADO
            UpdateGame(&game, dt); // ADICIONADO
            if (game.state == STATE_GAME) game.state = previousState; // ADICIONADO: Se não deu Game Over, devolve para o modo fácil

            nextQuestionTimer -= dt; // ADICIONADO

            if (nextQuestionTimer <= 0) // ADICIONADO
            { // ADICIONADO
                game.state = STATE_QUESTION_EASY; // ADICIONADO: Direciona para o novo estado de pergunta fácil
                currentQuestion = GetRandomEasyQuestion(); // ADICIONADO: Sorteia as perguntas de curiosidades gerais

                userInput[0] = '\0'; // ADICIONADO
                letterCount = 0; // ADICIONADO
                questionTimer = 15.0f; // ADICIONADO
                showFeedback = false; // ADICIONADO

                nextQuestionTimer = 25.0f; // ADICIONADO
            } // ADICIONADO
            break; // ADICIONADO

        case STATE_PAUSE:
            if (IsKeyPressed(KEY_P))
                game.state = isEasyMode ? STATE_GAME_EASY : STATE_GAME; // MODIFICADO: Retorna para o estado correto dependendo de qual modo estava ativo

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

        case STATE_QUESTION_EASY: // ADICIONADO: Bloco completo para capturar as alternativas (A, B, C, D) no modo fácil
            if (!showFeedback) // ADICIONADO
            { // ADICIONADO
                questionTimer -= dt; // ADICIONADO

                if (questionTimer <= 0) // ADICIONADO
                { // ADICIONADO
                    isCorrect = false; // ADICIONADO
                    showFeedback = true; // ADICIONADO
                    feedbackTimer = 2.5f; // ADICIONADO
                    AddPenaltyLine(&game); // ADICIONADO
                } // ADICIONADO

                // Captura a alternativa de múltipla escolha pressionada pelo jogador // ADICIONADO
                int selectedAnswer = -1; // ADICIONADO
                if (IsKeyPressed(KEY_A)) selectedAnswer = 0; // ADICIONADO
                if (IsKeyPressed(KEY_B)) selectedAnswer = 1; // ADICIONADO
                if (IsKeyPressed(KEY_C)) selectedAnswer = 2; // ADICIONADO
                if (IsKeyPressed(KEY_D)) selectedAnswer = 3; // ADICIONADO

                if (selectedAnswer != -1) // ADICIONADO
                { // ADICIONADO
                    char choiceStr[2] = { 'A' + selectedAnswer, '\0' }; // ADICIONADO: Transforma o índice selecionado em texto ("A", "B", "C" ou "D")
                    isCorrect = ValidateAnswer(choiceStr, &currentQuestion); // ADICIONADO: Valida se a alternativa bate com a correta

                    showFeedback = true; // ADICIONADO
                    feedbackTimer = 2.5f; // ADICIONADO

                    if (isCorrect) // ADICIONADO
                    { // ADICIONADO
                        game.score += 150; // ADICIONADO
                        RemovePenaltyLine(&game); // ADICIONADO
                    } // ADICIONADO
                    else // ADICIONADO
                    { // ADICIONADO
                        AddPenaltyLine(&game); // ADICIONADO
                    } // ADICIONADO
                } // ADICIONADO
            } // ADICIONADO
            else // ADICIONADO
            { // ADICIONADO
                feedbackTimer -= dt; // ADICIONADO

                if (feedbackTimer <= 0) // ADICIONADO
                { // ADICIONADO
                    game.state = STATE_GAME_EASY; // ADICIONADO: Retorna para a partida do modo fácil
                } // ADICIONADO
            } // ADICIONADO
            break; // ADICIONADO
            
        case STATE_REPORT:
            // MODIFICADO: Removido o DrawText incorreto daqui de dentro pois quebrava o Raylib por rodar fora do BeginDrawing/EndDrawing.
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE))
                game.state = STATE_MENU;
            break;


        case STATE_GAMEOVER:

            if (IsKeyPressed(KEY_ENTER))
            {
                MatchHistory currentMatch;

                currentMatch.score = game.score;
                currentMatch.lines = game.lines;
                currentMatch.level = game.level;
                currentMatch.timestamp = time(NULL);

                if (isEasyMode) // ADICIONADO: Condicional para salvar no arquivo correspondente ao modo jogado
                { // ADICIONADO
                    SaveHistory(currentMatch, HISTORY_EASY_FILE); // ADICIONADO: Salva o registro no histórico separado do modo fácil
                } // ADICIONADO
                else // ADICIONADO
                { // ADICIONADO
                    SaveHistory(currentMatch, HISTORY_FILE); // MODIFICADO: Passa o arquivo do histórico normal por parâmetro
                } // ADICIONADO

                game.state = STATE_MENU;
                menuIndex = 0;
            }

            break;
        }

        // Renderização Centralizada
        BeginDrawing();

        // Hack técnico limpo: engana o DrawGame do render.c para desenhar o fundo e os blocos de Tetris perfeitamente no modo fácil // ADICIONADO
        bool wasEasyGame = (game.state == STATE_GAME_EASY); // ADICIONADO
        if (wasEasyGame) game.state = STATE_GAME; // ADICIONADO

        DrawGame(&game, menuIndex);

        if (wasEasyGame) game.state = STATE_GAME_EASY; // ADICIONADO: Restaura o estado verdadeiro após desenhar o grid do jogo

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
                WHITE);

            DrawText(
                "Pressione P para continuar",
                sw / 2 - MeasureText("Pressione P para continuar", (int)(20 * s)) / 2,
                sh / 2 + (int)(20 * s),
                (int)(20 * s),
                LIGHTGRAY);
        }

        else if (game.state == STATE_QUESTION)
        {
            DrawRectangle(0, 0, sw, sh, (Color){10, 10, 25, 240});

            Rectangle qBox = {
                sw * 0.1f,
                sh * 0.15f,
                sw * 0.8f,
                sh * 0.7f};

            DrawRectangleLinesEx(
                qBox,
                3 * s,
                showFeedback ? (isCorrect ? GREEN : RED) : COLOR_TEXT);

            DrawText(
                "DESAFIO DE C",
                sw / 2 - MeasureText("DESAFIO DE C", (int)(35 * s)) / 2,
                (int)(qBox.y + 40 * s),
                (int)(35 * s),
                COLOR_TEXT);

            DrawText(
                currentQuestion.question,
                sw / 2 - MeasureText(currentQuestion.question, (int)(22 * s)) / 2,
                (int)(qBox.y + 120 * s),
                (int)(22 * s),
                WHITE);

            // Input Box
            Rectangle iBox = {
                sw / 2 - 250 * s,
                qBox.y + 220 * s,
                500 * s,
                60 * s};

            DrawRectangleRec(iBox, COLOR_PANEL);

            DrawRectangleLinesEx(
                iBox,
                2 * s,
                showFeedback ? (isCorrect ? GREEN : RED) : WHITE);

            DrawText(
                userInput,
                (int)(iBox.x + 15 * s),
                (int)(iBox.y + 15 * s),
                (int)(30 * s),
                COLOR_TEXT);

            // Cursor piscante
            if (!showFeedback && ((int)(GetTime() * 2) % 2 == 0))
            {
                int textWidth = MeasureText(userInput, (int)(30 * s));

                DrawRectangle(
                    (int)(iBox.x + 15 * s + textWidth + 2 * s),
                    (int)(iBox.y + 15 * s),
                    (int)(2 * s),
                    (int)(30 * s),
                    COLOR_TEXT);
            }

            // Barra de Tempo
            float timerWidth = (questionTimer / 15.0f) * 500 * s;

            DrawRectangle(
                (int)(sw / 2 - 250 * s),
                (int)(iBox.y + 70 * s),
                (int)timerWidth,
                (int)(5 * s),
                (questionTimer < 5) ? RED : GREEN);

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
                    fColor);

                if (!isCorrect)
                {
                    char ans[128];

                    sprintf(ans, "A resposta era: %s", currentQuestion.answers[0]);

                    DrawText(
                        ans,
                        sw / 2 - MeasureText(ans, (int)(20 * s)) / 2,
                        (int)(qBox.y + 410 * s),
                        (int)(20 * s),
                        LIGHTGRAY);
                }
            }
        }

        else if (game.state == STATE_QUESTION_EASY) // ADICIONADO: Renderização visual da tela de perguntas do Modo Easy (Alternativas)
        { // ADICIONADO
            DrawRectangle(0, 0, sw, sh, (Color){10, 20, 15, 240}); // ADICIONADO: Fundo escuro com uma tonalidade esverdeada para mudar a estética

            Rectangle qBox = { sw * 0.1f, sh * 0.15f, sw * 0.8f, sh * 0.7f }; // ADICIONADO: Caixa centralizada
            DrawRectangleLinesEx(qBox, 3 * s, showFeedback ? (isCorrect ? GREEN : RED) : COLOR_TEXT); // ADICIONADO

            DrawText("CURIOSIDADES GERAIS", sw / 2 - MeasureText("CURIOSIDADES GERAIS", (int)(35 * s)) / 2, (int)(qBox.y + 40 * s), (int)(35 * s), COLOR_TEXT); // ADICIONADO

            DrawText(currentQuestion.question, sw / 2 - MeasureText(currentQuestion.question, (int)(22 * s)) / 2, (int)(qBox.y + 110 * s), (int)(22 * s), WHITE); // ADICIONADO

            // ADICIONADO: Loop para gerar e alinhar na tela dinamicamente as 4 caixas com as alternativas (A, B, C, D)
            for (int i = 0; i < 4; i++) // ADICIONADO
            { // ADICIONADO
                Rectangle optBox = { sw / 2 - 250 * s, qBox.y + 180 * s + i * (50 * s), 500 * s, 42 * s }; // ADICIONADO
                DrawRectangleRec(optBox, COLOR_PANEL); // ADICIONADO
                DrawRectangleLinesEx(optBox, 1 * s, WHITE); // ADICIONADO
                
                char optText[256]; // ADICIONADO
                sprintf(optText, "%c) %s", 'A' + i, currentQuestion.answers[i]); // ADICIONADO: Renderiza como "A) Opção", "B) Opção", etc.
                DrawText(optText, (int)(optBox.x + 15 * s), (int)(optBox.y + 12 * s), (int)(16 * s), WHITE); // ADICIONADO
            } // ADICIONADO

            // ADICIONADO: Barra de tempo correndo na parte inferior da caixa de pergunta
            float timerWidth = (questionTimer / 15.0f) * 500 * s; // ADICIONADO
            DrawRectangle((int)(sw / 2 - 250 * s), (int)(qBox.y + 395 * s), (int)timerWidth, (int)(5 * s), (questionTimer < 5) ? RED : GREEN); // ADICIONADO

            if (showFeedback) // ADICIONADO
            { // ADICIONADO
                Color fColor = isCorrect ? GREEN : RED; // ADICIONADO
                const char *fText = isCorrect ? "RESPOSTA CORRETA!" : "RESPOSTA INCORRETA!"; // ADICIONADO

                DrawText(fText, sw / 2 - MeasureText(fText, (int)(40 * s)) / 2, (int)(qBox.y + 450 * s), (int)(40 * s), fColor); // ADICIONADO
            } // ADICIONADO
        } // ADICIONADO

        else if (game.state == STATE_GAMEOVER)
        {
            DrawRectangle(0, 0, sw, sh, (Color){20, 5, 5, 230});

            DrawText(
                "GAME OVER",
                sw / 2 - MeasureText("GAME OVER", (int)(80 * s)) / 2,
                (int)(sh * 0.35f),
                (int)(80 * s),
                RED);

            char finalScore[64];

            sprintf(finalScore, "PONTUACAO FINAL: %d", game.score);

            DrawText(
                finalScore,
                sw / 2 - MeasureText(finalScore, (int)(30 * s)) / 2,
                (int)(sh * 0.5f),
                (int)(30 * s),
                WHITE);

            DrawText(
                "Pressione ENTER para voltar ao menu",
                sw / 2 - MeasureText("Pressione ENTER para voltar ao menu", (int)(20 * s)) / 2,
                (int)(sh * 0.7f),
          0.5f,
                (int)(20 * s),
                LIGHTGRAY);
        }

        else if (game.state == STATE_REPORT)
        {
            DrawRectangle(0, 0, sw, sh, (Color){15, 15, 30, 255});

            DrawText(
                "ESTATISTICAS",
                sw / 2 - MeasureText("ESTATISTICAS", (int)(35 * s)) / 2,
                (int)(sh * 0.1f),
                (int)(35 * s),
                COLOR_TEXT);

            if (stats.totalMatches == 0)
            {
                DrawText(
                    "Nenhuma partida registrada.",
                    sw / 2 - MeasureText("Nenhuma partida registrada.", (int)(20 * s)) / 2,
                    (int)(sh / 2),
                    (int)(20 * s),
                    LIGHTGRAY);
            }
            else
            {
                char buf[128];

                sprintf(buf, "Partidas jogadas: %d", stats.totalMatches);
                DrawText(buf, sw / 2 - MeasureText(buf, (int)(20 * s)) / 2,
                         (int)(sh * 0.25f), (int)(20 * s), WHITE);

                sprintf(buf, "Media de pontuacao: %.1f", stats.averageScore);
                DrawText(buf, sw / 2 - MeasureText(buf, (int)(20 * s)) / 2,
                         (int)(sh * 0.35f), (int)(20 * s), WHITE);

                sprintf(buf, "Melhor pontuacao: %d", stats.bestScore);
                DrawText(buf, sw / 2 - MeasureText(buf, (int)(20 * s)) / 2,
                         (int)(sh * 0.45f), (int)(20 * s), GREEN);

                sprintf(buf, "Pior pontuacao: %d", stats.worstScore);
                DrawText(buf, sw / 2 - MeasureText(buf, (int)(20 * s)) / 2,
                         (int)(sh * 0.55f), (int)(20 * s), RED);

                sprintf(buf, "Desvio padrao: %.1f", stats.standardDeviation);
                DrawText(buf, sw / 2 - MeasureText(buf, (int)(20 * s)) / 2,
                         (int)(sh * 0.65f), (int)(20 * s), YELLOW);

                DrawText(stats.heuristicMessage,
                         sw / 2 - MeasureText(stats.heuristicMessage, (int)(18 * s)) / 2,
                         (int)(sh * 0.75f), (int)(18 * s), LIGHTGRAY);
            }

            DrawText(
                "Pressione ENTER ou ESC para voltar",
                sw / 2 - MeasureText("Pressione ENTER ou ESC para voltar", (int)(18 * s)) / 2,
                (int)(sh * 0.9f),
                (int)(18 * s),
                LIGHTGRAY);
        }

        else if (game.state == STATE_HISTORY)
        {
            DrawRectangle(0, 0, sw, sh, (Color){10, 10, 25, 255});

            DrawText(
                "HISTORICO DE PARTIDAS",
                sw / 2 - MeasureText("HISTORICO DE PARTIDAS", (int)(35 * s)) / 2,
                (int)(sh * 0.08f),
                (int)(35 * s),
                COLOR_TEXT);

            if (game.historyCount == 0)
            {
                DrawText(
                    "Nenhuma partida registrada.",
                    sw / 2 - MeasureText("Nenhuma partida registrada.", (int)(20 * s)) / 2,
                    sh / 2,
                    (int)(20 * s),
                    LIGHTGRAY);
            }
            else
            {
                int displayCount = (game.historyCount > 10) ? 10 : game.historyCount;
                int startIndex = game.historyCount - displayCount;
                for (int i = startIndex; i < game.historyCount; i++)
                {
                    char line[128];
                    char dateStr[32];

                    struct tm *timeInfo = localtime(&game.history[i].timestamp);

                    strftime(
                        dateStr,
                        sizeof(dateStr),
                        "%d/%m/%Y %H:%M",
                        timeInfo);

                    sprintf(
                        line,
                        "%d. Score: %d | Linhas: %d | Nivel: %d | %s",
                        i - startIndex + 1,
                        game.history[i].score,
                        game.history[i].lines,
                        game.history[i].level,
                        dateStr);

                    DrawText(
                        line,
                        sw / 2 - MeasureText(line, (int)(16 * s)) / 2,
                        (int)(sh * 0.2f) + (i - startIndex) * (int)(35 * s),
                        (int)(16 * s),
                        WHITE);
                }
            }

            DrawText(
                "Pressione ENTER ou ESC para voltar",
                sw / 2 - MeasureText("Pressione ENTER ou ESC para voltar", (int)(18 * s)) / 2,
                (int)(sh * 0.9f),
                (int)(18 * s),
                LIGHTGRAY);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}