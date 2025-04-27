#include <fstream>
#include "arquivo.hpp"
#include "matriz.hpp"
#include "fogo.hpp"
#include "config.hpp"
#include "animal.hpp"
#include <iostream>

void alocarMatriz(int*** matriz, int n, int m){
    *matriz = new int*[n];
    for (int i = 0; i < n; i++) {
        (*matriz)[i] = new int[m];
    }
}

void limparMatriz(int** matriz, int n){
    for(int i =0; i < n; i++){
        delete[] matriz[i];
    } 
    delete[] matriz;
}

void printarMatriz(int** matriz, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            std::cout << matriz[i][j] << " ";
        }
        std::cout<<"\n";
    }
}


void printarMatrizComAnimal(int** matriz, int n, int m, int posX, int posY) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == posX && j == posY) {
                std::cout << "A ";
            } else {
                std::cout << matriz[i][j] << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void executarSimulacao() {
    int n, m, fogo_i, fogo_j, posX, posY;
    int** floresta = nullptr;

    lerArquivo("input.dat", n, m, fogo_i, fogo_j, posX, posY, &floresta);

    if (posX < 0 || posX >= n || posY < 0 || posY >= m || (floresta[posX][posY] != 0 && floresta[posX][posY] != 1)) {
        std::cerr << "Erro: Posição inicial do animal inválida no arquivo.\n";
        return;
    }

    //int posX = 0; 
    //int posY = 0; 
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
}