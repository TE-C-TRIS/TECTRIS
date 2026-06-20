#include "common.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>



static Question questionBank[] = {

    /* =========================================================
     * NÍVEL 1: Básico — 20 perguntas (índices 0–19)
     * Fonte: PDF Guia_Correcao_e_Perguntas_Tectris_V3, Parte 2
     * ========================================================= */

    /* 1 */
    {"Qual e a saida de: printf(\"%d\", 5 + 3);",
        {"8"}, 1, 1},

    /* 2 */
    {"Qual funcao usamos para imprimir na tela em C?",
        {"printf", "printf()"}, 2, 1},

    /* 3 */
    {"Qual tipo de dado armazena numeros inteiros em C?",
        {"int"}, 1, 1},

    /* 4 — PDF lista duas respostas aceitas */
    {"Em C, qual simbolo indica o final de uma instrucao?",
        {";", "ponto e virgula"}, 2, 1},

    /* 5 */
    {"Qual palavra inicia a funcao principal de um programa em C?",
        {"main", "main()"}, 2, 1},

    /* 6 */
    {"Qual simbolo usamos para comentario de uma linha em C?",
        {"//"}, 1, 1},

    /* 7 */
    {"Qual operador e usado para atribuicao em C?",
        {"="}, 1, 1},

    /* 8 */
    {"Qual e o tipo de dado para caracteres unicos em C?",
        {"char"}, 1, 1},

    /* 9 */
    {"Qual funcao usamos para ler entrada do usuario em C?",
        {"scanf", "scanf()"}, 2, 1},

    /* 10 */
    {"Qual e o resultado de 10 / 3 em C (inteiros)?",
        {"3"}, 1, 1},

    /* 11 — operador corrompido no PDF: "& &" → "&&" */
    {"Qual e o operador logico E em C?",
        {"&&"}, 1, 1},

    /* 12 — operador corrompido no PDF: "| |" → "||" */
    {"Qual e o operador logico OU em C?",
        {"||"}, 1, 1},

    /* 13 */
    {"Qual e o operador logico NAO em C?",
        {"!"}, 1, 1},

    /* 14 */
    {"Qual palavra-chave e usada para declarar uma constante em C?",
        {"const"}, 1, 1},

    /* 15 */
    {"Qual e o valor padrao de uma variavel global nao inicializada em C?",
        {"0", "zero"}, 2, 1},

    /* 16 — operador corrompido no PDF: "+ +" → "++" */
    {"Qual e o operador de incremento em C?",
        {"++"}, 1, 1},

    /* 17 — operador corrompido no PDF: "- -" → "--" */
    {"Qual e o operador de decremento em C?",
        {"--"}, 1, 1},

    /* 18 */
    {"Qual header e necessario para usar printf e scanf?",
        {"stdio.h"}, 1, 1},

    /* 19 */
    {"Qual e o tipo de dado para numeros de ponto flutuante de precisao simples?",
        {"float"}, 1, 1},

    /* 20 */
    {"Qual e o tipo de dado para numeros de ponto flutuante de precisao dupla?",
        {"double"}, 1, 1},

    /* =========================================================
     * NÍVEL 2: Intermediário — 30 perguntas (índices 20–49)
     * ========================================================= */

    /* 21 */
    {"Qual palavra-chave e usada para criar uma condicao?",
        {"if"}, 1, 2},

    /* 22 — resultado de precedência: 2 + (2*3) = 8 */
    {"Qual e o resultado de: 2 + 2 * 3?",
        {"8"}, 1, 2},

    /* 23 — três respostas válidas aceitas */
    {"Qual palavra-chave e usada para repetir codigo em C?",
        {"for", "while", "do"}, 3, 2},

    /* 24 — operador corrompido no PDF: "= =" → "==" */
    {"Qual operador compara igualdade em C?",
        {"=="}, 1, 2},

    /* 25 */
    {"Qual palavra-chave sai de um loop em C?",
        {"break"}, 1, 2},

    /* 26 */
    {"Qual palavra-chave pula para a proxima iteracao de um loop em C?",
        {"continue"}, 1, 2},

    /* 27 */
    {"Qual e a sintaxe correta para um loop for?",
        {"for (init; cond; incr)"}, 1, 2},

    /* 28 */
    {"Qual e a sintaxe correta para um loop while?",
        {"while (cond)"}, 1, 2},

    /* 29 */
    {"Qual e a sintaxe correta para um loop do-while?",
        {"do { } while (cond);"}, 1, 2},

    /* 30 */
    {"Qual e o tamanho em bytes de um int em um sistema de 32 bits?",
        {"4"}, 1, 2},

    /* 31 */
    {"Qual e o tamanho em bytes de um char?",
        {"1"}, 1, 2},

    /* 32 */
    {"Qual e o tamanho em bytes de um float?",
        {"4"}, 1, 2},

    /* 33 */
    {"Qual e o tamanho em bytes de um double?",
        {"8"}, 1, 2},

    /* 34 */
    {"Qual e a funcao para alocar memoria dinamicamente em C?",
        {"malloc", "malloc()"}, 2, 2},

    /* 35 */
    {"Qual e a funcao para liberar memoria alocada dinamicamente em C?",
        {"free", "free()"}, 2, 2},

    /* 36 — operador corrompido no PDF: "- >" → "->" */
    {"Qual e o operador para acessar membros de uma struct via ponteiro?",
        {"->"}, 1, 2},

    /* 37 */
    {"Qual e o operador para acessar membros de uma struct diretamente?",
        {"."}, 1, 2},

    /* 38 */
    {"Qual e a funcao para comparar duas strings em C?",
        {"strcmp", "strcmp()"}, 2, 2},

    /* 39 */
    {"Qual e a funcao para copiar uma string em C?",
        {"strcpy", "strcpy()"}, 2, 2},

    /* 40 */
    {"Qual e a funcao para concatenar duas strings em C?",
        {"strcat", "strcat()"}, 2, 2},

    /* 41 */
    {"Qual e a funcao para obter o comprimento de uma string em C?",
        {"strlen", "strlen()"}, 2, 2},

    /* 42 */
    {"Qual e o valor de um ponteiro NULL?",
        {"0", "NULL"}, 2, 2},

    /* 43 */
    {"Qual e a funcao para converter string para inteiro?",
        {"atoi", "atoi()"}, 2, 2},

    /* 44 */
    {"Qual e a funcao para converter string para float?",
        {"atof", "atof()"}, 2, 2},

    /* 45 */
    {"Qual e a funcao para gerar numeros aleatorios em C?",
        {"rand", "rand()"}, 2, 2},

    /* 46 */
    {"Qual e a funcao para inicializar o gerador de numeros aleatorios?",
        {"srand", "srand()"}, 2, 2},

    /* 47 */
    {"Qual e o tipo de retorno de uma funcao que nao retorna valor?",
        {"void"}, 1, 2},

    /* 48 */
    {"Qual palavra-chave e usada para retornar um valor de uma funcao?",
        {"return"}, 1, 2},

    /* 49 */
    {"Qual e o operador de modulo em C?",
        {"%"}, 1, 2},

    /* 50 */
    {"Qual e o operador de divisao inteira em C?",
        {"/"}, 1, 2},

    /* =========================================================
     * NÍVEL 3: Avançado — 30 perguntas (índices 50–79)
     * ========================================================= */

    /* 51 */
    {"Qual operador usamos para obter o endereco de uma variavel?",
        {"&"}, 1, 3},

    /* 52 */
    {"Qual palavra-chave define uma estrutura em C?",
        {"struct"}, 1, 3},

    /* 53 */
    {"Qual operador ternario representa if-else em C?",
        {"?"}, 1, 3},

    /* 54 */
    {"Qual e a diferenca entre um array e um ponteiro em C?",
        {"Array e um bloco de memoria contiguo, ponteiro armazena endereco"}, 1, 3},

    /* 55 */
    {"Como se declara um ponteiro para uma funcao em C?",
        {"tipo (*nome)(parametros)"}, 1, 3},

    /* 56 */
    {"Qual e a funcao para realocar memoria dinamicamente em C?",
        {"realloc", "realloc()"}, 2, 3},

    /* 57 */
    {"Qual e a funcao para alocar memoria e inicializa-la com zero?",
        {"calloc", "calloc()"}, 2, 3},

    /* 58 */
    {"Qual e a diferenca entre passagem por valor e passagem por referencia?",
        {"Valor copia, Referencia endereco"}, 1, 3},

    /* 59 */
    {"O que e um ponteiro nulo?",
        {"Ponteiro que nao aponta para nenhum local valido"}, 1, 3},

    /* 60 */
    {"O que e um ponteiro void?",
        {"Ponteiro generico que pode apontar para qualquer tipo"}, 1, 3},

    /* 61 */
    {"Qual e a funcao para abrir um arquivo em C?",
        {"fopen", "fopen()"}, 2, 3},

    /* 62 */
    {"Qual e a funcao para fechar um arquivo em C?",
        {"fclose", "fclose()"}, 2, 3},

    /* 63 */
    {"Qual e a funcao para escrever em um arquivo formatado?",
        {"fprintf", "fprintf()"}, 2, 3},

    /* 64 */
    {"Qual e a funcao para ler de um arquivo formatado?",
        {"fscanf", "fscanf()"}, 2, 3},

    /* 65 */
    {"O que e o pre-processador em C?",
        {"Fase de compilacao que processa diretivas como #include e #define"}, 1, 3},

    /* 66 */
    {"Qual a diretiva para incluir um arquivo de cabecalho?",
        {"#include"}, 1, 3},

    /* 67 */
    {"Qual a diretiva para definir uma macro?",
        {"#define"}, 1, 3},

    /* 68 */
    {"O que e um typedef em C?",
        {"Permite criar um alias para um tipo existente"}, 1, 3},

    /* 69 */
    {"Qual a diferenca entre 'a' e \"a\" em C?",
        {"'a' e char, \"a\" e string/char*"}, 1, 3},

    /* 70 */
    {"O que e um union em C?",
        {"Permite armazenar diferentes tipos de dados no mesmo local de memoria"}, 1, 3},

    /* 71 */
    {"Qual a palavra-chave para um tipo enumerado?",
        {"enum"}, 1, 3},

    /* 72 */
    {"O que e um bitwise operator?",
        {"Operador que manipula bits individuais"}, 1, 3},

    /* 73 */
    {"Qual e o operador bitwise AND?",
        {"&"}, 1, 3},

    /* 74 */
    {"Qual e o operador bitwise OR?",
        {"|"}, 1, 3},

    /* 75 */
    {"Qual e o operador bitwise XOR?",
        {"^"}, 1, 3},

    /* 76 */
    {"Qual e o operador bitwise NOT?",
        {"~"}, 1, 3},

    /* 77 — operador corrompido no PDF: "< <" → "<<" */
    {"Qual e o operador bitwise left shift?",
        {"<<"}, 1, 3},

    /* 78 — operador corrompido no PDF: "> >" → ">>" */
    {"Qual e o operador bitwise right shift?",
        {">>"}, 1, 3},

    /* 79 */
    {"O que e um ponteiro para ponteiro?",
        {"Variavel que armazena o endereco de outro ponteiro"}, 1, 3},

    /* 80 */
    {"Qual a funcao para definir o locale do programa?",
        {"setlocale", "setlocale()"}, 2, 3},

    /* =========================================================
     * NÍVEL 4: Expert — 15 perguntas (índices 80–94)
     * ========================================================= */

    /* 81 */
    {"O que e um dangling pointer?",
        {"Ponteiro que aponta para uma memoria que foi liberada"}, 1, 4},

    /* 82 */
    {"O que e um memory leak?",
        {"Memoria alocada dinamicamente que nao foi liberada"}, 1, 4},

    /* 83 — resposta truncada no PDF; reconstruída pelo contexto */
    {"Qual a diferenca entre const char* p e char* const p?",
        {"Primeiro: ponteiro para char constante. Segundo: ponteiro constante para char"}, 1, 4},

    /* 84 */
    {"O que e o volatile keyword em C?",
        {"Indica que o valor de uma variavel pode ser alterado por algo externo ao programa"}, 1, 4},

    /* 85 */
    {"O que e o extern keyword em C?",
        {"Declara uma variavel global definida em outro arquivo"}, 1, 4},

    /* 86 — operadores corrompidos no PDF: "<>" e "\"\"" */
    {"Qual a diferenca entre #include <file.h> e #include \"file.h\"?",
        {"<> busca em diretorios padrao, \"\" busca no diretorio atual"}, 1, 4},

    /* 87 */
    {"O que e um makefile?",
        {"Arquivo que automatiza o processo de compilacao e linkagem"}, 1, 4},

    /* 88 */
    {"O que e um segfault?",
        {"Erro de acesso a memoria invalida"}, 1, 4},

    /* 89 */
    {"Como evitar buffer overflow?",
        {"Usar funcoes seguras como snprintf, strncpy, fgets"}, 1, 4},

    /* 90 */
    {"O que e um array de ponteiros para caracteres?",
        {"Um array onde cada elemento e um ponteiro para uma string"}, 1, 4},

    /* 91 */
    {"Qual a funcao para sair do programa em C?",
        {"exit", "exit()"}, 2, 4},

    /* 92 */
    {"Qual a funcao para manipular sinais em C?",
        {"signal", "signal()"}, 2, 4},

    /* 93 */
    {"O que e um registrador?",
        {"Pequena area de armazenamento de alta velocidade na CPU"}, 1, 4},

    /* 94 */
    {"Qual a diferenca entre stack e heap?",
        {"Stack: alocacao automatica, Heap: alocacao dinamica"}, 1, 4},

    /* 95 */
    {"O que e um macro com argumentos?",
        {"Macro que aceita parametros e os substitui no codigo"}, 1, 4},

    /* =========================================================
     * NÍVEL 5: Desafio — 5 perguntas (índices 95–99)
     * ========================================================= */

    /* 96 */
    {"Explique o conceito de Undefined Behavior em C.",
        {"Comportamento nao especificado pela norma C, pode variar entre compiladores"}, 1, 5},

    /* 97 */
    {"Como implementar um array dinamico em C?",
        {"Usando malloc/realloc para gerenciar o tamanho do array em tempo de execucao"}, 1, 5},

    /* 98 */
    {"Qual a diferenca entre fork() e exec() em sistemas Unix-like?",
        {"fork cria processo filho, exec substitui processo atual"}, 1, 5},

    /* 99 */
    {"O que e um mutex e para que serve em programacao concorrente?",
        {"Mecanismo de sincronizacao para proteger secoes criticas de acesso concorrente"}, 1, 5},

    /* 100 — última pergunta do PDF, cortada entre páginas; reconstruída pelo contexto */
    {"Descreva o ciclo de vida de um programa C (compilacao, linkagem, execucao).",
        {"Pre-processamento, Compilacao, Montagem, Linkagem, Carregamento, Execucao"}, 1, 5}
};


