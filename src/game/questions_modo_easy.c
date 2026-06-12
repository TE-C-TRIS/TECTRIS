#include "common.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char pergunta[256];
    char alternativas[4][100]; // 4 alternativas de até 100 caracteres
    int alternativaCorreta;    // Índice da resposta certa (0 = 1, 1 = 2, 2 = 3, 3 = 4)
} PerguntaEasy;

static PerguntaEasy bancoEasy[] = {
    {"1. Quantos coracoes um polvo possui?", {"1) 3", "2) 1", "3) 2", "4) 8"}, 0},
    {"2. Quantos litros de sangue possui, em media, um adulto?", {"1) 1 L", "2) 5 L", "3) 15 L", "4) 30 L"}, 1},
    {"3. Quantos dentes tem um adulto saudavel?", {"1) 24", "2) 28", "3) 32", "4) 40"}, 2},
    {"4. Quantos planetas existem no Sistema Solar?", {"1) 7", "2) 9", "3) 12", "4) 8"}, 3},
    {"5. Quantos ossos possui um bebe ao nascer?", {"1) 300", "2) 120", "3) 206", "4) 500"}, 0},
    {"6. Quantos ossos possui um adulto?", {"1) 156", "2) 206", "3) 300", "4) 412"}, 1},
    {"7. Quantos lados tem um hexagono?", {"1) 5", "2) 8", "3) 6", "4) 10"}, 2},
    {"8. Quantos minutos ha em um dia?", {"1) 720", "2) 1.000", "3) 2.400", "4) 1.440"}, 3},
    {"9. Quantas horas tem uma semana?", {"1) 168", "2) 120", "3) 200", "4) 240"}, 0},
    {"10. Quantos satelites naturais a Terra possui?", {"1) 2", "2) 1", "3) 4", "4) 8"}, 1},
    {"11. Quantas casas possui um tabuleiro de xadrez?", {"1) 32", "2) 48", "3) 64", "4) 100"}, 2},
    {"12. Quantos jogadores ha em campo por equipe no futebol?", {"1) 9", "2) 10", "3) 12", "4) 11"}, 3},
    {"13. Quantos continentes existem?", {"1) 7", "2) 5", "3) 6", "4) 8"}, 0},
    {"14. Quantos dias possui um ano bissexto?", {"1) 365", "2) 366", "3) 367", "4) 364"}, 1},
    {"15. Quantas cordas tem um violao tradicional?", {"1) 4", "2) 5", "3) 6", "4) 8"}, 2},
    {"16. Quantos aneis aparecem no simbolo olimpico?", {"1) 4", "2) 6", "3) 7", "4) 5"}, 3},
    {"17. Quantos tentaculos possui uma lula?", {"1) 10", "2) 8", "3) 12", "4) 16"}, 0},
    {"18. Quantos lados possui um octogono?", {"1) 6", "2) 8", "3) 7", "4) 10"}, 1},
    {"19. Quantos segundos ha em uma hora?", {"1) 600", "2) 1.800", "3) 3.600", "4) 6.000"}, 2},
    {"20. Quantos anos durou a construcao da Torre Eiffel?", {"1) 10", "2) 20", "3) 50", "4) 2"}, 3},
    {"21. Quantas patas possui uma aranha?", {"1) 8", "2) 6", "3) 10", "4) 12"}, 0},
    {"22. Quantos metros tem uma piscina olimpica?", {"1) 25", "2) 50", "3) 40", "4) 100"}, 1},
    {"23. Quantos meses tem 28 dias?", {"1) 1", "2) 2", "3) 12", "4) 6"}, 2},
    {"24. Quantas teclas possui um piano padrao?", {"1) 61", "2) 76", "3) 100", "4) 88"}, 3},
    {"25. Quantos fusos horarios existem aproximadamente no mundo?", {"1) 24", "2) 12", "3) 18", "4) 36"}, 0},
    {"26. Quantos anos tem um seculo?", {"1) 10", "2) 100", "3) 50", "4) 1.000"}, 1},
    {"27. Quantos paises existem reconhecidos pela ONU?", {"1) 120", "2) 250", "3) 193", "4) 300"}, 2},
    {"28. Quantas casas existem em um jogo de domino tradicional?", {"1) 14", "2) 21", "3) 40", "4) 28"}, 3},
    {"29. Quantos metros tem a estatua do Cristo Redentor (sem pedestal)?", {"1) 30", "2) 20", "3) 50", "4) 70"}, 0},
    {"30. Quantos anos durou a Primeira Guerra Mundial?", {"1) 2", "2) 4", "3) 8", "4) 12"}, 1},
    {"31. Quantos elementos quimicos existem oficialmente reconhecidos?", {"1) 92", "2) 100", "3) 118", "4) 150"}, 2},
    {"32. Quantos metros tem aproximadamente uma quadra de volei de comprimento?", {"1) 12", "2) 24", "3) 30", "4) 18"}, 3},
    {"33. Quantos jogadores formam uma equipe de volei em quadra?", {"1) 6", "2) 5", "3) 7", "4) 8"}, 0},
    {"34. Quantos cromossomos possui um ser humano saudavel?", {"1) 23", "2) 46", "3) 32", "4) 92"}, 1},
    {"35. Quantos metros mede aproximadamente uma girafa adulta?", {"1) 2", "2) 3", "3) 5", "4) 10"}, 2},
    {"36. Quantos litros de agua um camelo pode beber de uma so vez?", {"1) 10", "2) 30", "3) 300", "4) 100"}, 3},
    {"37. Quantos lados tem um decagono?", {"1) 10", "2) 8", "3) 9", "4) 12"}, 0},
    {"38. Quantos anos dura uma decada?", {"1) 5", "2) 10", "3) 20", "4) 100"}, 1},
    {"39. Quantos dias possui fevereiro em um ano comum?", {"1) 27", "2) 29", "3) 28", "4) 30"}, 2},
    {"40. Quantos metros tem a rede de volei no centro da quadra (masculino)?", {"1) 1,5 m", "2) 3,5 m", "3) 5 m", "4) 2,43 m"}, 3},
    {"41. Quantos tentaculos possui um polvo?", {"1) 8", "2) 6", "3) 10", "4) 12"}, 0},
    {"42. Quantos quilometros tem aproximadamente a Maratona Olimpica?", {"1) 10 km", "2) 42 km", "3) 21 km", "4) 100 km"}, 1},
    {"43. Quantos lados possui um triangulo?", {"1) 2", "2) 4", "3) 3", "4) 5"}, 2},
    {"44. Quantas cartas possui um baralho comum sem coringas?", {"1) 40", "2) 48", "3) 60", "4) 52"}, 3},
    {"45. Quantos satelites naturais possui Marte?", {"1) 2", "2) 1", "3) 4", "4) 8"}, 0},
    {"46. Quantos anos vive, em media, uma tartaruga-gigante?", {"1) 20", "2) 100", "3) 50", "4) 300"}, 1},
    {"47. Quantos graus tem um circulo completo?", {"1) 180", "2) 270", "3) 360", "4) 720"}, 2},
    {"48. Quantos metros mede aproximadamente a cauda de uma baleia-azul adulta?", {"1) 1 m", "2) 3 m", "3) 15 m", "4) 7 m"}, 3},
    {"49. Quantos litros de agua ha aproximadamente no corpo humano?", {"1) 42 L", "2) 5 L", "3) 15 L", "4) 100 L"}, 0},
    {"50. Quantos anos tinha aproximadamente Tutancamon quando morreu?", {"1) 9", "2) 19", "3) 39", "4) 59"}, 1},
    {"51. Quantos olhos uma abelha possui?", {"1) 2", "2) 3", "3) 5", "4) 8"}, 2},
    {"52. Quantos estomagos possui uma vaca?", {"1) 1", "2) 2", "3) 8", "4) 4"}, 3},
    {"53. Quantos metros tem aproximadamente a lingua de uma baleia-azul?", {"1) 5 m", "2) 1 m", "3) 3 m", "4) 10 m"}, 0},
    {"54. Quantos quilometros por hora um guepardo pode atingir?", {"1) 40 km/h", "2) 110 km/h", "3) 80 km/h", "4) 180 km/h"}, 1},
    {"55. Quantos coracoes possui uma minhoca?", {"1) 1", "2) 3", "3) 5", "4) 10"}, 2},
    {"56. Quantos litros de leite uma vaca produz por dia, em media?", {"1) 3 L", "2) 10 L", "3) 100 L", "4) 30 L"}, 3},
    {"57. Quantos dentes possui um tubarao-branco adulto ao mesmo tempo?", {"1) 300", "2) 50", "3) 100", "4) 1.000"}, 0},
    {"58. Quantos metros mede aproximadamente a maior cobra ja registrada?", {"1) 6 m", "2) 10 m", "3) 9 m", "4) 18 m"}, 1},
    {"59. Quantos quilometros a luz percorre em um segundo?", {"1) 3.000 km", "2) 30.000 km", "3) 300.000 km", "4) 3.000.000 km"}, 2},
    {"60. Quantas luas possui Jupiter atualmente?", {"1) 27", "2) 52", "3) 180", "4) 95"}, 3},
    {"61. Quantos dias Marte leva para dar uma volta ao Sol?", {"1) 687", "2) 365", "3) 500", "4) 1.200"}, 0},
    {"62. Quantos quilometros tem aproximadamente o diametro da Lua?", {"1) 1.000 km", "2) 3.474 km", "3) 10.000 km", "4) 20.000 km"}, 1},
    {"63. Em que ano o homem pisou na Lua?", {"1) 1959", "2) 1979", "3) 1969", "4) 1989"}, 2},
    {"64. Quantos minutos a luz do Sol leva para chegar a Terra?", {"1) 2", "2) 20", "3) 60", "4) 8"}, 3},
    {"65. Quantos quilometros tem aproximadamente o Monte Everest?", {"1) 8,8 km", "2) 4 km", "3) 6 km", "4) 12 km"}, 0},
    {"66. Quantos litros de agua doce existem no planeta em porcentagem aproximada?", {"1) 15%", "2) 3%", "3) 30%", "4) 50%"}, 1},
    {"67. Quantos metros mede aproximadamente a maior arvore do mundo?", {"1) 40 m", "2) 70 m", "3) 116 m", "4) 200 m"}, 2},
    {"68. Quantos anos vive, em media, uma rainha das abelhas?", {"1) 1", "2) 2", "3) 20", "4) 5"}, 3},
    {"69. Quantos litros de agua um elefante pode beber por dia?", {"1) 200 L", "2) 10 L", "3) 50 L", "4) 800 L"}, 0},
    {"70. Quantos anos durou a construcao das Piramides de Gize?", {"1) 5", "2) 20", "3) 100", "4) 300"}, 1},
    {"71. Quantos andares tem aproximadamente a Torre Eiffel?", {"1) 10", "2) 20", "3) 3", "4) 50"}, 2},
    {"72. Quantos sinos existem no Big Ben?", {"1) 1", "2) 3", "3) 12", "4) 5"}, 3},
    {"73. Quantos quilometros possui a Muralha da China?", {"1) 21.000 km", "2) 2.000 km", "3) 8.000 km", "4) 50.000 km"}, 0},
    {"74. Quantos anos tinha Leonardo da Vinci quando morreu?", {"1) 47", "2) 67", "3) 87", "4) 97"}, 1},
    {"75. Quantos anos viveu, aproximadamente, Albert Einstein?", {"1) 56", "2) 96", "3) 76", "4) 106"}, 2},
    {"76. Quantos filhos teve Mozart?", {"1) 2", "2) 4", "3) 12", "4) 6"}, 3},
    {"77. Quantos anos tinha Napoleao quando morreu?", {"1) 51", "2) 31", "3) 71", "4) 91"}, 0},
    {"78. Quantos metros mede aproximadamente uma girafa recem-nascida?", {"1) 50 cm", "2) 1,8 m", "3) 3 m", "4) 5 m"}, 1},
    {"79. Quantas horas por dia um coala costuma dormir?", {"1) 6", "2) 10", "3) 18", "4) 24"}, 2},
    {"80. Quantos litros de mel uma colmeia forte pode produzir por ano?", {"1) 2 L", "2) 10 L", "3) 200 L", "4) 45 L"}, 3},
    {"81. Quantas vezes por segundo um beija-flor pode bater as asas?", {"1) 80", "2) 5", "3) 20", "4) 300"}, 0},
    {"82. Quantos metros pode alcancar o salto de uma pulga em relacao ao seu tamanho?", {"1) 10 vezes", "2) 150 vezes", "3) 50 vezes", "4) 500 vezes"}, 1},
    {"83. Quantos litros de refrigerante sao consumidos por segundo no mundo?", {"1) 100", "2) 1.000", "3) 10.000", "4) 1.000.000"}, 2},
    {"84. Quantos musculos aproximadamente utilizamos para sorrir?", {"1) 5", "2) 50", "3) 120", "4) 17"}, 3},
    {"85. Quantos quilometros de vasos sanguineos existem no corpo humano?", {"1) 100.000 km", "2) 1.000 km", "3) 10.000 km", "4) 1.000.000 km"}, 0},
    {"86. Quantas vezes o coracao humano bate por dia, em media?", {"1) 10.000", "2) 100.000", "3) 50.000", "4) 500.000"}, 1},
    {"87. Quantos fios de cabelo uma pessoa possui em media?", {"1) 10.000", "2) 50.000", "3) 100.000", "4) 1.000.000"}, 2},
    {"88. Quantos litros de saliva uma pessoa produz por dia?", {"1) 500 ml", "2) 5 L", "3) 20 L", "4) 1,5 L"}, 3},
    {"89. Quantos litros de ar respiramos por dia, aproximadamente?", {"1) 11.000 L", "2) 500 L", "3) 2.000 L", "4) 100.000 L"}, 0},
    {"90. Quantos quilometros por hora pode atingir um falcao-peregrino em mergulho?", {"1) 120 km/h", "2) 390 km/h", "3) 220 km/h", "4) 700 km/h"}, 1},
    {"91. Quantos metros mede aproximadamente a lingua de uma girafa?", {"1) 10 cm", "2) 25 cm", "3) 50 cm", "4) 1 m"}, 2},
    {"92. Quantos anos viveu, aproximadamente, a pessoa mais velha ja registrada?", {"1) 98", "2) 110", "3) 150", "4) 122"}, 3},
    {"93. Quantos quilometros quadrados tem aproximadamente o Brasil?", {"1) 8,5 milhoes", "2) 2 milhoes", "3) 5 milhoes", "4) 15 milhoes"}, 0},
    {"94. Quantos estados possui o Brasil?", {"1) 24", "2) 26", "3) 27", "4) 28"}, 1},
    {"95. Quantos municipios possui o Brasil aproximadamente?", {"1) 1.500", "2) 3.000", "3) 5.570", "4) 10.000"}, 2},
    {"96. Quantos quilometros tem aproximadamente o Rio Amazonas?", {"1) 2.000", "2) 4.000", "3) 12.000", "4) 6.400"}, 3},
    {"97. Quantos litros de agua passam pelas Cataratas do Iguacu por segundo?", {"1) 6.500", "2) 500", "3) 1.500", "4) 50.000"}, 0},
    {"98. Quantos metros de altura possui aproximadamente o Cristo Redentor com pedestal?", {"1) 20 m", "2) 38 m", "3) 80 m", "4) 120 m"}, 1},
    {"99. Quantos quilometros tem aproximadamente a Ponte Rio-Niteroi?", {"1) 3 km", "2) 7 km", "3) 13 km", "4) 25 km"}, 2},
    {"100. Quantos anos durou a construcao da Catedral de Notre-Dame de Paris?", {"1) 20", "2) 50", "3) 500", "4) 182"}, 3}
};

static int bankSizeEasy = sizeof(bancoEasy) / sizeof(PerguntaEasy);

PerguntaEasy GetRandomQuestionEasy() {
    if (bankSizeEasy == 0) return bancoEasy[0]; // Retorna a primeira caso dê erro
    
    int r = rand() % bankSizeEasy;
    return bancoEasy[r];
}

bool ValidateAnswerEasy(int escolhaJogador, const PerguntaEasy* q) {
    if (q == NULL) return false;
    
    // Se o índice escolhido for igual ao índice da resposta certa, ele acertou!
    return (escolhaJogador == q->alternativaCorreta);
}