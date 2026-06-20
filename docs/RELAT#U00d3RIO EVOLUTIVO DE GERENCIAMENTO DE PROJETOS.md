# RELATÓRIO EVOLUTIVO DE GERENCIAMENTO DE PROJETOS

**Disciplina:** Projetos 2
**Nome da Equipe:** Alice Sena, Cecília Lopes, Diogo Alcelino, Emily Raquel, João Rafael Morato, Kezia Aguiar, Larissa Morais e Matheus Vaz.
**Nome do Projeto:** TeCtris
**Professor(a):** André Luiz Gomes da Silva
**Curso/Turma:** ADS - EMBARQUE
**Período de Desenvolvimento:** 13 / 04 / 2026  a  12 / 06 / 2026

---

## 1. Identificação da Equipe

| Nome do integrante | Função no projeto | Responsabilidades principais |
| :--- | :--- | :--- |
| **Larissa Lira** | Product Owner | Definir a visão do produto (jogo), gerenciar e priorizar o Backlog, garantir que o projeto atenda aos requisitos gerais propostos e realizar as entregas. |
| **Alice Sena** | Scrum Master | Garante que o grupo não se perca nos prazos, organiza as reuniões de status, ajuda a resolver conflitos e garante que todos saibam o que precisam fazer hoje para o projeto andar. |
| **João Rafael Morato** | Tech Leader | Liderar as decisões técnicas, definir a arquitetura do código (quais bibliotecas usar, como organizar os arquivos, etc), revisar os códigos da equipe e garantir a qualidade e escalabilidade do sistema. |
| **Cecília Lopes** | Desenvolvedora front-end | Implementar a camada gráfica do sistema via código, garantindo que os elementos visuais planejados sejam renderizados e posicionados corretamente na tela. |
| **Emily Raquel** | Desenvolvedora front-end | Programar a interface de interação com o usuário, gerenciar o feedback visual das ações e integrar a captura dos comandos/controles dos jogadores ao sistema. |
| **Matheus Vaz** | Desenvolvedor back-end | Desenvolver o núcleo lógico do software, estruturar o comportamento dinâmico dos elementos, a física básica, as regras de funcionamento, o controle de estado das partidas, a lógica de pontuação, o gerenciamento de sessões e a validação de dados internos. |
| **Diogo Alcelino** | Designer | Criar a identidade visual do projeto, definir paletas de cores, tipografia, projetar o layout e realizar testes de usabilidade para validar a interface. |
| **Kezia Aguiar** | Designer | Projetar o layout das telas, estruturar a organização visual das informações e realizar testes de usabilidade para validar a interface. |

---

## 2. Apresentação do Projeto

### 2.1 Título do Projeto
O título do projeto é TeCtris. O nome é uma junção criativa que faz referência direta à linguagem de programação "C", base do nosso desenvolvimento e tema central das perguntas, e ao clássico jogo "Tetris", cuja mecânica de queda de blocos inspira a base da nossa jogabilidade. Além disso, a sonoridade remete ao prefixo "Tec" (tecnologia), alinhando o título ao contexto do nosso curso de Análise e Desenvolvimento de Sistemas. 

### 2.2 Problema ou Necessidade Identificada
O ensino tradicional da linguagem C, muitas vezes, apoia-se em métodos puramente teóricos ou listas de exercícios monótonas. Esse cenário gera um problema comum: a desmotivação e a dificuldade de aprendizado dos estudantes iniciantes na área de TI. Esses alunos, que são os principais afetados por essa abordagem convencional, frequentemente enfrentam frustrações devido à curva de aprendizado inicial, o que impacta negativamente o desempenho acadêmico e diminui o engajamento com a disciplina. 

Diante dessa necessidade, o TeCtris propõe transformar esse aprendizado em uma experiência prática, dinâmica e competitiva, a fim de mitigar esse problema. Ao integrar perguntas sobre C à mecânica clássica de encaixe de peças, exigindo resoluções em tempo real para influenciar o desempenho no jogo, a solução substitui a frustração tradicional pelo engajamento. Dessa forma, o conhecimento é incorporado à gameplay, estimulando a tomada de decisões rápidas e permitindo que o jogador aprenda de forma muito mais intuitiva e eficaz enquanto se diverte.

