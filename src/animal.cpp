bool movimentoAnimal(int** matriz, int n, int m, int& posX, int& posY, int& numCiclos, int& passos) {
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    if (matriz[posX][posY] == 0 && numCiclos < 3) {
        numCiclos++;
        return true;
    }

    int melhorX = posX;
    int melhorY = posY;
    int melhorPrioridade = 5;

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

        // ⚠️ Força saída após 3 ciclos numa posição segura (0)
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
    }

    // Verifica se está cercado
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
}
