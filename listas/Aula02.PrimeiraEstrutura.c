#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int peso;	//	Peso em kg
	int altura;
}PesoAltura;

int main()
{
	PesoAltura *pessoa1 = (PesoAltura*) malloc(sizeof(PesoAltura));
	pessoa1->peso = 65;
	pessoa1->altura = 175;
	printf("Peso: %i, Altura %i. ", pessoa1->peso, pessoa1->altura);
	return 0;
}