### 2.3 Público-Alvo
O público-alvo principal do TeCtris é composto por estudantes de graduação e cursos técnicos na área de tecnologia que estão iniciando sua jornada no aprendizado da lógica de programação e da linguagem C. O projeto também se estende a docentes que buscam ferramentas pedagógicas alternativas e interativas para dinamizar o ensino em sala de aula, bem como entusiastas de programação que desejam revisar conceitos básicos de forma lúdica e prática. 

### 2.4 Objetivo Geral do Projeto
Desenvolver um jogo educacional interativo em linguagem C que integre mecânicas clássicas de puzzle com desafios de lógica e sintaxe, visando facilitar a assimilação de conteúdos acadêmicos de forma dinâmica e engajadora. 

### 2.5 Objetivos Específicos

| Nº | Objetivo específico |
| :--- | :--- |
| **1** | Implementar as mecânicas fundamentais de movimentação e encaixe de peças, garantindo a fluidez do jogo. |
| **2** | Desenvolver um sistema de banco de questões focado em lógica de programação e fundamentos da linguagem C. |
| **3** | Criar uma interface visual funcional que permita a transição intuitiva entre a jogabilidade de ação e os momentos de quiz. |
| **4** | Implementar a lógica de competição para dois jogadores e o sistema de pontuação baseado no desempenho técnico dos participantes. |
| **5** | Aplicar e integrar os conhecimentos técnicos adquiridos nas diversas disciplinas do período letivo em uma única aplicação coesa. |

### 2.6 Justificativa
A criação do TeCtris justifica-se pela crescente necessidade de métodos de ensino que utilizem a gamificação como estratégia para aumentar a retenção de conhecimento. No ensino de programação, a transição da teoria para a prática é frequentemente um obstáculo, então, ao oferecer uma plataforma onde o acerto de uma questão técnica gera um benefício imediato dentro do jogo, o projeto estimula o aluno a estudar de forma orgânica.

A importância do projeto reside em oferecer uma alternativa ao estudo puramente passivo, transformando o erro em uma oportunidade de aprendizado imediato. Os benefícios gerados incluem o desenvolvimento do raciocínio lógico sob pressão e o fortalecimento do engajamento dos estudantes com a linguagem C. Para a equipe, o projeto é fundamental por consolidar a capacidade de integrar diferentes camadas de software (lógica, interface e dados) em um produto final que resolve um problema real de aprendizado.

---

## 3. Escopo do Projeto

### 3.1 O que será entregue pelo projeto?
O projeto entregará um software executável (jogo para desktop) desenvolvido inteiramente na linguagem C, além de sua respectiva documentação. As principais entregas incluem:

* O executável do jogo TeCtris, com a mecânica de “puzzle” funcional integrada a um sistema de eventos que dispara perguntas de programação em tempo real.
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
**Link do Trello:** https://trello.com/b/XpkqB8dX/projeto-integrado 

---

## 5. Acompanhamento Semanal do Projeto:

### Semana 1 — Definição Inicial do Projeto
**Período:** 11 / 05 / 2026  a  15 / 05 / 2026

**5.1 Atividades realizadas**
* **Estruturação Ágil:** Transposição dos conceitos teóricos de Kanban e Planejamento Ágil para a realidade prática do projeto, organizando o fluxo de trabalho da equipe.
* **Prototipagem e Desenvolvimento C:** Implementação de uma versão funcional preliminar do jogo e de um sistema de histórico básico, contemplando um menu de navegação (Jogar, Analisar, Sair), a execução de uma partida completa com sistema de dicas e a lógica de salvamento/carregamento de histórico de partidas.
* **Validação de Usabilidade:** Elaboração de uma apresentação focada na comprovação prática dos critérios de usabilidade. Foram analisados exemplos reais da interface inicial (protótipo/sistema funcional), demonstrando a aplicação de cada critério e documentando oportunidades de melhoria.
* **Documentação:** Avanço significativo na documentação oficial do projeto.

**5.2 Decisões tomadas**
Nesta semana, não houve a necessidade de novas decisões arquiteturais ou mudanças de rota significativas. A equipe optou por manter estritamente o escopo, as diretrizes de desenvolvimento e a divisão de responsabilidades que já haviam sido previamente discutidas e validadas, garantindo o foco na execução do planejamento inicial. 

**5.3 Entregas da semana**

| Entrega | Foi concluída? | Observações |
| :--- | :--- | :--- |
| Definição do problema | Sim | Problema: desmotivação no ensino tradicional de C. |
| Definição do público-alvo | Sim | Público-alvo: estudantes de tecnologia e docentes. |
| Definição dos objetivos | Sim | Objetivo geral e 5 objetivos específicos definidos e alinhados com o escopo do TeCtris. |

