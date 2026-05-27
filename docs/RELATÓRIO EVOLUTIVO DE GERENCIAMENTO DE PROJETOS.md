# RELATÓRIO EVOLUTIVO DE GERENCIAMENTO DE PROJETOS

- **Disciplina:** Projetos
- **Nome da Equipe:** [Preencher]
- **Nome do Projeto:** TeCtris
- **Professor(a):** André Luiz Gomes da Silva
- **Curso/Turma:** ADS - EMBARQUE
- **Período de Desenvolvimento:** __/05/2026 a 12/06/2026

---

## 1. Identificação da Equipe

| Nome do integrante | Função no projeto | Responsabilidades principais |
| :--- | :--- | :--- |
| **Larissa Lira** | Product Owner | Definir a visão do produto (jogo), gerenciar e priorizar o Backlog, garantir que o projeto atenda aos requisitos gerais propostos e realizar as entregas. |
| **Diogo Alcelino** | Scrum Master | Garante que o grupo não se perca nos prazos, organiza as reuniões de status, ajuda a resolver conflitos e garante que todos saibam o que precisam fazer hoje para o projeto andar. |
| **João Rafael Morato** | Tech Leader | Liderar as decisões técnicas, definir a arquitetura do código (quais bibliotecas usar, como organizar os arquivos, etc), revisar os códigos da equipe e garantir a qualidade e escalabilidade do sistema. |
| **Cecília Lopes** | Desenvolvedora front-end | Implementar a camada gráfica do sistema via código, garantindo que os elementos visuais planejados sejam renderizados e posicionados corretamente na tela. |
| **Emily Raquel** | Desenvolvedora back-end | Programar a interface de interação com o usuário, gerenciar o feedback visual das ações e integrar a captura dos comandos/controles dos jogadores ao sistema. |
| **Alice Sena** | Desenvolvedora | Desenvolver o núcleo lógico do software, estruturando o comportamento dinâmico dos elementos, a física básica e as regras fundamentais de funcionamento. |
| **Matheus Vaz** | Desenvolvedor back-end | Estruturar os sistemas de controle de estado das partidas, a lógica de pontuação, o gerenciamento de sessões para multiplayer e a validação de dados internos. |
| **Kezia Aguiar** | Designer | Criar a identidade visual do projeto, definir paletas de cores, tipografia, projetar o layout e realizar testes de usabilidade para validar a interface. |

---

## 2. Apresentação do Projeto

### 2.1 Título do Projeto
O título do projeto é **TeCtris**. O nome é uma junção criativa que faz referência direta à linguagem de programação "C", base do nosso desenvolvimento e tema central das perguntas, e ao clássico jogo "Tetris", cuja mecânica de queda de blocos inspira a base da nossa jogabilidade. Além disso, a sonoridade remete ao prefixo "Tec" (tecnologia), alinhando o título ao contexto do nosso curso de Análise e Desenvolvimento de Sistemas.

### 2.2 Problema ou Necessidade Identificada
O ensino tradicional da sintaxe da linguagem C, muitas vezes, apoia-se em métodos puramente teóricos ou listas de exercícios monótonas. Esse cenário gera um problema comum: a desmotivação e a dificuldade de assimilação por parte dos estudantes iniciantes na área de tecnologia. Esses alunos, que são os principais afetados por essa abordagem convencional, frequentemente enfrentam frustrações devido à curva de aprendizado inicial, o que impacta negativamente o desempenho acadêmico e diminui o engajamento com a disciplina.

Diante dessa necessidade, o TeCtris propõe transformar esse aprendizado em uma experiência prática, dinâmica e competitiva, a fim de mitigar esse problema. Ao integrar perguntas sobre C à mecânica clássica de encaixe de peças, exigindo resoluções em tempo real para influenciar o desempenho no jogo, a solução substitui a frustração tradicional pelo engajamento. Dessa forma, o conhecimento é incorporado à gameplay, estimulando a tomada de decisões rápidas e permitindo que o jogador aprenda de forma muito mais intuitiva e eficaz enquanto se diverte.

### 2.3 Público-Alvo
O público-alvo principal do TeCtris é composto por estudantes de graduação e cursos técnicos na área de tecnologia que estão iniciando sua jornada no aprendizado da lógica de programação e da linguagem C. O projeto também se estende a docentes que buscam ferramentas pedagógicas alternativas e interativas para dinamizar o ensino em sala de aula, bem como entusiastas de programação que desejam revisar conceitos básicos de forma lúdica e prática.

### 2.4 Objetivo Geral do Projeto
Desenvolver um jogo educacional interativo em linguagem C que integre mecânicas clássicas de puzzle com desafios de lógica e sintaxe, visando facilitar a assimilação de conteúdos acadêmicos de forma dinâmica e engajadora.

