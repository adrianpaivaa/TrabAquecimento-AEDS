#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

void lerArquivo(const char* caminho, int& n, int& m, int& fogo_i, int& fogo_j, int& posAnimalX, int& posAnimalY, int*** matriz);//passagem por referência
void printarArquivo(const char* caminho, int n, int m, int** matriz, int ciclo, int posX, int posY);
void limparArquivo(int** matriz, int n);

#endif