**5.4 Dificuldades encontradas**
Nesta etapa inicial, a principal dificuldade da equipe foi integrar a lógica inicial de manipulação de arquivos (para o salvamento do histórico) com o loop principal do jogo, exigindo um esforço extra de pesquisa e testes por parte dos desenvolvedores. 

**5.5 Próximos passos**
* **Execução da Sprint 01:** Iniciar o ciclo de desenvolvimento focado na implementação das histórias de usuário prioritárias, garantindo a organização do board, o controle rigoroso de versionamento, a execução de testes locais e a documentação das atividades.
* **Relatório Analítico do código em C:** Implementar uma análise completa com sugestões baseada no histórico de partidas, incluindo o cálculo de estatísticas agregadas (média, melhor/pior pontuação, desvio), uso de funções recursivas (para soma, mínimo, máximo e soma de quadrados) e a aplicação de heurísticas textuais para avaliação de estratégia.

---

### Semana 2 — Acompanhamento Semanal
**Período:** 18 / 05 / 2026  a  22 / 05 / 2026

**5.1 Atividades realizadas**
Realizamos reuniões de alinhamento para planejar as entregas da próxima semana. Devido ao surgimento de novas demandas acadêmicas no mesmo período (Trabalho de lógica e entregas da Residência Tecnológica), ajustamos nosso planejamento e redistribuímos as tarefas entre os integrantes.

**5.2 Decisões tomadas**
Após avaliarmos se seria melhor adaptar o nosso jogo atual ou criar um novo, decidimos desenvolver um jogo físico independente e já definimos o seu conteúdo e regras. Nesse contexto, para dar conta de todas as entregas da semana e evitar atrasos, decidimos dividir a equipe em subgrupos, cada um focado em uma entrega específica.

**5.3 Dificuldades encontradas**
O principal desafio da semana foi a gestão do tempo e a sobrecarga de tarefas. Tivemos prazos muito curtos para os trabalhos de lógica e da Residência, exatamente na mesma semana em que já tínhamos validações do projeto principal (TeCtris) com três professores diferentes. Isso dificultou bastante a organização e a priorização do que deveria ser feito primeiro.

**5.4 Próximos passos**
Concluir e entregar as soluções da disciplina de lógica e da Residência Tecnológica dentro dos prazos para, após essas entregas, retomar o foco total da equipe para o desenvolvimento, testes e finalização do projeto TeCtris.

---

### Semana 3 — Ideação e Definição da Solução
**Período:** 25 / 05 / 2026  a  29 / 05 / 2026

**5.1 Atividades realizadas**
Foi realizada a implementação das estatísticas do jogo, incluindo cálculo de média, melhor e pior desempenho. Também foram desenvolvidas funções recursivas para operações de soma, mínimo, máximo e soma dos quadrados, bem como heurísticas textuais voltadas à estratégia do jogo. Como resultado, foi estruturado um relatório analítico funcional do TeCtris. 

**5.2 Decisões tomadas**
Nesta semana, não houve decisões significativas relacionadas ao direcionamento do projeto, sendo mantido o planejamento previamente estabelecido pela equipe.

**5.3 Dificuldades encontradas**
A principal dificuldade encontrada esteve relacionada à compreensão de determinadas partes do código-fonte. Entretanto, por meio de análises, discussões em equipe e ajuda da Inteligência Artificial, foi possível superar os obstáculos e desenvolver as funcionalidades propostas. 

**5.4 Próximos passos**
Os próximos passos consistem na realização de testes funcionais e de usabilidade, além da aplicação dos ajustes necessários para a finalização e refinamento do jogo. 

---

### Semana 4 — Testes, Validação e Melhorias
**Período:** 01 / 06 / 2026  a  05 / 06 / 2026

**5.1 Atividades realizadas**
* Realização de testes funcionais para identificação de bugs e ajustes no jogo.
* Identificação de melhorias para a versão final do protótipo.
* Elaboração do relatório sobre a experiência de programação em par.

**5.2 Como a solução foi testada ou validada?**
A solução foi apresentada ao professor Ricardo Baudel, da disciplina de Interface Humano-Computador, que avaliou aspectos relacionados à experiência do usuário e à interface do jogo. Além disso, algumas funcionalidades foram demonstradas ao professor Lucas Farias, da disciplina de Fundamentos de Desenvolvimento de Software, que contribuiu com sugestões para aprimoramento do projeto. 

