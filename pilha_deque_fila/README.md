# Pilhas
- Na pilha, os elementos são inseridos no topo; e devem ser retirados somente pelo topo
- Dessa forma, essa estrutura de dados segue a lógica LIFO (last in, first out) ou UEPS (último a entrar, primeiro a sair)
- A pilha possui diversas aplicações na computação. Por exemplo, a pilha é bastante usada no gerenciamento de chamada de funções. Quando uma função é chamada, seu contexto (incluindo variáveis locais e endereço de retorno) é empilhado, e quando ter. Quando a função retorna, seu contexto é desempilhado.

```c
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
```
- Notas:
    - `if (p->topo1 + 1 == p->topo2) return false;` : retorna false se Pilha estiver cheia