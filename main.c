#include "trabalho.c"
int main()
{
    void *pBuffer = (Fila *)malloc(sizeof(Fila));
    if (!pBuffer)
    {
        printf("Erro memoria main\n");
        return -1;
    }
    Initialize(pBuffer);
    Menu(pBuffer);
    return 0;
}
