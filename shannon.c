#include "shannon.h"

#define uchar unsigned char


/**
 * @brief Calcula a entropia de Shannon de uma string utilizando uma base
 * especificada para o logaritmo.
 * 
 * @param info - string para a qual a Entropia de Shannon será calculada
 * @param base - base do logaritmo utilizado no cálculo da entropia
 * @return long double - valor da entropia de Shannon calculada
 */
long double ep3CalculaEntropiaShannon(char *info, int base)
{
    int tamanho = strlen(info);

    // Contagem de ocorrências de cada caractere (ASCII)
    int contagem[256] = {0};
    for (int i = 0; i < tamanho; ++i) contagem[(uchar)info[i]]++;

    // Calcular probabilidades e Entropia de Shannon
    long double entropia = 0.0;
    long double probabilidade;

    for (int i = 0; i < 256; ++i)
    {
        if (contagem[i] > 0)
        {
            probabilidade = (double)contagem[i] / tamanho;
            entropia -= probabilidade * log(probabilidade) / log(base);
        }
    }

    return entropia;
}