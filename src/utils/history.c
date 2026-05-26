#include "history.h"
#include "common.h"
#include <stdio.h>

void SaveHistory(MatchHistory data) {
    FILE *file = fopen(HISTORY_FILE, "a");
    if (file == NULL) {
        TraceLog(LOG_WARNING, "HISTORY: Nao foi possivel abrir o arquivo de historico para escrita.");
        return;
    }
    fprintf(file, "%d,%d,%d,%ld\n", data.score, data.lines, data.level, data.timestamp);
    fclose(file);
    TraceLog(LOG_INFO, "HISTORY: Partida salva no historico.");
}

int LoadHistory(MatchHistory *history, int maxCount) {
    FILE *file = fopen(HISTORY_FILE, "r");
    if (file == NULL) {
        TraceLog(LOG_WARNING, "HISTORY: Arquivo de historico nao encontrado");
        return 0;
    }
    int count = 0;
    while(count < maxCount) {
        int result = fscanf(file, "%d,%d,%d,%ld\n",
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