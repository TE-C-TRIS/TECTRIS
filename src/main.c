#include "common.h"
#include "game.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "history.h"
#include "stats.h"
#include "audio_fx.h"
#include <time.h>

// ADICIONADO: Declaração externa da função do seu novo arquivo "questions_modo_easy.c"
PerguntaEasy GetRandomQuestionEasy();
bool ValidateAnswerEasy(int escolhaJogador, const PerguntaEasy* q);

int main()
{
    // Configuração de Janela Redimensionável
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(800, 700, "Tectris - Aprenda C Jogando");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL); // ESC e usado como "voltar" em varias telas; sem isso o raylib fecha a janela ao apertar ESC em qualquer lugar

    GameContext game;
    InitGame(&game);
    int menuIndex = 0;
    bool isEasyMode = false; // ADICIONADO: Variável flag para saber se a partida atual é do modo fácil ou do modo C
    MatchHistory history[MAX_HISTORY_RECORDS];
    int historyCount = 0;
    GameStats stats;
    int scoresArr[MAX_HISTORY_RECORDS];

    Question currentQuestion;
    PerguntaEasy currentEasyQuestion;
    char userInput[64] = "\0";
    int letterCount = 0;
    float questionTimer = 0;
    bool isCorrect = false;
    bool showFeedback = false;
    float feedbackTimer = 0;
    float nextQuestionTimer = 20.0f; // Tempo entre perguntas

    // ===== NOVO: Audio (musica + efeitos sonoros) =====
    AudioAssets audio;
    InitAudioAssets(&audio);

    // ===== NOVO: Estado de pausa generico (volta para o estado certo, inclusive multiplayer) =====
    GameState pauseReturnState = STATE_GAME;

    // ===== NOVO: Entrada de nome (single-player) e ranking unificado =====
    char nameInput[24] = "\0";
    int nameLetters = 0;
    RankingEntry rankingBuf[MAX_RANKING_RECORDS];
    int rankingCount = 0;

    // ===== NOVO: Efeitos visuais do modo single-player (popup + flash de acerto/erro) =====
    PopupSystem popsSingle;
    InitPopupSystem(&popsSingle);
    FlashEffect flashSingle = {0};

    // ===== NOVO: Multiplayer local =====
    char multiP1Name[24] = "\0";
    char multiP2Name[24] = "\0";
    int multiNameLetters = 0;
    int multiNameStep = 0; // 0 = digitando nome do J1, 1 = digitando nome do J2

    GameContext gameP1, gameP2;
    InitGame(&gameP1);
    InitGame(&gameP2);

    PopupSystem popsP1, popsP2;
    InitPopupSystem(&popsP1);
    InitPopupSystem(&popsP2);
    FlashEffect flashP1 = {0}, flashP2 = {0};

    MultiQuestionState mq;
    memset(&mq, 0, sizeof(mq));
    float multiQuestionInterval = 0;
    bool multiResultSaved = false;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        UpdateAudioAssets(&audio);
        UpdatePopups(&popsSingle, dt);
        UpdateFlash(&flashSingle, dt);
        UpdatePopups(&popsP1, dt);
        UpdatePopups(&popsP2, dt);
        UpdateFlash(&flashP1, dt);
        UpdateFlash(&flashP2, dt);

        // Atalhos globais de musica/efeitos - desativados enquanto o jogador esta digitando texto
        bool isTypingText = (game.state == STATE_QUESTION) ||
                             (game.state == STATE_NAME_ENTRY) ||
                             (game.state == STATE_MULTI_NAME_ENTRY) ||
                             (game.state == STATE_MULTI_QUESTION && mq.activeTurn != TURN_NONE);
        if (!isTypingText) {
            if (IsKeyPressed(KEY_M)) ToggleMusic(&audio);
            if (IsKeyPressed(KEY_N)) ToggleSfx(&audio);
        }

        // Máquina de Estados
        switch (game.state)
        {
        case STATE_MENU:
            if (IsKeyPressed(KEY_DOWN))
            {
                menuIndex++;
                PlayFx(&audio, audio.sfxSelect);
                if (menuIndex > 7) // 8 opcoes no total (0..7)
                    menuIndex = 0;
            }

            if (IsKeyPressed(KEY_UP))
            {
                menuIndex--;
                PlayFx(&audio, audio.sfxSelect);
                if (menuIndex < 0)
                    menuIndex = 7;
            }

            if (IsKeyPressed(KEY_ENTER))
            {

                if (menuIndex == 0) // Jogar (Desafio de C)
                {
                    isEasyMode = false;
                    InitGame(&game);
                    nameInput[0] = '\0';
                    nameLetters = 0;
                    game.state = STATE_NAME_ENTRY;
                }

                else if (menuIndex == 1) // Modo Easy (Curiosidades)
                {
                    isEasyMode = true;
                    InitGame(&game);
                    nameInput[0] = '\0';
                    nameLetters = 0;
                    game.state = STATE_NAME_ENTRY;
                }

                else if (menuIndex == 2) // Multiplayer Local
                {
                    InitGame(&gameP1);
                    InitGame(&gameP2);
                    multiP1Name[0] = '\0';
                    multiP2Name[0] = '\0';
                    multiNameLetters = 0;
                    multiNameStep = 0;
                    multiResultSaved = false;
                    game.state = STATE_MULTI_NAME_ENTRY;
                }

                else if (menuIndex == 3) // Ranking Geral
                {
                    rankingCount = LoadRanking(rankingBuf, MAX_RANKING_RECORDS);
                    SortRankingByScoreDesc(rankingBuf, rankingCount);
                    game.state = STATE_RANKING;
                }

                else if (menuIndex == 4) // Historico - Desafio de C
                {
                    game.historyCount = LoadHistoryEx(game.history, MAX_HISTORY_RECORDS, HISTORY_FILE);
                    game.state = STATE_HISTORY;
                }

                else if (menuIndex == 5) // Historico - Modo Easy
                {
                    game.historyCount = LoadHistoryEx(game.history, MAX_HISTORY_RECORDS, HISTORY_EASY_FILE);
                    game.state = STATE_HISTORY;
                }

                else if (menuIndex == 6) // Analisar Estatisticas
                {
                    historyCount = LoadHistoryEx(history, MAX_HISTORY_RECORDS, HISTORY_FILE);

                    stats.totalMatches = historyCount;
                    stats.averageScore = CalculateAverageScore(history, historyCount);
                    stats.bestScore = CalculateBestScore(history, historyCount);
                    stats.worstScore = CalculateWorstScore(history, historyCount);
                    stats.standardDeviation = CalculateStandardDeviation(history, historyCount, stats.averageScore);

                    for (int i = 0; i < historyCount; i++)
                    {
                        scoresArr[i] = history[i].score;
                    }

                    GenerateHeuristic(&stats);
                    game.state = STATE_REPORT;
                }

                else if (menuIndex == 7) // Sair
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
            if (IsKeyPressed(KEY_P)) {
                pauseReturnState = STATE_GAME;
                game.state = STATE_PAUSE;
            }

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

                int linesBefore = game.lines;
                MergePiece(&game);
                if (game.state == STATE_GAMEOVER) PlayFx(&audio, audio.sfxGameOver);
                else if (game.lines > linesBefore) PlayFx(&audio, audio.sfxLineClear);
                else PlayFx(&audio, audio.sfxLock);
            }

            {
                int linesBefore = game.lines;
                GameState stateBefore = game.state;
                UpdateGame(&game, dt);
                if (game.state == STATE_GAMEOVER && stateBefore != STATE_GAMEOVER) PlayFx(&audio, audio.sfxGameOver);
                else if (game.lines > linesBefore) PlayFx(&audio, audio.sfxLineClear);
            }

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
            if (IsKeyPressed(KEY_P)) { // ADICIONADO
                pauseReturnState = STATE_GAME_EASY;
                game.state = STATE_PAUSE; // ADICIONADO
            }

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
                int linesBeforeEasy = game.lines;
                MergePiece(&game); // ADICIONADO
                if (game.state == STATE_GAMEOVER) PlayFx(&audio, audio.sfxGameOver);
                else if (game.lines > linesBeforeEasy) PlayFx(&audio, audio.sfxLineClear);
                else PlayFx(&audio, audio.sfxLock);
            } // ADICIONADO

            // Hack técnico limpo: altera temporariamente o estado interno para rodar a física do game.c perfeitamente // ADICIONADO
            GameState previousState = game.state; // ADICIONADO
            game.state = STATE_GAME; // ADICIONADO
            {
                int linesBeforeEasy2 = game.lines;
                UpdateGame(&game, dt); // ADICIONADO
                if (game.state == STATE_GAMEOVER) PlayFx(&audio, audio.sfxGameOver);
                else if (game.lines > linesBeforeEasy2) PlayFx(&audio, audio.sfxLineClear);
            }
            if (game.state == STATE_GAME) game.state = previousState; // ADICIONADO: Se não deu Game Over, devolve para o modo fácil

            nextQuestionTimer -= dt; // ADICIONADO

            if (nextQuestionTimer <= 0) // ADICIONADO
            { // ADICIONADO
                game.state = STATE_QUESTION_EASY; // ADICIONADO: Direciona para o novo estado de pergunta fácil
                currentEasyQuestion = GetRandomQuestionEasy(); // ADICIONADO: Sorteia as perguntas de curiosidades gerais

                userInput[0] = '\0'; // ADICIONADO
                letterCount = 0; // ADICIONADO
                questionTimer = 15.0f; // ADICIONADO
                showFeedback = false; // ADICIONADO

                nextQuestionTimer = 25.0f; // ADICIONADO
            } // ADICIONADO
            break; // ADICIONADO

        case STATE_PAUSE:
            if (IsKeyPressed(KEY_P))
                game.state = pauseReturnState; // Retorna para o estado correto, inclusive multiplayer

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
                    PlayFx(&audio, audio.sfxWrong);
                    TriggerFlash(&flashSingle, RED, 0.4f);
                    AddPopup(&popsSingle, "Tempo esgotado", RED);
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
                        PlayFx(&audio, audio.sfxCorrect);
                        TriggerFlash(&flashSingle, GREEN, 0.4f);
                        AddPopup(&popsSingle, "+150", GREEN);
                    }
                    else
                    {
                        AddPenaltyLine(&game);
                        PlayFx(&audio, audio.sfxWrong);
                        TriggerFlash(&flashSingle, RED, 0.4f);
                        AddPopup(&popsSingle, "Penalidade", RED);
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
                    PlayFx(&audio, audio.sfxWrong);
                    TriggerFlash(&flashSingle, RED, 0.4f);
                    AddPopup(&popsSingle, "Tempo esgotado", RED);
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
                    isCorrect = ValidateAnswerEasy(selectedAnswer, &currentEasyQuestion); // ADICIONADO: Valida se a alternativa bate com a correta

                    showFeedback = true; // ADICIONADO
                    feedbackTimer = 2.5f; // ADICIONADO

                    if (isCorrect) // ADICIONADO
                    { // ADICIONADO
                        game.score += 150; // ADICIONADO
                        RemovePenaltyLine(&game); // ADICIONADO
                        PlayFx(&audio, audio.sfxCorrect);
                        TriggerFlash(&flashSingle, GREEN, 0.4f);
                        AddPopup(&popsSingle, "+150", GREEN);
                    } // ADICIONADO
                    else // ADICIONADO
                    { // ADICIONADO
                        AddPenaltyLine(&game); // ADICIONADO
                        PlayFx(&audio, audio.sfxWrong);
                        TriggerFlash(&flashSingle, RED, 0.4f);
                        AddPopup(&popsSingle, "Penalidade", RED);
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
                    SaveHistoryEx(currentMatch, HISTORY_EASY_FILE); // ADICIONADO: Salva o registro no histórico separado do modo fácil
                } // ADICIONADO
                else // ADICIONADO
                { // ADICIONADO
                    SaveHistoryEx(currentMatch, HISTORY_FILE); // MODIFICADO: Passa o arquivo do histórico normal por parâmetro
                } // ADICIONADO

                // NOVO: tambem salva no Ranking Geral unificado (com nome + indicador de modo)
                RankingEntry rEntry;
                strncpy(rEntry.name, game.playerName[0] ? game.playerName : "Jogador", RANKING_NAME_LEN - 1);
                rEntry.name[RANKING_NAME_LEN - 1] = '\0';
                rEntry.score = game.score;
                rEntry.lines = game.lines;
                rEntry.level = game.level;
                strncpy(rEntry.mode, isEasyMode ? MODE_EASY : MODE_C, RANKING_MODE_LEN - 1);
                rEntry.mode[RANKING_MODE_LEN - 1] = '\0';
                rEntry.timestamp = time(NULL);
                SaveRankingEntry(rEntry);

                game.state = STATE_MENU;
                menuIndex = 0;
            }

            break;

        case STATE_NAME_ENTRY:
        {
            int key = GetCharPressed();
            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (nameLetters < 23))
                {
                    nameInput[nameLetters] = (char)key;
                    nameInput[nameLetters + 1] = '\0';
                    nameLetters++;
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && nameLetters > 0)
            {
                nameLetters--;
                nameInput[nameLetters] = '\0';
            }

            if (IsKeyPressed(KEY_ENTER) && nameLetters > 0)
            {
                SanitizePlayerName(nameInput);
                strncpy(game.playerName, nameInput, sizeof(game.playerName) - 1);
                game.playerName[sizeof(game.playerName) - 1] = '\0';
                PlayFx(&audio, audio.sfxSelect);
                game.state = isEasyMode ? STATE_GAME_EASY : STATE_GAME;
            }

            if (IsKeyPressed(KEY_ESCAPE))
            {
                game.state = STATE_MENU;
            }
            break;
        }

        case STATE_MULTI_NAME_ENTRY:
        {
            char *activeBuf = (multiNameStep == 0) ? multiP1Name : multiP2Name;

            int key = GetCharPressed();
            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (multiNameLetters < 23))
                {
                    activeBuf[multiNameLetters] = (char)key;
                    activeBuf[multiNameLetters + 1] = '\0';
                    multiNameLetters++;
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && multiNameLetters > 0)
            {
                multiNameLetters--;
                activeBuf[multiNameLetters] = '\0';
            }

            if (IsKeyPressed(KEY_ENTER) && multiNameLetters > 0)
            {
                SanitizePlayerName(activeBuf);
                PlayFx(&audio, audio.sfxSelect);

                if (multiNameStep == 0)
                {
                    multiNameStep = 1;
                    multiNameLetters = 0;
                }
                else
                {
                    strncpy(gameP1.playerName, multiP1Name, sizeof(gameP1.playerName) - 1);
                    gameP1.playerName[sizeof(gameP1.playerName) - 1] = '\0';
                    strncpy(gameP2.playerName, multiP2Name, sizeof(gameP2.playerName) - 1);
                    gameP2.playerName[sizeof(gameP2.playerName) - 1] = '\0';

                    gameP1.state = STATE_GAME;
                    gameP2.state = STATE_GAME;
                    InitPopupSystem(&popsP1);
                    InitPopupSystem(&popsP2);
                    flashP1.timer = 0;
                    flashP2.timer = 0;
                    memset(&mq, 0, sizeof(mq));
                    multiQuestionInterval = 24.0f;
                    multiResultSaved = false;

                    game.state = STATE_MULTI_GAME;
                }
            }

            if (IsKeyPressed(KEY_ESCAPE))
            {
                game.state = STATE_MENU;
            }
            break;
        }

        case STATE_MULTI_GAME:
        {
            if (IsKeyPressed(KEY_P)) {
                pauseReturnState = STATE_MULTI_GAME;
                game.state = STATE_PAUSE;
                break;
            }

            // ----- Jogador 1: WASD + Espaco -----
            if (IsKeyPressed(KEY_A)) { if (!CheckCollision(&gameP1, gameP1.currentPiece, -1, 0)) gameP1.currentPiece.pos.x--; }
            if (IsKeyPressed(KEY_D)) { if (!CheckCollision(&gameP1, gameP1.currentPiece, 1, 0)) gameP1.currentPiece.pos.x++; }
            if (IsKeyPressed(KEY_S)) { if (!CheckCollision(&gameP1, gameP1.currentPiece, 0, 1)) gameP1.currentPiece.pos.y++; }
            if (IsKeyPressed(KEY_W)) { TryRotate(&gameP1); }
            if (IsKeyPressed(KEY_SPACE))
            {
                while (!CheckCollision(&gameP1, gameP1.currentPiece, 0, 1)) gameP1.currentPiece.pos.y++;
                int linesBeforeP1 = gameP1.lines;
                MergePiece(&gameP1);
                if (gameP1.state == STATE_GAMEOVER) PlayFx(&audio, audio.sfxGameOver);
                else if (gameP1.lines > linesBeforeP1) PlayFx(&audio, audio.sfxLineClear);
                else PlayFx(&audio, audio.sfxLock);
            }

            // ----- Jogador 2: Setas + Enter -----
            if (IsKeyPressed(KEY_LEFT)) { if (!CheckCollision(&gameP2, gameP2.currentPiece, -1, 0)) gameP2.currentPiece.pos.x--; }
            if (IsKeyPressed(KEY_RIGHT)) { if (!CheckCollision(&gameP2, gameP2.currentPiece, 1, 0)) gameP2.currentPiece.pos.x++; }
            if (IsKeyPressed(KEY_DOWN)) { if (!CheckCollision(&gameP2, gameP2.currentPiece, 0, 1)) gameP2.currentPiece.pos.y++; }
            if (IsKeyPressed(KEY_UP)) { TryRotate(&gameP2); }
            if (IsKeyPressed(KEY_ENTER))
            {
                while (!CheckCollision(&gameP2, gameP2.currentPiece, 0, 1)) gameP2.currentPiece.pos.y++;
                int linesBeforeP2 = gameP2.lines;
                MergePiece(&gameP2);
                if (gameP2.state == STATE_GAMEOVER) PlayFx(&audio, audio.sfxGameOver);
                else if (gameP2.lines > linesBeforeP2) PlayFx(&audio, audio.sfxLineClear);
                else PlayFx(&audio, audio.sfxLock);
            }

            // ----- Gravidade automatica (reaproveita UpdateGame para os dois) -----
            {
                int l1Before = gameP1.lines;
                UpdateGame(&gameP1, dt);
                if (gameP1.lines > l1Before) PlayFx(&audio, audio.sfxLineClear);
            }
            {
                int l2Before = gameP2.lines;
                UpdateGame(&gameP2, dt);
                if (gameP2.lines > l2Before) PlayFx(&audio, audio.sfxLineClear);
            }

            // ----- Pergunta de logica periodica -----
            multiQuestionInterval -= dt;
            if (multiQuestionInterval <= 0 && gameP1.state == STATE_GAME && gameP2.state == STATE_GAME)
            {
                int qLevel = (gameP1.level > gameP2.level) ? gameP1.level : gameP2.level;
                mq.question = GetRandomQuestion(qLevel);
                mq.activeTurn = TURN_NONE;
                mq.p1Done = false; mq.p2Done = false;
                mq.p1Correct = false; mq.p2Correct = false;
                mq.p1Input[0] = '\0'; mq.p2Input[0] = '\0';
                mq.p1Letters = 0; mq.p2Letters = 0;
                mq.questionTimeMax = 22.0f;
                mq.questionTimer = mq.questionTimeMax;
                mq.showFeedback = false;
                game.state = STATE_MULTI_QUESTION;
            }

            // ----- Fim de partida: alguem violou a Kill Line -----
            if (gameP1.state == STATE_GAMEOVER || gameP2.state == STATE_GAMEOVER)
            {
                game.state = STATE_MULTI_GAMEOVER;
            }

            break;
        }

        case STATE_MULTI_QUESTION:
        {
            if (!mq.showFeedback)
            {
                mq.questionTimer -= dt;

                // So pode reivindicar a vez quem ainda nao tentou nessa pergunta.
                // Se o primeiro errar, a vez passa automaticamente pro outro.
                if (IsKeyPressed(KEY_S) && mq.activeTurn == TURN_NONE && !mq.p1Done)
                {
                    mq.activeTurn = TURN_P1;
                    PlayFx(&audio, audio.sfxOpenInput);
                }
                if (IsKeyPressed(KEY_DOWN) && mq.activeTurn == TURN_NONE && !mq.p2Done)
                {
                    mq.activeTurn = TURN_P2;
                    PlayFx(&audio, audio.sfxOpenInput);
                }

                if (mq.activeTurn == TURN_P1)
                {
                    int key = GetCharPressed();
                    while (key > 0)
                    {
                        if ((key >= 32) && (key <= 125) && (mq.p1Letters < 63))
                        {
                            mq.p1Input[mq.p1Letters] = (char)key;
                            mq.p1Input[mq.p1Letters + 1] = '\0';
                            mq.p1Letters++;
                        }
                        key = GetCharPressed();
                    }
                    if (IsKeyPressed(KEY_BACKSPACE) && mq.p1Letters > 0)
                    {
                        mq.p1Letters--;
                        mq.p1Input[mq.p1Letters] = '\0';
                    }
                    if (IsKeyPressed(KEY_ENTER) && mq.p1Letters > 0)
                    {
                        mq.p1Correct = ValidateAnswer(mq.p1Input, &mq.question);
                        mq.p1Done = true;
                        if (mq.p1Correct)
                        {
                            gameP1.score += 150;
                            RemovePenaltyLine(&gameP1);
                            AddPenaltyLine(&gameP2); // ataque ao adversario
                            PlayFx(&audio, audio.sfxCorrect);
                            TriggerFlash(&flashP1, GREEN, 0.4f);
                            TriggerFlash(&flashP2, ORANGE, 0.3f);
                            AddPopup(&popsP1, "+150", GREEN);
                        }
                        else
                        {
                            AddPenaltyLine(&gameP1);
                            PlayFx(&audio, audio.sfxWrong);
                            TriggerFlash(&flashP1, RED, 0.4f);
                            AddPopup(&popsP1, "Penalidade", RED);
                            if (!mq.p2Done) PlayFx(&audio, audio.sfxWarning); // avisa que a vez passou
                        }
                        mq.activeTurn = TURN_NONE;
                    }
                }
                else if (mq.activeTurn == TURN_P2)
                {
                    int key = GetCharPressed();
                    while (key > 0)
                    {
                        if ((key >= 32) && (key <= 125) && (mq.p2Letters < 63))
                        {
                            mq.p2Input[mq.p2Letters] = (char)key;
                            mq.p2Input[mq.p2Letters + 1] = '\0';
                            mq.p2Letters++;
                        }
                        key = GetCharPressed();
                    }
                    if (IsKeyPressed(KEY_BACKSPACE) && mq.p2Letters > 0)
                    {
                        mq.p2Letters--;
                        mq.p2Input[mq.p2Letters] = '\0';
                    }
                    if (IsKeyPressed(KEY_ENTER) && mq.p2Letters > 0)
                    {
                        mq.p2Correct = ValidateAnswer(mq.p2Input, &mq.question);
                        mq.p2Done = true;
                        if (mq.p2Correct)
                        {
                            gameP2.score += 150;
                            RemovePenaltyLine(&gameP2);
                            AddPenaltyLine(&gameP1); // ataque ao adversario
                            PlayFx(&audio, audio.sfxCorrect);
                            TriggerFlash(&flashP2, GREEN, 0.4f);
                            TriggerFlash(&flashP1, ORANGE, 0.3f);
                            AddPopup(&popsP2, "+150", GREEN);
                        }
                        else
                        {
                            AddPenaltyLine(&gameP2);
                            PlayFx(&audio, audio.sfxWrong);
                            TriggerFlash(&flashP2, RED, 0.4f);
                            AddPopup(&popsP2, "Penalidade", RED);
                            if (!mq.p1Done) PlayFx(&audio, audio.sfxWarning);
                        }
                        mq.activeTurn = TURN_NONE;
                    }
                }

                // Resolve a pergunta assim que alguem acertar (o outro nem precisa
                // responder), ou quando os dois ja tiverem tentado e errado.
                bool someoneCorrect = (mq.p1Done && mq.p1Correct) || (mq.p2Done && mq.p2Correct);
                bool bothAttempted = mq.p1Done && mq.p2Done;

                if (mq.questionTimer <= 0)
                {
                    if (!mq.p1Done) { mq.p1Done = true; mq.p1Correct = false; AddPenaltyLine(&gameP1); PlayFx(&audio, audio.sfxWrong); }
                    if (!mq.p2Done) { mq.p2Done = true; mq.p2Correct = false; AddPenaltyLine(&gameP2); PlayFx(&audio, audio.sfxWrong); }
                    mq.showFeedback = true;
                    mq.feedbackTimer = 2.2f;
                }
                else if (someoneCorrect || bothAttempted)
                {
                    mq.showFeedback = true;
                    mq.feedbackTimer = someoneCorrect ? 1.6f : 2.2f;
                }
            }
            else
            {
                mq.feedbackTimer -= dt;
                if (mq.feedbackTimer <= 0)
                {
                    game.state = STATE_MULTI_GAME;
                    multiQuestionInterval = 20.0f + (float)GetRandomValue(0, 8);
                }
            }
            break;
        }

        case STATE_MULTI_GAMEOVER:
        {
            if (!multiResultSaved)
            {
                multiResultSaved = true;
                PlayFx(&audio, audio.sfxWin);

                GameContext *winner;
                if (gameP1.state == STATE_GAMEOVER && gameP2.state == STATE_GAMEOVER)
                    winner = (gameP1.score >= gameP2.score) ? &gameP1 : &gameP2;
                else if (gameP1.state == STATE_GAMEOVER)
                    winner = &gameP2;
                else
                    winner = &gameP1;

                RankingEntry rEntry;
                strncpy(rEntry.name, winner->playerName[0] ? winner->playerName : "Jogador", RANKING_NAME_LEN - 1);
                rEntry.name[RANKING_NAME_LEN - 1] = '\0';
                rEntry.score = winner->score;
                rEntry.lines = winner->lines;
                rEntry.level = winner->level;
                strncpy(rEntry.mode, MODE_MULTI, RANKING_MODE_LEN - 1);
                rEntry.mode[RANKING_MODE_LEN - 1] = '\0';
                rEntry.timestamp = time(NULL);
                SaveRankingEntry(rEntry);
            }

            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE))
            {
                game.state = STATE_MENU;
                menuIndex = 0;
            }
            break;
        }

        case STATE_RANKING:
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE))
                game.state = STATE_MENU;
            break;
        }

        // Renderização Centralizada
        BeginDrawing();

        if (game.state == STATE_NAME_ENTRY)
        {
            DrawNameEntryScreen(isEasyMode ? "MODO EASY - CURIOSIDADES" : "DESAFIO DE C", nameInput, isEasyMode);
        }
        else if (game.state == STATE_MULTI_NAME_ENTRY)
        {
            DrawMultiNameEntryScreen(multiP1Name, multiP2Name, multiNameStep);
        }
        else if (game.state == STATE_MULTI_GAME || game.state == STATE_MULTI_QUESTION || game.state == STATE_MULTI_GAMEOVER)
        {
            DrawMultiplayerGame(&gameP1, &gameP2, &flashP1, &flashP2, &popsP1, &popsP2, multiQuestionInterval);

            if (game.state == STATE_MULTI_QUESTION)
            {
                DrawMultiQuestionOverlay(&mq, &gameP1, &gameP2);
            }
            else if (game.state == STATE_MULTI_GAMEOVER)
            {
                bool p1Won;
                if (gameP1.state == STATE_GAMEOVER && gameP2.state == STATE_GAMEOVER)
                    p1Won = (gameP1.score >= gameP2.score);
                else if (gameP1.state == STATE_GAMEOVER)
                    p1Won = false;
                else
                    p1Won = true;
                DrawMultiGameOverScreen(&gameP1, &gameP2, p1Won);
            }
        }
        else if (game.state == STATE_RANKING)
        {
            DrawRankingScreen(rankingBuf, rankingCount);
        }
        else
        {
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

            DrawText(currentEasyQuestion.pergunta, sw / 2 - MeasureText(currentEasyQuestion.pergunta, (int)(22 * s)) / 2, (int)(qBox.y + 110 * s), (int)(22 * s), WHITE); // ADICIONADO

            // ADICIONADO: Loop para gerar e alinhar na tela dinamicamente as 4 caixas com as alternativas (A, B, C, D)
            for (int i = 0; i < 4; i++) // ADICIONADO
            { // ADICIONADO
                Rectangle optBox = { sw / 2 - 250 * s, qBox.y + 180 * s + i * (50 * s), 500 * s, 42 * s }; // ADICIONADO
                DrawRectangleRec(optBox, COLOR_PANEL); // ADICIONADO
                DrawRectangleLinesEx(optBox, 1 * s, WHITE); // ADICIONADO
                
                char optText[256]; // ADICIONADO
                sprintf(optText, "%c) %s", 'A' + i, currentEasyQuestion.alternativas[i]); // ADICIONADO: Renderiza como "A) Opção", "B) Opção", etc.
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
        }

        EndDrawing();
    }

    UnloadAudioAssets(&audio);
    CloseWindow();

    return 0;
}