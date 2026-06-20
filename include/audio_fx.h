#ifndef AUDIO_FX_H
#define AUDIO_FX_H

#include "raylib.h"
#include <stdbool.h>

// Conjunto de todos os assets de audio do jogo. Carregados uma unica vez
// no inicio do programa e descarregados ao fechar.
typedef struct {
    Music music;          // trilha de fundo (loop automatico via raylib)
    Sound sfxCorrect;
    Sound sfxWrong;
    Sound sfxLock;
    Sound sfxLineClear;
    Sound sfxPenalty;     // linha de penalidade adicionada / ataque ao adversario
    Sound sfxWarning;     // kill line subindo (perigo)
    Sound sfxGameOver;
    Sound sfxWin;
    Sound sfxSelect;      // navegacao de menu
    Sound sfxOpenInput;   // jogador abriu a caixa de resposta (multiplayer)

    bool musicEnabled;
    bool sfxEnabled;
    bool loaded;
} AudioAssets;

// Inicializa o dispositivo de audio e carrega todos os assets de assets/audio/.
// Se algum arquivo nao for encontrado, o jogo continua rodando silenciosamente
// (nao trava por falta de audio).
void InitAudioAssets(AudioAssets *audio);

// Deve ser chamada uma vez por frame (necessario para o streaming de musica).
void UpdateAudioAssets(AudioAssets *audio);

void UnloadAudioAssets(AudioAssets *audio);

// Liga/desliga musica e efeitos independentemente.
void ToggleMusic(AudioAssets *audio);
void ToggleSfx(AudioAssets *audio);

// Toca um efeito sonoro respeitando o estado de sfxEnabled.
void PlayFx(AudioAssets *audio, Sound sound);

#endif // AUDIO_FX_H
