#ifndef filas
#define filas

struct NO{
  int num;
  struct NO *esquerdo;
  struct NO *direito;
};

typedef struct NO* ArvBin;

typedef struct BSTNode_struct BSTNode;

struct BSTNode_struct {
    BSTNode *ptLeft, *ptRight;

    //length of the edge from this node to its children
    int edge_length;

    int height;

    int element;

    //-1=I am left, 0=I am root, 1=right
    int parent_dir;

    //max supported unit32 in dec, 10 digits max
    char label[11];
};

ArvBin* cria_ArvBin();

void libera_ArvBin(ArvBin *raiz);

void libera_NO(struct NO* no);

int estaVazia_ArvBin(ArvBin* raiz);

int altura_ArvBin(ArvBin *raiz);

int n_NOS(ArvBin *raiz);

void preOrdem_ArvBin(ArvBin *raiz);

void emOrdem_ArvBin(ArvBin *raiz);

void posOrdem_ArvBin(ArvBin *raiz);

int  insere_ArvBin(ArvBin *raiz, int valor);

int remove_ArvBin(ArvBin *raiz, int valor);

struct NO* remove_atual(struct NO *atual);

int consulta_ArvBin(ArvBin *raiz, int valor);

ArvBin* loadTreeFromFile(char *name);

void printElements(ArvBin *t);

BSTNode *build_ascii_tree_recursive(ArvBin *t);

BSTNode *build_ascii_tree(ArvBin *t);

void free_ascii_tree(BSTNode *node);

void compute_lprofile(BSTNode *node, int x, int y);

void compute_rprofile(BSTNode *node, int x, int y);

void filledge(BSTNode *node);

void printLevel(BSTNode *node, int x, int level);

int MIN(int X, int Y);

int MAX(int X, int Y);

#endif
/* Chamada das funções

ArvBin* raiz = cria_ArvBin();
libera_ArvBin(raiz);
int x = estaVazia_ArvBin(raiz);
int x = n_NOS(raiz);
preOrdem_ArvBin(raiz);
emOrdem_ArvBin(raiz);
posOrdem_ArvBin(raiz);
int x = insere_ArvBin(raiz, valor);
int x = remove_ArvBin(raiz, valor);
int x = consulta_ArvBin(raiz, valor);
*/
