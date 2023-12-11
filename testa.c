#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hashliza.h"
#include "shannon.h"


/**
 * @brief Executa todos os passos para gerar o hash de uma string através das
 * funções da biblioteca hashliza e compara o resultado com o hash esperado.
 * 
 * @param entrada - string a ser hasheada
 * @param saida_esperada - hash esperado para a string de entrada 
 * @param vetor_magico - ponteiro para vetor mágico utilizado para gerar o hash
 */
void testa_hashliza(char *entrada, char *saida_esperada, int *vetor_magico)
{
    char *saida_1 = ep1Passo1Preenche(entrada);
    int tamanho_saida_2;
    char *saida_2 = ep1Passo2XOR(saida_1, vetor_magico, &tamanho_saida_2);
    char *saida_3 = ep1Passo3Comprime(saida_2, tamanho_saida_2, vetor_magico);
    char *saida_4 = ep1Passo4Hash(saida_3);
    char *hash = ep1Passo4HashEmHexa(saida_4);

    if (strcmp(hash, saida_esperada) != 0)
    {
        printf("ERRO: hash em hexadecimal não é o esperado pasa a string:\n");
        printf("%s\n", entrada);
    }
    
    free(saida_1);
    free(saida_2);
    free(saida_3);
    free(saida_4);
    free(hash);
}


/**
 * @brief Testa a função ep3CriaVetorMagico, garantindo que (a) a mesma semente
 * gera o mesmo vetor, (b) sementes diferentes geram vetores diferentes e (c)
 * todos os números de 0 a 255 aparecem exatamente uma vez no vetor.
 * 
 * @param semente - semente utilizada para gerar o vetor mágico
 */
void testa_vetor_magico(int semente)
{
    int *vetor_magico = ep3CriaVetorMagico(semente);
    int *confirma_vetor_magico = ep3CriaVetorMagico(semente);
    int *vetor_magico_outra_semente = ep3CriaVetorMagico(semente + 1);

    int numero_esta_no_vetor[256] = {0};

    int gera_o_mesmo_vetor = 1;
    int sementes_diferentes_geram_vetores_diferentes = 0;
    int todos_os_numeros_aparecem = 1;

    for (int i = 0; i < 256; i++)
    {
        if (vetor_magico[i] != confirma_vetor_magico[i])
            gera_o_mesmo_vetor = 0;

        if (vetor_magico[i] != vetor_magico_outra_semente[i])
            sementes_diferentes_geram_vetores_diferentes = 1;

        numero_esta_no_vetor[vetor_magico[i]] = 1;
    }

    for (int i = 0; i < 256; i++)
    {
        if (numero_esta_no_vetor[i] != 1)
            todos_os_numeros_aparecem = 0;
    }

    if (!gera_o_mesmo_vetor || !sementes_diferentes_geram_vetores_diferentes || 
        !todos_os_numeros_aparecem)
    {
        printf("ERRO NA GERAÇÃO DO VETOR MÁGICO PSEUDO-ALEATÓRIO:\n");
        if (!gera_o_mesmo_vetor)
            printf("- A mesma semente gera vetores diferentes.\n");
        if (!sementes_diferentes_geram_vetores_diferentes)
            printf("- Sementes diferentes geram o mesmo vetor.\n");
        if (!todos_os_numeros_aparecem)
            printf("- Erro: há números repetidos ou ausentes.\n");
    }

    free(vetor_magico);
    free(confirma_vetor_magico);
    free(vetor_magico_outra_semente);
}


/**
 * @brief Testa a função ep3CalculaEntropiaShannon, comparando o valor retornado
 * com o valor esperado, com uma tolerância de 0.000001.
 * 
 * @param info - string para a qual a Entropia de Shannon será calculada
 * @param base - base do logaritmo utilizado no cálculo da entropia
 * @param valor_esperado - valor esperado para a entropia da string de entrada
 */
void testa_shannon(char *info, int base, long double valor_esperado)
{
    long double calculado = ep3CalculaEntropiaShannon(info, base);

    // Como se trata de um valor de ponto flutuante, a comparação é feita
    // com uma tolerância de 0.000001
    if (abs(calculado - valor_esperado) > 0.000001)
    {
        printf("ERRO: entropia de '%s' não é a esperada.\n", info);
        printf("- Valor esperado: %Lf\n", valor_esperado);
        printf("- Valor calculado: %Lf\n", calculado);
    }
}