### 2.5 Objetivos Específicos

| N° | Objetivo específico |
| :---: | :--- |
| 1 | Implementar as mecânicas fundamentais de movimentação e encaixe de peças, garantindo a fluidez do jogo. |
| 2 | Desenvolver um sistema de banco de questões focado em lógica de programação e fundamentos da linguagem C. |
| 3 | Criar uma interface visual funcional que permita a transição intuitiva entre a jogabilidade de ação e os momentos de quiz. |
| 4 | Implementar a lógica de competição para dois jogadores e o sistema de pontuação baseado no desempenho técnico dos participantes. |
| 5 | Aplicar e integrar os conhecimentos técnicos adquiridos nas diversas disciplinas do período letivo em uma única aplicação coesa. |

### 2.6 Justificativa
A criação do TeCtris justifica-se pela crescente necessidade de métodos de ensino que utilizem a gamificação como estratégia para aumentar a retenção de conhecimento. No ensino de programação, a transição da teoria para a prática é frequentemente um obstáculo, então, ao oferecer uma plataforma onde o acerto de uma questão técnica gera um benefício imediato dentro do jogo, o projeto estimula o aluno a estudar de forma orgânica. 

A importância do projeto reside em oferecer uma alternativa ao estudo puramente passivo, transformando o erro em uma oportunidade de aprendizado imediato. Os benefícios gerados incluem o desenvolvimento do raciocínio lógico sob pressão e o fortalecimento do engajamento dos estudantes com a linguagem C. Para a equipe, o projeto é fundamental por consolidar a capacidade de integrar diferentes camadas de software (lógica, interface e dados) em um produto final que resolve um problema real de aprendizado.

---

## 3. Escopo do Projeto

### 3.1 O que será entregue pelo projeto?
O projeto entregará um software executável (jogo para desktop) desenvolvido inteiramente na linguagem C, além de sua respectiva documentação.
As principais entregas incluem:
* O executável do jogo TeCtris, com a mecânica de "puzzle" funcional integrada a um sistema de eventos que dispara perguntas de programação em tempo real.
* Uma Interface de Usuário (UI) que divide a tela para suportar uma experiência competitiva entre dois jogadores (Player 1, Player 2).
* Um banco de questões local e embutido no código, focado em lógica e C, capaz de rodar totalmente offline.
* Um sistema interno completo de engine de tempo (timer), pontuação (com condição de vitória ao atingir 100 pontos) e penalidades aplicadas ao grid do jogador em caso de erros.
* Documentação técnica (hospedada no GitHub), contendo o guia de execução, instruções de compilação e relatórios de desenvolvimento.

### 3.2 O que não faz parte do projeto?
* **Modo Multiplayer Online/em Rede:** O jogo foi projetado exclusivamente para multiplayer local (ambos os jogadores dividindo o mesmo teclado/máquina). Não haverá comunicação via rede (sockets) para jogar em computadores diferentes.
* **Banco de Dados em Nuvem (Online):** O sistema não utilizará conexões com a internet para buscar as perguntas ou salvar pontuações globais. Tudo será manipulado estaticamente na memória ou através de arquivos locais.
* **Portabilidade para Mobile/Web:** O software não funcionará em celulares ou navegadores de internet. Ele é voltado exclusivamente para execução em sistema operacional desktop.
* **Sistema de Login e Autenticação:** Não haverá criação de contas de usuário, senhas ou perfis com persistência de histórico de longo prazo para os jogadores.

---

## 4. Planejamento Geral do Projeto

