# 🔥 Trabalho de Aquecimento - AEDS1

<div align="center">
  <img height="25px" src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white"/>
  <img height="25px" src="https://img.shields.io/badge/Made%20for-VSCode-1f425f.svg"/>
</div>

---

# 📌 Introdução

Este repositório é referente ao trabalho de aquecimento da disciplina **Algoritmos e Estrutura de Dados I**, ministrada pelo professor **Daniel Morais** do **Centro Federal de Educação Tecnológica de Minas Gerais (CEFET-MG)**.

O projeto simula a **propagação de fogo** em uma floresta representada por uma matriz, onde um **animal tenta sobreviver** movendo-se estrategicamente.

---

# 🎯 Objetivos

- Representar diferentes tipos de terreno:
  - Área vazia
  - Árvores saudáveis
  - Árvores em chamas
  - Árvores queimadas
  - Água
- Simular propagação realista do fogo com influência do vento
- Criar comportamento inteligente para o animal fugir do fogo
- Simular geração de umidade ao redor de fontes de água

---

# 📁 Organização dos Arquivos

```bash
.
├── include/
│   ├── animal.hpp
│   ├── arquivo.hpp
│   ├── config.hpp
│   ├── fogo.hpp
│   └── matriz.hpp
├── src/
│   ├── animal.cpp
│   ├── arquivo.cpp
│   ├── fogo.cpp
│   ├── main.cpp
│   └── matriz.cpp
├── input.dat
├── output.dat
└── Makefile

```
# 🛠️ Implementação
## Configurações das constantes globais
```c
#ifndef CONFIG_HPP
#define CONFIG_HPP

const int MAX_ITERACOES = 100;
const bool VENTO_CIMA = true;
const bool VENTO_BAIXO = true;
const bool VENTO_DIREITA = true;
const bool VENTO_ESQUERDA = true;

#endif
```
Esse arquivo define constantes globais que são utilizadas para configurar o comportamento da simulação.

## Constantes definidas:
### - MAX_ITERACOES
  
  Define o máximo de ciclos que a simulação executará.
### - VENTO_CIMA, VENTO_BAIXO, VENTO_DIREITA, VENTO_ESQUERDA
  
  Controlam a influência do vento na propagação do fogo. Se qualquer uma dessas constantes por true, o fogo poderá se propagar mais facilmente naquela direção.  
  ## 📄 Formato do `input.dat`

Exemplo do arquivo de entrada da floresta:
```
5 5 1 1 2 2
1 1 1 1 4
1 2 1 1 4
1 1 1 1 1
0 0 1 1 1
1 4 1 0 4
```

- **5 5**: número de linhas e colunas da floresta
- **1 1**: posição inicial do fogo (linha e coluna)
- **2 2**: posição inicial do animal (linha e coluna)
- **Linhas seguintes**: representação da floresta:
  - `0`: espaço vazio
  - `1`: árvore
  - `2`: árvore em chamas (aparece durante a simulação)
  - `3`: árvore queimada (aparece durante a simulação)
  - `4`: água

---
  

## 💡 Principais Funções
#### `bool movimentoAnimal(int** matriz, int n, int m, int& posX, int& posY, int& numCiclos, int& passos)`

Essa função controla o comportamento do animal em cada ciclo do simulador. 
Vamos dividi-la em partes para termos uma melhor compreensão:

#### 1- Direções possíveis de movimento

```c
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
```
Define o movimento apenas para as direções ortogonais.

#### 2- Permanecer em célula segura por até 3 ciclos

```c
if (matriz[posX][posY] == 0 && numCiclos < 3) {
    numCiclos++;
    return true;
}
```
Se o animal estiver em uma célula segura (0) por menos de 3 ciclos, ele permanece na posição atual e atualiza o contador de ciclos.

