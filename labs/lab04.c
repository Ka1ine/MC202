#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
    char name[55];
    int friend[1010];
} Person;
//max_line = 115
int main()
{
    Person *people = NULL;
    int n = 0;

    char linha[115];
    char *s1 = malloc(55);
    char *s2 = malloc(55);
    char *temp = malloc(55);

    while (fgets(linha, 115, stdin) != NULL) {
	//limpa as strings
	s1[0] = '\0';
	s2[0] = '\0';

	temp = strtok(linha, " ");
	//le o primeiro nome
	while (temp != NULL) {
	    if (!strcmp(temp, "conhece"))
		break;
	    if (s1[0] != '\0')
		strcat(s1, " ");
	    strcat(s1, temp);
	    temp = strtok(NULL, " ");
	}

	//pula a palavra conhece
	temp = strtok(NULL, " ");
	//le o segundo nome
	while (temp != NULL) {

	    if (s2[0] != '\0')
		strcat(s2, " ");
	    strcat(s2, temp);
	    temp = strtok(NULL, " ");
	}

	//limpa o /n do segundo nome
	for (int aux = 0; aux < 55; aux++) {
	    if (s2[aux] == '\n') {
		s2[aux] = '\0';
		break;
	    }
	}

	//define os indices das duas pessoas
	int pt1 = -1, pt2 = -1;
	for (int i = 0; i < n; i++) {
	    //verificar se a pessoa ja ta no array
	    if (!strcmp(people[i].name, s1))
		pt1 = i;
	    if (!strcmp(people[i].name, s2))
		pt2 = i;
	}


	//se  a primeira nao tiver, cria
	if (pt1 == -1) {
	    pt1 = n++;
	    people = (Person *) realloc(people, n * sizeof(Person));
	    strcpy(people[pt1].name, s1);
	    memset(people[pt1].friend, 0, sizeof(int) * 1010);
	}
	//se as duas pessoas sao iguais, nao cria denovo
	if (pt2 == -1 && !strcmp(s1, s2))
	    pt2 = pt1;


	//se a segunda pessoa nao foi criada, cria
	if (pt2 == -1) {
	    pt2 = n++;
	    people = (Person *) realloc(people, n * sizeof(Person));
	    strcpy(people[pt2].name, s2);
	    memset(people[pt2].friend, 0, sizeof(int) * 1010);
	}
	//define amizade
	people[pt1].friend[pt2] = 1;
    }

    //conta quantas pessoas conhecem a pessoa i
    int *knows = malloc(sizeof(int) * n);


    for (int i = 0; i < n; i++) {
	//guarda quantas pessoas i conhece
	int kn = 0;
	for (int j = 0; j < n; j++) {
	    kn += people[i].friend[j];

	    //atualiza quem conhece j
	    if (people[i].friend[j]) {
		knows[j]++;
	    }

	}

	//guarda na posicao i
	people[i].friend[i] = kn;

    }


    //uma pessoa e celebridade se todo mundo conhece ela e nao conhece ngm
    for (int i = 0; i < n; i++) {
	if (knows[i] >= n - 1 && !people[i].friend[i]) {
	    printf("%s e' celebridade.\n", people[i].name);
	    return 0;
	}
    }

    //caso contratio printa
    printf("Nao ha' celebridade.\n");

    return 0;

}