/**
 * @brief Esta função mede os tempos mínimo, médio e máximo de execução de cada
 * uma das funções das bibliotecas hashliza e shannon, para um conjunto de dez
 * execuções. Os tempos são medidos em segundos e impressos na saída padrão.
 * 
 */
void medir_tempos()
{
    char teste[] = "Uma string qualquer para testar o tempo de execução!!!!!!!";

    char *temp;
    int *vetor_magico = ep3CriaVetorMagico(999);

    clock_t inicial, final;

    double min, max, media, aux;

    // PASSO 1
    media = 0;
    min = 999;
    max = 0;
    for (int i = 0; i < 10; i++)
    {
        inicial = clock();
        temp = ep1Passo1Preenche(teste);
        final = clock();
        free(temp);

        aux = (double)(final - inicial) / CLOCKS_PER_SEC;

        media += aux;
        if (aux < min) min = aux;
        if (aux > max) max = aux;
    }
    printf("ep1Passo1Preenche:\n");
    printf("Tempo médio: %.7lf\n", media / 10.0);
    printf("Tempo mínimo: %.7lf\n", min);
    printf("Tempo máximo: %.7lf\n\n", max);

    // PASSO 2
    media = 0;
    min = 999;
    max = 0;
    char *saida_1 = ep1Passo1Preenche(teste);
    int tamanho;
    for (int i = 0; i < 10; i++)
    {
        inicial = clock();
        temp = ep1Passo2XOR(saida_1, vetor_magico, &tamanho);
        final = clock();
        free(temp);

        aux = (double)(final - inicial) / CLOCKS_PER_SEC;

        media += aux;
        if (aux < min) min = aux;
        if (aux > max) max = aux;
    }
    printf("ep1Passo2XOR:\n");
    printf("Tempo médio: %.7lf\n", media / 10.0);
    printf("Tempo mínimo: %.7lf\n", min);
    printf("Tempo máximo: %.7lf\n\n", max);

    // PASSO 3
    media = 0;
    min = 999;
    max = 0;
    char *saida_2 = ep1Passo2XOR(saida_1, vetor_magico, &tamanho);
    free(saida_1);
    for (int i = 0; i < 10; i++)
    {
        inicial = clock();
        temp = ep1Passo3Comprime(saida_2, tamanho, vetor_magico);
        final = clock();
        free(temp);

        aux = (double)(final - inicial) / CLOCKS_PER_SEC;

        media += aux;
        if (aux < min) min = aux;
        if (aux > max) max = aux;
    }
    printf("ep1Passo3Comprime:\n");
    printf("Tempo médio: %.7lf\n", media / 10.0);
    printf("Tempo mínimo: %.7lf\n", min);
    printf("Tempo máximo: %.7lf\n\n", max);

    // PASSO 4 - parte 1
    media = 0;
    min = 999;
    max = 0;
    char *saida_3 = ep1Passo3Comprime(saida_2, tamanho, vetor_magico);
    free(saida_2);
    for (int i = 0; i < 10; i++)
    {
        inicial = clock();
        temp = ep1Passo4Hash(saida_3);
        final = clock();
        free(temp);

        aux = (double)(final - inicial) / CLOCKS_PER_SEC;

        media += aux;
        if (aux < min) min = aux;
        if (aux > max) max = aux;
    }
    printf("ep1Passo4Hash:\n");
    printf("Tempo médio: %.7lf\n", media / 10.0);
    printf("Tempo mínimo: %.7lf\n", min);
    printf("Tempo máximo: %.7lf\n\n", max);

    // PASSO 4 - parte 2
    media = 0;
    min = 999;
    max = 0;
    char *saida_4 = ep1Passo4Hash(saida_3);
    free(saida_3);
    for (int i = 0; i < 10; i++)
    {
        inicial = clock();
        temp = ep1Passo4HashEmHexa(saida_4);
        final = clock();
        free(temp);

        aux = (double)(final - inicial) / CLOCKS_PER_SEC;

        media += aux;
        if (aux < min) min = aux;
        if (aux > max) max = aux;
    }
    printf("ep1Passo4HashEmHexa:\n");
    printf("Tempo médio: %.7lf\n", media / 10.0);
    printf("Tempo mínimo: %.7lf\n", min);
    printf("Tempo máximo: %.7lf\n\n", max);
    free(vetor_magico);
    free(saida_4);

    // VETOR MÁGICO
    media = 0;
    min = 999;
    max = 0;
    for (int i = 0; i < 10; i++)
    {
        inicial = clock();
        vetor_magico = ep3CriaVetorMagico(42);
        final = clock();
        free(vetor_magico);

        aux = (double)(final - inicial) / CLOCKS_PER_SEC;

        media += aux;
        if (aux < min) min = aux;
        if (aux > max) max = aux;
    }
    printf("ep3CriaVetorMagico:\n");
    printf("Tempo médio: %.7lf\n", media / 10.0);
    printf("Tempo mínimo: %.7lf\n", min);
    printf("Tempo máximo: %.7lf\n\n", max);

    // SHANNON
    media = 0;
    min = 999;
    max = 0;
    for (int i = 0; i < 10; i++)
    {
        inicial = clock();
        ep3CalculaEntropiaShannon(teste, 2);
        final = clock();

        aux = (double)(final - inicial) / CLOCKS_PER_SEC;

        media += aux;
        if (aux < min) min = aux;
        if (aux > max) max = aux;
    }
    printf("ep3CalculaEntropiaShannon:\n");
    printf("Tempo médio: %.7lf\n", media / 10.0);
    printf("Tempo mínimo: %.7lf\n", min);
    printf("Tempo máximo: %.7lf\n\n", max);
}


