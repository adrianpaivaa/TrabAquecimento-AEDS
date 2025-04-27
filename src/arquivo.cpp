#include "arquivo.hpp"
#include "fogo.hpp"
#include "animal.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib> 

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

