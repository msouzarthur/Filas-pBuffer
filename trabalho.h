//Struct dos daos salvos nos nodos
typedef struct 
{
    char nome[40];
    int idade;
} dados;
//Struct dos nodos, contendo dados e nodo seguinte e anterior
typedef struct 
{
    dados info;
    struct TipoFila *pPrevious;
    struct TipoFila *pNext;
} TipoFila;
//Struc da fila, contem os nodos, o primeiro e ultimo, tamanho e auxiliares para as funcoes 
typedef struct
{
    dados *pAgeOrder;
    TipoFila *pAtual, *pSucessor;
    TipoFila *pAux;
    TipoFila *pFirst;
    TipoFila *pLast;
    int i, j, quantidade;
    char auxiliar[30];
} Fila;

int escolhido(void *pBuffer);
void escolha(void *pBuffer);
void Initialize(void *pBuffer);
void Push(void *pBuffer);
void Pop(void *pBuffer);
void PopName(void *pBuffer);
void Print(void *pBuffer);
void MenuPrint(void *pBuffer);
void PrintOrder(void *pBuffer);
void PrintAge(void *pBuffer);
void Menu(void *pBuffer);
void Clear(void *pBuffer);
bool Search(void *pBuffer);
bool Empty(void *pBuffer);