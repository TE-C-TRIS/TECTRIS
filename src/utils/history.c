#include "history.h"
#include "common.h"
#include <stdio.h>

void SaveHistory(MatchHistory data) {
    SaveHistoryEx(data, HISTORY_FILE);
}

void SaveHistoryEx(MatchHistory data, const char* filename) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        TraceLog(LOG_WARNING, "HISTORY: Nao foi possivel abrir o arquivo de historico para escrita.");
        return;
    }
    fprintf(file, "%d,%d,%d,%lld\n", data.score, data.lines, data.level, (long long)data.timestamp);
    fclose(file);
    TraceLog(LOG_INFO, "HISTORY: Partida salva no historico.");
}

int LoadHistory(MatchHistory *history, int maxCount) {
    return LoadHistoryEx(history, maxCount, HISTORY_FILE);
}

int LoadHistoryEx(MatchHistory *history, int maxCount, const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        TraceLog(LOG_WARNING, "HISTORY: Arquivo de historico nao encontrado");
        return 0;
    }
    int count = 0;
    while (count < maxCount) {
        int result = fscanf(file, "%d,%d,%d,%lld",
            &history[count].score,
            &history[count].lines,
            &history[count].level,
            (long long *)&history[count].timestamp);
        if (result != 4) break;
        count++;
    }
    fclose(file);
    return count;
}