static int bankSize = sizeof(questionBank) / sizeof(Question);

Question GetRandomQuestion(int level) {
    int count = 0;
    for(int i=0; i<bankSize; i++) if(questionBank[i].level <= level) count++;
    
    if (count == 0) return questionBank[0];

    int r = rand() % count;
    int current = 0;
    for(int i=0; i<bankSize; i++) {
        if(questionBank[i].level <= level) {
            if(current == r) return questionBank[i];
            current++;
        }
    }
    return questionBank[0];
}

// Função de Trim Robusta: Remove espaços APENAS no início e no fim
static char* trim(char* str) {
    char* end;
    // Leading spaces
    while(isspace((unsigned char)*str)) str++;
    if(*str == 0) return str;
    // Trailing spaces
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    return str;
}

// Validação Case-Insensitive e Multi-Resposta (Preserva espaços internos)
bool ValidateAnswer(const char* user, const Question* q) {
    if (user == NULL || q == NULL) return false;

    char u_copy[128];
    strncpy(u_copy, user, 127);
    u_copy[127] = '\0';
    
    char* u_trimmed = trim(u_copy);
    
    for(int i = 0; i < q->answerCount; i++) {
        char c_copy[128];
        strncpy(c_copy, q->answers[i], 127);
        c_copy[127] = '\0';
        char* c_trimmed = trim(c_copy);
        
        // Comparação case-insensitive usando stricmp (Windows) ou strcasecmp (Linux)
        #ifdef _WIN32
        if (_stricmp(u_trimmed, c_trimmed) == 0) return true;
        #else
        if (strcasecmp(u_trimmed, c_trimmed) == 0) return true;
        #endif
    }
    
    return false;
}
