#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int linha;
    int coluna;
    int distancia;
} Posicao;

Posicao criar_posicao(int linha, int coluna, int distancia) {
    Posicao p = {linha, coluna, distancia};
    return p;
}

int menor_caminho(int linhas, int colunas, int **cidade) {
    int frente = 0;
    int tras = 0;
    int menor_distancia = -1;

    int direcoes[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    bool **visitado = calloc(linhas, sizeof(bool *));
    Posicao *fila = malloc(linhas * colunas * sizeof(Posicao));

    for (int i = 0; i < linhas; i++) {
        visitado[i] = calloc(colunas, sizeof(bool));
        for (int j = 0; j < colunas; j++) {
            if (cidade[i][j] == 3) {
                fila[tras++] = criar_posicao(i, j, 0);
                visitado[i][j] = true;
            }
        }
    }

    while (frente < tras) {
        Posicao p = fila[frente++];
        int linha = p.linha;
        int coluna = p.coluna;
        int distancia = p.distancia;

        if (cidade[linha][coluna] == 0) {
            if (menor_distancia == -1 || distancia < menor_distancia) {
                menor_distancia = distancia;
            }
        }

        for (int i = 0; i < 4; i++) {
            int novaLinha = linha + direcoes[i][0];
            int novaColuna = coluna + direcoes[i][1];

            if (novaLinha >= 0 && novaLinha < linhas && novaColuna >= 0 && novaColuna < colunas && !visitado[novaLinha][novaColuna] && cidade[novaLinha][novaColuna] != 2) {
                fila[tras++] = criar_posicao(novaLinha, novaColuna, distancia + 1);
                visitado[novaLinha][novaColuna] = true;
            }
        }
    }

    for (int i = 0; i < linhas; i++) {
        free(visitado[i]);
    }
    free(visitado);
    free(fila);

    return menor_distancia;
}

int main() {
    int linhas, colunas;
    scanf("%d %d", &linhas, &colunas);

    int **cidade = malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        cidade[i] = malloc(colunas * sizeof(int));
        for (int j = 0; j < colunas; j++) {
            scanf("%d", &cidade[i][j]);
        }
    }

    int resultado = menor_caminho(linhas, colunas, cidade);

    printf("%d\n", resultado);

    for (int i = 0; i < linhas; i++) {
        free(cidade[i]);
    }
    free(cidade);

    return 0;
}
