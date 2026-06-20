# Changelog — Multiplayer, Ranking, Áudio e Efeitos

Resumo do que foi implementado em cima da base já existente do projeto (raylib + C),
mantendo 100% do código single-player original intacto.

## ✅ O que foi adicionado

### 1. Multiplayer Local
- Novo modo de jogo: dois tabuleiros simultâneos lado a lado, na mesma janela.
- **Jogador 1**: `A` `D` mover · `W` girar · `S` segurado = soft drop · `S` durante pergunta = abrir
  caixa de resposta · `ESPAÇO` = hard drop.
- **Jogador 2**: setas `←` `→` mover · `↑` girar · `↓` segurado = soft drop · `↓` durante pergunta =
  abrir caixa de resposta · `ENTER` = hard drop.
- Cada jogador tem seu próprio tabuleiro, Kill Line, pontuação e nível — toda a física é
  100% reaproveitada das funções que já existiam em `game.c` (`CheckCollision`, `TryRotate`,
  `MergePiece`, `ClearLines`, `AddPenaltyLine`, `RemovePenaltyLine`), rodando em paralelo para
  os dois (`gameP1` e `gameP2`).
- **Pergunta com entrada alternada**: como é um teclado só, quem aperta a tecla "baixo" do seu
  próprio esquema primeiro (`S` ou `↓`) abre a caixa de digitação. O outro espera. A barra de
  tempo é compartilhada — se ninguém responder a tempo, ambos levam penalidade.
- **Interação competitiva**: acertar a pergunta sobe a Kill Line do adversário (manda uma linha
  de penalidade pra ele) — efeito comentado no README original (UC08).
- Fim de partida: quando um dos dois viola a Kill Line, o outro é declarado vencedor.

### 2. Ranking Geral (pódio)
- Novo arquivo `ranking.txt` (separado do `history.txt`/`history_easy.txt`, que continuam
  funcionando exatamente como antes).
- Junta resultados dos três modos — Desafio de C, Modo Easy e Multiplayer (só o vencedor) —
  num único ranking ordenado por pontuação, cada entrada com um indicador de modo
  (cor + texto: `C` ciano, `EASY` laranja, `MULTI` verde).
- Pódio visual (1º/2º/3º) + lista do 4º ao 13º colocado.
- Tela acessível a qualquer momento pelo menu ("Ranking Geral"), e atualizada automaticamente
  toda vez que uma partida termina.
- Como agora o ranking tem nome de jogador, os modos single-player ganharam uma tela de
  "Digite seu nome" antes de começar a partida.

### 3. Áudio
- Música de fundo original em chiptune (`assets/audio/music_loop.wav`) — **não é a trilha
  clássica do Tetris**, é uma composição própria, pra evitar qualquer problema de direitos
  autorais.
- Efeitos sonoros: acerto, erro, peça encaixando, linha completada, linha de penalidade,
  aviso de Kill Line subindo, fim de jogo, vitória, navegação de menu, abertura de caixa de
  resposta — todos sintetizados (sem nenhum asset de terceiros).
- Todos os `.wav` foram gerados pelo script `tools/gen_audio.py` (Python puro, sem
  dependências) — se quiserem ajustar a música ou os efeitos, é só editar e rodar de novo.
- Atalhos `M` (música) e `N` (efeitos) ligam/desligam a qualquer momento.

### 4. Efeitos visuais de acerto/erro
- Flash colorido (verde/vermelho) no tabuleiro de quem respondeu, em todos os modos
  (single-player e multiplayer).
- Texto flutuante de pontuação (`+150`, `Penalidade`) que sobe e desaparece.
- No multiplayer, a coluna central mostra o "VS", as próximas peças dos dois, e a contagem
  regressiva pra próxima pergunta.

## 🐛 Bugs encontrados e corrigidos
Três problemas que apareceram (dois já existiam no código original, um foi descoberto
durante o build do Matheus numa raylib mais nova):

1. **Menu desalinhado**: o menu já tinha 6 opções funcionais no `main.c`, mas a lista de
   textos desenhada em `render.c` só tinha 5 itens — então a partir da 3ª opção, o texto
   mostrado na tela não batia com a ação real. Corrigido (e expandido para as 8 opções novas).
2. **ESC fechava o jogo inteiro**: o raylib, por padrão, fecha a janela quando `ESC` é
   pressionado em qualquer lugar — mas o jogo usa `ESC` como "voltar" em várias telas
   (Histórico, Relatório, e agora Ranking/Nome/Multiplayer). Sem corrigir isso, apertar ESC
   pra voltar ao menu na verdade fechava o programa. Adicionei `SetExitKey(KEY_NULL)` logo no
   início do `main()` pra desativar esse comportamento padrão.
3. **`DrawRectangleRoundedLines` não compilava na raylib do Matheus**: em versões mais
   recentes do raylib essa função perdeu o parâmetro de espessura da linha (passou de 5 para
   4 argumentos). Como o raylib de vocês é puxado direto do source (`C:/raylib/raylib/src`),
   cada pessoa do grupo pode estar numa versão diferente dependendo de quando clonou/atualizou.
   Troquei todo o uso dessa função por um helper próprio (`DrawPanelOutline`, em `render.c`)
   baseado em `DrawRectangleLinesEx`, que é uma API estável há várias versões — assim compila
   igual independente da versão exata do raylib instalada.

## 📁 Arquivos novos
```
include/ranking.h          include/audio_fx.h
src/utils/ranking.c        src/utils/audio_fx.c
assets/audio/*.wav         tools/gen_audio.py
```

## 🔧 Arquivos modificados
`include/common.h`, `include/game.h`, `src/main.c`, `src/render/render.c`,
`src/game/game.c` (só adicionei o campo `playerName`), `CMakeLists.txt` (2 fontes novas).
Nenhuma função antiga foi removida ou teve sua assinatura alterada.

## ✅ Como validei
Como o build é feito pra Windows (MinGW + raylib), montei um ambiente Linux paralelo aqui
(raylib 5.0 compilado do zero) só para testes — não faz parte da entrega, é só pra eu
conseguir compilar e rodar de verdade antes de mandar o código:
- Build completo sem nenhum erro, sem warning novo (só os 3 que já existiam antes).
- Rodei o executável várias vezes com entrada de teclado simulada: menu → multiplayer →
  nome dos dois jogadores → partida rodando → pergunta disparando → os dois respondendo →
  pausa/despausa → ranking com pódio populado. Tudo funcionando, sem nenhum crash.
- Tirei screenshots de cada tela nova pra conferir visualmente (pódio, tela de nomes,
  tabuleiro duplo, pergunta com as duas caixas).

## ▶️ Build (Windows, sem mudanças no processo)
Continua exatamente como no `GUIA_EXECUCAO.md`:
```bash
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build . --config Release
```
O `Tectris.exe` vai estar em `build/bin/`. Rodem a partir da pasta `build/` (ou da raiz do
projeto) para os áudios serem encontrados automaticamente — o carregamento de assets tenta
alguns caminhos relativos diferentes justamente pra cobrir isso.
