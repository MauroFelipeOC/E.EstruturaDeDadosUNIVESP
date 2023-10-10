#include <stdioh.h>
#include <stdlib.h>

typedef int TIPOCHAVE;
typedef struct{
    TIPOCHAVE chave;
} REGISTRO;

typedef struct aux{
    REGISTRO reg;
    struct aux* prox; 
}ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct{
    PONT topo;
} PILHA;

void inicializarPilha(PILHA* p){
    p->topo = NULL; // Pilha vazia
}

int tamanhoPilha (PILHA* p){    // Para essa funcao, nao ha grande diferenca de custo entre passar um ponteiro para pilha ou passar uma copia da pilha
    PONT end = p->topo;         // Pois PILHA apenas é um ponteiro para o topo
    int tam = 0;
    while (end != NULL)
    {
        tam++;
        end = end->prox;
    }
    return tam;
}

bool estaVazia (PILHA* p){
    if(p->topo == NULL) return true;
    return false;
}

void exibirPilha(PILHA* p){
    PONT end = p->topo;
    printf("Pilha: \" ");
    while (end != NULL)
    {
        printf("%i ", end->reg.chave);
        end = end->prox;
    }    
    printf("\"\n");
}

bool inserirElementoPilha(PILHA* p, REGISTRO reg){  // PUSH
    PONT novo = (PONT) malloc(sizeof(ELEMENTO));
    novo->reg = reg;
    novo->prox = p->topo
    p->topo = novo;
    return true;
}

bool excluirElementoPilha(PILHA* p, REGISTRO* reg){
    if(p->topo == NULL) return false;
    *reg = p->topo->reg;    // reg "retorna" o registro que foi apagado
    PONT apagar = p->topo;
    p->topo = p->topo->prox;
    free(apagar);
    return true;
}

void reinicializarPilha(PILHA* p){
    PONT apagar;
    PONT posicao = p->topo;
    while ( posicao != NULL)
    {
        apagar = posicao;
        posicao = posicao->prox;
        free(apagar);
    }
    p->topo = NULL;
}