**5.3 Resultados dos testes ou feedbacks recebidos**

| Pessoa/grupo consultado | Feedback recebido | Melhorias sugeridas |
| :--- | :--- | :--- |
| **Prof. Ricardo Baudel** | Avaliou positivamente a proposta do jogo e sua aplicação educacional. | Aprimorar aspectos visuais e a experiência do usuário. |
| **Prof. Lucas Farias** | Considerou a mecânica do jogo interessante para o aprendizado de programação. | Expandir funcionalidades e aumentar a variedade de perguntas. |
| **Equipe de desenvolvimento (testes internos)** | Foram identificados pequenos bugs e inconsistências durante as partidas. | Corrigir falhas na mecânica do jogo e refinar a interface. |

**5.4 Melhorias realizadas no projeto**
* Implementação de trilha sonora e efeitos sonoros.
* Aprimoramento visual da interface do jogo.
* Implementação do modo Jogador vs. Jogador (PvP).
* Correção de bugs identificados durante os testes.

**5.5 Próximos passos**
Como evolução futura do projeto, será implementado o Modo Easy, uma versão do TeCtris voltada para pessoas sem experiência prévia em programação ou na linguagem C. Nesse modo, as perguntas técnicas serão substituídas por questões de conhecimentos e curiosidades gerais, tornando o jogo mais acessível para diferentes perfis de usuários. 

---

### Semana 5 — Finalização e Preparação da Apresentação
**Período:** 08 / 06 / 2026  a  12 / 06 / 2026

**5.1 Atividades realizadas**
Implementamos algumas melhorias e estruturamos a apresentação final do jogo para os professores e para a Mostra Tech.

**5.2 Entregas finais do projeto**

| Entrega final | Status | Observações |
| :--- | :--- | :--- |
| Relatório final | Concluído | Documentação técnica completa, revisada e consolidada, contemplando o histórico ágil de todas as semanas e a síntese da solução. |
| Protótipo ou proposta | Concluído | Executável do jogo TeCtris totalmente funcional em linguagem C, contendo modo PvP, banco de questões, sistema de histórico e melhorias sonoras/visuais. |
| Apresentação | Concluído | Material visual (slides) e roteiro estruturados para a defesa acadêmica e para a demonstração prática ao público na Mostra Tech. |
| Validação/testes | Concluído | Testes internos e validação de usabilidade e interface realizados com sucesso. |

**5.3 Síntese da solução final**
A solução final desenvolvida é o TeCtris, um jogo desktop educacional totalmente programado em linguagem C. O software integra a mecânica clássica de puzzle (queda e encaixe de blocos) a um sistema de quiz dinâmico em tempo real. O jogo conta com um modo competitivo local (PvP em tela dividida), onde os acertos e erros em questões de lógica e sintaxe em C impactam diretamente o grid e a pontuação, tendo como condição de vitória o alcance de 100 pontos. 

A aplicação roda 100% offline, possuindo um banco de questões embutido, engine de tempo, interface gráfica aprimorada com trilha e efeitos sonoros, além de um sistema robusto de salvamento de histórico de partidas que gera relatórios analíticos utilizando funções recursivas. 

**5.4 Principais resultados alcançados**
* **Consolidação do aprendizado:** Integração bem-sucedida dos conhecimentos adquiridos em diversas disciplinas do semestre (Lógica, Fundamentos de Desenvolvimento de Software, Programação Imperativa e Funcional, Interface Humano-Computador e Gestão de Projetos) em uma única aplicação coesa e funcional.
* **Engajamento e Gamificação:** Criação de uma ferramenta prática que mitiga a desmotivação do ensino tradicional de programação, transformando a pressão e o erro em oportunidades de aprendizado imediato.
* **Validação Acadêmica:** Aprovação e feedback positivo dos professores Ricardo Baudel, Lucas Farias e André Luiz, atestando o valor educacional e a qualidade da usabilidade da interface.
* **Entrega Completa do Escopo:** Implementação bem-sucedida de todas as mecânicas propostas, incluindo o modo PvP, manipulação de arquivos (leitura e salvamento de histórico) e relatórios analíticos com heurísticas textuais.
* **Preparação para a Mostra Tech:** Finalização de um executável estável e documentação completa (GitHub), com o projeto pronto para ser exibido e testado pelo público do evento.

