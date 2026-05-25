#include "stats.h"
#include <math.h> // Para sqrtf e powf
#include <stdio.h> // Para sprintf

// Implementação das funções de estatísticas
float CalculateAverageScore(MatchHistory *history, int count) {
    if (count == 0) return 0.0f;
    long totalScore = 0;
    for (int i = 0; i < count; i++) {
        totalScore += history[i].score;
    }
    return (float)totalScore / count;
}
int CalculateBestScore(MatchHistory *history, int count) {
    if (count == 0) return 0;
    int best = history[0].score;
    for (int i = 1; i < count; i++) {
        if (history[i].score > best) {
        best = history[i].score;
        }
    }
    return best;
}
int CalculateWorstScore(MatchHistory *history, int count) {
    if (count == 0) return 0;
    int worst = history[0].score;
    for (int i = 1; i < count; i++) {
        if (history[i].score < worst) {
            worst = history[i].score;
        }
    }
    return worst;
}

float CalculateStandardDeviation(MatchHistory *history, int count,
float average) {
    if (count <= 1) return 0.0f;
    float sumOfSquaredDifferences = 0.0f;
    for (int i = 0; i < count; i++) {
        sumOfSquaredDifferences += powf(history[i].score - average, 2);
    }
    return sqrtf(sumOfSquaredDifferences / (count - 1));
}

// Funções recursivas (stubs - serão implementadas pelo Dev 3)
int RecursiveSum(int *arr, int n) {
    if (n <= 0) {
        return 0;
    }
    return arr[n - 1] + RecursiveSum(arr, n - 1);
}

int RecursiveMax(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    if (n == 1) {
        return arr[0];
    }

    int maxOfRest = RecursiveMax(arr, n - 1);

    return (arr[n - 1] > maxOfRest) ? arr[n - 1] : maxOfRest;
}

int RecursiveMin(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    if (n == 1) {
        return arr[0];
    }

    int minOfRest = RecursiveMin(arr, n - 1);

    return (arr[n - 1] < minOfRest) ? arr[n - 1] : minOfRest;
}

long RecursiveSquareSum(int *arr, int n) {
    if (n <= 0) {
        return 0;
    }
    return (long)arr[n - 1] * arr[n - 1] + RecursiveSquareSum(arr, n - 1);
}
// Função para gerar heurísticas (stub - será implementada pelo Dev 4)
void GenerateHeuristic(GameStats *stats) {
    sprintf(stats->heuristicMessage, "Analise de desempenho em andamento...");
}