#### 3- Busca e movimentação para a melhor célula vizinha com base em prioridade
```c
for (int i = 0; i < 4; i++) {
        int novoX = posX + dx[i];
        int novoY = posY + dy[i];

        if (novoX >= 0 && novoX < n && novoY >= 0 && novoY < m) {
            int valor = matriz[novoX][novoY];

            int prioridade = 5;
            if (valor == 4) prioridade = 1;
            else if (valor == 0) prioridade = 2;
            else if (valor == 1) prioridade = 3;
            else if (valor == 3) prioridade = 4;

            if (prioridade < melhorPrioridade) {
                melhorPrioridade = prioridade;
                melhorX = novoX;
                melhorY = novoY;
            }
        }
    }

    if (melhorPrioridade < 5) {
        posX = melhorX;
        posY = melhorY;
        numCiclos = 0;
        passos++;
    } else {
        numCiclos++;
```
Analisa as células vizinhas e escolhe a melhor com base nas seguintes prioridades:
| Tipo de célula | Valor            | Prioridade |
|------------------|------------------------|-------------|
| Água | 4  | 1 (melhor)|
| Espaço vazio | 0 | 2 |
| Árvores| 1 | 3 |
| Árvores queimadas| 3 | 4 |
| Árvores em chamas| 2 | 5 (evitado) |

Caso identifique uma célula com prioridade melhor que 5, o animal se move para ela. O contador de ciclos em que ele não se moveu é zerado e o número de passos aumenta.

#### 4- Força saída após 3 ciclos parado
```c
if (matriz[posX][posY] == 0 && numCiclos >= 3) {
    int fugaX = posX;
    int fugaY = posY;
    int melhorPrioridadeFuga = 5;

    for (int i = 0; i < 4; i++) {
        int novoX = posX + dx[i];
        int novoY = posY + dy[i];

        if (novoX >= 0 && novoX < n && novoY >= 0 && novoY < m) {
            int valor = matriz[novoX][novoY];

            int prioridade = 5;
            if (valor == 4) prioridade = 1;
            else if (valor == 0) prioridade = 2;
            else if (valor == 1) prioridade = 3;
            else if (valor == 3) prioridade = 4;

            if (prioridade < melhorPrioridadeFuga) {
                melhorPrioridadeFuga = prioridade;
                fugaX = novoX;
                fugaY = novoY;
            }
        }
    }

    if (melhorPrioridadeFuga < 5) {
        posX = fugaX;
        posY = fugaY;
        numCiclos = 0;
        passos++;
    }
}
```
Se o animal estiver em uma célula segura (0) por 3 ciclos consecutivos, ele é forçado a se movimentar para uma célula adjacente. Novamente, buscando a célula mais segura através das prioridades.

#### 5- Verificação de movimento
```c
bool cercado = true;
for (int i = 0; i < 4; i++) {
    int adjX = posX + dx[i];
    int adjY = posY + dy[i];
    if (adjX >= 0 && adjX < n && adjY >= 0 && adjY < m && matriz[adjX][adjY] != 2) {
        cercado = false;
        break;
    }
}

if (matriz[posX][posY] == 4) cercado = false;
return !cercado;
```
Verifica se o animal está cercado por células de árvores queimadas (2). A função retorna *true*, permitindo movimento do animal ou *false*, caso o animal esteja cercado.

#### `void lerArquivo(const char* caminho, int& n, int& m, int& fogo_i, int& fogo_j, int& posX, int& posY, int*** matriz)`
```c
void lerArquivo(const char* caminho, int& n, int& m, int& fogo_i, int& fogo_j, int& posX, int& posY, int*** matriz) {
    std::ifstream arquivo(caminho);
    if (!arquivo.is_open()) {
        std::cout << "Não foi possível abrir o arquivo: " << caminho << std::endl;
        std::exit(1); // evita continuar a execução
    }

    if(!(arquivo >> n >> m >> fogo_i >> fogo_j >> posX >> posY)){
        std::cerr << "Erro ao ler as informações necessárias no arquivo.\n";
        std::exit(1);
    };

    *matriz = new int*[n];
    for (int i = 0; i < n; i++) {
        (*matriz)[i] = new int[m];
        for (int j = 0; j < m; j++) {
            if (!(arquivo >> (*matriz)[i][j])) {
                std::cerr << "Erro ao ler a matriz na posição [" << i << "][" << j << "]\n";
                std::exit(1);
            }
        }
    }

    arquivo.close();
}
```
Essa função é responsável por ler o arquivo de entrada, que contém a configuração da simulação, incluindo o tamanho da matriz (n e m), a posição inicial do fogo e do animal e a matriz que representa o ambiente. A matriz é alocada dinamicamente e preenchida com os dados do arquivo.

