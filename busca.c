#include <stdlib.h>
#include <stdio.h>

int busca_binaria(int tam, int elem, int * vet){
    if (tam <= 0){
        printf("Não tem nada");
        return 0;
    }
    else {
        int meio = (tam - 1) / 2;
        if (elem < vet[meio]){
            return busca_binaria(meio, elem, vet);
        }
        else if (elem > vet[meio]){
            return busca_binaria(tam - 1 - meio, elem, &vet[meio + 1]);
        }
        else{
            printf("%d", vet[meio]);
            return 1;
        }

    }
}

int busca_binaria_index(int tam, int elem, int * vet){
    if (tam <= 0){
        printf("Não tem nada");
        return -1;
    }
    else {
        int meio = (tam - 1) / 2;
        if (elem < vet[meio]){
            return busca_binaria_index(meio, elem, vet);
        }
        else if (elem > vet[meio]){
            int valor = busca_binaria_index(tam - 1 - meio, elem, &vet[meio + 1]);
            if (valor < 0) 
                return -1;
            else 
                printf("%d", meio+1+valor);
                return meio+1+valor;
        }
        else{
            printf("%d", meio);
            return meio;
        }

    }
}

int main(){
    int vet[] = {1, 2, 3, 4, 5, 6, 7};
    int tam = 7;
    int elem = 3;

    busca_binaria_index(tam, elem, vet);

}