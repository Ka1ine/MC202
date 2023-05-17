// Nome: Yasmin Kaline de Carvalho Silva
// RA: 241066

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct music
{
    char nome[100];
    struct music* next;
} music;

typedef struct playlist
{
    music* head;
    music* cursor;
    music* indicador;
} playlist;

// Insere depois do indicador
void inserir(playlist* q, char* novo_nome)
{
    music* musica = (music*)malloc(sizeof(music));
    strcpy(musica->nome, novo_nome);
    musica->next = NULL;

    /*Se estiver vazia*/
    if (q->head == NULL) {
        q->head = musica;
        q->indicador = musica;
    }
    else {
        musica->next = q->indicador->next;
        q->indicador->next = musica;
    }
}

// Remove pelo nome da música
void remover(playlist* q, char* musica)
{   
    if (q->head != NULL){
    
    
        music* p = q->head;
        if (!strcmp(p->nome, musica))
        {
            if (q->indicador == p)
            {
                q->indicador = q->indicador->next;
            }

            music* apagar = p;
            q->head = q->head->next;
            free(apagar);
            return;
        }

        while (p->next != NULL && strcmp(p->next->nome, musica))
        {
            p = p->next;
        }
        if (q->indicador == p->next)
        {
            q->indicador = p;
        }
        if(p->next != NULL){
            if(p->next->next != NULL){
                music* apagar = p->next;
                p->next = p->next->next;
                free(apagar);
            
            }else{
                music* apagar = p->next;
                p->next = NULL;
                free(apagar);
            }
        }
    }
}

// Printa a musica depois indicador e passa o indicador para a proxima musica
void tocar_musica(playlist* q)
{
    if (q->head != NULL)
    {
        printf("%s\n", q->indicador->nome);
        if (q->indicador->next != NULL)
        {
            q->indicador = q->indicador->next;
        }
        return;
    }
    printf("\n");

}

playlist* comecar() {
    playlist* q = (playlist*)malloc(sizeof(playlist));
    q->cursor = NULL;
    q->head = NULL;
    q->indicador = NULL;
    return q;
}

// Printa todas as musicas depois do indicador
void tocar_final(playlist* q) {
    music* p = q->indicador;
    printf("%s\n", p->nome);
    while (p->next != NULL) {
        printf("%s\n", p->next->nome);
        p = p->next;
    }
    q->indicador = p;
    if (q->head == NULL){
        printf("\n");
    }
}

// Volta o indicador para a musica anterior
void voltar_musica(playlist* q) {
    if (q->indicador != q->head) {
        music* p = q->head;
        while (p->next != q->indicador) {
            p = p->next;
        }
        q->indicador = p;
    }
}

void apagar_music(playlist* q) {
    music* musica = q->head;
    while (musica != NULL) {
        music* x = musica;
        musica = musica->next;
        free(x);
    }
    q->head = NULL;
    q->indicador = NULL;
    q->cursor = NULL;
}

void apagar_playlist(playlist* q) {
    apagar_music(q);
    free(q);
}

// Inverte todas as musicas
void inverte_playlist(playlist* q) {
    music* anterior = NULL;
    music* atual = q->head;
    music* proximo = NULL;

    while (atual != NULL) {
        proximo = atual->next;
        atual->next = anterior;
        anterior = atual;
        atual = proximo;
    }

    q->head = anterior;
}

void print_playlist(playlist *q) {
    printf("-----------\n");
    music *p = q->head;
    while (p != NULL) {
        if (p == q->indicador) {
            printf("(cursor)");
        }
        printf("%s\n", p->nome);
        p = p->next;
    }
    printf("---------------\n");
}

int main() {
    playlist* q = comecar();

    int quant;
    scanf(" %d", &quant);

    while (quant != 0) {
        for (int i = 0; i < quant; i++) {
            char ordem[8];
            scanf(" %s", ordem);
            if (!strcmp(ordem, "toca"))
                tocar_musica(q);
            if (!strcmp(ordem, "volta"))
                voltar_musica(q);
            if (!strcmp(ordem, "final"))
                tocar_final(q);
            if (!strcmp(ordem, "inverte"))
                inverte_playlist(q);
            if (!strcmp(ordem, "insere")) {
                char palavra[100];
                scanf(" %[^\n]", palavra);
                inserir(q, palavra);
            }
            if (!strcmp(ordem, "remove")) {
                char palavra[100];
                scanf(" %[^\n]", palavra);
                remover(q, palavra);
            }
        }

        apagar_music(q);
        scanf(" %d", &quant);
        if (quant == 0) {
            break;
        }
        printf("\n");

    }
    apagar_playlist(q);
}
