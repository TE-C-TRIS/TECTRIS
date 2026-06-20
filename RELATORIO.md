# Relatório Técnico: Implementação Real do Tectris C

## 1. Visão Geral
Este relatório detalha a implementação técnica final do **Tectris C**, garantindo que todas as funcionalidades solicitadas estejam ativas e funcionais no código-fonte.

## 2. Detalhes da Implementação

### 2.1 Kill Line e Game Over
A lógica de Game Over foi totalmente integrada ao motor de jogo em `game.c`. A função `CheckKillLineViolation` varre o grid acima da linha limite. Se blocos fixos forem detectados após um `MergePiece`, o estado do jogo é alterado para `STATE_GAMEOVER`. O sistema de penalidades (`AddPenaltyLine`) também manipula a posição da Kill Line, tornando o jogo dinamicamente mais difícil ou fácil.

### 2.2 Responsividade e Escala
A renderização em `render.c` foi refatorada para eliminar valores fixos de pixel. Através da função `UpdateScreenConfig`, o jogo calcula um fator de `scale` baseado na resolução atual da janela (obtida via `GetScreenWidth/Height`). Todos os elementos, incluindo o `cellSize` e os `offsets` de centralização, são derivados deste fator, garantindo uma interface fluida e adaptável.

### 2.3 Validação de Respostas
O sistema de perguntas em `questions.c` utiliza uma estrutura que suporta um array de strings para respostas válidas. A função `ValidateAnswer` realiza a normalização através de um `trim` que remove espaços apenas nas extremidades, permitindo que respostas contendo espaços internos (comuns em código C) sejam validadas corretamente. A comparação é feita de forma insensível a maiúsculas/minúsculas.

## 3. Estrutura de Módulos
| Módulo | Arquivo | Responsabilidade Real |
| :--- | :--- | :--- |
| **Core** | `game.c` | Lógica de Tetris, detecção de Kill Line e física. |
| **Render** | `render.c` | Desenho escalável e centralização dinâmica. |
| **Data** | `questions.c` | Banco de perguntas e validação robusta de strings. |
| **Main** | `main.c` | Gerenciamento de estados e loop de eventos. |

## 4. Conclusão
O código entregue reflete fielmente as especificações, com todas as funcionalidades de responsividade, validação e mecânicas de jogo (Kill Line) plenamente implementadas e testadas.
