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
    
    for(i=0;i<25000;i++){ // insere endereços iniciais aleatorios no hash
        r = rand() % MEM_VIRTUAL;
        hash_insere(H,r);
    }
    printf("Foram inseridos %d items no Hash\n",H->qtd_itm);
}

/* Calcula a pagina de determinado endereço */
int buscaPagina(int addr){
    int pagina = addr/4096;
    return pagina;
}
 
/* Calcula a função de hash */
int hash_func(int addr){
    int indx;
    indx = buscaPagina(addr);
    indx = indx % HASH_TAM; // método da divisão
    return indx;
}
 
/* Cria novo tipo item para ser inserido na hash */
HItem* hash_novo(int addr){
    HItem *novo;
    novo = malloc(sizeof(HItem));
    novo->virt_addr = addr;
    novo->fis_addr = rand() % MEM_FISICA;
    novo->prox = NULL;
    novo->pagina = buscaPagina(addr);
    novo->moldura = buscaPagina(novo->fis_addr);
    return novo;
}

/* Insere novo item na hash */
void hash_insere(THash *H, int novo){
    int idx;
    HItem *aux,*pont;
    idx = hash_func(novo);
    pont = H->indx[idx];
    if(H->indx[idx] == NULL){
        H->indx[idx] = hash_novo(novo);
    }
    else{
        aux = hash_novo(novo);
        while(pont->prox != NULL){
            if(init && pont->virt_addr == aux->virt_addr) return;
            pont = pont->prox;
        }
        pont->prox = aux;
    }
    printf("Inserido endereço %8X na página %7d de memória virtual. Indice de Hash: %5d\n",novo,buscaPagina(novo),idx);
    H->qtd_itm++;
}
  
/* Busca um item pela sua addr na hash */
HItem* hash_busca(HItem *ini, int addr){
    HItem *item = ini;
    if(item == NULL) return item;
    while(True){
        if(item->prox == NULL) return NULL;
        if(item->prox->virt_addr == addr){
            return item;
        }
        item = item->prox;
    }
}

/* Simula um gerenciador de memória virtual */
void mmu(THash *H){
    int CPU_request, idx, i, busca, miss=0, OK=0;
    HItem *addr;
    
    for(i=0; i<100000;i++){ // valor escolhido para a quantidade de requisições da CPU
        CPU_request = rand() % MEM_VIRTUAL;
        idx = hash_func(CPU_request);

        if(H->indx[idx] == NULL) addr = H->indx[idx]; // caso o indice do hash esteja vazio
        else if(H->indx[idx]->virt_addr == CPU_request) addr = H->indx[idx]; // caso primeiro item seja o buscado
        else addr = hash_busca(H->indx[idx],CPU_request); // busca endereço na lista do indice

        if(addr == NULL){ // endreço nao carregado na memoria real
            printf("Page Miss\n");
            miss++;
        }else{ // endereço encontrado
            printf("Endereço Virtual: %10X  Página Virtual: %10d  Endereço Físico: %10X  Moldura Física: %10d\n",addr->virt_addr,addr->pagina,addr->fis_addr,addr->moldura);
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
    scanf("%d",&i); // Scanf serve apenas para pausar o código
    mmu(&hash);   
    return 0;
}