#### ` void printarArquivo(const char* caminho, int n, int m, int** matriz, int ciclo, int posX, int posY)`
```c
void printarArquivo(const char* caminho, int n, int m, int** matriz, int ciclo, int posX, int posY) {
std::ofstream arquivo(caminho, std::ios::app);
    if (!arquivo.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo para escrita: " << caminho << std::endl;
        std::exit(1);
    }

    arquivo << "Ciclo " << ciclo << ":\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arquivo << matriz[i][j] << " ";
        }
        arquivo << "\n";
    }
    arquivo << "Posição do animal: (" << posX << ", " << posY << ")\n";
    arquivo << "\n";

    arquivo.close();
}
```
Escreve no arquivo a configuração atual da matriz a cada ciclo de simulação. Mostrando o número do ciclo, o estado atual da matriz e a posição do animal.

### `void propagacaoFogo(int** matriz, int n, int m, int** tempoChamas)`

Essa função simula a propagação do fogo ao longo da floresta com influência do vento e controle do tempo das chamas.

#### 1- Cópia da matriz original para uma matriz temporária

```c
int** novaMatriz = new int*[n];
for (int i = 0; i < n; i++) {
    novaMatriz[i] = new int[m];
    for (int j = 0; j < m; j++) {
        novaMatriz[i][j] = matriz[i][j];
    }
}

```
Permite simular a propagação sem afetar diretamente a matriz original durante o ciclo

#### 2- Verificação de propagação com base no vento

```c
if (matriz[i][j] == 1) {
    if ((VENTO_BAIXO && i > 0 && matriz[i - 1][j] == 2) ||
        (VENTO_CIMA && i < n - 1 && matriz[i + 1][j] == 2) ||
        (VENTO_DIREITA && j > 0 && matriz[i][j - 1] == 2) ||
        (VENTO_ESQUERDA && j < m - 1 && matriz[i][j + 1] == 2)) {
        novaMatriz[i][j] = 2;
        tempoChamas[i][j] = 1;
    }
}

```
Se a célula atual é uma árvore (1) e existe uma célula vizinha em chamas (2) na direção permitida pelo vento, ela pega fogo. O tempo de chama é iniciado com 1.

#### 3- Controle do tempo em que uma célula permanece em chamas
```c
else if (matriz[i][j] == 2) {
    if (tempoChamas[i][j] == 1) {
        tempoChamas[i][j]++;
    } else if (tempoChamas[i][j] == 2) {
        novaMatriz[i][j] = 3;
    }
}

```
-No primeiro ciclo, o tempo é incrementado.

-No segundo ciclo, a célula se torna uma árvore queimada(3).

#### 4- Atualização final da matriz e limpeza
```c
for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        matriz[i][j] = novaMatriz[i][j];
        if (matriz[i][j] != 2) {
            tempoChamas[i][j] = 0;
        }
    }
    delete[] novaMatriz[i];
}
delete[] novaMatriz;

```
-Substitui a matriz antiga pela nova versão atualizada

-Zera o tempo de chama nas células que não estão mais pegando fogo

-Libera a memória da matriz temporária

### `void espalharUmidade(int** matriz, int n, int m, int posX, int posY)`
```c
void espalharUmidade(int** matriz, int n, int m, int posX, int posY) {
    if (matriz[posX][posY] == 4) {
        matriz[posX][posY] = 0;
    
        // Cima
        if (posX - 1 >= 0 && matriz[posX - 1][posY] != 4) {
            matriz[posX - 1][posY] = 1;
        }
        // Baixo
        if (posX + 1 < n && matriz[posX + 1][posY] != 4) {
            matriz[posX + 1][posY] = 1;
        }
        // Esquerda
        if (posY - 1 >= 0 && matriz[posX][posY - 1] != 4) {
            matriz[posX][posY - 1] = 1;
        }
        // Direita
        if (posY + 1 < m && matriz[posX][posY + 1] != 4) {
            matriz[posX][posY + 1] = 1;
        }
    }
}
```
Simula o efeito da célula de água (4) sobre o ambiente ao redor.

