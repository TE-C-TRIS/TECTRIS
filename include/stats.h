#ifndef STATS_H
#define STATS_H
#include "common.h"

// Estrutura para armazenar as estatísticas calculadas
typedef struct {
int totalMatches;
float averageScore;
int bestScore;
int worstScore;
float standardDeviation;
char heuristicMessage[256];
} GameStats;

// Funções para cálculo de estatísticas
float CalculateAverageScore(MatchHistory *history, int count);
int CalculateBestScore(MatchHistory *history, int count);
int CalculateWorstScore(MatchHistory *history, int count);
float CalculateStandardDeviation(MatchHistory *history, int count,
float average);

// Funções recursivas (declaradas aqui, implementadas pelo Dev 3)
int RecursiveSum(int *arr, int n);
int RecursiveMax(int *arr, int n);
int RecursiveMin(int *arr, int n);
long RecursiveSquareSum(int *arr, int n);

// Função para gerar heurísticas
void GenerateHeuristic(GameStats *stats);
#endif // STATS_H