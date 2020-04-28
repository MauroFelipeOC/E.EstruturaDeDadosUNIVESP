#include <stdio.h>
#include <stdbool.h>

#define MAX 50

typedef int TIPOCHAVE;
typedef struct{
	TIPOCHAVE chave;
	//	outros campos
}REGISTRO;
typedef struct{
	REGISTRO A[MAX];
	int nroElem;
}LISTA;

void inicializarLista (LISTA* l){
	l->nroElem = 0;	//	Sem nenhum elemnto
}

int tamanho (LISTA* l){
	return l->nroElem;
}

void exibirLista(LISTA* l){
	int i;
	printf("Lista: \" ");
	for(i=0; i < l->nroElem; i++)
		printf("%i ", l->A[i].chave);
	printf("\"\n");
}

int buscaSequencial (LISTA* l, TIPOCHAVE ch){
	int i = 0;
	while(i < l->nroElem){
		if(ch == l->A[i].chave) return i;
			else i++;
	}
	return -1;
}

bool inserirElemLista (LISTA *l, REGISTRO reg, int i){	// i: posicao em que o elemento sera inserido na lista
	int j;
	if((l->nroElem == MAX) || (i<0) || (i > l->nroElem))	// Se a lista estiver cheia ou i maior que o nroElem
		return false;
	for (j = l->nroElem; j > i; j--)	// Abre espaco na lista para inserir na posição i
	{
		l->A[j] = l->A[j-1];			// Comeca do ultimo elemento da lista e vai ate posicao seguinte de i
	}
	l->A[i] = reg;
	l->nroElem++;
	return true;
}

bool excluirElemLista (TIPOCHAVE ch, LISTA* l){
	int pos, j;
	pos = buscaSequencial(l,ch);
	if(pos == -1) return false;
	for(j = pos; j < l->nroElem-1; j++)
		l->A[j] = l->A[j+1];
	l->nroElem--;
	return true;
}

int exibeMenu(void){
	int i;
	printf("Lista Linear Sequencial\n");
	printf("1. Incluir\n");
	printf("2. Excluir \n");
	printf("3. Exibir \n");
	printf("4. Buscar\n");
	printf("Selecione a opcao desejada: ");
	scanf("%i", &i);
	printf("\n");
	return i;
}

bool menuInserir(LISTA* l)
{
	REGISTRO reg;
	int i;
	printf("Digite o valor a ser inserido:\n");
	scanf("%i", &reg.chave);
	printf("\nDigite a posicao em que sera inserido\n");
	scanf("%i", &i);
	return inserirElemLista(l, reg, i);
}

void menuExcluir(LISTA* l)
{
	TIPOCHAVE ch;
	printf("Digite a chave a ser excluida:\n");
	scanf("%i", &ch);
	if(excluirElemLista(ch, l))
		printf("Chave %i excluida\n", ch);
}

void menuBusca(LISTA* l)
{
	int i;
	TIPOCHAVE ch;
	printf("Digite a chave a ser buscada:\n");
	scanf("%i", &ch);
	i = buscaSequencial(l, ch);
	if(i != -1)
		printf("Chave %i na posicao [%i]\n", ch, i);
	else
		printf("Chave nao encontrada\n");
}

int main(){
	LISTA pessoas;
	inicializarLista(&pessoas);
	REGISTRO teste = {10};
	while(1){	
		switch(exibeMenu())
		{
			case 1:{
//				inserirElemento(&pessoas, teste);
				menuInserir(&pessoas);
				break;
			}
			case 2:{
				menuExcluir(&pessoas);
				break;
			}
			case 3:{
				exibirLista(&pessoas);
				break;
			}
			case 4:
				menuBusca(&pessoas);
				break;
			default:
				printf("Opcao invalida");
				break;
		}
	}
	return (0);
}