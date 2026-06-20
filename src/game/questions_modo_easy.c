#include "common.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>


static PerguntaEasy bancoEasy[] = {
    {"1. Quantos coracoes um polvo possui?", {"3", "1", "2", "8"}, 0},
    {"2. Quantos litros de sangue possui, em media, um adulto?", {"1 L", "5 L", "15 L", "30 L"}, 1},
    {"3. Quantos dentes tem um adulto saudavel?", {"24", "28", "32", "40"}, 2},
    {"4. Quantos planetas existem no Sistema Solar?", {"7", "9", "12", "8"}, 3},
    {"5. Quantos ossos possui um bebe ao nascer?", {"300", "120", "206", "500"}, 0},
    {"6. Quantos ossos possui um adulto?", {"156", "206", "300", "412"}, 1},
    {"7. Quantos lados tem um hexagono?", {"5", "8", "6", "10"}, 2},
    {"8. Quantos minutos ha em um dia?", {"720", "1.000", "2.400", "1.440"}, 3},
    {"9. Quantas horas tem uma semana?", {"168", "120", "200", "240"}, 0},
    {"10. Quantos satelites naturais a Terra possui?", {"2", "1", "4", "8"}, 1},
    {"11. Quantas casas possui um tabuleiro de xadrez?", {"32", "48", "64", "100"}, 2},
    {"12. Quantos jogadores ha em campo por equipe no futebol?", {"9", "10", "12", "11"}, 3},
    {"13. Quantos continentes existem?", {"7", "5", "6", "8"}, 0},
    {"14. Quantos dias possui um ano bissexto?", {"365", "366", "367", "364"}, 1},
    {"15. Quantas cordas tem um violao tradicional?", {"4", "5", "6", "8"}, 2},
    {"16. Quantos aneis aparecem no simbolo olimpico?", {"4", "6", "7", "5"}, 3},
    {"17. Quantos tentaculos possui uma lula?", {"10", "8", "12", "16"}, 0},
    {"18. Quantos lados possui um octogono?", {"6", "8", "7", "10"}, 1},
    {"19. Quantos segundos ha em uma hora?", {"600", "1.800", "3.600", "6.000"}, 2},
    {"20. Quantos anos durou a construcao da Torre Eiffel?", {"10", "20", "50", "2"}, 3},
    {"21. Quantas patas possui uma aranha?", {"8", "6", "10", "12"}, 0},
    {"22. Quantos metros tem uma piscina olimpica?", {"25", "50", "40", "100"}, 1},
    {"23. Quantos meses tem 28 dias?", {"1", "2", "12", "6"}, 2},
    {"24. Quantas teclas possui um piano padrao?", {"61", "76", "100", "88"}, 3},
    {"25. Quantos fusos horarios existem aproximadamente no mundo?", {"24", "12", "18", "36"}, 0},
    {"26. Quantos anos tem um seculo?", {"10", "100", "50", "1.000"}, 1},
    {"27. Quantos paises existem reconhecidos pela ONU?", {"120", "250", "193", "300"}, 2},
    {"28. Quantas casas existem em um jogo de domino tradicional?", {"14", "21", "40", "28"}, 3},
    {"29. Quantos metros tem a estatua do Cristo Redentor (sem pedestal)?", {"30", "20", "50", "70"}, 0},
    {"30. Quantos anos durou a Primeira Guerra Mundial?", {"2", "4", "8", "12"}, 1},
    {"31. Quantos elementos quimicos existem oficialmente reconhecidos?", {"92", "100", "118", "150"}, 2},
    {"32. Quantos metros tem aproximadamente uma quadra de volei de comprimento?", {"12", "24", "30", "18"}, 3},
    {"33. Quantos jogadores formam uma equipe de volei em quadra?", {"6", "5", "7", "8"}, 0},
    {"34. Quantos cromossomos possui um ser humano saudavel?", {"23", "46", "32", "92"}, 1},
    {"35. Quantos metros mede aproximadamente uma girafa adulta?", {"2", "3", "5", "10"}, 2},
    {"36. Quantos litros de agua um camelo pode beber de uma so vez?", {"10", "30", "300", "100"}, 3},
    {"37. Quantos lados tem um decagono?", {"10", "8", "9", "12"}, 0},
    {"38. Quantos anos dura uma decada?", {"5", "10", "20", "100"}, 1},
    {"39. Quantos dias possui fevereiro em um ano comum?", {"27", "29", "28", "30"}, 2},
    {"40. Quantos metros tem a rede de volei no centro da quadra (masculino)?", {"1,5 m", "3,5 m", "5 m", "2,43 m"}, 3},
    {"41. Quantos tentaculos possui um polvo?", {"8", "6", "10", "12"}, 0},
    {"42. Quantos quilometros tem aproximadamente a Maratona Olimpica?", {"10 km", "42 km", "21 km", "100 km"}, 1},
    {"43. Quantos lados possui um triangulo?", {"2", "4", "3", "5"}, 2},
    {"44. Quantas cartas possui um baralho comum sem coringas?", {"40", "48", "60", "52"}, 3},
    {"45. Quantos satelites naturais possui Marte?", {"2", "1", "4", "8"}, 0},
    {"46. Quantos anos vive, em media, uma tartaruga-gigante?", {"20", "100", "50", "300"}, 1},
    {"47. Quantos graus tem um circulo completo?", {"180", "270", "360", "720"}, 2},
    {"48. Quantos metros mede aproximadamente a cauda de uma baleia-azul adulta?", {"1 m", "3 m", "15 m", "7 m"}, 3},
    {"49. Quantos litros de agua ha aproximadamente no corpo humano?", {"42 L", "5 L", "15 L", "100 L"}, 0},
    {"50. Quantos anos tinha aproximadamente Tutancamon quando morreu?", {"9", "19", "39", "59"}, 1},
    {"51. Quantos olhos uma abelha possui?", {"2", "3", "5", "8"}, 2},
    {"52. Quantos estomagos possui uma vaca?", {"1", "2", "8", "4"}, 3},
    {"53. Quantos metros tem aproximadamente a lingua de uma baleia-azul?", {"5 m", "1 m", "3 m", "10 m"}, 0},
    {"54. Quantos quilometros por hora um guepardo pode atingir?", {"40 km/h", "110 km/h", "80 km/h", "180 km/h"}, 1},
    {"55. Quantos coracoes possui uma minhoca?", {"1", "3", "5", "10"}, 2},
    {"56. Quantos litros de leite uma vaca produz por dia, em media?", {"3 L", "10 L", "100 L", "30 L"}, 3},
    {"57. Quantos dentes possui um tubarao-branco adulto ao mesmo tempo?", {"300", "50", "100", "1.000"}, 0},
    {"58. Quantos metros mede aproximadamente a maior cobra ja registrada?", {"6 m", "10 m", "9 m", "18 m"}, 1},
    {"59. Quantos quilometros a luz percorre em um segundo?", {"3.000 km", "30.000 km", "300.000 km", "3.000.000 km"}, 2},
    {"60. Quantas luas possui Jupiter atualmente?", {"27", "52", "180", "95"}, 3},
    {"61. Quantos dias Marte leva para dar uma volta ao Sol?", {"687", "365", "500", "1.200"}, 0},
    {"62. Quantos quilometros tem aproximadamente o diametro da Lua?", {"1.000 km", "3.474 km", "10.000 km", "20.000 km"}, 1},
    {"63. Em que ano o homem pisou na Lua?", {"1959", "1979", "1969", "1989"}, 2},
    {"64. Quantos minutos a luz do Sol leva para chegar a Terra?", {"2", "20", "60", "8"}, 3},
    {"65. Quantos quilometros tem aproximadamente o Monte Everest?", {"8,8 km", "4 km", "6 km", "12 km"}, 0},
    {"66. Quantos litros de agua doce existem no planeta em porcentagem aproximada?", {"15%", "3%", "30%", "50%"}, 1},
    {"67. Quantos metros mede aproximadamente a maior arvore do mundo?", {"40 m", "70 m", "116 m", "200 m"}, 2},
    {"68. Quantos anos vive, em media, uma rainha das abelhas?", {"1", "2", "20", "5"}, 3},
    {"69. Quantos litros de agua um elefante pode beber por dia?", {"200 L", "10 L", "50 L", "800 L"}, 0},
    {"70. Quantos anos durou a construcao das Piramides de Gize?", {"5", "20", "100", "300"}, 1},
    {"71. Quantos andares tem aproximadamente a Torre Eiffel?", {"10", "20", "3", "50"}, 2},
    {"72. Quantos sinos existem no Big Ben?", {"1", "3", "12", "5"}, 3},
    {"73. Quantos quilometros possui a Muralha da China?", {"21.000 km", "2.000 km", "8.000 km", "50.000 km"}, 0},
    {"74. Quantos anos tinha Leonardo da Vinci quando morreu?", {"47", "67", "87", "97"}, 1},
    {"75. Quantos anos viveu, aproximadamente, Albert Einstein?", {"56", "96", "76", "106"}, 2},
    {"76. Quantos filhos teve Mozart?", {"2", "4", "12", "6"}, 3},
    {"77. Quantos anos tinha Napoleao quando morreu?", {"51", "31", "71", "91"}, 0},
    {"78. Quantos metros mede aproximadamente uma girafa recem-nascida?", {"50 cm", "1,8 m", "3 m", "5 m"}, 1},
    {"79. Quantas horas por dia um coala costuma dormir?", {"6", "10", "18", "24"}, 2},
    {"80. Quantos litros de mel uma colmeia forte pode produzir por ano?", {"2 L", "10 L", "200 L", "45 L"}, 3},
    {"81. Quantas vezes por segundo um beija-flor pode bater as asas?", {"80", "5", "20", "300"}, 0},
    {"82. Quantos metros pode alcancar o salto de uma pulga em relacao ao seu tamanho?", {"10 vezes", "150 vezes", "50 vezes", "500 vezes"}, 1},
    {"83. Quantos litros de refrigerante sao consumidos por segundo no mundo?", {"100", "1.000", "10.000", "1.000.000"}, 2},
    {"84. Quantos musculos aproximadamente utilizamos para sorrir?", {"5", "50", "120", "17"}, 3},
    {"85. Quantos quilometros de vasos sanguineos existem no corpo humano?", {"100.000 km", "1.000 km", "10.000 km", "1.000.000 km"}, 0},
    {"86. Quantas vezes o coracao humano bate por dia, em media?", {"10.000", "100.000", "50.000", "500.000"}, 1},
    {"87. Quantos fios de cabelo uma pessoa possui em media?", {"10.000", "50.000", "100.000", "1.000.000"}, 2},
    {"88. Quantos litros de saliva uma pessoa produz por dia?", {"500 ml", "5 L", "20 L", "1,5 L"}, 3},
    {"89. Quantos litros de ar respiramos por dia, aproximadamente?", {"11.000 L", "500 L", "2.000 L", "100.000 L"}, 0},
    {"90. Quantos quilometros por hora pode atingir um falcao-peregrino em mergulho?", {"120 km/h", "390 km/h", "220 km/h", "700 km/h"}, 1},
    {"91. Quantos metros mede aproximadamente a lingua de uma girafa?", {"10 cm", "25 cm", "50 cm", "1 m"}, 2},
    {"92. Quantos anos viveu, aproximadamente, a pessoa mais velha ja registrada?", {"98", "110", "150", "122"}, 3},
    {"93. Quantos quilometros quadrados tem aproximadamente o Brasil?", {"8,5 milhoes", "2 milhoes", "5 milhoes", "15 milhoes"}, 0},
    {"94. Quantos estados possui o Brasil?", {"24", "26", "27", "28"}, 1},
    {"95. Quantos municipios possui o Brasil aproximadamente?", {"1.500", "3.000", "5.570", "10.000"}, 2},
    {"96. Quantos quilometros tem aproximadamente o Rio Amazonas?", {"2.000", "4.000", "12.000", "6.400"}, 3},
    {"97. Quantos litros de agua passam pelas Cataratas do Iguacu por segundo?", {"6.500", "500", "1.500", "50.000"}, 0},
    {"98. Quantos metros de altura possui aproximadamente o Cristo Redentor com pedestal?", {"20 m", "38 m", "80 m", "120 m"}, 1},
    {"99. Quantos quilometros tem aproximadamente a Ponte Rio-Niteroi?", {"3 km", "7 km", "13 km", "25 km"}, 2},
    {"100. Quantos anos durou a construcao da Catedral de Notre-Dame de Paris?", {"20", "50", "500", "182"}, 3}
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