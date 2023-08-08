#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int linha;
    int coluna;
    int distancia;
} Ponto;

Ponto criarPonto(int linha, int coluna, int distancia) {
    Ponto p;
    p.linha = linha;
    p.coluna = coluna;
    p.distancia = distancia;
    return p;
}

int menorCaminho(int linhas, int colunas, int **cidade) {
    int direcoes[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    bool **visitado = (bool **)malloc(linhas * sizeof(bool *));
    for (int i = 0; i < linhas; i++) {
        visitado[i] = (bool *)malloc(colunas * sizeof(bool));
        for (int j = 0; j < colunas; j++) {
            visitado[i][j] = false;
        }
    }

    Ponto *fila = (Ponto *)malloc(linhas * colunas * sizeof(Ponto));
    int frente = 0, traseira = 0;
    int menorDistancia = -1;

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (cidade[i][j] == 3) {
                fila[traseira++] = criarPonto(i, j, 0);
                visitado[i][j] = true;
            }
        }
    }

    while (frente < traseira) {
        Ponto p = fila[frente++];
        int linha = p.linha;
        int coluna = p.coluna;
        int distancia = p.distancia;

        if (cidade[linha][coluna] == 0) {
            if (menorDistancia == -1 || distancia < menorDistancia) {
                menorDistancia = distancia;
            }
        }

        for (int i = 0; i < 4; i++) {
            int novaLinha = linha + direcoes[i][0];
            int novaColuna = coluna + direcoes[i][1];

            if (novaLinha >= 0 && novaLinha < linhas && novaColuna >= 0 && novaColuna < colunas && !visitado[novaLinha][novaColuna] && cidade[novaLinha][novaColuna] != 2) {
                fila[traseira++] = criarPonto(novaLinha, novaColuna, distancia + 1);
                visitado[novaLinha][novaColuna] = true;
            }
        }
    }

    for (int i = 0; i < linhas; i++) {
        free(visitado[i]);
    }
    free(visitado);
    free(fila);

    return menorDistancia;
}

int main() {
    int linhas, colunas;
    scanf("%d %d", &linhas, &colunas);

    int **cidade = (int **)malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        cidade[i] = (int *)malloc(colunas * sizeof(int));
        for (int j = 0; j < colunas; j++) {
            scanf("%d", &cidade[i][j]);
        }
    }

    int resultado = menorCaminho(linhas, colunas, cidade);

    printf("%d\n", resultado);

    for (int i = 0; i < linhas; i++) {
        free(cidade[i]);
    }
    free(cidade);

    return 0;
}