/**
 * @brief Testa as funções das bibliotecas hashliza e shannon. Caso algum erro
 * seja encontrado, uma mensagem de erro é impressa na saída padrão.
 * 
 * @return int - retorno padrão da função main (0 se tudo ocorreu bem)
 */
int main()
{
    // TESTES DA LIB HASHLIZA ==================================================
    // Obs: os testes são realizados com o vetor dado no EP1, para garantir
    // que a implementação está correta. A geração de vetores mágicos pseudo-
    // aleatórios é testada separadamente.

    printf("------------\nIniciando testes da lib hashliza...\n");

    int VETOR_MAGICO[] = {
        122, 77, 153, 59, 173, 107, 19, 104, 123, 183, 75, 10, 114, 236, 106,
        83, 117, 16, 189, 211, 51, 231, 143, 118, 248, 148, 218, 245, 24, 61,
        66, 73, 205, 185, 134, 215, 35, 213, 41, 0, 174, 240, 177, 195, 193, 39,
        50, 138, 161, 151, 89, 38, 176, 45, 42, 27, 159, 225, 36, 64, 133, 168,
        22, 247, 52, 216, 142, 100, 207, 234, 125, 229, 175, 79, 220, 156, 91,
        110, 30, 147, 95, 191, 96, 78, 34, 251, 255, 181, 33, 221, 139, 119,
        197, 63, 40, 121, 204, 4, 246, 109, 88, 146, 102, 235, 223, 214, 92,
        224, 242, 170, 243, 154, 101, 239, 190, 15, 249, 203, 162, 164, 199,
        113, 179, 8, 90, 141, 62, 171, 232, 163, 26, 67, 167, 222, 86, 87, 71,
        11, 226, 165, 209, 144, 94, 20, 219, 53, 49, 21, 160, 115, 145, 17, 187,
        244, 13, 29, 25, 57, 217, 194, 74, 200, 23, 182, 238, 128, 103, 140, 56,
        252, 12, 135, 178, 152, 84, 111, 126, 47, 132, 99, 105, 237, 186, 37,
        130, 72, 210, 157, 184, 3, 1, 44, 69, 172, 65, 7, 198, 206, 212, 166,
        98, 192, 28, 5, 155, 136, 241, 208, 131, 124, 80, 116, 127, 202, 201,
        58, 149, 108, 97, 60, 48, 14, 93, 81, 158, 137, 2, 227, 253, 68, 43,
        120, 228, 169, 112, 54, 250, 129, 46, 188, 196, 85, 150, 6, 254, 180,
        233, 230, 31, 76, 55, 18, 9, 32, 82, 70
    };

    // TESTA PASSO A PASSO -----------------------------------------------------

    // TESTA PASSO 1
    char *saida_1 = ep1Passo1Preenche("Ola mundo!");
    char esperado_saida_1[] = {
        79, 108, 97, 32, 109, 117, 110, 100, 111, 33, 6, 6, 6, 6, 6, 6
    };
    for (int i = 0; i < 16; i++)
    {
        if (esperado_saida_1[i] != saida_1[i])
            printf("ERRO: saída do passo 1 não é a esperada.\n");
    }

    // TESTA PASSO 2
    int tamanho_saida_2;
    char *saida_2 = ep1Passo2XOR(saida_1, VETOR_MAGICO, &tamanho_saida_2);
    char esperado_saida_2[] = {
        79, 108, 97, 32, 109, 117, 110, 100, 111, 33, 6, 6, 6, 6, 6, 6,
        147, 70, 0, 205, 74, 247, 244, 219, 105, 175, 252, 55, 151, 53, 38, 205
    };
    for (int i = 0; i < tamanho_saida_2; i++)
    {
        if (esperado_saida_2[i] != saida_2[i])
            printf("ERRO: saída do passo 2 não é a esperada.\n");
    }

    // TESTA PASSO 3
    char *saida_3 = ep1Passo3Comprime(saida_2, tamanho_saida_2, VETOR_MAGICO);
    char esperado_saida_3[] = {
        126, 162, 49, 155, 224, 208, 56, 144, 129, 97, 180, 232, 194, 107, 252,
        122, 194, 53, 21, 66, 190, 179, 174, 146, 84, 143, 170, 129, 200, 98,
        35, 92, 209, 123, 47, 192, 63, 184, 225, 80, 61, 23, 150, 202, 180, 27,
        57, 216
    };
    for (int i = 0; i < 48; i++)
    {
        if (esperado_saida_3[i] != saida_3[i])
            printf("ERRO: saída do passo 3 não é a esperada.\n");
    }

    // TESTA PASSO 4
    char *saida_4 = ep1Passo4Hash(saida_3);
    char esperado_saida_4[] = {
        126, 162, 49, 155, 224, 208, 56, 144, 129, 97, 180, 232, 194, 107, 252,
        122
    };
    for (int i = 0; i < 16; i++)
    {
        if (esperado_saida_4[i] != saida_4[i])
            printf("ERRO: saída do passo 4 não é a esperada.\n");
    }
    char *hash = ep1Passo4HashEmHexa(saida_4);
    char esperado_hash[] = "7ea2319be0d038908161b4e8c26bfc7a";
    if (strcmp(hash, esperado_hash) != 0)
        printf("ERRO: hash em hexadecimal não é o esperado.\n");
    
    // Desaloca memória
    free(saida_1);
    free(saida_2);
    free(saida_3);
    free(saida_4);
    free(hash);

    // TESTA HASHES ------------------------------------------------------------
    
    // Outros casos utilizados no EP1
    char caso_1[] = "Ole mundo!";
    char caso_2[] = "que tistreza";
    char caso_3[] = "MAC0216 eh muito legal!";

    // Testa o processo completo de geração de hash
    testa_hashliza(caso_1, "c0900a10ded215a7297b69d86d81e25a", VETOR_MAGICO);
    testa_hashliza(caso_2, "878561c1134d1fd53e9b36822e1914cc", VETOR_MAGICO);
    testa_hashliza(caso_3, "9bc1e12b591694d3354f658d46006f7a", VETOR_MAGICO);

    // TESTA VETOR MÁGICO GERADO ALERATORIAMENTE -------------------------------
    testa_vetor_magico(42);
    testa_vetor_magico(13);
    testa_vetor_magico(1993);

    printf("Finalizando testes da lib hashliza...\n");
    printf("Se não recebeu mensagem de erro, todos os testes passaram!\n");

    // TESTES DA LIB SHANNON ===================================================
    // Obs: os casos de teste foram obtidos a partir de calculadoras online
    // (base 2) ou confirmando as saídas com colegas (outras bases).

    printf("------------\nIniciando testes da lib shannon...\n");
    
    // Exemplo do vídeo
    testa_shannon("araraquara", 2, 1.685475);

    // Testes com base 2 - saídas obtidas com calculadora online
    testa_shannon("AAAAAAAAAA", 2, 0.0);
    testa_shannon("AAAAAAAAAB", 2, 0.468996);
    testa_shannon("Hello, World!", 2, 3.180833);
    testa_shannon("MAC0216 eh muito legal!", 2, 4.142915);

    // Bases variadas - saídas comparadas com colegas
    testa_shannon("Teste com base 3", 3, 2.069853);
    testa_shannon("Teste com base 4", 4, 1.640320);
    testa_shannon("Teste com base 5", 5, 1.412894);

    printf("Finalizando testes da lib shannon...\n");
    printf("Se não recebeu mensagem de erro, todos os testes passaram!\n");
    printf("------------\n");

    // TESTES DE TEMPO DE EXECUÇÃO =============================================
    // medir_tempos();

    return 0;
}