**5.5 O que ainda poderia ser melhorado?**
* **Implementação do Modo Easy:** Conforme planejado nas semanas anteriores, a adição de um modo com perguntas de conhecimentos e curiosidades gerais para tornar o jogo acessível a usuários sem experiência prévia em programação.
* **Expansão do Banco de Questões:** Aumentar a variedade e os níveis de dificuldade das perguntas de programação em C, criando uma progressão de aprendizado mais longa.
* **Melhorias Visuais e de Feedback:** Refinamento contínuo das animações de transição entre a tela de puzzle e o quiz, além de aprimorar os feedbacks visuais de penalidade quando o jogador erra uma questão.
* **Evolução Tecnológica (Futuro):** Embora fora do escopo atual, uma versão futura poderia implementar conectividade em rede (Multiplayer Online) e um banco de dados em nuvem para um ranking global de pontuações entre os alunos.

---

## 6. Gestão da Equipe

### 6.1 Divisão de responsabilidades

| Integrante | Responsabilidades assumidas | Entregas realizadas | Participação na equipe |
| :--- | :--- | :--- | :--- |
| **Larissa Morais** | Atuar como Product Owner, garantindo o cumprimento de prazos e requisitos, elaborando a documentação oficial e realizando as entregas gerais do projeto. | Relatórios | Alta |
| **Alice Sena** | Atuar como Scrum Master, definindo a visão do jogo, organizando as demandas diárias e mediando as cerimônias/reuniões da equipe. | Organização e priorização do Backlog no Trello e estruturação dos slides para a apresentação na Mostra Tech. | Alta |
| **João Rafael Morato** | Atuar como Tech Leader, liderando as decisões de arquitetura de software, definindo bibliotecas e garantindo a escalabilidade do sistema. | Estrutura base da arquitetura do jogo em C, revisão estrutural e integração (merge) dos códigos da equipe. | Alta |
| **Matheus Vaz** | Desenvolver o back-end, focando no núcleo lógico, física de blocos, controle de estado, pontuação e validação de dados em C. | Código da engine de regras, sistema de histórico com funções recursivas, lógica de pontuação e integração do modo PvP. | Alta |
| **Kezia Aguiar** | Atuar no Design, projetando o layout das telas, estruturando a organização visual e realizando testes de usabilidade. | Visual do jogo, organização estrutural das informações e protótipo no Figma. | Alta |
| **Diogo Alcelino** | Atuar no Design, criando a identidade visual do projeto, definindo cores e tipografia, além de projetar layouts e aplicar testes. | Visual do jogo, identidade estabelecida. | Alta |
| **Cecília Lopes** | Desenvolver o front-end, implementando a camada gráfica via código e garantindo a correta renderização dos elementos planejados. | Código responsável pela exibição da interface de usuário, transições de tela e renderização do grid visual. | Alta |
| **Emily Raquel** | Desenvolver o front-end, focando na interface de interação, feedback visual de ações e captura de comandos dos jogadores. | Código de captura dos inputs (teclado) integrado ao sistema e implementação do feedback visual (animações de acerto/erro). | Alta |

### 6.2 Comunicação da Equipe
A comunicação e a colaboração da equipe ocorreram de forma híbrida e contínua, utilizando diversas ferramentas para garantir o alinhamento do grupo em todas as frentes do projeto. As discussões rápidas, o acompanhamento diário e a resolução de dúvidas pontuais foram realizados via grupo no WhatsApp. Para alinhamentos mais aprofundados, validações de ideias e planejamento das entregas, a equipe realizou reuniões presenciais e encontros virtuais periódicos através do Google Meet.

O gerenciamento visual das tarefas e do fluxo de trabalho foi centralizado no Trello, enquanto o Google Drive serviu como repositório principal para os arquivos relacionados ao design. Para o desenvolvimento da interface e da identidade visual, a equipe utilizou o Canva e o Figma. Por fim, o GitHub foi adotado como ferramenta oficial para o controle de versionamento do código-fonte em C e hospedagem da documentação técnica, permitindo que os desenvolvedores integrassem suas implementações de forma segura.

### 6.3 Organização do Trabalho
A organização do trabalho foi estruturada para atender rigorosamente aos prazos e requisitos parciais estipulados pelos professores das disciplinas envolvidas no projeto integrado. Na prática, o cumprimento desse calendário acadêmico fez com que o fluxo de trabalho da equipe funcionasse em um formato de sprints semanais.

