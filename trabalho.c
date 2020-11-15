#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "trabalho.h"

void Menu(void *pBuffer)
{
    //exibe o menu e chama função conforme escolha do usuário
    while (1)
    {
        printf("| 0 - Incluir pessoa\n");
        printf("| 1 - Apagar primeiro\n");
        printf("| 2 - Apagar por nome\n");
        printf("| 3 - Buscar pessoa\n");
        printf("| 4 - Listar pessoas\n");
        printf("| 5 - Sair\n");
        escolha(pBuffer);
        switch (escolhido(pBuffer))
        {
        case 0:
            printf("| Adicionar\n");
            Push(pBuffer);
            break;
        case 1:
            printf("| Remover primeiro\n");
            Pop(pBuffer);
            break;
        case 2:
            printf("| Remover nome\n");
            PopName(pBuffer);
            break;
        case 3:
            printf("| Buscar Pessoa\n");
            if (Search(pBuffer))
                printf("| Nome encontrado\n");
            else
                printf("| Nome nao encontrado\n");
            break;
        case 4:
            printf("| Imprimir\n");
            MenuPrint(pBuffer);
            break;
        case 5:
            printf("| Saindo...\n");
            Clear(pBuffer);
            return 0;
            break;
        default:
            return 0;
            break;
        }
    }
    return 0;
}
int escolhido(void *pBuffer)
{
    //Retorna a escolha feita anteriormente
    Fila *pFila;
    pFila = pBuffer;
    return pFila->i;
}
void escolha(void *pBuffer)
{
    //Capta a escolha do usuário
    //Salva ela na fila
    Fila *pFila;
    pFila = pBuffer;
    scanf("%d", &pFila->i);
}
void Clear(void *pBuffer)
{
    //Funcao de limpeza
    Fila *pFila;
    pFila = pBuffer;
    while(pFila->pFirst!=NULL)
    {
        Pop(pBuffer);
    }
    free(pFila);
}
void Initialize(void *pBuffer)
{
    //Inicializa a fila
    //Aponta o primeiro e ultimo pra null
    //Quantidade é zero
    Fila *pFila;
    pFila = pBuffer;
    pFila->quantidade = 0;
    pFila->pFirst = NULL;
    pFila->pLast = NULL;
    return;
}
void Push(void *pBuffer)
{
    Fila *pFila;
    pFila = pBuffer;
    pFila->pAux = (TipoFila *)malloc(sizeof(TipoFila));
    if (!pFila->pAux)
    {
        printf("ERRO MEMORIA PUSH\n");
        return;
    }
    printf("Digite o nome para adicionar: ");
    getchar();
    fgets(pFila->pAux->info.nome, 30, stdin);
    printf("Digite a idade: ");
    scanf("%d", &pFila->pAux->info.idade);
    if (pFila->pLast == NULL) //nao ha cadastro
    {
        //Seguinte e antecessor do nome eh nulo
        pFila->pAux->pNext	= NULL;
        pFila->pAux->pPrevious = NULL;
        //Primeiro e ultimo termo eh ele
        pFila->pFirst = pFila->pAux;
        pFila->pLast = pFila->pAux;
    }
    else //tem cadastrado
    {
        //Seguinte eh nulo, antecessor eh o ultimo da fila
        pFila->pAux->pNext = NULL;
        //Seguinte do ultimo se torna ele
        pFila->pLast->pNext = pFila->pAux;
        pFila->pAux->pPrevious = pFila->pLast;
        //Assume posicao de ultimo
        pFila->pLast = pFila->pAux;
    }
    pFila->quantidade++;
    printf("| Nomes salvos: %d\n", pFila->quantidade);
}
void Pop(void *pBuffer)
{
    if (!Empty(pBuffer))
    {
        printf("| Removendo...\n");
        Fila *pFila;
        pFila = pBuffer;
        //salvo o endereço do primeiro termo
        pFila->pAux = pFila->pFirst;
        //Mudo o então primeiro termo para o seguinte do primeiro termo (2º termo)
        pFila->pFirst = pFila->pAux->pNext;
        //Aponto o anterior do novo primeiro termo como nulo
        pFila->pAux->pPrevious = NULL;
        free(pFila->pAux);
        pFila->quantidade--;
    }
    else
        printf("| Lista vazia\n");
}
void PopName(void *pBuffer)
{
    //Acha o nome
    //Posiciona ele no começo
    //Chama o Pop
    Fila *pFila;
    pFila = pBuffer;
    if (!Empty(pBuffer))
    {
        if (Search(pBuffer))
        {
            printf("| Nome localizado\n");
            printf("| Excluindo...\n");
            //Atual recebe o primeiro da fila
            pFila->pAtual = pFila->pFirst;
            if (strcmp(pFila->pAtual->info.nome, pFila->auxiliar) == 0)
                Pop(pBuffer);
            else
            {
                while (strcmp(pFila->pAtual->info.nome, pFila->auxiliar) != 0)
                {
                    //Pesquisa o nome
                    //pAux eh o antecessor ao nome
                    //pAtual eh o nome
                    //pSucessor eh o proximo do nome
                    pFila->pAux = pFila->pAtual;
                    pFila->pAtual = pFila->pAtual->pNext;
                    pFila->pSucessor = pFila->pAtual->pNext;
                }
                if (pFila->pAtual->pNext == NULL) //Caso nome seja o ultimo
                {
                    //Ultimo da fila eh o anterior ao nome
                    pFila->pLast = pFila->pAtual->pPrevious;
                    //Ultimo da fila nao tem sucessor
                    pFila->pLast->pNext = NULL;
                    //Apaga o nome
                    pFila->pAtual->pNext = pFila->pFirst;
                    pFila->pFirst->pPrevious = pFila->pAtual;
                    pFila->pFirst = pFila->pAtual;
                    Pop(pBuffer);
                }
                else //Caso nao seja o ultimo
                {
                    //Antecessor do nome aponta pro sucessor do nome
                    pFila->pAux->pNext = pFila->pAtual->pNext;
                    //Sucessor do nome aponta pro antecessor do nome
                    pFila->pSucessor->pPrevious = pFila->pAux;
                    //Apaga o nome
                    pFila->pAtual->pNext = pFila->pFirst;
                    pFila->pFirst->pPrevious = pFila->pAtual;
                    pFila->pFirst = pFila->pAtual;
                    Pop(pBuffer);
                }
            }
            printf("| Nome excluido\n");
        }
        else
        {
            printf("| Nome nao localizado\n");
            printf("| Falha ao excluir\n");
        }
    }
    else
        printf("| Lista vazia\n");
}
void PrintOrder(void *pBuffer)
{
    Fila *pFila;
    pFila = pBuffer;
    pFila->i = 0;
    pFila->pAux = pFila->pFirst;        //Auxiliar recebe o primeiro nome
    printf("| Tamanho da lista: %d\n", pFila->quantidade);
    if (!Empty(pBuffer))
    {
        do
        {
            //Exibe a posicao, idade e nome
            printf("%d - ", pFila->i);
            printf("Idade: %d ano(s), ", pFila->pAux->info.idade);
            printf("Nome: %s", pFila->pAux->info.nome);
            //Auxiliar recebe o seguinte termo
            pFila->pAux = pFila->pAux->pNext;
            //Incrementa um contador pra controle
            pFila->i++;
        } while (pFila->i < pFila->quantidade);
    }
    else
        printf("| Lista vazia\n");
}
void PrintAge(void *pBuffer)
{
    if (!Empty(pBuffer))
    {
        /*
        //Bubble sort pra ordenar de idade menor à maior
        Fila *pFila;
        TipoFila *pAnterior, *pAtual, *pAux;
        pFila = pBuffer;
        for (pAnterior = pFila->pFirst; pAnterior != NULL; pAnterior = pAnterior->pNext)
        {
            for (pAtual = pAnterior->pNext; pAtual != NULL; pAtual = pAtual->pNext)
            {
                if (pAnterior->info.idade > pAtual->info.idade)
                {
                    pAux->info = pAnterior->info;
                    pAnterior->info = pAtual->info;
                    pAtual->info = pAux->info;
                }
            }
        }
        pFila->i = 0;
        pAux = pFila->pFirst;
        do
        {
            //Exibe a posicao, idade e nome
            printf("%d - ", pFila->i);
            printf("Idade: %d ano(s), ", pAux->info.idade);
            printf("Nome: %s", pAux->info.nome);
            //Auxiliar recebe o seguinte termo
            pAux = pAux->pNext;
            //Incrementa um contador pra controle
            pFila->i++;
        } while (pFila->i < pFila->quantidade);
        */
    }
    else
        printf("| Lista vazia\n");
}
void MenuPrint(void *pBuffer)
{
    //Menu de seleçao para o modo de impressao
    //Impressao por ordem de insercao (PrintOrder)
    //Impressao por idade crescente (PrintAge)
    while (1)
    {
        printf("| Deseja imprimir como?\n");
        printf("| 0 - Ordem de insercao\n");
        printf("| 1 - Idade crescente\n");
        printf("| 9 - Voltar\n");
        escolha(pBuffer);
        if (escolhido(pBuffer) == 0 || escolhido(pBuffer) == 1 || escolhido(pBuffer) == 9)
            break;
    }
    switch (escolhido(pBuffer))
    {
    case 0:
        PrintOrder(pBuffer);
        break;
    case 1:
        PrintAge(pBuffer);
        break;
    case 9:
        return;
        break;
    default:
        return;
        break;
    }
}
bool Search(void *pBuffer)
{
    if (!Empty(pBuffer))
    {
        Fila *pFila;
        pFila = pBuffer;
        pFila->pAux = pFila->pFirst; //Auxiliar recebe o primeiro termo
        pFila->i = 0;                //Contador para controle
        printf("| Digite o nome: ");
        getchar();
        fgets(pFila->auxiliar, 30, stdin);  //Capta o nome a ser pesquisado
        printf("| Buscando por: %s...\n", pFila->auxiliar);
        while (pFila->i < pFila->quantidade)
        {
            if (strcmp(pFila->auxiliar, pFila->pAux->info.nome) == 0) //Se forem iguais
                return true;
            else //Se nao forem iguais
            {
                //Aux recebe o proximo
                pFila->pAux = pFila->pAux->pNext;
                pFila->i++;
            }
        }
        return false;
    }
    else
        printf("| Lista vazia\n");
}
bool Empty(void *pBuffer)
{
    //Retorna falso se não houver termos
    Fila *pFila;
    pFila = pBuffer;
    if (pFila->quantidade == 0 || pFila->pFirst == NULL)
        return true;
    else
        return false;
}