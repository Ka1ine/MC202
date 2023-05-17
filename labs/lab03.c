#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b);

int main()
{

    //le numero de caixa e clientes
    int c, n;

    scanf("%d %d", &c, &n);

    //cria array com o tempo de finalizacao de atendimento pra cada caixa
    int *at = malloc(sizeof(int) * c);
    memset(at, 0, sizeof(int) * c);

    int t, d;

    //guarda quantos clientes esperaram mais de 20min
    int ans = 0;
    for (int i = 0; i < n; i++) {
	scanf("%d %d", &t, &d);

	int mt = 2000, id = 0;
	//pra cada cliente, ele sera atendido pelo caixa que terminar o atendimento primeiro
	//ou seja, aquele com menor tempo de finalizacao
	for (int j = 0; j < c; j++) {
	    if (at[j] < mt) {
		mt = at[j];
		id = j;
	    }
	}

	//o tempo de espera sera o tempo que o caixa termina menos o tempo de entrada na fila
	//ou 0, se o caixa estiver livre assim que o cliente entra na fila
	int te = max(mt - t, 0);
	//atualizo o tempo de finalziacoa do atendimento = tempo que entrou na fila + tempo de espera + tempo de atendimento
	at[id] = t + te + d;

	//se eseperou mais de 20 minutos, atualizo a resposta
	if (te > 20)
	    ans++;
    }

    //retorno a resposta
    printf("%d\n", ans);

    free(at);

    return 0;

}

int max(int a, int b)
{
    return (a > b) ? a : b;
}
