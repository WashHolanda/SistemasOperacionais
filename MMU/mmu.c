#include <stdio.h>
#include <stdlib.h>
#include "mmu.h"

 
/* Inicializa a tabela hash */
void hash_ini(THash *H){
    int i,r;
    H->indx = malloc(HASH_TAM*sizeof(HItem*)); // cria os indices de hash com base em i
    H->tam = HASH_TAM;
    H->qtd_itm = 0;
    for(i=0;i<HASH_TAM;i++) // inicializa todos os indices como nulo
        H->indx[i] = NULL;

    for(i=0;i<rand()%100000;i++){ // insere endereços iniciais aleatorios no hash
        r = rand() % MEM_FISICA;
        hash_insere(H,r);
    }
    printf("Foram inseridos %d items no Hash\n",H->qtd_itm);
}
 
/* Calcula a função de hash */
int hash_func(int chave){
    int indx;
    indx = chave % HASH_TAM; // método da divisão
    if(indx<0) indx *= -1;
    return indx;
}
 
/* Cria novo tipo item para ser inserido na hash */
HItem* hash_novo(int chave){
    HItem *novo;
    novo = malloc(sizeof(HItem));
    novo->chave = chave;
    novo->prox = NULL;
    novo->modificado = False;
    return novo;
}

/* Insere novo item na hash */
void hash_insere(THash *H, int novo){
    int idx,coli=1;
    HItem *aux,*pont;
    H->qtd_itm++;
    idx = hash_func(novo);
    pont = H->indx[idx];
    if(H->indx[idx] == NULL){
        H->indx[idx] = hash_novo(novo);
    }
    else{
        aux = hash_novo(novo);
        while(pont->prox != NULL){
            if(init && pont->chave == aux->chave) return;

            if(coli == MAX_COLI){ // caso supere o nivel esperado de colisões, remove o item mais antigo
                hash_remove(H,H->indx[idx]->chave);
            }
            pont = pont->prox;
            coli++;
        }
        pont->prox = aux;
    }
    printf("Inserido endereço 0x%X na posição 0x%X de memória virtual\n",novo,idx);
}
  
/* Busca um item pela sua chave na hash */
HItem* hash_busca(HItem *ini, int chave){
    HItem *item = ini;
    if(item == NULL) return item;
    while(True){
        if(item->prox == NULL) return NULL;
        if(item->prox->chave == chave) return item;
        item = item->prox;
    }
}
 
/* Remove item na hash */
Boolean hash_remove(THash *H, int chave){
    HItem *item;
    int idx = hash_func(chave);
    // confere se a lista está vazia
    if(H->indx[idx] == NULL) return False;
    // confere se item buscado é o primeiro da lista
    if(H->indx[idx]->chave == chave){
        H->indx[idx] = H->indx[idx]->prox;
        return True;
    }
    // procura iten dentro da lista
    item = hash_busca(H->indx[idx],chave);
    if(item != NULL){
        // remove item
        item->prox = item->prox->prox;
        return True;
    }
    else{
        hash_insere(H,chave);
        return False;
    }
}

/* Imprime a tabela hash */
void hash_imprime(THash *H){
    int i = 0;
    HItem *aux = H->indx[i];
    // primeiro item
    printf("[0]: ");
    while(True){
        // confere se está no final da lista
        if(aux == NULL){
            i++;
            aux = H->indx[i];
            if(i == H->tam){
                printf("\n");
                return;
            }
            // imprime cabeçalho
            printf("\n" "[%d]: ", i);
        }else{
            // imprime item
            printf("%d ",aux->chave);
            aux = aux->prox;
        }
    }
    printf("\n");
}

/* Simula um gerenciador de memória virtual */
void mmu(THash *H){
    int CPU_request, idx, i, busca, miss=0, OK=0;
    HItem *addr;
    busca = rand()%10000;
    
    for(i=0; i<busca;i++){
        CPU_request = rand() % MEM_FISICA;
        idx = hash_func(CPU_request);

        if(H->indx[idx] == NULL) addr = H->indx[idx];
        else if(H->indx[idx]->chave == CPU_request) addr = H->indx[idx];
        else addr = hash_busca(H->indx[idx],CPU_request);

        if(addr == NULL){
            printf("Page Miss: 0x%X\n",CPU_request);
            miss++;
        }else{
            printf("Endereço: 0x%X  Indice: 0x%X  Modificado: ",addr->chave,idx);
            if(addr->modificado) printf("True\n");
            else printf("False\n");
            OK++;
        }
    }

    printf("Páginas não encontradas: %d\nPáginas encontradas: %d\n",miss,OK);
}
 
/* Função principal */
int main(){
    THash hash;
    int i;
    hash_ini(&hash);
    //hash_imprime(&hash);
    scanf("%d",&i);
    mmu(&hash);   
    return 0;
}