### 4.1 Cronograma de 6 Semanas
**Link do Trello:** [https://trello.com/b/XpkqB8dX/projeto-integrado]

---

## 5. Acompanhamento Semanal do Projeto
*(Esta seção deve ser preenchida a cada semana pela equipe, funcionando como um diário de evolução do projeto).*

### Semana 1: Definição Inicial do Projeto
**Período:** 11/05/2026 a 15/05/2026

**5.1 Atividades realizadas**
* **Estruturação Ágil:** Transposição dos conceitos teóricos de Kanban e Planejamento Ágil para a realidade prática do projeto, organizando o fluxo de trabalho da equipe.
* **Prototipagem e Desenvolvimento C:** Implementação de uma versão funcional preliminar do jogo e de um sistema de histórico básico, contemplando um menu de navegação (Jogar, Analisar, Sair), a execução de uma partida completa com sistema de dicas e a lógica de salvamento/carregamento de histórico de partidas.
* **Validação de Usabilidade:** Elaboração de uma apresentação focada na comprovação prática dos critérios de usabilidade. Foram analisados exemplos reais da interface inicial (protótipo/sistema funcional), demonstrando a aplicação de cada critério e documentando oportunidades de melhoria.
* **Documentação:** Avanço significativo na documentação oficial do projeto.

**5.2 Decisões tomadas**
Nesta semana, não houve a necessidade de novas decisões arquiteturais ou mudanças de rota significativas. A equipe optou por manter estritamente o escopo, as diretrizes de desenvolvimento e a divisão de responsabilidades que já haviam sido previamente discutidas e validadas, garantindo o foco na execução do planejamento inicial.

**5.3 Entregas da semana**

| Entrega | Foi concluída? | Observações |
| :--- | :---: | :--- |
| Definição do problema | Sim | Problema: desmotivação no ensino tradicional de C. |
| Definição do público-alvo | Sim | Público-alvo: estudantes de tecnologia e docentes. |
| Definição dos objetivos | Sim | Objetivo geral e 5 objetivos específicos definidos e alinhados com o escopo do TeCtris. |

**5.4 Dificuldades encontradas**
Nesta etapa inicial, a principal dificuldade da equipe foi integrar a lógica inicial de manipulação de arquivos (para o salvamento do histórico) com o loop principal do jogo, exigindo um esforço extra de pesquisa e testes por parte dos desenvolvedores.

**5.5 Próximos passos**
* **Execução da Sprint 01:** Iniciar o ciclo de desenvolvimento focado na implementação das histórias de usuário prioritárias, garantindo a organização do board, o controle rigoroso de versionamento, a execução de testes locais e a documentação das atividades.
* **Relatório Analítico do código em C:** Implementar uma análise completa com sugestões baseada no histórico de partidas, incluindo o cálculo de estatísticas agregadas (média, melhor/pior pontuação, desvio), uso de funções recursivas (para soma, mínimo, máximo e soma de quadrados) e a aplicação de heurísticas textuais para avaliação de estratégia.

---

### Semana 2: Acompanhamento Semanal
**Período:** 18/05/2026 a 22/05/2026

**5.1 Atividades realizadas**
* Realizamos reuniões de alinhamento para planejar as entregas da próxima semana.
* Devido ao surgimento de novas demandas acadêmicas no mesmo período (trabalho de lógica e entregas da Residência Tecnológica), ajustamos nosso planejamento e redistribuímos as tarefas entre os integrantes.

**5.2 Decisões tomadas**
* **Projeto de Lógica:** Após avaliarmos se seria melhor adaptar o nosso jogo atual ou criar um novo, decidimos desenvolver um jogo físico independente e já definimos o seu conteúdo e regras.
* **Divisão da equipe:** Para dar conta de todas as entregas da semana e evitar atrasos, decidimos dividir a equipe em subgrupos, cada um focado em uma entrega específica.

**5.3 Dificuldades encontradas**
* O principal desafio da semana foi a gestão do tempo e a sobrecarga de tarefas. Tivemos prazos muito curtos para os trabalhos de Lógica e da Residência, exatamente na mesma semana em que já tínhamos validações do projeto principal (TeCtris) com três professores diferentes. Isso dificultou bastante a organização e a priorização do que deveria ser feito primeiro.

**5.4 Próximos passos**
* Concluir e entregar as soluções da disciplina de Lógica e da Residência Tecnológica dentro dos prazos.
* Após essas entregas, retomar o foco total da equipe para o desenvolvimento, testes e finalização do projeto TeCtris.

---

### Semana 3 — Ideação e Definição da Solução  
**Período:** 25/05/2026 a 29/05/2026

**5.1 Atividades realizadas**
* Foi realizada a implementação das estatísticas do jogo, incluindo cálculo de média, melhor e pior desempenho. Também foram desenvolvidas funções recursivas para operações de soma, mínimo, máximo e soma dos quadrados, bem como heurísticas textuais voltadas à estratégia do jogo. Como resultado, foi estruturado um relatório analítico funcional do TeCtris.

**5.2 Decisões tomadas**
* Nesta semana, não houve decisões significativas relacionadas ao direcionamento do projeto, sendo mantido o planejamento previamente estabelecido pela equipe.

**5.3 Dificuldades encontradas**
* A principal dificuldade encontrada esteve relacionada à compreensão de determinadas partes do código-fonte. Entretanto, por meio de análises, discussões em equipe e apoio da Inteligência Artificial, foi possível superar os obstáculos e desenvolver as funcionalidades propostas.

**5.4 Próximos passos**
* Os próximos passos consistem na realização de testes funcionais e de usabilidade, além da aplicação dos ajustes necessários para a finalização e refinamento do jogo.

---

### Semana 4: Testes, Validação e Melhorias
**Período:** [Preencher]

* **5.1 Atividades realizadas:** [Descrever o que a equipe fez durante a semana]
* **5.2 Como a solução foi testada ou validada?:** [Descrever se a equipe apresentou a solução para usuários, colegas, professor, possíveis clientes ou outras pessoas]

**5.3 Resultados dos testes ou feedbacks recebidos**

| Pessoa/grupo consultado | Feedback recebido | Melhorias sugeridas |
| :--- | :--- | :--- |
| [Preencher] | [Preencher] | [Preencher] |

* **5.4 Melhorias realizadas no projeto:** [Preencher]
* **5.5 Próximos passos:** [Preencher]

---

### Semana 5: Finalização e Preparação da Apresentação
**Período:** [Preencher]

* **5.1 Atividades realizadas:** [Preencher]

**5.2 Entregas finais do projeto**

| Entrega final | Status | Observações |
| :--- | :--- | :--- |
| Relatório final | Concluído / Parcial / Não concluído | [Preencher] |
| Protótipo / Proposta | Concluído / Parcial / Não concluído | [Preencher] |
| Apresentação | Concluído / Parcial / Não concluído | [Preencher] |
| Validação/testes | Concluído / Parcial / Não concluído | [Preencher] |

* **5.3 Síntese da solução final:** [Descrever, de forma objetiva, qual foi a solução final desenvolvida pela equipe]
* **5.4 Principais resultados alcançados:** [Preencher]
* **5.5 O que ainda poderia ser melhorado?:** [Preencher]

---

## 6. Gestão da Equipe

**6.1 Divisão de responsabilidades**

| Integrante | Responsabilidades assumidas | Entregas realizadas | Participação na equipe |
| :--- | :--- | :--- | :--- |
| [Nome] | [Preencher] | [Preencher] | Alta / Média / Baixa |
| [Nome] | [Preencher] | [Preencher] | Alta / Média / Baixa |
| [Nome] | [Preencher] | [Preencher] | Alta / Média / Baixa |

* **6.2 Comunicação da Equipe:** [Descrever como a equipe se comunicou durante o projeto. Ex: WhatsApp, Meet, Trello, Discord, GitHub, etc.]
* **6.3 Organização do Trabalho:** [Descrever como a equipe organizou as tarefas, prazos e entregas]

---

## 7. Avaliação da Solução Desenvolvida

* **7.1 A solução responde ao problema inicial?:** [Explique se a solução desenvolvida atende ao problema identificado no início do projeto]
* **7.2 Pontos fortes da solução:**
  * Ponto forte 1: [Justificativa]
  * Ponto forte 2: [Justificativa]
* **7.3 Limitações da solução:**
  * Limitação 1: [Possível melhoria futura]
* **7.4 Potencial de aplicação prática:** [Explicar se a solução poderia ser aplicada em uma situação real, em uma empresa, comunidade, escola, instituição ou mercado]

---

## 8. Aprendizados da Equipe

* **8.1 O que a equipe aprendeu durante o desenvolvimento do projeto?:** [Resposta da equipe]

**8.2 Quais competências foram desenvolvidas?**

| Competência | Foi desenvolvida? | Comentário da equipe |
| :--- | :--- | :--- |
| Trabalho em equipe | Sim / Não / Parcial | [Preencher] |
| Comunicação | Sim / Não / Parcial | [Preencher] |
| Organização e planejamento | Sim / Não / Parcial | [Preencher] |
| Resolução de problemas | Sim / Não / Parcial | [Preencher] |
| Criatividade e inovação | Sim / Não / Parcial | [Preencher] |
| Gestão do tempo | Sim / Não / Parcial | [Preencher] |
| Uso de ferramentas digitais | Sim / Não / Parcial | [Preencher] |
| Pensamento crítico | Sim / Não / Parcial | [Preencher] |

* **8.3 Principais desafios enfrentados pela equipe:** [Preencher]
* **8.4 Como a equipe superou os desafios?:** [Preencher]

---

## 9. Autoavaliação da Equipe

**9.1 Avaliação geral da equipe**
*(Atribuir uma nota de 0 a 10 para o próprio desempenho)*

| Critério | Nota de 0 a 10 | Justificativa |
| :--- | :---: | :--- |
| Organização | [Nota] | [Preencher] |
| Participação dos integrantes | [Nota] | [Preencher] |
| Cumprimento dos prazos | [Nota] | [Preencher] |
| Qualidade das entregas | [Nota] | [Preencher] |
| Comunicação interna | [Nota] | [Preencher] |
| Criatividade da solução | [Nota] | [Preencher] |
| Aprendizado durante o projeto| [Nota] | [Preencher] |

**9.2 Autoavaliação individual**
*(Cada integrante deve preencher sua própria autoavaliação)*

| Integrante | O que contribuiu para o projeto? | O que poderia ter feito melhor? | Nota de participação |
| :--- | :--- | :--- | :---: |
| [Nome] | [Preencher] | [Preencher] | [Nota] |
