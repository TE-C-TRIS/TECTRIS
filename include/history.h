#ifndef HISTORY_H    // Se HISTORY_H ainda não foi definido...
#define HISTORY_H    // ...define ele (evita o arquivo ser lido duas vezes)

#include "common.h"  // Importa o common.h pois precisa conhecer a struct MatchHistory

void SaveHistory(MatchHistory data); // Avisa ao compilador que essa função existe

int LoadHistory(MatchHistory *history, int maxCount);

void SaveHistoryEx(MatchHistory data, const char* filename);
int LoadHistoryEx(MatchHistory *history, int maxCount, const char* filename);

#endif // Fim da proteção