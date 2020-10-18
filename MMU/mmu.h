#define True 1
#define False 0
#define HASH_TAM 65530 // 2^28 / 2^12
#define MEM_FISICA 268435456 // 2^28
#define MEM_VIRTUAL 536870912 // 2^29

typedef int Boolean;
 
typedef struct THash{
    struct HItem **indx;
    int tam, qtd_itm;
}THash;
 
typedef struct HItem{
    int virt_addr;
    int moldura;
    int pagina;
    int fis_addr;
    struct HItem *prox;
}HItem;

Boolean init = True;
int coli_cont = 0;
 
/* Calcula a função de hash */
int hash_func(int addr);
 
/* Cria novo tipo item para ser inserido na hash */
HItem* hash_novo(int addr);

/* Insere novo item na hash */
void hash_insere(THash *H, int novo);
  
/* Busca um item pela sua addr na hash */
HItem* hash_busca(HItem *ini, int addr);
 
/* Remove item na hash */
Boolean hash_remove(THash *H, int addr);
 
/* Inicializa a tabela hash */
void hash_ini(THash *H);
 
/* Imprime a tabela hash */
void hash_imprime(THash *H);

/* Simula um gerenciador de memória virtual */
void mmu(THash *H);