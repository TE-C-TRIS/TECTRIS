#include "ranking.h"
#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void SanitizePlayerName(char *name) {
    if (name == NULL) return;

    // Remove caracteres que quebrariam o parser (delimitador '|' e quebras de linha)
    size_t w = 0;
    for (size_t r = 0; name[r] != '\0' && r < RANKING_NAME_LEN - 1; r++) {
        char c = name[r];
        if (c == '|' || c == '\n' || c == '\r') continue;
        name[w++] = c;
    }
    name[w] = '\0';

    // Remove espacos nas pontas
    while (w > 0 && isspace((unsigned char)name[w-1])) { name[--w] = '\0'; }

    size_t start = 0;
    while (name[start] != '\0' && isspace((unsigned char)name[start])) start++;
    if (start > 0) memmove(name, name + start, strlen(name + start) + 1);

    if (name[0] == '\0') {
        strncpy(name, "Jogador", RANKING_NAME_LEN - 1);
        name[RANKING_NAME_LEN - 1] = '\0';
    }
}

void SaveRankingEntry(RankingEntry entry) {
    SanitizePlayerName(entry.name);

    FILE *file = fopen(RANKING_FILE, "a");
    if (file == NULL) {
        TraceLog(LOG_WARNING, "RANKING: Nao foi possivel abrir o arquivo de ranking para escrita.");
        return;
    }
    fprintf(file, "%s|%d|%d|%d|%s|%lld\n",
        entry.name, entry.score, entry.lines, entry.level, entry.mode,
        (long long)entry.timestamp);
    fclose(file);
    TraceLog(LOG_INFO, "RANKING: Entrada salva no ranking geral.");
}

int LoadRanking(RankingEntry *out, int maxCount) {
    FILE *file = fopen(RANKING_FILE, "r");
    if (file == NULL) {
        TraceLog(LOG_WARNING, "RANKING: Arquivo de ranking nao encontrado ainda.");
        return 0;
    }

    char line[256];
    int count = 0;
    while (count < maxCount && fgets(line, sizeof(line), file) != NULL) {
        char name[RANKING_NAME_LEN] = {0};
        char mode[RANKING_MODE_LEN] = {0};
        int score = 0, lines = 0, level = 0;
        long long timestamp = 0;

        // Formato: nome|score|lines|level|modo|timestamp
        char *token = strtok(line, "|");
        if (token == NULL) continue;
        strncpy(name, token, RANKING_NAME_LEN - 1);

        token = strtok(NULL, "|"); if (token == NULL) continue; score = atoi(token);
        token = strtok(NULL, "|"); if (token == NULL) continue; lines = atoi(token);
        token = strtok(NULL, "|"); if (token == NULL) continue; level = atoi(token);
        token = strtok(NULL, "|"); if (token == NULL) continue; strncpy(mode, token, RANKING_MODE_LEN - 1);
        token = strtok(NULL, "|\n"); if (token == NULL) continue; timestamp = atoll(token);

        strncpy(out[count].name, name, RANKING_NAME_LEN - 1);
        out[count].name[RANKING_NAME_LEN - 1] = '\0';
        out[count].score = score;
        out[count].lines = lines;
        out[count].level = level;
        strncpy(out[count].mode, mode, RANKING_MODE_LEN - 1);
        out[count].mode[RANKING_MODE_LEN - 1] = '\0';
        out[count].timestamp = (time_t)timestamp;

        count++;
    }
    fclose(file);
    return count;
}

void SortRankingByScoreDesc(RankingEntry *arr, int count) {
    // Insertion sort: o ranking raramente tera mais que algumas centenas de
    // entradas, entao simplicidade > performance aqui.
    for (int i = 1; i < count; i++) {
        RankingEntry key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].score < key.score) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