A cada nova semana, a equipe realizava o planejamento das atividades, definindo uma meta clara de entrega (como estruturação da lógica, prototipagem de telas, validação de usabilidade ou consolidação do código) que precisava ser desenvolvida e finalizada naquele período. O acompanhamento dessas tarefas foi feito pelo quadro Kanban no Trello, permitindo que a equipe monitorasse o que estava "A Fazer", "Em Andamento" e "Concluído". Esse método de fragmentar o escopo total em pequenas entregas semanais garantiu que o projeto evoluísse de maneira constante e organizada até a finalização completa do jogo TeCtris.

---

## 7. Avaliação da Solução Desenvolvida

### 7.1 A solução responde ao problema inicial?
Sim. O problema inicial identificado foi a desmotivação e a dificuldade de assimilação de estudantes iniciantes no ensino tradicional da linguagem C, frequentemente baseado em métodos teóricos ou listas de exercícios monótonas. O TeCtris atende perfeitamente a esse problema ao substituir a passividade do estudo convencional por uma experiência ativa e gamificada. Ao integrar o conhecimento técnico à mecânica do jogo, exigindo resoluções sob pressão para não acumular blocos na tela, a solução transforma o erro em aprendizado imediato, aumentando significativamente o engajamento e reduzindo a frustração dos alunos com a sintaxe da linguagem. 

### 7.2 Pontos fortes da solução

| Ponto forte | Justificativa |
| :--- | :--- |
| **Gamificação do aprendizado** | Transforma o estudo puramente teórico em uma atividade dinâmica, mantendo o usuário engajado através de recompensas e penalidades diretas na mecânica do jogo. |
| **Funcionamento 100% Offline** | O banco de questões e o sistema de salvamento são locais, o que garante total acessibilidade e permite que o jogo rode em laboratórios ou máquinas sem conexão com a internet. |
| **Relatórios analíticos detalhados** | O uso de funções recursivas e heurísticas para calcular estatísticas (média, melhor/pior pontuação) permite que os jogadores monitorem sua evolução técnica ao longo das partidas. |
| **Modo Competitivo (PvP Local)** | A possibilidade de jogar em dupla divide a experiência, estimula a tomada rápida de decisões e promove um ambiente de revisão colaborativa e saudável entre os alunos. |

### 7.3 Limitações da solução

| Limitação | Possível melhoria futura |
| :--- | :--- |
| **Restrito ao multiplayer local** | Desenvolvimento de um sistema de comunicação em rede (sockets) para permitir partidas online entre alunos em computadores diferentes. |
| **Execução exclusiva para Desktop** | Adaptação e portabilidade do projeto para rodar em navegadores (Web) ou dispositivos móveis (Mobile), ampliando a acessibilidade. |
| **Banco de questões estático** | Criação de um banco de dados dinâmico em nuvem, permitindo que professores adicionem novas perguntas remotamente para atualizar os desafios do jogo. |

### 7.4 Potencial de aplicação prática
O TeCtris possui um alto potencial de aplicação prática, especialmente no contexto acadêmico e institucional. Ele pode ser adotado por universidades, escolas técnicas e cursos livres de tecnologia como uma ferramenta de apoio pedagógico. Professores de laboratório podem utilizá-lo para promover "torneios" amigáveis ao final de cada módulo da disciplina, servindo como uma avaliação formativa ou revisão para provas. Além disso, centros acadêmicos, comunidades de desenvolvedores ou grupos de estudo podem instalá-lo em espaços de convivência para incentivar o treino da lógica de programação de maneira lúdica e descontraída. 

---

## 8. Aprendizados da Equipe

### 8.1 O que a equipe aprendeu durante o desenvolvimento do projeto?
**Resposta da equipe:** Durante o desenvolvimento do TeCtris, a equipe adquiriu uma sólida experiência prática na integração de conhecimentos multidisciplinares, unindo conceitos de Lógica de Programação, Fundamentos de Desenvolvimento de Software, Programação Imperativa e Funcional e Interface Humano-Computador. 

No aspecto técnico, aprimoramos substancialmente nosso domínio da linguagem C, aprendendo a estruturar interfaces gráficas via código, manipular arquivos locais e aplicar funções recursivas na geração de estatísticas. No âmbito da gestão e colaboração, o projeto trouxe grandes aprendizados sobre a importância da metodologia ágil. Aprendemos a organizar fluxos de trabalho semanais no Trello, controlar o versionamento no GitHub e, principalmente, a lidar com a pressão de prazos curtos dividindo a equipe em subgrupos focados. 

