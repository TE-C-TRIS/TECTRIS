#include "stats.h"
#include <math.h>  // Para sqrtf e powf
#include <stdio.h> // Para sprintf

// Implementação das funções de estatísticas
float CalculateAverageScore(MatchHistory *history, int count){
    if (count == 0) return 0.0f;
        int scores[count];
    for (int i = 0; i < count; i++) {
        scores[i] = history[i].score;
    }
    return (float)RecursiveSum(scores, count) / count;
}

int CalculateBestScore(MatchHistory *history, int count)
{
    if (count == 0) return 0;
    int scores[count];
    for (int i = 0; i < count; i++) {
        scores[i] = history[i].score;
    }
    return RecursiveMax(scores, count);
}

int CalculateWorstScore(MatchHistory *history, int count)
{
    if (count == 0) return 0;
    int scores[count];
    for (int i = 0; i < count; i++) {
        scores[i] = history[i].score;
    }
    return RecursiveMin(scores, count);
}

float CalculateStandardDeviation(MatchHistory *history, int count, float average)
{
    if (count <= 1) return 0.0f;
    
    float sumOfSquaredDifferences = 0.0f;
    for (int i = 0; i < count; i++) {
        sumOfSquaredDifferences += powf(history[i].score - average, 2);
    }
    return sqrtf(sumOfSquaredDifferences / (count - 1));
}

// Funções recursivas (stubs - serão implementadas pelo Dev 3)
int RecursiveSum(int *arr, int n)
{
    if (n <= 0)
    {
        return 0;
    }

    return arr[n - 1] + RecursiveSum(arr, n - 1);
}

int RecursiveMax(int *arr, int n)
{
    if (arr == NULL || n <= 0)
    {
        return 0;
    }

    if (n == 1)
    {
        return arr[0];
    }

    int maxOfRest = RecursiveMax(arr, n - 1);

    return (arr[n - 1] > maxOfRest) ? arr[n - 1] : maxOfRest;
}

int RecursiveMin(int *arr, int n)
{
    if (arr == NULL || n <= 0)
    {
        return 0;
    }

    if (n == 1)
    {
        return arr[0];
    }

    int minOfRest = RecursiveMin(arr, n - 1);

    return (arr[n - 1] < minOfRest) ? arr[n - 1] : minOfRest;
}

long RecursiveSquareSum(int *arr, int n)
{
    if (n <= 0)
    {
        return 0;
    }

    return (long)arr[n - 1] * arr[n - 1] +
           RecursiveSquareSum(arr, n - 1);
}

void GenerateHeuristic(GameStats *stats) {
    if (stats->totalMatches == 0) {
        sprintf(stats->heuristicMessage,
                "Nenhuma partida registrada para analise.");
        return;
    }

    if (stats->totalMatches < 5) {
        sprintf(stats->heuristicMessage,
                "Continue jogando! Precisa de mais partidas para uma analise completa.");
    }
    else if (stats->averageScore > 2000 && stats->standardDeviation < 200) {
        sprintf(stats->heuristicMessage,
                "Excelente consistencia! Voce domina o Tectris!");
    }
    else if (stats->bestScore > 3000 && stats->averageScore < 1000) {
        sprintf(stats->heuristicMessage,
                "Voce tem potencial! Seu melhor jogo prova isso. Mantenha o foco!");
    }
    else if (stats->worstScore == 0) {
        sprintf(stats->heuristicMessage,
                "Algumas partidas foram dificeis, mas todo expert ja foi iniciante!");
    }
    else if (stats->standardDeviation > 500 && stats->averageScore < 1000) {
        sprintf(stats->heuristicMessage,
                "Desempenho inconsistente. Respire fundo e mantenha a calma!");
    }
    else if (stats->bestScore > 3000) {
        sprintf(stats->heuristicMessage,
                "Pontuacao impressionante! Voce esta no caminho certo.");
    }
    else if (stats->totalMatches > 10 && stats->averageScore < 500) {
        sprintf(stats->heuristicMessage,
                "Muitas partidas e dedicacao! Tente focar nas perguntas para ganhar mais pontos.");
    }
    else if (stats->averageScore >= 1000 && stats->averageScore <= 2000) {
        sprintf(stats->heuristicMessage,
                "Bom desempenho! Voce esta evoluindo, continue assim.");
    }
    else {
        sprintf(stats->heuristicMessage,
                "Continue praticando! Cada partida e um aprendizado.");
    }
}