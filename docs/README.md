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

[![Figma](https://img.shields.io/badge/figma-%23F24E1E.svg?style=for-the-badge&logo=figma&logoColor=white)](https://www.figma.com/design/kRNpjNgWIFwauorghAjyIY/Tectris-Design-System---Primeira-Vers%C3%A3o?node-id=64-3864&p=f&t=RYiLQKL7cvNZuk9i-0)
[![Trello](https://img.shields.io/badge/Trello-%23026AA7.svg?style=for-the-badge&logo=Trello&logoColor=white)](https://trello.com/invite/b/69cadb5e6451c7e81081f2af/ATTI17b970f7bb190cbabe4d257b4311c5dfC761625F/projeto-integrado)

</div>

# Diagramas UML das Funcionalidades

Os <b>diagramas UML (Unified Modeling Language)</b> são representações visuais utilizadas para descrever, planejar e documentar sistemas de software. Eles permitem visualizar a estrutura e o comportamento da aplicação, facilitando o entendimento das funcionalidades e dos fluxos do sistema.

A utilização de diagramas UML é importante, pois ajuda a organizar as ideias antes da implementação, melhora a comunicação entre os membros da equipe e garante maior clareza sobre como o sistema deve funcionar. Além disso, servem como documentação do projeto, permitindo que outras pessoas compreendam e contribuam com mais facilidade no desenvolvimento.

## Guia Rápido de Diagramas UML (Atividades)

| Formato da Forma                                      | Descrição                                                                       | Exemplo (o que ilustrar)                             |
| ----------------------------------------------------- | ------------------------------------------------------------------------------- | ---------------------------------------------------- |
| 🔵 Círculo preenchido (Início)                        | Representa o ponto inicial do fluxo do sistema                                  | Tela inicial do jogo sendo aberta                    |
| ⚫ Círculo com borda (Fim)                            | Indica o final de um fluxo ou processo                                          | Fim de uma partida ou término de uma ação            |
| ⬛ Retângulo (Ação)                                   | Representa uma ação ou etapa executada no sistema                               | "Exibir pergunta", "Mover peça", "Validar resposta"  |
| 🔷 Losango (Decisão)                                  | Representa uma condição (if/else), onde o fluxo pode seguir caminhos diferentes | "Resposta correta?" ou "Colidiu?"                    |
| ➡️ Seta (Fluxo)                                       | Indica a direção do fluxo entre as etapas                                       | Ligação entre ações (ex: da pergunta para validação) |
| 🟦 Retângulo com borda dupla (Subprocesso - opcional) | Representa um processo mais complexo que pode ser detalhado em outro diagrama   | "Processar pontuação" ou "Gerenciar lógica do jogo"  |
| 🧍‍♂️ Swimlane (Raia - opcional)                         | Divide responsabilidades entre usuário e sistema                                | Separar ações do jogador e do sistema no diagrama    |

# Diagrama dos BackLogs

## UC01
UC01. Jogar partida local 

```mermaid
stateDiagram-v2

[*] --> Iniciar_Partida

state Iniciar_Partida {
    [*] --> Inicializar_Jogadores
    Inicializar_Jogadores --> Iniciar_Queda_Blocos
}

Iniciar_Partida --> Pergunta_Ativa

state Pergunta_Ativa {
    [*] --> Exibir_Pergunta
    Exibir_Pergunta --> Aguardar_Resposta
    Aguardar_Resposta --> Capturar_Resposta : primeiro jogador responde
}

Pergunta_Ativa --> Validar_Resposta

state Validar_Resposta {
    [*] --> Verificar_Correcao

    Verificar_Correcao --> Adicionar_Pontos : resposta correta
    Verificar_Correcao --> Aplicar_Penalidade : resposta incorreta

    Adicionar_Pontos --> Atualizar_Pontuacao
    Aplicar_Penalidade --> Atualizar_Pontuacao
}

Validar_Resposta --> Feedback

state Feedback {
    [*] --> Exibir_Feedback
}

Feedback --> Verificar_Vitoria

state Verificar_Vitoria {
    [*] --> Checar_Pontuacao

    Checar_Pontuacao --> Pergunta_Ativa : nenhum jogador >=100
    Checar_Pontuacao --> Determinar_Vencedor : jogador >=100
}

Determinar_Vencedor --> [*]
```

## UC02
UC02. Sistema de queda de blocos 

```mermaid
stateDiagram-v2

[*] --> Iniciar_Partida

Iniciar_Partida --> Gerar_Bloco

state Gerar_Bloco {
    [*] --> Novo_Bloco
}

Gerar_Bloco --> Queda_Ativa

state Queda_Ativa {

    [*] --> Bloco_Caindo

    Bloco_Caindo --> Movimento_Lateral : mover esquerda/direita
    Movimento_Lateral --> Rotacao

    Bloco_Caindo --> Rotacao : sem movimento lateral

    Rotacao --> Atualizar_Rotacao : rotacionar
    Rotacao --> Verificar_Colisao : sem rotação

    Atualizar_Rotacao --> Verificar_Colisao

    Verificar_Colisao --> Bloco_Caindo : sem colisão
    Verificar_Colisao --> Fixar_Bloco : colisão
}

Queda_Ativa --> Processar_Tabuleiro

state Processar_Tabuleiro {

    [*] --> Fixar_Bloco

    Fixar_Bloco --> Verificar_Linha

    Verificar_Linha --> Atualizar_Pontuacao : linha completa
    Verificar_Linha --> Gerar_Bloco : nenhuma linha completa

    Atualizar_Pontuacao --> Gerar_Bloco
}

Gerar_Bloco --> Queda_Ativa
```

## UC03
UC03. Perguntas de lógica durante o jogo

```mermaid
stateDiagram-v2

[*] --> Partida_Em_Andamento

Partida_Em_Andamento --> Pergunta_Ativa

state Pergunta_Ativa {

    [*] --> Exibir_Pergunta

    Exibir_Pergunta --> Receber_Resposta

    Receber_Resposta --> Receber_Resposta : entrada inválida
    Receber_Resposta --> Registrar_Resposta : entrada válida
}

Pergunta_Ativa --> Avaliar_Resposta

state Avaliar_Resposta {

    [*] --> Verificar_Correcao

    Verificar_Correcao --> Aplicar_Beneficio : resposta correta
    Verificar_Correcao --> Aplicar_Penalidade : resposta incorreta
}

Avaliar_Resposta --> Retornar_Partida

state Retornar_Partida {
    [*] --> Continuar_Jogo
}

Retornar_Partida --> [*]
```

## UC04
UC04. Sistema de pontuação baseado na dificuldade da pergunta

```mermaid
stateDiagram-v2

[*] --> Resposta_Correta_Registrada

Resposta_Correta_Registrada --> Avaliar_Dificuldade

state Avaliar_Dificuldade {

    [*] --> Verificar_Dificuldade

    Verificar_Dificuldade --> Pontuacao_Basica : fácil
    Verificar_Dificuldade --> Pontuacao_Intermediaria : média
    Verificar_Dificuldade --> Pontuacao_Avancada : difícil
}

Avaliar_Dificuldade --> Atualizar_Pontos

state Atualizar_Pontos {

    [*] --> Pontuacao_Basica
    Pontuacao_Basica --> Atualizar_Pontuacao

    [*] --> Pontuacao_Intermediaria
    Pontuacao_Intermediaria --> Atualizar_Pontuacao

    [*] --> Pontuacao_Avancada
    Pontuacao_Avancada --> Atualizar_Pontuacao
}

Atualizar_Pontos --> Exibir_Interface

state Exibir_Interface {
    [*] --> Mostrar_Pontuacao
}

Exibir_Interface --> [*]
```

## UC05
UC05. Penalidade por erro

```mermaid
stateDiagram-v2

[*] --> Resposta_Incorreta

Resposta_Incorreta --> Perda_Pontos

Perda_Pontos --> Bloco_Penalidade : penalidade adicional
Perda_Pontos --> Fluxo_Normal : sem penalidade extra

Bloco_Penalidade --> Impacto_Jogo
Impacto_Jogo --> Feedback

Fluxo_Normal --> Feedback

Feedback --> Atualizar_Estado_Jogo

Atualizar_Estado_Jogo --> [*]
```

## UC06
UC06. Sistema de vitória

```mermaid
stateDiagram-v2

[*] --> Partida_Em_Andamento

Partida_Em_Andamento --> Atualizar_Pontuacao

Atualizar_Pontuacao --> Partida_Em_Andamento : nenhum jogador com 100 pontos

Atualizar_Pontuacao --> Determinar_Vencedor : P1 ou P2 >=100

Determinar_Vencedor --> Exibir_Vencedor

Exibir_Vencedor --> Encerrar_Partida

Encerrar_Partida --> [*]
```

## UC07
UC07. Sistema de tempo nas perguntas

```mermaid
stateDiagram-v2

[*] --> Exibir_Pergunta

Exibir_Pergunta --> Iniciar_Timer

Iniciar_Timer --> Contagem_Regressiva

Contagem_Regressiva --> Resposta_Recebida : jogador responde
Contagem_Regressiva --> Tempo_Esgotado : timeout

Resposta_Recebida --> Avaliar_Progresso

Tempo_Esgotado --> Aplicar_Penalidade
Aplicar_Penalidade --> Avaliar_Progresso

Avaliar_Progresso --> Reduzir_Tempo : progresso aumenta
Avaliar_Progresso --> Reiniciar_Rodada : sem alteração

Reduzir_Tempo --> Reiniciar_Rodada

Reiniciar_Rodada --> Exibir_Pergunta

Reiniciar_Rodada --> [*]
```

## UC08
UC08. Efeito competitivo (impactar adversário)

```mermaid

stateDiagram-v2
    [*] --> AcaoJogador

    AcaoJogador: Jogador acerta pergunta

    AcaoJogador --> ValidarAcerto

    ValidarAcerto --> AcertoConfirmado: [Resposta correta]
    ValidarAcerto --> NaoAplicavel: [Resposta incorreta]

    AcertoConfirmado --> SelecionarAdversario
    SelecionarAdversario: Identificar jogador oponente

    SelecionarAdversario --> EscolherEfeito

    EscolherEfeito --> ForcarPergunta
    EscolherEfeito --> AplicarAtraso

    ForcarPergunta: Enviar nova pergunta ao adversário
    AplicarAtraso: Reduzir velocidade\nou travar ações temporariamente

    ForcarPergunta --> AplicarEfeito
    AplicarAtraso --> AplicarEfeito

    AplicarEfeito --> AtualizarEstadoAdversario
    AtualizarEstadoAdversario: Modificar estado do oponente

    AtualizarEstadoAdversario --> ExibirFeedbackVisual
    ExibirFeedbackVisual: Mostrar efeito visual\nno adversário

    ExibirFeedbackVisual --> ConfirmarImpacto
    ConfirmarImpacto: Garantir que ação foi aplicada

    ConfirmarImpacto --> RetornarFluxoPrincipal
    RetornarFluxoPrincipal: Continuar jogo normalmente

    RetornarFluxoPrincipal --> [*]

    NaoAplicavel --> EncerrarFluxo
    EncerrarFluxo --> [*]
```

## UC09
UC09. Interface gráfica (renderização e atualização)

```mermaid

stateDiagram-v2
    [*] --> InicializarInterface

    InicializarInterface --> CriarLayoutBase
    CriarLayoutBase: Definir estrutura da tela

    CriarLayoutBase --> CriarTabuleiros
    CriarTabuleiros: Renderizar dois tabuleiros

    CriarTabuleiros --> ExibirPontuacao
    ExibirPontuacao: Mostrar pontuação inicial

    ExibirPontuacao --> OrganizarElementos
    OrganizarElementos: Ajustar alinhamento\nGarantir legibilidade

    OrganizarElementos --> RenderizarInterface
    RenderizarInterface: Exibir UI na tela

    RenderizarInterface --> IniciarLoopInterface

    IniciarLoopInterface --> AtualizarInterface
    AtualizarInterface: Atualizar pontuação\nAtualizar estado dos tabuleiros

    AtualizarInterface --> VerificarEstadoJogo

    VerificarEstadoJogo --> ContinuarAtualizacao: [Jogo em andamento]
    VerificarEstadoJogo --> EncerrarInterface: [Jogo finalizado]

    ContinuarAtualizacao --> IniciarLoopInterface

    EncerrarInterface --> ExibirTelaFinal
    ExibirTelaFinal: Mostrar resultado final

    ExibirTelaFinal --> [*]
```

## UC10
UC10. Banco de perguntas (fixo/local)

```mermaid

stateDiagram-v2
    [*] --> InicializarSistema

    InicializarSistema --> LocalizarArquivo
    LocalizarArquivo: Identificar fonte local (JSON)

    LocalizarArquivo --> VerificarArquivo

    VerificarArquivo --> ArquivoEncontrado: [Arquivo disponível]
    VerificarArquivo --> ArquivoNaoEncontrado: [Arquivo ausente]

    ArquivoNaoEncontrado --> ExibirErroArquivo
    ExibirErroArquivo: Informar erro de carregamento

    ExibirErroArquivo --> EncerrarSistema
    EncerrarSistema --> [*]

    ArquivoEncontrado --> CarregarDados
    CarregarDados: Ler arquivo JSON local

    CarregarDados --> ValidarDados

    ValidarDados --> DadosValidos: [Estrutura correta]
    ValidarDados --> DadosInvalidos: [Erro no JSON]

    DadosInvalidos --> ExibirErroDados
    ExibirErroDados: Informar inconsistência

    ExibirErroDados --> EncerrarSistema

    DadosValidos --> ArmazenarPerguntas
    ArmazenarPerguntas: Salvar em memória

    ArmazenarPerguntas --> DisponibilizarPerguntas
    DisponibilizarPerguntas: Sistema pronto para uso

    DisponibilizarPerguntas --> VerificarModoOffline

    VerificarModoOffline --> ModoOffline: [Sem conexão]
    VerificarModoOffline --> ModoOnline: [Com conexão]

    ModoOffline --> OperarOffline
    OperarOffline: Usar apenas dados locais

    ModoOnline --> OperarNormal
    OperarNormal: Utilizar dados já carregados

    OperarOffline --> [*]
    OperarNormal --> [*]
```

## UC11
UC11. Aumento de dificuldade progressiva

```mermaid

stateDiagram-v2
    [*] --> IniciarJogo

    IniciarJogo --> DefinirParametrosIniciais
    DefinirParametrosIniciais: Definir velocidade inicial\nDefinir tempo padrão

    DefinirParametrosIniciais --> IniciarLoopJogo

    IniciarLoopJogo --> ExecutarCicloJogo
    ExecutarCicloJogo: Rodada em andamento\n(blocos caindo / adivinhação)

    ExecutarCicloJogo --> VerificarProgresso

    VerificarProgresso --> AumentarDificuldade: [Critério atingido]
    VerificarProgresso --> ManterDificuldade: [Critério não atingido]

    AumentarDificuldade --> AjustarVelocidade
    AjustarVelocidade: Aumentar velocidade do jogo

    AjustarVelocidade --> ReduzirTempo
    ReduzirTempo: Diminuir tempo de resposta

    ReduzirTempo --> AtualizarParametros
    AtualizarParametros: Aplicar novas configurações

    AtualizarParametros --> ContinuarJogo

    ManterDificuldade --> ContinuarJogo

    ContinuarJogo --> VerificarFimJogo

    VerificarFimJogo --> FimJogo: [Jogo encerrado]
    VerificarFimJogo --> ContinuarLoop: [Jogo continua]

    ContinuarLoop --> IniciarLoopJogo

    FimJogo --> EncerrarPartida
    EncerrarPartida --> [*]

```

## UC12
UC12. Feedback visual para acertos e erros

```mermaid

stateDiagram-v2
    [*] --> AguardarResposta

    AguardarResposta --> ReceberResposta: Jogador envia resposta

    ReceberResposta --> ValidarResposta

    ValidarResposta --> RespostaCorreta: [Resposta correta]
    ValidarResposta --> RespostaIncorreta: [Resposta incorreta]

    RespostaCorreta --> ExibirFeedbackPositivo
    ExibirFeedbackPositivo: Mostrar cor verde\nExibir animação de acerto

    ExibirFeedbackPositivo --> AtualizarEstadoJogo
    AtualizarEstadoJogo: Liberar continuidade\nPontuar jogador

    AtualizarEstadoJogo --> ContinuarJogo

    RespostaIncorreta --> ExibirFeedbackNegativo
    ExibirFeedbackNegativo: Mostrar cor vermelha\nExibir animação de erro

    ExibirFeedbackNegativo --> AplicarPenalidade
    AplicarPenalidade: Reduzir vidas ou aplicar efeito

    AplicarPenalidade --> VerificarEstadoJogador

    VerificarEstadoJogador --> ContinuarJogo: [Ainda pode jogar]
    VerificarEstadoJogador --> GameOver: [Sem vidas]

    GameOver --> ExibirTelaGameOver
    ExibirTelaGameOver --> [*]

    ContinuarJogo --> RetornarLoop
    RetornarLoop --> AguardarResposta: Nova pergunta ou continuação
```

# Backlog do Sistema de Adivinhação

## UC13
UC13. Gerar número aleatório e definir intervalo

```mermaid

stateDiagram-v2
    [*] --> IniciarRodada

    IniciarRodada --> DefinirIntervalo
    DefinirIntervalo: Definir intervalo [0 - 100]

    DefinirIntervalo --> GerarNumeroAleatorio
    GerarNumeroAleatorio: Gerar número pseudo-aleatório

    GerarNumeroAleatorio --> ValidarIntervalo

    ValidarIntervalo --> NumeroValido: [Número entre 0 e 100]
    ValidarIntervalo --> NumeroInvalido: [Fora do intervalo]

    NumeroInvalido --> GerarNumeroAleatorio: Regerar número

    NumeroValido --> ArmazenarNumero
    ArmazenarNumero: Salvar número secreto\n(oculto ao jogador)

    ArmazenarNumero --> OcultarNumero
    OcultarNumero: Garantir que não será exibido

    OcultarNumero --> PrepararRodada
    PrepararRodada: Sistema pronto para adivinhação

    PrepararRodada --> VerificarNovaRodada

    VerificarNovaRodada --> NovaRodada: [Nova rodada iniciada]
    VerificarNovaRodada --> [*]: [Fim do fluxo atual]

    NovaRodada --> IniciarRodada
```

## UC14
UC14. Loop de adivinhação (entrada, validação, feedback)

```mermaid

stateDiagram-v2
    [*] --> IniciarLoopAdivinhacao

    IniciarLoopAdivinhacao --> SolicitarTentativa
    SolicitarTentativa: Solicitar número ao jogador

    SolicitarTentativa --> ReceberTentativa
    ReceberTentativa: Jogador insere tentativa

    ReceberTentativa --> ValidarEntrada

    ValidarEntrada --> EntradaValida: [Entrada numérica válida]
    ValidarEntrada --> EntradaInvalida: [Entrada inválida]

    EntradaInvalida --> ExibirErro
    ExibirErro: Informar erro ao jogador

    ExibirErro --> SolicitarTentativa

    EntradaValida --> CompararNumero

    CompararNumero --> Acertou: [Número correto]
    CompararNumero --> NaoAcertou: [Número incorreto]

    NaoAcertou --> VerificarCondicaoParada

    VerificarCondicaoParada --> ContinuarLoop: [Pode continuar]
    VerificarCondicaoParada --> EncerrarLoop: [Condição de parada atingida]

    ContinuarLoop --> SolicitarTentativa

    Acertou --> ExibirSucesso
    ExibirSucesso: Informar acerto ao jogador

    ExibirSucesso --> IntegrarFluxoPrincipal
    IntegrarFluxoPrincipal: Atualizar progresso no jogo

    IntegrarFluxoPrincipal --> [*]

    EncerrarLoop --> ExibirFalha
    ExibirFalha: Informar fim das tentativas ou condição atingida

    ExibirFalha --> IntegrarFluxoPrincipal

```

## UC15
UC15. Validação de entrada (número, intervalo)

```mermaid

stateDiagram-v2
    [*] --> ReceberEntrada

    ReceberEntrada: Jogador insere valor

    ReceberEntrada --> VerificarTipoEntrada

    VerificarTipoEntrada --> EntradaNumerica: [É número]
    VerificarTipoEntrada --> EntradaNaoNumerica: [Não é número]

    EntradaNaoNumerica --> ExibirErroTipo
    ExibirErroTipo: Mostrar mensagem\n"Entrada inválida"

    ExibirErroTipo --> SolicitarNovaEntrada

    SolicitarNovaEntrada --> ReceberEntrada

    EntradaNumerica --> ValidarIntervalo

    ValidarIntervalo --> DentroIntervalo: [0 <= valor <= 100]
    ValidarIntervalo --> ForaIntervalo: [Valor inválido]

    ForaIntervalo --> ExibirErroIntervalo
    ExibirErroIntervalo: Mostrar mensagem\n"Fora do intervalo permitido"

    ExibirErroIntervalo --> SolicitarNovaEntrada

    DentroIntervalo --> EntradaValida
    EntradaValida: Entrada aceita pelo sistema

    EntradaValida --> RetornarParaFluxo
    RetornarParaFluxo: Enviar valor para lógica do jogo

    RetornarParaFluxo --> [*]

```

## UC16
UC16. Feedback: “Muito baixo”

```mermaid

stateDiagram-v2
    [*] --> ReceberPalpite

    ReceberPalpite: Jogador insere tentativa válida

    ReceberPalpite --> ObterNumeroSecreto
    ObterNumeroSecreto: Recuperar valor armazenado

    ObterNumeroSecreto --> CompararValores

    CompararValores --> PalpiteMenor: [Palpite < Número secreto]
    CompararValores --> NaoAplicavel: [Palpite >= Número secreto]

    PalpiteMenor --> ExibirMensagemBaixo
    ExibirMensagemBaixo: Mostrar "Muito baixo"

    ExibirMensagemBaixo --> AtualizarInterface
    AtualizarInterface: Exibir feedback ao jogador

    AtualizarInterface --> RetornarLoop
    RetornarLoop: Permitir nova tentativa

    RetornarLoop --> [*]

    NaoAplicavel --> EncerrarFluxo
    EncerrarFluxo: Retornar ao fluxo principal

    EncerrarFluxo --> [*]

```

## UC17
UC17. Feedback: “Muito alto”

```mermaid  

stateDiagram-v2
    [*] --> ReceberPalpite

    ReceberPalpite: Jogador insere tentativa válida

    ReceberPalpite --> ObterNumeroSecreto
    ObterNumeroSecreto: Recuperar valor armazenado

    ObterNumeroSecreto --> CompararValores

    CompararValores --> PalpiteMaior: [Palpite > Número secreto]
    CompararValores --> NaoAplicavel: [Palpite <= Número secreto]

    PalpiteMaior --> ExibirMensagemAlto
    ExibirMensagemAlto: Mostrar "Muito alto"

    ExibirMensagemAlto --> AtualizarInterface
    AtualizarInterface: Exibir feedback ao jogador

    AtualizarInterface --> RetornarLoop
    RetornarLoop: Permitir nova tentativa

    RetornarLoop --> [*]

    NaoAplicavel --> EncerrarFluxo
    EncerrarFluxo: Retornar ao fluxo principal

    EncerrarFluxo --> [*]

```

## UC18
UC18. Feedback: “Acertou”

```mermaid

stateDiagram-v2
    [*] --> ReceberPalpite

    ReceberPalpite: Jogador insere tentativa válida

    ReceberPalpite --> ObterNumeroSecreto
    ObterNumeroSecreto: Recuperar valor armazenado

    ObterNumeroSecreto --> CompararValores

    CompararValores --> Acertou: [Palpite == Número secreto]
    CompararValores --> NaoAplicavel: [Palpite != Número secreto]

    Acertou --> ExibirMensagemAcerto
    ExibirMensagemAcerto: Mostrar "Acertou"

    ExibirMensagemAcerto --> AtualizarInterface
    AtualizarInterface: Exibir feedback ao jogador

    AtualizarInterface --> AplicarRecompensa

    AplicarRecompensa: Adicionar pontos\nou bônus ao jogador

    AplicarRecompensa --> AtualizarEstadoJogo
    AtualizarEstadoJogo: Registrar progresso\nou avanço de fase

    AtualizarEstadoJogo --> IntegrarFluxoPrincipal
    IntegrarFluxoPrincipal: Notificar sistema principal

    IntegrarFluxoPrincipal --> EncerrarLoop
    EncerrarLoop: Finalizar rodada de adivinhação

    EncerrarLoop --> [*]

    NaoAplicavel --> EncerrarFluxo
    EncerrarFluxo: Retornar ao fluxo principal

    EncerrarFluxo --> [*]

```
