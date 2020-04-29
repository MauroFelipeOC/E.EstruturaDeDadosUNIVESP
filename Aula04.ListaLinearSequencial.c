#include <stdio.h>
#include <stdbool.h>

#define MAX 50

typedef int TIPOCHAVE;
typedef struct{
	TIPOCHAVE chave;
	//	outros campos
}REGISTRO;
typedef struct{
	REGISTRO A[MAX+1];// Para comportar o a buscaSentinela
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

int buscaSentinela (LISTA *l, TIPOCHAVE ch){
	int i = 0;	// Comeca a busca a partir do inicio da lista
	l->A[l->nroElem].chave = ch;	//	O ultimo elemento da lista sera o sentinela
	while(l->A[i].chave !=ch) i++;	// Percorre a lista buscando a chave
	if(i == l->nroElem) return -1;	// Se o elemento procurado for o sentinela, retorna o valor invalido -1
	else return i;
}

bool inserirElemListaOrd (LISTA* l, REGISTRO reg) {
	if(l->nroElem >= MAX) return false;
	int pos = l->nroElem;
	while (pos > 0 && l->A[pos-1].chave > reg.chave){	// Abre espaço na lista para inserir o novo registro
		exibirLista(l);
		l->A[pos] = l->A[pos-1];
		pos--;
	}
	exibirLista(l);
	l->A[pos] = reg;
	l->nroElem++;
}

int buscaBinaria(LISTA *l, TIPOCHAVE ch) {
	int esq, dir, meio;
	esq = 0;
	dir = l->nroElem-1;
	while(esq<=dir){
		meio = ((esq+dir)/2);
		if(l->A[meio].chave == ch) return meio;
		else{
			if(l->A[meio].chave < ch) esq = meio +1;
			else dir = meio - 1;
		}
	}
	return -1;
}

bool excluirElemListaBinaria (TIPOCHAVE ch, LISTA* l){
	int pos, j;
	pos = buscaBinaria(l,ch);
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
	return inserirElemListaOrd(l, reg);
}

void menuExcluir(LISTA* l)
{
	TIPOCHAVE ch;
	printf("Digite a chave a ser excluida:\n");
	scanf("%i", &ch);
	if(excluirElemListaBinaria(ch, l))
		printf("\nChave %i excluida\n", ch);
	else printf("\nElemento nao encontrado\n");
}

void menuBusca(LISTA* l)
{
	int i;
	TIPOCHAVE ch;
	printf("Digite a chave a ser buscada:\n");
	scanf("%i", &ch);
	i = buscaBinaria(l, ch);
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
				printf("Opcao invalida\n");
				break;
		}
	}
	return (0);
}