Por fim, as validações com os professores reforçaram a importância de colocar o usuário no centro do desenvolvimento, mostrando que a criação de uma boa identidade visual e a realização de testes de usabilidade são passos fundamentais para que o software não apenas funcione bem, mas também seja intuitivo e cumpra seu papel educacional.

### 8.2 Quais competências foram desenvolvidas?

| Competência | Foi desenvolvida? | Comentário da equipe |
| :--- | :--- | :--- |
| **Trabalho em equipe** | Sim | A divisão do grupo em frentes específicas (back-end, front-end, design e gestão) exigiu alta colaboração para garantir que o código, o visual e as regras se integrassem perfeitamente na versão final. |
| **Comunicação** | Sim | Foi fundamental para manter o alinhamento constante, utilizando WhatsApp, Google Meet e reuniões presenciais para debater ideias, repassar feedbacks dos professores e resolver conflitos técnicos. |
| **Organização e planejamento** | Sim | O gerenciamento das entregas no formato de sprints semanais, com o uso do Trello, foi crucial para cumprir o cronograma rigoroso sem comprometer a qualidade do software. |
| **Resolução de problemas** | Sim | A equipe lidou com obstáculos complexos na linguagem C, como a integração da lógica de arquivos (para salvar o histórico) com o loop principal do jogo e a correção de bugs na movimentação das peças. |
| **Criatividade e inovação** | Sim | Desenvolver o conceito do "TeCtris", unindo a mecânica clássica de puzzle com um quiz técnico, e projetar uma interface atrativa puramente via código exigiu grande capacidade inventiva. |
| **Gestão do tempo** | Sim | Foi uma das competências mais testadas, especialmente quando a equipe precisou conciliar as entregas do jogo com outras demandas acadêmicas (Trabalho de lógica e Residência Tecnológica) simultaneamente. |
| **Uso de ferramentas digitais** | Sim | Houve um salto de aprendizado na adoção de ferramentas de mercado, como GitHub (versionamento de código), Figma/Canva (design de UI/UX) e Trello (metodologia ágil). |
| **Pensamento crítico** | Sim | Aplicado durante a análise dos testes de usabilidade, na avaliação de heurísticas e na absorção dos feedbacks dos professores para decidir quais melhorias realmente agregavam valor ao jogo. |

### 8.3 Principais desafios enfrentados pela equipe
O desenvolvimento do TeCtris impôs desafios tanto técnicos quanto de gestão. Do ponto de vista técnico, a maior dificuldade inicial foi compreender lógicas complexas do código-fonte em C, especialmente a integração do sistema de salvamento/leitura de arquivos (histórico) com o loop principal de funcionamento do jogo. Além disso, a implementação de funções recursivas e a sincronização do timer com os comandos do teclado (inputs) exigiram muita pesquisa. 

Do ponto de vista da gestão, o principal desafio ocorreu na sobrecarga de demandas acadêmicas, onde a equipe precisou equilibrar prazos extremamente curtos para a entrega de trabalhos de outras disciplinas (como Lógica e a Residência Tecnológica) ao mesmo tempo em que realizava validações do projeto com três professores diferentes. 

### 8.4 Como a equipe superou os desafios?
Para superar a sobrecarga de prazos e tarefas, a principal estratégia adotada foi a reorganização do fluxo de trabalho: dividimos a equipe em subgrupos, permitindo que cada frente focasse exclusivamente em uma entrega prioritária, garantindo o cumprimento de todos os compromissos acadêmicos. Para os desafios técnicos, a equipe recorreu ao estudo colaborativo, intensas discussões em grupo e ao uso de ferramentas de Inteligência Artificial para auxiliar na compreensão e refatoração de trechos complexos do código. A comunicação contínua e o uso do versionamento no GitHub também foram essenciais para garantir que, mesmo divididos, os módulos desenvolvidos separadamente fossem integrados com sucesso na versão final do jogo. 

---

## 9. Autoavaliação da Equipe

### 9.1 Avaliação geral da equipe

