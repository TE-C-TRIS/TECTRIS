#include "audio_fx.h"
#include <stdio.h>
#include <string.h>

// Tenta localizar os assets independente de onde o executavel foi chamado
// (raiz do projeto, build/, build/bin/, etc.)
static const char *kSearchPrefixes[] = { "", "../", "../../", "../../../" };
static const int kSearchPrefixCount = 4;

static bool ResolveAssetPath(const char *relPath, char *outPath, int outSize) {
    for (int i = 0; i < kSearchPrefixCount; i++) {
        snprintf(outPath, outSize, "%s%s", kSearchPrefixes[i], relPath);
        if (FileExists(outPath)) return true;
    }
    return false;
}

static Sound LoadSoundFlex(const char *relPath) {
    char path[256];
    if (ResolveAssetPath(relPath, path, sizeof(path))) {
        return LoadSound(path);
    }
    TraceLog(LOG_WARNING, "AUDIO: arquivo nao encontrado (%s) - efeito ficara silencioso.", relPath);
    Sound empty = { 0 };
    return empty;
}

static Music LoadMusicFlex(const char *relPath) {
    char path[256];
    if (ResolveAssetPath(relPath, path, sizeof(path))) {
        return LoadMusicStream(path);
    }
    TraceLog(LOG_WARNING, "AUDIO: musica nao encontrada (%s) - jogo seguira sem trilha.", relPath);
    Music empty = { 0 };
    return empty;
}

void InitAudioAssets(AudioAssets *audio) {
    InitAudioDevice();

    audio->music = LoadMusicFlex("assets/audio/music_loop.wav");
    audio->sfxCorrect = LoadSoundFlex("assets/audio/sfx_correct.wav");
    audio->sfxWrong = LoadSoundFlex("assets/audio/sfx_wrong.wav");
    audio->sfxLock = LoadSoundFlex("assets/audio/sfx_lock.wav");
    audio->sfxLineClear = LoadSoundFlex("assets/audio/sfx_lineclear.wav");
    audio->sfxPenalty = LoadSoundFlex("assets/audio/sfx_penalty.wav");
    audio->sfxWarning = LoadSoundFlex("assets/audio/sfx_warning.wav");
    audio->sfxGameOver = LoadSoundFlex("assets/audio/sfx_gameover.wav");
    audio->sfxWin = LoadSoundFlex("assets/audio/sfx_win.wav");
    audio->sfxSelect = LoadSoundFlex("assets/audio/sfx_select.wav");
    audio->sfxOpenInput = LoadSoundFlex("assets/audio/sfx_open_input.wav");

    audio->musicEnabled = true;
    audio->sfxEnabled = true;
    audio->loaded = true;

    if (audio->music.stream.buffer != NULL) {
        SetMusicVolume(audio->music, 0.32f);
        audio->music.looping = true;
        PlayMusicStream(audio->music);
    }
}

void UpdateAudioAssets(AudioAssets *audio) {
    if (!audio->loaded) return;
    if (audio->musicEnabled && audio->music.stream.buffer != NULL) {
        UpdateMusicStream(audio->music);
    }
}

void UnloadAudioAssets(AudioAssets *audio) {
    if (!audio->loaded) return;
    if (audio->music.stream.buffer != NULL) UnloadMusicStream(audio->music);
    UnloadSound(audio->sfxCorrect);
    UnloadSound(audio->sfxWrong);
    UnloadSound(audio->sfxLock);
    UnloadSound(audio->sfxLineClear);
    UnloadSound(audio->sfxPenalty);
    UnloadSound(audio->sfxWarning);
    UnloadSound(audio->sfxGameOver);
    UnloadSound(audio->sfxWin);
    UnloadSound(audio->sfxSelect);
    UnloadSound(audio->sfxOpenInput);
    CloseAudioDevice();
    audio->loaded = false;
}

void ToggleMusic(AudioAssets *audio) {
    audio->musicEnabled = !audio->musicEnabled;
    if (audio->music.stream.buffer == NULL) return;
    if (audio->musicEnabled) {
        ResumeMusicStream(audio->music);
    } else {
        PauseMusicStream(audio->music);
    }
}

void ToggleSfx(AudioAssets *audio) {
    audio->sfxEnabled = !audio->sfxEnabled;
}

void PlayFx(AudioAssets *audio, Sound sound) {
    if (!audio->sfxEnabled) return;
    if (sound.stream.buffer == NULL) return;
    PlaySound(sound);
}
