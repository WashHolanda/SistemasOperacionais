#define AMAR "\e[0;33m"  // Texto normal amarelo
#define AZ "\e[0;34m"    // Texto normal azul
#define RESET "\e[0m"    // Texto padrão
#define True 1
#define False 0
#define HASH_TAM 65536 // 2^28 / 2^12
#define MEM_FISICA 268435456 // 2^28
#define MAX_COLI 2

typedef int Boolean;
 
typedef struct THash{
    struct HItem **indx;
    int tam, qtd_itm;
}THash;
 
typedef struct HItem{
    int chave;
    Boolean modificado;
    struct HItem *prox;
}HItem;

Boolean init = True;
int coli_cont = 0;
 
/* Calcula a função de hash */
int hash_func(int chave);
 
/* Cria novo tipo item para ser inserido na hash */
HItem* hash_novo(int chave);

/* Insere novo item na hash */
void hash_insere(THash *H, int novo);
  
/* Busca um item pela sua chave na hash */
HItem* hash_busca(HItem *ini, int chave);
 
/* Remove item na hash */
Boolean hash_remove(THash *H, int chave);
 
/* Inicializa a tabela hash */
void hash_ini(THash *H);
 
/* Imprime a tabela hash */
void hash_imprime(THash *H);

/* Simula um gerenciador de memória virtual */
void mmu(THash *H);