Se o animal está sobre uma célula de água, ela é convertida em espaço vazio (0) e a umidade é espalhada nas quatro direções ortogonais, transformando as células vizinhas em árvores saudáveis (1).

### `void executarSimulacao()`

Essa função coordena toda a lógica da simulação: leitura do mapa, controle do fogo, movimentação do animal e registro de saída.

#### 1- Validação da posição inicial

```c
int n, m, fogo_i, fogo_j, posX, posY;
int** floresta = nullptr;

lerArquivo("input.dat", n, m, fogo_i, fogo_j, posX, posY, &floresta);

if (posX < 0 || posX >= n || posY < 0 || posY >= m || (floresta[posX][posY] != 0 && floresta[posX][posY] != 1)) {
    std::cerr << "Erro: Posição inicial do animal inválida no arquivo.\n";
    return;
}

```
Carrega a matriz da floresta e verifica se a posição inicial do animal é válida

#### 2- Inicialização da matriz tempoChamas 

```c
int numCiclos = 0;

int** tempoChamas = new int*[n];
for (int i = 0; i < n; i++) {
    tempoChamas[i] = new int[m];
    for (int j = 0; j < m; j++) {
        tempoChamas[i][j] = (floresta[i][j] == 2) ? 1 : 0;
    }
}

std::ofstream output("output.dat", std::ios::trunc);
output.close();

printarArquivo("output.dat", n, m, floresta, 0, posX, posY);

```
Cria a matriz tempoChamas, usada para controlar por quanto tempo cada célula está em chamas, se a célula já está em chamas, recebe 1, o restante da matriz recebe 0.

#### 3- Loop principal da simulação
```c
bool animalSobreviveu = true;
int passos = 0;

for (int ciclo = 0; ciclo < MAX_ITERACOES; ciclo++) {
    bool sobreviveu = movimentoAnimal(floresta, n, m, posX, posY, numCiclos, passos);

    if (!sobreviveu) {
        std::cout << "O animal morreu no ciclo " << ciclo + 1 << "!\n";
        animalSobreviveu = false;
        break;
    }

    propagacaoFogo(floresta, n, m, tempoChamas);

    espalharUmidade(floresta, n, m, posX, posY);

    printarMatrizComAnimal(floresta, n, m, posX, posY);

    printarArquivo("output.dat", n, m, floresta, ciclo + 1, posX, posY);
}
```
Para cada ciclo:

-Move o animal com a função movimentoAnimal. Caso o animal seja morto, o loop termina.

-Propaga o fogo com base no vento e tempo das chamas

-Caso o animal esteja em água, umedece o entorno.

-Salva todas as informações no arquivo

#### 4- Escrita do resultado final 
```c
output.open("output.dat", std::ios::app);
if(output.is_open()){
   if(animalSobreviveu){
       output << "O animal sobreviveu!\n";
   } else {
       output << "O animal não sobreviveu!\n";
   }
   output << "Número de passos: " << passos << "\n";
   output.close();

   for (int i = 0; i < n; i++) {
       delete[] tempoChamas[i];
   }
   delete[] tempoChamas;

   limparMatriz(floresta, n);
}

```
Registra se o animal sobreviveu e quantos passos ele deu. Depois libera toda a memória alocada dinamicamente (tempoChamas e floresta).

# ▶️ Compilação

Para compilar e rodar o código usando MakeFile, basta seguir os seguintes comandos.
| Comando                |  Função                                                                                               |                     
| -----------------------| ------------------------------------------------------------------------------------------------------|
|  make clean          | Apaga a última compilação realizada contida na pasta build                                            |
|  make                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build               |
|  make run            | Executa o programa da pasta build após a realização da compilação                                     |
|make r| Faz os três processos descritos acima em apenas um comando|

# Autor
<p>
  Ádrian Henrique de Abreu Paiva - Graduando em Engenharia da Computação pelo <a href="https://www.cefetmg.br" target="_blank">CEFET-MG</a>.   
  Contato: (<a href="mailto:adrian.paiva@aluno.cefetmg.br">adrian.paiva@aluno.cefetmg.br</a>)
</p>
