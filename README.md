
<div align="center">
  <img src="https://i.imgur.com/Ur8TtyZ.png" alt="Tectris Logo" width="400">
</div>

<div align="center">

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/TE-C-TRIS/LICENSE)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/tectris/tectris/actions)
![Version](https://img.shields.io/badge/version-1.0.0-blue)

[![GitHub commits](https://badgen.net/github/commits/TE-C-TRIS/TECTRIS)](https://github.com/TE-C-TRIS/TECTRIS/commits/)
[![GitHub latest commit](https://badgen.net/github/last-commit/TE-C-TRIS/TECTRIS)](https://badgen.net/github/last-commit/TE-C-TRIS/TECTRIS)
[![GitHub issues](https://badgen.net/github/issues/TE-C-TRIS/TECTRIS)](https://GitHub.com/TE-C-TRIS/TECTRIS/issues/)
<br>

[![GitHub Org's stars](https://img.shields.io/github/stars/TE-C-TRIS/TECTRIS.svg?style=social&label=Stars)](https://github.com/TE-C-TRIS/TECTRIS/stargazers)
[![GitHub Org's forks](https://img.shields.io/github/forks/TE-C-TRIS/TECTRIS.svg?style=social&label=Fork)](https://github.com/TE-C-TRIS/TECTRIS/fork)
[![GitHub Org's followers](https://img.shields.io/github/followers/TE-C-TRIS.svg?style=social&label=Follow)](https://github.com/TE-C-TRIS)

<br>

[![Figma](https://img.shields.io/badge/figma-%23F24E1E.svg?style=for-the-badge&logo=figma&logoColor=white)](https://www.figma.com/community/file/1629208173322160825)
[![Trello](https://img.shields.io/badge/Trello-%23026AA7.svg?style=for-the-badge&logo=Trello&logoColor=white)](https://trello.com/b/XpkqB8dX/projeto-integrado)
[![GitBook](https://img.shields.io/badge/GitBook-%23000000.svg?style=for-the-badge&logo=gitbook&logoColor=white)](https://drive.google.com/file/d/1ziHHvH0VzPCdym8xTf5XPHfrV1DrTZkW/view?usp=sharing)
</div>

<div align="center">
  <h1>Tectris: O Jogo Educacional de Lógica em C</h1>
</div>

O Tectris é um jogo educacional desenvolvido em C que combina a mecânica clássica do Tetris com desafios de lógica de programação. Durante a partida, os jogadores precisam resolver questões em tempo real para influenciar diretamente seu desempenho no jogo.

A proposta do projeto é transformar o aprendizado de lógica em uma experiência prática, dinâmica e competitiva, estimulando o raciocínio lógico, a tomada de decisões rápidas e o engajamento do usuário.

Diferente de métodos tradicionais, o Tectris integra o conhecimento à gameplay, permitindo que o jogador aprenda enquanto joga, tornando o processo mais intuitivo e eficaz.

<div align="center">
  <h2>Visão Geral do Quadro do Projeto</h2>
  <img src="https://i.imgur.com/MfuGcIR.png" alt="Tectris Logo" width="600">
  <h2>Visão do Padrão de Backlogs</h2>
  <img src="https://i.imgur.com/2GZPThl.png" alt="Tectris Gameplay" width="300">
</div>

<div align="center">
  <h2>Features</h2>
</div>

As funcionalidades do Tectris foram definidas com base em **histórias de usuário estruturadas no padrão 3Cs (Card, Conversation, Confirmation)**, garantindo rastreabilidade, clareza de requisitos e validação objetiva das entregas.

As features estão organizadas por **nível de prioridade e impacto no core do sistema**.

### Core Features (Alta Prioridade)

### 1. Sistema de Partida Local (Multiplayer Local)

| **Elemento**     | **Descrição** |
|-----------------|--------------|
| **Card**        | Como jogador, quero iniciar uma partida local contra outro jogador para competir em tempo real. |
| **Conversation** | • Execução síncrona para dois jogadores no mesmo dispositivo <br> • Inicialização simultânea de dois game loops independentes <br> • Separação lógica de estados (Player 1 e Player 2) <br> • Renderização paralela de dois tabuleiros |
| **Confirmation** | • [ ] Dois jogadores conseguem iniciar uma sessão simultânea <br> • [ ] Cada jogador possui estado isolado (grid, score, peças) <br> • [ ] Loop principal mantém sincronização entre os jogadores | 

### 2. Engine de Blocos (Core Tetris System)

| **Elemento**     | **Descrição** |
|-----------------|--------------|
| **Card**        | Como jogador, quero visualizar blocos caindo no estilo Tetris para jogar de forma intuitiva. |
| **Conversation** | • Implementação de grid 10x20 por jogador <br> • Sistema de queda automática baseado em tempo (tick rate) <br> • Controle de input (movimento lateral e rotação) <br> • Sistema de colisão e fixação de peças <br> • Geração pseudo-aleatória de peças (Tetrominos) |
| **Confirmation** | • [ ] Blocos caem com base em tempo configurável <br> • [ ] Inputs do usuário alteram posição corretamente <br> • [ ] Colisões são detectadas sem inconsistência <br> • [ ] Peças são fixadas corretamente no grid |

### 3. Sistema de Perguntas (Logic Engine)

| **Elemento**     | **Descrição** |
|-----------------|--------------|
| **Card**        | Como jogador, quero responder perguntas de lógica durante a partida para influenciar meu desempenho. |
| **Conversation** | • Sistema de eventos que dispara perguntas durante o gameplay <br> • Estrutura de dados para armazenar perguntas (array/struct) <br> • Usuário digita a resposta <br> • Associação de dificuldade a cada pergunta |
| **Confirmation** | • [ ] Perguntas são exibidas em momentos definidos do jogo <br> • [ ] Jogador consegue digitar a resposta <br> • [ ] Sistema valida a resposta corretamente <br> • [ ] Resultado é persistido no estado do jogo |

### 4. Sistema de Pontuação

| **Elemento**     | **Descrição** |
|-----------------|--------------|
| **Card**        | Como jogador, quero ganhar pontos ao acertar perguntas para medir meu desempenho. |
| **Conversation** | • Pontuação baseada na dificuldade da pergunta <br> • Atualização em tempo real do score <br> • Armazenamento separado por jogador |
| **Confirmation** | • [ ] Pontuação incrementa corretamente por acerto <br> • [ ] Valores variam conforme dificuldade <br> • [ ] Interface reflete atualização em tempo real |

### 5. Sistema de Penalidades

| **Elemento**     | **Descrição** |
|-----------------|--------------|
| **Card**        | Como jogador, quero sofrer penalidades ao errar perguntas para tornar o jogo desafiador. |
| **Conversation** | • Redução de pontuação <br> • Inserção de blocos extras (penalidade visual) <br> • Impacto direto no estado do grid |
| **Confirmation** | • [ ] Penalidade aplicada imediatamente após erro <br> • [ ] Estado do jogador é alterado corretamente <br> • [ ] Feedback visual reforça penalidade |

### 6. Sistema de Vitória

| **Elemento**     | **Descrição** |
|-----------------|--------------|
| **Card**        | Como jogador, quero que o jogo declare um vencedor ao atingir 100 pontos. |
| **Conversation** | • Definição de condição de término baseada em score <br> • Interrupção do game loop <br> • Exibição de tela de resultado |
| **Confirmation** | • [ ] Jogo encerra ao atingir 100 pontos <br> • [ ] Vencedor é corretamente identificado <br> • [ ] Interface exibe resultado final |

## Secondary Features (Média Prioridade)

### 7. Sistema de Tempo (Timer Engine)

| **Elemento**     | **Descrição** |
|-----------------|--------------|
| **Card**        | Como jogador, quero ter tempo limitado para responder perguntas para aumentar a dificuldade. |
| **Conversation** | • Timer associado a cada pergunta <br> • Redução progressiva do tempo ao longo da partida <br> • Integração com loop principal |
| **Confirmation** | • [ ] Timer é exibido na interface <br> • [ ] Tempo reduz progressivamente <br> • [ ] Resposta inválida ao expirar o tempo |

### 8. Interface do Usuário (UI Layer)

| **Elemento**     | **Descrição** |
|-----------------|--------------|
| **Card**        | Como jogador, quero uma interface clara para entender o jogo facilmente. |
| **Conversation** | • Layout dividido em três áreas (Player 1, Centro, Player 2) <br> • Exibição de score, tempo e perguntas <br> • Hierarquia visual definida |
| **Confirmation** | • [ ] Interface apresenta informações essenciais <br> • [ ] Elementos são legíveis e organizados <br> • [ ] Navegação é intuitiva |

### 9. Banco de Perguntas Local

| **Elemento**     | **Descrição** |
|-----------------|--------------|
| **Card**        | Como sistema, quero carregar perguntas locais para manter o jogo funcional offline. |
| **Conversation** | • Armazenamento em estrutura estática (array/struct) <br> • Carregamento em memória na inicialização <br> • Sem dependência de serviços externos |
| **Confirmation** | • [ ] Perguntas são carregadas corretamente <br> • [ ] Sistema funciona sem conexão externa <br> • [ ] Estrutura de dados é acessível durante o jogo |

## Advanced Features (Baixa Prioridade / Diferencial)

### 10. Sistema Competitivo (Interação entre jogadores)

| **Elemento**     | **Descrição** |
|-----------------|--------------|
| **Card**        | Como jogador, quero afetar o adversário ao acertar perguntas para aumentar a competitividade. |
| **Conversation** | • Eventos que impactam o estado do adversário <br> • Exemplo: forçar nova pergunta, atrasar progresso <br> • Sincronização entre estados dos jogadores |
| **Confirmation** | • [ ] Ação de um jogador afeta o outro <br> • [ ] Sistema mantém consistência entre estados <br> • [ ] Feedback visual é exibido |

### 11. Dificuldade Progressiva

| **Elemento**     | **Descrição** |
|-----------------|--------------|
| **Card**        | Como jogador, quero que o jogo fique mais difícil ao longo do tempo. |
| **Conversation** | • Aumento da velocidade de queda <br> • Redução do tempo de resposta <br> • Escalonamento baseado em tempo de jogo |
| **Confirmation** | • [ ] Velocidade aumenta gradualmente <br> • [ ] Tempo de resposta diminui <br> • [ ] Jogabilidade se torna mais desafiadora |

### 12. Sistema de Feedback Visual

| **Elemento**     | **Descrição** |
|-----------------|--------------|
| **Card**        | Como jogador, quero receber feedback visual ao responder perguntas. |
| **Conversation** | • Uso de cores semânticas (verde/vermelho) <br> • Animações de resposta <br> • Destaque visual de estados |
| **Confirmation** | • [ ] Feedback imediato ao responder <br> • [ ] Cores representam corretamente o estado <br> • [ ] Interface reforça ações do usuário |

### 13. Sistema de Estatísticas de Desempenho

| **Elemento**     | **Descrição** |
|-----------------|--------------|
| **Card**        | Como jogador, quero visualizar estatísticas do meu desempenho ao final da partida para entender minha evolução. |
| **Conversation** | • Cálculo de média de pontuação entre as rodadas <br> • Identificação do melhor e pior desempenho registrado <br> • Exibição dos dados em formato de relatório <br> • Dados calculados a partir do histórico de scores do jogador |
| **Confirmation** | • [ ] Média de desempenho é calculada corretamente <br> • [ ] Melhor e pior resultado são identificados e exibidos <br> • [ ] Relatório é gerado ao encerrar a partida <br> • [ ] Dados refletem o histórico real da sessão |

### 14. Funções Recursivas de Análise

| **Elemento**     | **Descrição** |
|-----------------|--------------|
| **Card**        | Como sistema, quero utilizar funções recursivas para calcular operações matemáticas sobre os dados da partida para garantir precisão analítica. |
| **Conversation** | • Implementação recursiva de soma total de pontos <br> • Funções recursivas para mínimo e máximo do histórico <br> • Cálculo recursivo da soma dos quadrados para análise de variância <br> • Funções isoladas e reutilizáveis pelo sistema |
| **Confirmation** | • [ ] Função recursiva de soma retorna valor correto <br> • [ ] Mínimo e máximo são identificados via recursão <br> • [ ] Soma dos quadrados é calculada sem erros <br> • [ ] Funções operam corretamente sobre o histórico de dados |

### 15. Heurísticas Textuais de Estratégia

| **Elemento**     | **Descrição** |
|-----------------|--------------|
| **Card**        | Como jogador, quero receber dicas e mensagens estratégicas durante a partida para orientar minhas decisões de jogo. |
| **Conversation** | • Geração de mensagens textuais baseadas no estado atual do jogo <br> • Heurísticas que analisam desempenho e sugerem ações <br> • Integração com o loop principal para exibição contextual <br> • Mensagens adaptadas ao nível de pontuação do jogador |
| **Confirmation** | • [ ] Mensagens são exibidas em momentos relevantes do jogo <br> • [ ] Conteúdo das dicas é coerente com o estado da partida <br> • [ ] Heurísticas analisam corretamente os dados disponíveis <br> • [ ] Jogador consegue ler e compreender as orientações |

[Vídeo das Funcionalidades da Semana 3](https://youtu.be/YD0pkZ8R3CI)

[Vídeo das Funcionalidades da Semana 4 (entrega final)](https://canva.link/jm0du2mh5azwsbt)

## Backlog — Sistema de Adivinhação (Alta Prioridade)

### 1. Sorteio do número secreto

| **Elemento**     | **Descrição** |
|-----------------|--------------|
| **Card**        | Como sistema, quero gerar um número aleatório para que o jogador tenha um desafio de adivinhação durante a partida. |
| **Conversation** | • Geração de número pseudo-aleatório <br> • Intervalo definido (ex: 1 a 10 ou 1 a 100) <br> • Número oculto para o jogador |
| **Confirmation** | • [ ] Número é gerado a cada nova rodada <br> • [ ] Valor está dentro do intervalo definido <br> • [ ] Número não é exibido ao jogador |

### 2. Loop de adivinhação

| **Elemento**     | **Descrição** |
|-----------------|--------------|
| **Card**        | Como jogador, quero tentar adivinhar o número até acertar para progredir no jogo. |
| **Conversation** | • Sistema deve permitir múltiplas tentativas <br> • Loop continua até acerto ou condição de parada <br> • Integração com fluxo principal do jogo |
| **Confirmation** | • [ ] Jogador pode inserir múltiplas tentativas <br> • [ ] Loop continua enquanto não houver acerto <br> • [ ] Loop é encerrado corretamente ao acertar |


### 3. Validação da entrada

| **Elemento**     | **Descrição** |
|-----------------|--------------|
| **Card**        | Como sistema, quero validar a entrada do jogador para evitar erros e garantir funcionamento correto. |
| **Conversation** | • Verificar se entrada é numérica <br> • Validar se está dentro do intervalo permitido <br> • Tratar entradas inválidas |
| **Confirmation** | • [ ] Entrada inválida é identificada <br> • [ ] Sistema impede valores fora do intervalo <br> • [ ] Mensagem de erro é exibida quando necessário |

## Backlog — Sistema de Adivinhação (Média Prioridade)

### 4. Feedback: “Muito baixo” 

| **Elemento**     | **Descrição** |
|-----------------|--------------|
| **Card**        | Como jogador, quero saber quando meu palpite está abaixo do valor correto para ajustar minha estratégia. |
| **Conversation** | • Comparação entre palpite e número secreto <br> • Feedback textual exibido na interface |
| **Confirmation** | • [ ] Sistema identifica quando valor é menor <br> • [ ] Mensagem “Muito baixo” é exibida corretamente |


### 5. Feedback: “Muito alto”

| **Elemento**     | **Descrição** |
|-----------------|--------------|
| **Card**        | Como jogador, quero saber quando meu palpite está acima do valor correto para ajustar minha estratégia. |
| **Conversation** | • Comparação entre palpite e número secreto <br> • Feedback textual exibido na interface |
| **Confirmation** | • [ ] Sistema identifica quando valor é maior <br> • [ ] Mensagem “Muito alto” é exibida corretamente |

## Backlog — Sistema de Adivinhação (Baixa Prioridade)

### 6. Feedback: “Acertou”

| **Elemento**     | **Descrição** |
|-----------------|--------------|
| **Card**        | Como jogador, quero ser informado quando acertar o número para receber recompensa no jogo. |
| **Conversation** | • Comparação direta entre palpite e número secreto <br> • Integração com sistema de pontuação |
| **Confirmation** | • [ ] Sistema identifica acerto corretamente <br> • [ ] Mensagem “Acertou” é exibida <br> • [ ] Pontuação ou bônus é aplicado |


<div align="center">
  <h2>Protótipo Inicial</h2>
</div>

O protótipo inicial do Tectris foi desenvolvido com o objetivo de validar conceitos fundamentais de interação, fluxo de navegação e organização da interface, antes da implementação visual definitiva.

A abordagem adotada priorizou **alta fidelidade**, permitindo fiel iteração, coleta de feedback e ajustes baseados em princípios de Interação Humano-Computador (IHC).

<div align="center">

<img src="https://i.imgur.com/FZy8ieA.jpeg" alt="Tela Inicial" width="600">
<img src="https://i.imgur.com/L0rBGcN.jpeg" alt="Protótipo Baixa Fidelidade" width="600">
<img src="https://i.imgur.com/O48SvYZ.jpeg" alt="Protótipo Baixa Fidelidade" width="600">
<img src="https://i.imgur.com/kl5SFfg.jpeg" alt="Protótipo Baixa Fidelidade" width="600">
<img src="https://i.imgur.com/AJKFPEK.jpeg" alt="Protótipo Baixa Fidelidade" width="600">
<img src="https://i.imgur.com/GhrwawJ.jpeg" alt="Protótipo Baixa Fidelidade" width="600">
<img src="https://i.imgur.com/jwwL8aH.jpeg" alt="Protótipo Baixa Fidelidade" width="600">
<img src="https://i.imgur.com/kPxYGCu.jpeg" alt="Protótipo Baixa Fidelidade" width="600">
<img src="https://i.imgur.com/GfDJEGy.jpeg" alt="Protótipo Baixa Fidelidade" width="600">
</div>

[Assista ao vídeo de demostração](https://drive.google.com/file/d/1S764_kXx2NakTjTYahh-2aGr6Ac7MYS-/view?usp=sharing)


### Objetivos do Protótipo

- Validar a estrutura geral da interface  
- Definir o fluxo principal do jogo  
- Testar a disposição dos elementos em tela  
- Reduzir complexidade antes da implementação visual  
- Identificar problemas de usabilidade precocemente  

### Estrutura da Interface

O layout foi organizado em **três áreas principais**:


| 🟨 Player 1 (Esquerda) |  Centro (Interação) | 🟦 Player 2 (Direita) |
|----------------------|----------------------|----------------------|
| Tabuleiro (grid 10x20) | Logo do jogo | Tabuleiro (grid 10x20) |
| Área de próxima peça (NEXT) | Card de pergunta (código + alternativas) | Área de próxima peça |
| Exibição de pontuação | Botões de resposta | Exibição de pontuação |
|  | Barra de tempo |  |
|  | Contador de tempo |  |

<div align="center">
  <h2>Diagramas UML das Funcionalidades</h2>
</div>

Clique no titulo da funcionalidade para acessar o diagrama correspondente completo

| Funcionalidade | Diagrama | Funcionalidade | Diagrama | Funcionalidade | Diagrama |
|---------------|----------|----------------|----------|----------------|----------|
| **[UC01. Jogar partida local](./docs/README.md#uc01)** | ![Diagrama 1](https://i.imgur.com/vebaX5k.png) | **[UC02. Sistema de queda de blocos](./docs/README.md#uc02)** | ![Diagrama 2](https://i.imgur.com/8iNoBy2.png) | **[UC03. Perguntas de lógica durante o jogo](./docs/README.md#uc03-perguntas-de-lógica-durante-o-jogo)** | ![Diagrama 3](https://i.imgur.com/SXaUZCj.png) |
| **[UC04. Sistema de pontuação](./docs/README.md#uc04)** | ![Diagrama 4](https://i.imgur.com/LtrreYu.png) | **[UC05. Penalidade por erro](./docs/README.md#uc05)** | ![Diagrama 5](https://i.imgur.com/i42ltmm.png) | **[UC06. Sistema de vitória](./docs/README.md#uc06)** | ![Diagrama 6](https://i.imgur.com/tEdaKlH.png) |
| **[UC07. Sistema de tempo nas perguntas](./docs/README.md#uc07)** | ![Diagrama 7](https://i.imgur.com/UiL9VbL.png) | **[UC08. Efeito competitivo (impactar adversário)](./docs/README.md#uc08)** | ![Diagrama 8](https://i.imgur.com/PtGES5N.png) | **[UC09. Interface do jogo (UI básica)](./docs/README.md#uc09)** | ![Diagrama 9](https://i.imgur.com/Ujh8yhA.png) |
| **[UC10. Banco de perguntas (fixo/local)](./docs/README.md#uc10)** | ![Diagrama 10](https://i.imgur.com/mYMl6ge.png) | **[UC11. Aumento de dificuldade progressiva](./docs/README.md#uc11)** | ![Diagrama 11](https://i.imgur.com/T2FLBtS.png) | **[UC12. Feedback visual (acerto/erro)](./docs/README.md#uc12)** | ![Diagrama 12](https://i.imgur.com/jcvvJgt.png) |
| **[UC13. Sorteio do número secreto](./docs/README.md#uc13)** | ![Diagrama 13](https://i.imgur.com/RQbEro7.png) | **[UC14. Loop de adivinhação](./docs/README.md#uc14)** | ![Diagrama 14](https://i.imgur.com/JmUcAZ6.png) | **[UC15. Validação da entrada](./docs/README.md#uc15)** | ![Diagrama 15](https://i.imgur.com/OH9xhdq.png) |
| **[UC16. Feedback: "Muito baixo"](./docs/README.md#uc16)** | ![Diagrama 16](https://i.imgur.com/fOJ7Z6r.png) | **[UC17. Feedback: "Muito alto"](./docs/README.md#uc17)** | ![Diagrama 17](https://i.imgur.com/LQt8fTZ.png) | **[UC18. Feedback: "Acertou"](./docs/README.md#uc18)** | ![Diagrama 18](https://i.imgur.com/KagHfsw.png) |

<div align="center">
  <h2>Decisões de Design (IHC)</h2>
</div>

O protótipo foi projetado com base em princípios de usabilidade:

- **Visibilidade do sistema:**  
  Timer e pontuação sempre visíveis  

- **Feedback imediato:**  
  Respostas geram retorno instantâneo  

- **Consistência:**  
  Estrutura simétrica entre jogadores  

- **Reconhecimento ao invés de memorização:**  
  Interface clara e previsível  

### Testes Iniciais

O protótipo foi utilizado em testes rápidos com usuários simulados para avaliar:

- Facilidade de compreensão da interface  
- Clareza das ações disponíveis  
- Tempo de resposta às perguntas  
- Entendimento do fluxo do jogo  


### Principais Ajustes Identificados

- Necessidade de destacar melhor o tempo restante  
- Melhorar hierarquia visual da pergunta  
- Ajustar tamanho dos botões de resposta  
- Reforçar feedback visual (cores e animações)  

### Ferramentas Utilizadas

- Figma (prototipação e wireframe)  
- Estrutura baseada em grid e componentes reutilizáveis  


### Evolução do Protótipo

O protótipo de baixa fidelidade serviu como base para:
- Definição do design system  
- Construção do protótipo de alta fidelidade  
- Validação de critérios de usabilidade  

### Considerações

A utilização de prototipação inicial permitiu identificar problemas de interação antes da implementação, reduzindo retrabalho e melhorando a experiência do usuário desde as primeiras etapas do projeto.

<!-- 
## 🎨 Design System

O Design System do Tectris foi desenvolvido com o objetivo de garantir **consistência visual, escalabilidade e usabilidade**, seguindo princípios de Interação Humano-Computador (IHC) e heurísticas de Nielsen.

A padronização dos elementos visuais permite maior previsibilidade da interface, reduzindo a carga cognitiva do usuário e facilitando a interação.

---

### 🎯 Princípios de Design

O sistema visual foi orientado pelos seguintes princípios:

- **Consistência:** padronização de cores, tipografia e componentes  
- **Feedback imediato:** uso de cores e estados para indicar ações  
- **Visibilidade do sistema:** exibição clara de status (tempo, pontuação)  
- **Reconhecimento ao invés de memorização:** elementos visuais intuitivos  
- **Acessibilidade:** contraste adequado e redundância de informação  

---

### 🎨 Paleta de Cores

As cores foram definidas com base em significado semântico, inspiradas no universo do Tetris:

#### 🎮 Cores Primárias
- Player 1: `#3ABEFF` (azul)  
- Player 2: `#FF8C42` (laranja)  
- Accent/UI: `#9B5CFF` (roxo)  

#### ⚠️ Cores de Feedback
- Sucesso: `#4CAF50` (verde)  
- Erro: `#E53935` (vermelho)  
- Atenção/Tempo: `#FFD93D` (amarelo)  

#### 🖥️ Cores de Interface
- Fundo principal: `#1E1E2F`  
- Painéis: `#2A2A40`  
- Bordas: `#3A3A5A`  
- Texto principal: `#FFFFFF`  
- Texto secundário: `#B0B0C3`  

As cores são utilizadas de forma consistente para indicar estados do sistema, promovendo reconhecimento rápido por parte do usuário.

---

### ✍️ Tipografia

A tipografia foi escolhida para garantir legibilidade e identidade visual:

- **Títulos:** fonte com estilo futurista (ex: Orbitron)  
- **Texto:** fonte sans-serif (ex: Inter ou Roboto)  
- **Código:** fonte monoespaçada (ex: Courier New)  

#### Hierarquia Tipográfica
- Títulos principais: destaque e alto contraste  
- Textos secundários: leitura contínua  
- Elementos técnicos: monoespaçados para clareza  

---

### 🧩 Componentes

O sistema é composto por componentes reutilizáveis:

#### 🎮 Tabuleiro (Game Board)
- Grid estruturado (10x20)  
- Representação visual das peças  
- Estados: normal, crítico  

#### 🔘 Botões de Resposta
- Estados:
  - Default  
  - Hover  
  - Selecionado  
  - Correto (verde)  
  - Incorreto (vermelho)  

#### ⏳ Barra de Tempo
- Indicador visual progressivo  
- Mudança de cor conforme urgência  

#### 📦 Card de Pergunta
- Área de código  
- Pergunta textual  
- Opções de resposta  

#### 🔢 Score Display
- Exibição clara da pontuação  
- Diferenciação por jogador  

---

### 🔄 Estados da Interface

O sistema utiliza estados visuais para representar mudanças no sistema:

| Estado   | Cor        | Significado              |
|----------|------------|--------------------------|
| Idle     | Roxo       | Estado neutro            |
| Ativo    | Azul/Laranja | Jogador em ação         |
| Sucesso  | Verde      | Ação correta             |
| Erro     | Vermelho   | Ação incorreta           |
| Atenção  | Amarelo    | Tempo ou alerta          |

---

### 📐 Layout e Grid

- Sistema de espaçamento baseado em múltiplos de 8px  
- Layout dividido em três áreas principais:
  - Player 1  
  - Centro (interação)  
  - Player 2  
- Alinhamento consistente e uso de hierarquia visual  

---

### ♿ Acessibilidade

- Alto contraste entre texto e fundo  
- Uso de cores combinado com feedback visual adicional  
- Evita dependência exclusiva de cor para comunicação  
- Interface projetada para rápida compreensão  

---

### 🧠 Considerações

O Design System do Tectris foi estruturado para suportar a evolução do projeto, garantindo coerência visual e eficiência na construção da interface, ao mesmo tempo em que melhora a experiência do usuário por meio de princípios sólidos de usabilidade. -->

<div align="center">
  <h2> Arquitetura do Sistema</h2>
</div>

O Tectris foi desenvolvido seguindo uma arquitetura modular, com separação de responsabilidades, visando facilitar a manutenção, escalabilidade e organização do código.

A aplicação adota um modelo baseado em camadas lógicas, estruturado em componentes independentes que se comunicam por meio de interfaces bem definidas.

### Organização Modular

O sistema é dividido nos seguintes módulos principais:

- **Core:** responsável pelo controle do loop principal do jogo, gerenciamento de estados e sincronização das execuções.
- **Game Engine:** implementa as regras do Tetris, incluindo movimentação, rotação, colisão e fixação de blocos.
- **Logic Engine:** gerencia o sistema de perguntas, validação de respostas e aplicação de efeitos no jogo.
- **UI Layer:** responsável pela renderização dos elementos visuais e exibição das informações ao usuário.
- **Input Handler:** trata as entradas do usuário, convertendo interações em ações no sistema.
- **Utils:** contém funções auxiliares reutilizáveis.


### Fluxo de Execução

A execução do sistema segue um ciclo contínuo baseado em um game loop:

1. Inicialização dos estados do jogo  
2. Captura de entrada do usuário  
3. Atualização da lógica do jogo  
4. Processamento de eventos (ex: perguntas)  
5. Renderização da interface  
6. Repetição do ciclo até condição de término  


### Gerenciamento de Estado

Cada jogador possui um estado independente, contendo:

- Grid (tabuleiro)  
- Peça atual e próxima  
- Pontuação  
- Status de jogo  

Essa separação garante isolamento lógico e evita interferência direta entre os jogadores, exceto em eventos competitivos controlados.

### Comunicação entre Módulos

A comunicação entre os módulos ocorre de forma desacoplada, por meio de chamadas de função e estruturas de dados compartilhadas, reduzindo dependências e aumentando a coesão interna de cada componente.

### Considerações Arquiteturais

A arquitetura foi projetada para:

- Garantir clareza na separação de responsabilidades  
- Facilitar testes e manutenção  
- Permitir evolução incremental do sistema  
- Suportar futuras extensões, como novos modos de jogo  

### Limitações

Por se tratar de uma aplicação local, a arquitetura não contempla:

- Comunicação em rede  
- Persistência em banco de dados  
- Processamento distribuído  

## Mecânica do Jogo

A mecânica do Tectris integra elementos clássicos do Tetris com um sistema interativo de resolução de problemas, criando uma experiência híbrida entre jogo e aprendizado.


### Sistema de Blocos

O jogo utiliza um grid bidimensional de dimensões 10x20 para cada jogador, no qual peças (tetrominós) são geradas e inseridas continuamente.

As principais regras incluem:

- Queda automática de peças baseada em um intervalo de tempo (tick rate)  
- Movimentação lateral e rotação controladas pelo usuário  
- Detecção de colisão com limites do grid e outras peças  
- Fixação da peça ao atingir uma posição válida final  

Esse sistema constitui o núcleo da jogabilidade, exigindo coordenação motora e percepção espacial.


### Sistema de Perguntas

Durante a execução do jogo, eventos de interrupção são acionados para apresentar perguntas de lógica de programação aos jogadores.

Características principais:

- Perguntas exibidas simultaneamente para ambos os jogadores  
- Estrutura com múltiplas alternativas (2 a 3 opções)  
- Conteúdo baseado em conceitos fundamentais da linguagem C  

A resposta do jogador impacta diretamente o estado do jogo, integrando aprendizado à mecânica principal.

### Sistema de Recompensa e Penalidade

O sistema de progressão é baseado na relação entre acertos e erros:

- **Acerto:**
  - Incremento de pontuação  
  - Possível vantagem estratégica (ex: impacto no adversário)  

- **Erro:**
  - Redução de pontuação  
  - Aplicação de penalidades (ex: inserção de blocos adicionais)  

Esse equilíbrio promove um ambiente competitivo e dinâmico.

### Condição de Vitória

A partida é encerrada quando um dos jogadores atinge a pontuação máxima estabelecida (100 pontos).

Ao término:
- O loop principal é interrompido  
- O vencedor é identificado e exibido na interface  

### Mecânica Competitiva

O jogo incorpora interação indireta entre os jogadores, onde ações individuais podem afetar o adversário.

Exemplos:
- Ativação de eventos que forçam o oponente a responder novas perguntas  
- Alterações no ritmo de jogo do adversário  

Essa mecânica adiciona uma camada estratégica ao gameplay.

### Sistema de Tempo

Cada pergunta possui um tempo limite para resposta, controlado por um sistema de temporização integrado ao loop principal.

- O tempo disponível diminui progressivamente ao longo da partida  
- A ausência de resposta dentro do limite é tratada como erro  

Esse mecanismo aumenta a pressão cognitiva e a intensidade do jogo.

###  Progressão de Dificuldade

A dificuldade do jogo evolui dinamicamente com base no tempo de execução:

- Aumento da velocidade de queda das peças  
- Redução do tempo de resposta das perguntas  

Essa progressão garante manutenção do desafio e engajamento contínuo.

###  Considerações

A mecânica do Tectris foi projetada para integrar habilidades cognitivas (raciocínio lógico) e motoras (controle de peças), promovendo uma experiência de aprendizado ativa e competitiva.
sistema competitivo
- O Tectris pode incluir um modo multiplayer, onde jogadores competem em tempo real para ver quem consegue a maior pontuação ou eliminar mais linhas.
- Rankings online para incentivar a competição e o engajamento contínuo.

<div align="center">

<div align="center">
  <h2>Gestão do Projeto</h2>
</div>

|                            <img width="120" src="https://github.com/LarissamnLira.png">                           |                        <img width="120" src="https://github.com/alicessena.png">                        |                      <img width="120" src="https://github.com/jaozinnm.png">                     |
| :---------------------------------------------------------------------------------------------------------------: | :-----------------------------------------------------------------------------------------------------: | :----------------------------------------------------------------------------------------------: |
|                                                  **Larissa Lira**                                                 |                                              **Alice Sena**                                             |                                      **João Rafael Morato**                                      |
|                                               **Product Owner (PO)**                                              |                                             **Scrum Master**                                            |                                           **Tech Lead**                                          |
| 🔗 [LinkedIn](https://www.linkedin.com/in/larissa-morais-566833399/) • [GitHub](https://github.com/LarissamnLira) | 🔗 [LinkedIn](https://www.linkedin.com/in/alicessenapereira/) • [GitHub](https://github.com/alicessena) | 🔗 [LinkedIn](https://www.linkedin.com/in/joao-rafaell/) • [GitHub](https://github.com/jaozinnm) |

<br>


<div align="center">
  <h2>Equipe de Desenvolvimento</h2>
</div>


|                               <img width="120" src="https://github.com/emilyraquel.png">                              |                           <img width="120" src="https://github.com/cecilialopess.png">                          |                           <img width="120" src="https://github.com/MatheusSrp.png">                          |
| :-------------------------------------------------------------------------------------------------------------------: | :-------------------------------------------------------------------------------------------------------------: | :----------------------------------------------------------------------------------------------------------: |
|                                                    **Emily Raquel**                                                   |                                                **Cecília Lopes**                                                |                                                **Matheus Vaz**                                               |
|                                              **Desenvolvedora Frontend**                                              |                                           **Desenvolvedora Frontend**                                           |                                           **Desenvolvedor Backend**                                          |
| 🔗 [LinkedIn](https://www.linkedin.com/in/emily-raquel-marques-5abb523b7/) • [GitHub](https://github.com/emilyraquel) | 🔗 [LinkedIn](https://www.linkedin.com/in/cec%C3%ADlia-lopes3107/) • [GitHub](https://github.com/cecilialopess) | 🔗 [LinkedIn](https://www.linkedin.com/in/matheus-nascimento-vaz/) • [GitHub](https://github.com/MatheusSrp) |

<br>

|                             <img width="120" src="https://github.com/keziaguiar12.png">                             |                            <img width="120" src="https://github.com/dioguis.png">                           |
| :-----------------------------------------------------------------------------------------------------------------: | :---------------------------------------------------------------------------------------------------------: |
|                                                   **Kezia Aguiar**                                                  |                                              **Diogo Alcelino**                                             |
|                                                     **Designer**                                                    |                                                 **Designer**                                                |
| 🔗 [LinkedIn](https://www.linkedin.com/in/kezia-albuquerque-450522264/) • [GitHub](https://github.com/keziaguiar12) | 🔗 [LinkedIn](https://www.linkedin.com/in/diogo-alcelino-959690212/) • [GitHub](https://github.com/dioguis) |

</div>

## 🤝 Como Contribuir

Contribuições são sempre bem-vindas! Se você deseja ajudar no desenvolvimento do **Tectris**, siga os passos abaixo:

### 1. Faça um Fork do Projeto

Crie uma cópia deste repositório em sua conta GitHub.

### 2. Crie uma Branch

Crie uma branch para desenvolver sua funcionalidade ou correção:

```bash
git checkout -b feature/minha-feature
```

### 3. Desenvolva sua Solução

Implemente a melhoria seguindo os padrões de código e organização do projeto.

### 4. Realize Testes

Verifique se sua alteração não impacta funcionalidades existentes e se está funcionando corretamente.

### 5. Faça Commit das Alterações

Utilize mensagens de commit claras e descritivas:

```bash
git commit -m "feat: adiciona sistema de ranking"
```

### 6. Envie para o seu Fork

```bash
git push origin feature/minha-feature
```

### 7. Abra um Pull Request

Abra um Pull Request descrevendo:

* O que foi desenvolvido;
* O problema resolvido;
* Possíveis impactos da alteração;
* Evidências (prints, vídeos ou testes realizados).

### Boas Práticas

* Mantenha o código organizado e documentado;
* Utilize nomes claros para variáveis e funções;
* Respeite a arquitetura e estrutura do projeto;
* Documente novas funcionalidades quando necessário;
* Verifique se não existem Pull Requests semelhantes antes de criar um novo.

Agradecemos seu interesse em contribuir com o Tectris! 🚀


<div align="center">
  <h2>licença</h2>
</div>

MIT License

Copyright (c) 2026 TE-C-TRIS

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


