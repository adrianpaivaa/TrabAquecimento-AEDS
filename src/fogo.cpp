#include "fogo.hpp"
#include "config.hpp"

void propagacaoFogo(int** matriz, int n, int m, int** tempoChamas) {
    int** novaMatriz = new int*[n];
    for (int i = 0; i < n; i++) {
        novaMatriz[i] = new int[m];
        for (int j = 0; j < m; j++) {
            novaMatriz[i][j] = matriz[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matriz[i][j] == 1) {

                if ((VENTO_BAIXO && i > 0 && matriz[i - 1][j] == 2) ||
                    (VENTO_CIMA && i < n - 1 && matriz[i + 1][j] == 2) ||
                    (VENTO_DIREITA && j > 0 && matriz[i][j - 1] == 2) ||
                    (VENTO_ESQUERDA && j < m - 1 && matriz[i][j + 1] == 2)) {
                    novaMatriz[i][j] = 2;
                    tempoChamas[i][j] = 1;
                }
            } else if (matriz[i][j] == 2) {
                if (tempoChamas[i][j] == 1) {
                    tempoChamas[i][j]++;
                } else if (tempoChamas[i][j] == 2) {
                    novaMatriz[i][j] = 3;
                }
            }
            
        }
    }

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
}

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