| Critério | Nota de 0 a 10 | Justificativa |
| :--- | :--- | :--- |
| **Organização** | 10 | A equipe gerenciou o escopo de forma exemplar, utilizando Trello para o acompanhamento em sprints semanais e dividindo-se estrategicamente em subgrupos quando houve sobrecarga de demandas acadêmicas. |
| **Participação dos integrantes** | 10 | Todos os membros mantiveram um nível de engajamento alto, assumindo responsabilidades claras em suas frentes (Gestão, Back-end, Front-end e Design), se disponibilizando sempre para contribuir e entregar o que foi proposto. Fomos uma equipe muito coesa. |
| **Cumprimento dos prazos** | 10 | Apesar do cronograma apertado e da coincidência com trabalhos de outras disciplinas, a equipe honrou todas as entregas e validações exigidas pelos três professores envolvidos. |
| **Qualidade das entregas** | 9 | O projeto resultou em um executável robusto, sem crashes graves, com interface gráfica funcional, documentação completa no GitHub e um sistema de relatórios analíticos bem estruturado. |
| **Comunicação interna** | 10 | O uso eficiente do WhatsApp para o dia a dia e do Google Meet/reuniões presenciais para alinhamentos profundos garantiu que não houvesse gargalos de informação entre os desenvolvedores e os designers. |
| **Criatividade da solução** | 9 | A fusão da mecânica de puzzle com o ensino de programação foi uma abordagem altamente inovadora para o problema, perdendo apenas um ponto por ainda estar restrita ao ambiente desktop offline e ser uma adaptação de um jogo já existente (tetris). |
| **Aprendizado durante o projeto** | 9 | Houve um salto técnico gigantesco no domínio da linguagem C, manipulação de arquivos e metodologias ágeis, reconhecendo que sempre há espaço para evoluir em arquiteturas mais complexas no futuro. |

### 9.2 Autoavaliação individual

| Integrante | O que contribuiu para o projeto? | O que poderia ter feito melhor? | Nota de participação |
| :--- | :--- | :--- | :--- |
| **Larissa Morais** | Product Owner - Responsável pela elaboração dos relatórios, por avisar a equipe quanto aos prazos de cada entrega e se estavam de acordo com os requisitos propostos pelos professores. | “Inicialmente fiquei um pouco perdida quanto ao que eu faria na minha função e acho que poderia ter sido mais proativa para ajudar. Felizmente, não demorei muito para conversar com a equipe e ficar por dentro de tudo, me disponibilizando para ajudar no que fosse necessário e realizar as minhas responsabilidades”. | 10 |
| **Alice Sena** | Scrum Master - Contribuí para a organização da equipe, acompanhamento das tarefas e cumprimento dos prazos, garantindo uma boa comunicação entre os integrantes. | “Tive dificuldade em gerenciar o meu próprio tempo, por trabalhar e fazer pesquisa acadêmica. Poderia ter realizado um acompanhamento ainda mais frequente do progresso individual das tarefas e aprofundado a utilização de métricas ágeis para monitorar o desempenho da equipe. Além disso, poderia ter promovido mais momentos de retrospectiva ao longo do desenvolvimento para identificar oportunidades de melhoria de forma antecipada”. | 10 |
| **João Rafael Morato** | Responsável pelo planejamento e auxílio para os desenvolvedores back-end. | “No começo fiquei meio perdido, porém sinto que depois consegui auxiliar bem os meus colegas, tanto no back-end quanto na documentação do código”. | 10 |
| **Matheus Vaz** | Responsável pelo desenvolvimento back-end, features de histórico e estatísticas. | “Tive dificuldade de utilizar C e o Raylib, o que ocasionou em algumas demandas serem entregues rapidamente mas corrigidas ao longo do tempo corretamente”. | 10 |
| **Cecília Lopes** | Responsável pelo front-end. | “Apesar de ter entregado tudo dentro dos prazos, poderia ter gerenciado melhor meu tempo durante o projeto, o que me teria dado mais espaço para refinar a interface e deixá-la mais atrativa e cuidada esteticamente.” | 10 |
| **Emily Marques** | Responsável pelo front-end. | ”Tive um pouco de dificuldade em programar o front em C, mas com persistência e ajuda dos meus colegas consegui dar o meu máximo.” | 10 |
| **Kezia Aguiar** | Responsável pelo UX/UI e o desenvolvimento do design do protótipo. | “Tive uma certa dificuldade no início para aprender a usar o Figma, mas meus colegas mais experientes me auxiliaram e no final foi bem produtivo. E com relação às outras documentações de UX eu consegui desenvolver sem problemas.” | 10 |
| **Diogo Alcelino** | Contribui com o design do projeto e a organização do stand para a exposição dele na mostra tech. | Durante o projeto terminei ficando um pouco ausente, devido ao meu novo emprego e a rotina que mudou. Mas sempre que podia, disponibilizava minha ajuda caso precisassem. Percebo que realmente fiz o que estava ao meu alcance, mas de qualquer forma não contribui tanto quanto os meus colegas para o projeto. | 8 |