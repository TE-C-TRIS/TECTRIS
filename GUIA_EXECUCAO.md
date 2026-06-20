# 📘 Guia Completo de Instalação e Execução - Tectris C

Este guia fornece instruções passo a passo para configurar, compilar e rodar o **Tectris - Aprenda C Jogando** no Windows.

---

## 1. Requisitos do Sistema

Para compilar o projeto, você precisará das seguintes ferramentas instaladas:

| Ferramenta | Versão Recomendada | Link de Download |
| :--- | :--- | :--- |
| **Compilador C (GCC)** | MinGW-w64 (via w64devkit) | [Download w64devkit](https://github.com/skeeto/w64devkit/releases) |
| **CMake** | 3.10 ou superior | [Download CMake](https://cmake.org/download/) |
| **Raylib** | 4.5 ou superior | [Download Raylib](https://www.raylib.com/) |

---

## 2. Instalação Passo a Passo (Windows)

### Passo 1: Configurar o Compilador
1. Baixe o `w64devkit-x.x.x.zip` do link acima.
2. Extraia para uma pasta (ex: `C:\w64devkit`).
3. Adicione o caminho `C:\w64devkit\bin` às suas **Variáveis de Ambiente (PATH)** do Windows.

### Passo 2: Instalar a Raylib
1. Baixe o instalador `raylib_installer_vX.X.exe` para MinGW.
2. Instale no local padrão (ex: `C:\raylib`).
3. O CMake do projeto está configurado para procurar a Raylib automaticamente. Se você instalou em um local customizado, defina a variável `raylib_DIR` no CMake.

---

## 3. Compilação via CMake

Abra o **Prompt de Comando** ou **PowerShell** na pasta raiz do projeto e execute:

```bash
# 1. Criar diretório de build
mkdir build
cd build

# 2. Configurar o projeto
cmake -G "MinGW Makefiles" ..

# 3. Compilar o executável
cmake --build . --config Release
```

O executável será gerado na pasta `build/bin/Tectris.exe`.

---

## 4. Como Jogar

Após a compilação, basta executar o arquivo `Tectris.exe`.

### Controles:
- **Setas Esquerda/Direita**: Movem a peça lateralmente.
- **Seta Cima**: Rotaciona a peça (com sistema de Wall Kick).
- **Seta Baixo**: Soft Drop (queda lenta).
- **Espaço**: Hard Drop (queda instantânea).
- **P**: Pausa o jogo.
- **Enter**: Inicia o jogo e confirma respostas no desafio.

---

## 5. Estrutura do Projeto

```text
tectris_c/
├── include/          # Arquivos de cabeçalho (.h)
│   ├── common.h      # Definições globais e estruturas
│   └── game.h        # Protótipos das funções de jogo
├── src/              # Código-fonte (.c)
│   ├── main.c        # Loop principal e Máquina de Estados
│   ├── game/
│   │   ├── game.c    # Lógica do Tetris e Kill Line
│   │   └── questions.c # Banco de perguntas e validação
│   └── render/
│       └── render.c  # Renderização responsiva e escala
├── CMakeLists.txt    # Configuração do Build
├── README.md         # Visão geral do projeto
└── RELATORIO.md      # Detalhes técnicos da implementação
```

---

## 6. Problemas Comuns e Soluções

### Erro: "raylib not found"
**Causa:** O CMake não encontrou a biblioteca Raylib.
**Solução:** Execute o comando de configuração passando o caminho da Raylib:
`cmake -Draylib_DIR="C:/raylib/lib/cmake/raylib" ..`

### Erro: "gcc is not recognized"
**Causa:** O compilador MinGW não está no seu PATH.
**Solução:** Verifique se `C:\w64devkit\bin` (ou similar) foi adicionado corretamente às variáveis de ambiente e reinicie o terminal.

### O jogo abre e fecha imediatamente
**Causa:** Faltam DLLs ou erro de inicialização gráfica.
**Solução:** Certifique-se de que os drivers de vídeo estão atualizados e que a pasta `assets` (se existir) está no mesmo diretório do executável.

---

## 7. Melhorias Aplicadas (Refinamento Final)
- **Escala Dinâmica**: O jogo calcula o `cellSize` baseado na altura da janela, garantindo que o grid nunca saia da tela.
- **Wall Kicks**: Sistema de 5 tentativas de ajuste de posição durante a rotação.
- **Validação Robusta**: Uso de `_stricmp` (Windows) para comparação case-insensitive e suporte a múltiplas respostas.
- **Feedback Visual**: Kill Line pulsante e overlays de estado com transparência e efeitos de brilho.
