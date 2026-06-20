#ifndef RANKING_H
#define RANKING_H

#include <time.h>

#define RANKING_FILE "ranking.txt"
#define RANKING_NAME_LEN 24
#define RANKING_MODE_LEN 8
#define MAX_RANKING_RECORDS 300

// Modos possiveis (texto curto, usado tambem como tag visual no podio)
#define MODE_C     "C"      // Modo normal (Desafio de C, digitado)
#define MODE_EASY  "EASY"   // Modo facil (curiosidades, multipla escolha)
#define MODE_MULTI "MULTI"  // Multiplayer local (entra so o vencedor)

typedef struct {
    char name[RANKING_NAME_LEN];
    int score;
    int lines;
    int level;
    char mode[RANKING_MODE_LEN];
    time_t timestamp;
} RankingEntry;

// Adiciona uma entrada ao ranking geral (arquivo ranking.txt, cresce sempre)
void SaveRankingEntry(RankingEntry entry);

// Carrega todas as entradas do ranking. Retorna a quantidade lida (<= maxCount).
int LoadRanking(RankingEntry *out, int maxCount);

// Ordena um array de RankingEntry por score decrescente (maior primeiro)
void SortRankingByScoreDesc(RankingEntry *arr, int count);

// Sanitiza um nome de jogador digitado: remove '|' e o caractere de nova linha,
// e garante que nunca fique vazio (usa "Jogador" como fallback)
void SanitizePlayerName(char *name);

#endif // RANKING_H
