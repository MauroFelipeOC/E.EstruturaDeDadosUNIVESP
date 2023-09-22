# Listas

## Lista Linear

- Listá terá
  - REGISTRO A[MAX];
  - int nroElem
- Cada elemento é precedido por um elemento e sucedido por outro
- A ordem lógica é a mesma ordem física (na memória)
- Para inserir um elemento u ordenadamente numa posição i
  - Verifica se a lista está vaga e se a posição é válida
  - Abre espaço na lista (começa do último elemento)
  - Põe em [i]
```C
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
```
## Lista Ligada Estática

- Cada elemento indica quem é seu sucessor
- Quando for excluir um elemento, não que mexer em todos os outros
- l->inicio e l->A[MAX-1].prox. começam como =INVALIDO
- l->A[MAX-1].prox (prox do último elemento) marca o fim da lista
- O ->prox do último elemento será =INVALIDO
```c
#define MAX 50
#define INVALIDO -1
typedef int TIPOCHAVE;
typedef struct{
	TIPOCHAVE chave;
	//	outros campos
}REGISTRO;
typedef struct{
	REGISTRO reg;
	int prox;
}ELEMENTO;
typedef struct{
	ELEMENTO A[MAX+1];// Para comportar o a buscaSentinela
	int inicio;
	int dispo;
}LISTA;
void inicializarLista (LISTA* l){
	int i;
	for (i=0; i<MAX-1; i++)	//	Ligando os elementos da lista
		l->A[i].prox = i+1;	// prox de cada elemento aponta para o seguinte
	l->A[MAX-1].prox = INVALIDO;
	l->inicio=INVALIDO;
	l->dispo=0;
}
int obterNo(LISTA *l)	//	Atualiza posicao que ficara disponivel depois de fazer uma insercao
{
	int resultado = l->dispo;
	if (l->dispo != INVALIDO)
	{
		l->dispo = l->A[l->dispo].prox;
	}
	return resultado;
}
bool inserirElemListaOrd(LISTA* l, REGISTRO reg){
	if (l->dispo == INVALIDO) return false;	//	Lista cheia
	int ant = INVALIDO;
	int i = l->inicio;
	TIPOCHAVE ch = reg.chave;
	while ((i != INVALIDO) && (l->A[i].reg.chave < ch))	//	Se a lista nao estiver vazia
	{
		ant = i;
		i = l->A[i].prox;
	}
	if (i != INVALIDO && l->A[i].reg.chave==ch) return false; // Se está repetindo, retorna false
	i = obterNo(l);	
	l->A[i].reg = reg;	// Coloca na posicao disponivel
	if (ant == INVALIDO){	//	Se estiver inserindo no começo
		l->A[i].prox = l->inicio;
		l->inicio = i;
	}	else{
		l->A[i].prox = l->A[ant].prox;
		l->A[ant].prox = i;
	}
	return true;
}
void devolverNo (LISTA* l, int j){
	l->A[j].prox = l->dispo;
	l->dispo = j;
}
bool excluirElemLista(LISTA* l, TIPOCHAVE ch){
	int ant = INVALIDO;
	int i = l->inicio;
	while ((i != INVALIDO) && (l->A[i].reg.chave < ch)) // OBS.: a lista esta ordenada
	{
		ant = i;
		i = l->A[i].prox;
	}
	if (i == INVALIDO || l->A[i].reg.chave != ch) return false;
	if (ant == INVALIDO) l->inicio = l->A[i].prox;
	else l->A[ant].prox = l->A[i].prox;
	devolverNo(l, i);
	return true;	
}
void reinicializarLista(LISTA* l){
	inicializarLista(l);
}
```
- O ultimo elemento inserido e/ou o último do A[] sempre será =INVALIDO

## Lista Ligada Dinâmica

- Lista começa com início apontando para nada (NULL)

```C
typedef int TIPOCHAVE;
typedef struct{
    TIPOCHAVE chave;
    //outros campos
}REGISTRO;
typedef struct aux{
    REGISTRO reg;
    struct aux* prox; 
} ELEMENTO;
typedef ELEMENTO* PONT; //  PONT: ponteiro para uma estrutura do tipo ELEMENTO
typedef struct{
    PONT inicio;
} LISTA;
void inicializarLista (LISTA* l){
    l->inicio = NULL;   // Nao aponta para ninguem
}
```

## Lista Circular c/ Nó Cabeça

- A lista começa por um ponteiro - o cabeça - que a ponta para o primeiro elemento
- O último elemento aponta para o primeiro

```c
typedef int bool;
typedef int TIPOCHAVE;
typedef struct 
{
    TIPOCHAVE chave;
    //outros campos
}REGISTRO;
typedef struct tempRegistro{
    REGISTRO reg;
    struct tempRegistro* prox; 
} ELEMENTO;
typedef ELEMENTO* PONT; //  PONT: ponteiro para uma estrutura do tipo ELEMENTO
typedef struct{
    PONT cabeca;
} LISTA;
void incializarLista (LISTA* l){
    l->cabeca = (PONT) malloc(sizeof(ELEMENTO));
    l->cabeca->prox = l->cabeca;
}
PONT buscaSequencialExc(LISTA* l, TIPOCHAVE ch, PONT* ant){ // Retorna o PONT do valor buscado, e o PONT do anterior, usando *ant
    *ant = l->cabeca;
    PONT atual = l->cabeca->prox;   
    l->cabeca->reg.chave = ch;
    while (atual->reg.chave < ch)   // atual percorre a lista
    {
        *ant = atual;
        atual = atual->prox;
    }
    if((atual != l->cabeca) && (atual->reg.chave == ch)) return atual;  // Se não houver chegado no final do no (l->cabeca) e tiver encontrado
    return NULL;                    // Se nao  houver encontrado, retorna NULL
}
bool inserirElementoListaOrd(LISTA* l, REGISTRO reg){
    PONT ant, i;
    i = buscaSequencialExc(l, reg.chave, &ant);
    if (i != NULL) return false;    // Foi encontrado elemento com o mesmo valor
    i = (PONT) malloc(sizeof(ELEMENTO));
    i->reg = reg;
    i->prox = ant->prox;
    ant->prox = i;
    return true;
}
bool excluirElemLista (LISTA* l, TIPOCHAVE ch){
    PONT ant, i;
    i = buscaSequencialExc(l, ch, &ant);
    if(i == NULL) return false;
    else ant->prox = i->prox;
    free(i); // Libera a memoria do elemento i
    return true;
}
void reinicializarLista (LISTA* l){
    PONT end = l->cabeca->prox;
    while (end != l->cabeca)    {
        PONT apagar = end;
        end = end->prox;
        free(apagar);
    }
    l->cabeca = l->cabeca;
}
```

## Busca Binária

- Usada em listas ordenadas

```c
int buscaBinaria(LISTA *l, TIPOCHAVE ch) {
	int esq, dir, meio;
	esq = 0;
	dir = l->nroElem-1; // Obs: tem o sentinela no fim do array
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
```
