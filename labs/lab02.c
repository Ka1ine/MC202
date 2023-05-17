#include <stdio.h>

int main()
{
    int ryu = 0;
    int key = 0;
    int golpe = 0;
    int golpe_ryu = 0;
    int golpe_key = 0;

    scanf("%d", &ryu);
    scanf("%d", &key);

    int i = 0;

    while (i == 0) {
	scanf("%d", &golpe);
	if (golpe > 0) {
	    key -= golpe;
	    printf("RYU APLICOU UM GOLPE: %d\n", golpe);

	    printf("HP RYU = %d\n", ryu);

	    if (key <= 0) {
		printf("HP KEN = 0\n");
	    } else {
		printf("HP KEN = %d\n", key);
	    }

	    golpe_ryu += 1;
	    if (key <= 0) {
		printf("LUTADOR VENCEDOR: RYU\n");
		printf("GOLPES RYU = %d\n", golpe_ryu);
		printf("GOLPES KEN = %d\n", golpe_key);
		i = 1;
	    }

	} else {
	    ryu -= golpe * -1;
	    printf("KEN APLICOU UM GOLPE: %d\n", golpe * -1);

	    if (ryu <= 0) {
		printf("HP RYU = 0\n");
	    } else {
		printf("HP RYU = %d\n", ryu);
	    }

	    printf("HP KEN = %d\n", key);
	    golpe_key += 1;

	    if (ryu <= 0) {
		printf("LUTADOR VENCEDOR: KEN\n");
		printf("GOLPES RYU = %d\n", golpe_ryu);
		printf("GOLPES KEN = %d\n", golpe_key);
		i = 1;
	    }
	}



    }


    return 0;
}
