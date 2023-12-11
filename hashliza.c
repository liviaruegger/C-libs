#include "hashliza.h"

#define uchar unsigned char


/**
 * @brief 
 * 
 * @param entrada 
 * @return char* 
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
 * @brief 
 * 
 * @param saida_1 
 * @param vetor_magico 
 * @param tamanho_saida 
 * @return char* 
 */
char *ep1Passo2XOR(char *saida_1, int *vetor_magico, int *tamanho_saida)
{   
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
 * @brief 
 * 
 * @param saida_2 
 * @param tamanho_entrada 
 * @param vetor_magico 
 * @return char* 
 */
char *ep1Passo3Comprime(char *saida_2, int tamanho_entrada, int *vetor_magico)
{
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
 * @brief 
 * 
 * @param saida_3 
 * @return char* 
 */
char *ep1Passo4Hash(char *saida_3)
{
    char *hash = calloc(17, sizeof(char));
    for (int i = 0; i < 16; i++) hash[i] = saida_3[i];

    return hash;
}


/**
 * @brief 
 * 
 * @param hash 
 * @return char* 
 */
char *ep1Passo4HashEmHexa(char *hash)
{
    char *hexa = calloc(33, sizeof(char));
    for (int i = 0; i < 16; i++)
        sprintf(hexa + (i * 2), "%02hhx", hash[i]);

    return hexa;
}


/**
 * @brief constrói o vetor mágico utilizando o algoritmo de embaralhamento de
 * Fisher-Yates.
 * 
 * @param semente 
 * @return int* 
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