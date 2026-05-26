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

float CalculateStandardDeviation(MatchHistory *history, int count,
                                 float average)
{
    if (count <= 1) return 0.0f;
int scores[count];
for (int i = 0; i < count; i++) {
scores[i] = history[i].score;
}
// Para o desvio padrão, precisamos da soma dos quadrados das diferenças
// Uma abordagem recursiva direta para isso é mais complexa com a assinatura atual.
// Vamos adaptar para usar a soma recursiva dos quadrados dos scores e ajustar a fórmula.
// Ou, para simplificar e manter a recursão, podemos calcular a soma dos quadrados dos scores
// e usar a fórmula de variância: E[X^2] - (E[X])^2
// Criar um array de diferenças ao quadrado para usar RecursiveSum
    float diffsSquared[count];
    for (int i = 0; i < count; i++) {
    diffsSquared[i] = powf(history[i].score - average, 2);
}
// RecursiveSum opera com int*, então precisamos de uma adaptação ou nova função recursiva para float
// Para manter a exigência de recursão, vamos usar a RecursiveSquareSum para os scores e adaptar.
// Alternativa: Se a RecursiveSquareSum for para os scores, podemos fazer:
// Variância = (RecursiveSquareSum(scores, count) / count) - (average * average);
// stdDev = sqrtf(Variancia);
// No entanto, a definição original da RecursiveSquareSum é para um array de int.
// Vamos manter a implementação iterativa para o desvio padrão por enquanto, ou criar uma RecursiveSumFloat.
// Para aderir estritamente à recursão para
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

// Função para gerar heurísticas (stub - será implementada pelo Dev 4)
void GenerateHeuristic(GameStats *stats)
{
    if (stats->totalMatches == 0)
    {
        sprintf(stats->heuristicMessage,
                "Nenhuma partida registrada para analise.");
        return;
    }

    // Exemplo de heurísticas simples
    if (stats->totalMatches < 5)
    {
        sprintf(stats->heuristicMessage,
                "Jogue mais partidas para uma analise precisa.");
    }
    else if (stats->standardDeviation > 500 &&
             stats->averageScore < 1000)
    {
        sprintf(stats->heuristicMessage,
                "Desempenho inconsistente. Tente manter a calma!");
    }
    else if (stats->averageScore > 2000 &&
             stats->standardDeviation < 200)
    {
        sprintf(stats->heuristicMessage,
                "Excelente consistencia! Voce e um mestre do Tectris!");
    }
    else if (stats->bestScore > 3000)
    {
        sprintf(stats->heuristicMessage,
                "Pontuacao maxima impressionante! Continue assim.");
    }
    else
    {
        sprintf(stats->heuristicMessage,
                "Bom desempenho geral. Continue praticando!");
    }
}