#include "hashliza.h"

#define uchar unsigned char


/**
 * @brief Recebe uma string e realiza o padding com (16 - (tamanho % 16)) de tal
 * forma que a string resultante tenha um tamanho múltiplo de 16.
 * 
 * @param entrada - string original
 * @return char* - string com padding
 */
char *ep1Passo1Preenche(char *entrada)
{
    int tamanho = strlen(entrada);
    int complemento = 16 - (tamanho % 16);
    
    char *saida = malloc((tamanho + complemento + 1) * sizeof(char));
    strcpy(saida, entrada);
    saida[tamanho + complemento] = '\0';

    for (int i = tamanho; i < (tamanho + complemento); i++)
        saida[i] = complemento;

    return saida;
}


/**
 * @brief Recebe uma string gerada pelo passo 1 e realiza uma série de operações
 * XOR utilizando o "vetor mágico" para gerar uma nova string de saída com 16
 * bytes a mais.
 * 
 * @param saida_1 - string de saída do passo 1
 * @param vetor_magico - "vetor mágico" para realização dos XOR
 * @param tamanho_saida - ponteiro para armazenar o tamanho da string de saída
 * @return char* - saída do passo, ou NULL caso os argumentos sejam inválidos
 */
char *ep1Passo2XOR(char *saida_1, int *vetor_magico, int *tamanho_saida)
{   
    if (saida_1 == NULL || vetor_magico == NULL || tamanho_saida == NULL ||
        strlen(saida_1) % 16 != 0) return NULL;

    int n = strlen(saida_1) / 16;
    int tamanho = (n + 1) * 16;
    char *saida_2 = calloc(tamanho + 1, sizeof(char));
    strcpy(saida_2, saida_1);

    uchar novo_valor = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            uchar index = saida_1[i * 16 + j] ^ novo_valor;
            novo_valor = vetor_magico[index] ^ saida_2[tamanho - 16 + j];
            saida_2[tamanho - 16 + j] = (char)novo_valor;
        }
    }

    *tamanho_saida = tamanho;
    return saida_2;
}


/**
 * @brief Recebe uma string gerada pelo passo 2 e realiza novas operações com o
 * "vetor mágico" para gerar uma nova string de saída com 48 bytes.
 * 
 * @param saida_2 - string de saída do passo 2
 * @param tamanho_entrada - tamanho da string de entrada (saída do passo 2)
 * @param vetor_magico - "vetor mágico" para realização dos XOR
 * @return char* - saída do passo, ou NULL caso os argumentos sejam inválidos
 */
char *ep1Passo3Comprime(char *saida_2, int tamanho_entrada, int *vetor_magico)
{
    if (saida_2 == NULL || vetor_magico == NULL || tamanho_entrada % 16 != 0)
        return NULL;
    
    int n = tamanho_entrada / 16;

    char *saida_3 = calloc(49, sizeof(char));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            saida_3[16 + j] = saida_2[i * 16 + j];
            saida_3[32 + j] = saida_3[16 + j] ^ saida_3[j];
        }

        uchar temp = 0;
        for (int j = 0; j < 18; j++)
        {
            for (int k = 0; k < 48; k++)
            {
                temp = (uchar)saida_3[k] ^ (uchar)vetor_magico[temp];
                saida_3[k] = temp;
            }

            temp = (temp + j) % 256;
        }
    }

    return saida_3;
}


/**
 * @brief Recebe uma string gerada pelo passo 3 e retorna uma nova string com os
 * seus 16 primeiros bytes.
 * 
 * @param saida_3 - string de saída do passo 3
 * @return char* - saída do passo, ou NULL caso os argumentos sejam inválidos
 */
char *ep1Passo4Hash(char *saida_3)
{
    if (saida_3 == NULL) return NULL;

    char *hash = calloc(17, sizeof(char));
    for (int i = 0; i < 16; i++) hash[i] = saida_3[i];

    return hash;
}


/**
 * @brief Recebe uma string de 16 bytes, gerada pela primeira etapa do passo 4,
 * e retorna uma outra string com sua representação hexadecimal.
 * 
 * @param hash - string de 16 bytes gerada pelos passos anteriores
 * @return char* - string com a representação hexadecimal do hash, ou NULL caso
 * os argumentos sejam inválidos
 */
char *ep1Passo4HashEmHexa(char *hash)
{
    if (hash == NULL) return NULL;
    
    char *hexa = calloc(33, sizeof(char));
    for (int i = 0; i < 16; i++)
        sprintf(hexa + (i * 2), "%02hhx", hash[i]);

    return hexa;
}


/**
 * @brief Constrói um vetor pseudo-aleatório de tamanho 256, com inteiros de 0 a
 * 255 sem repetição, utilizando o algoritmo de embaralhamento de Fisher-Yates.
 * 
 * @param semente - semente utilizada para gerar o aleatoriamente o vetor
 * @return int* - "vetor mágico" pseudo-aleatório de tamanho 256
 */
int *ep3CriaVetorMagico(int semente)
{
    int *vetor_magico = (int *)malloc(256 * sizeof(int));
    for (int i = 0; i < 256; i++) vetor_magico[i] = i;

    srand(semente);

    for (int i = 255; i > 0; i--)
    {
        int j = rand() % (i + 1);

        int temp = vetor_magico[i];
        vetor_magico[i] = vetor_magico[j];
        vetor_magico[j] = temp;
    }

    return vetor_magico;
}