#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ep1Passo1Preenche(char *entrada);
char *ep1Passo2XOR(char *saida_1, int *vetor_magico, int *tamanho_saida);
char *ep1Passo3Comprime(char *saida_2, int tamanho_entrada, int *vetor_magico);
char *ep1Passo4Hash(char *saida_3);
char *ep1Passo4HashEmHexa(char *hash);
int  *ep3CriaVetorMagico(int semente);