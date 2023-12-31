------------------- EP03 -------------------
MAC0216 - Técnicas de Programação I - 2s2023
--------------------------------------------


=== AUTORA ===

Ana Lívia Rüegger Saldanha
NUSP: 8586691
ana.saldanha@usp.br


=== DESCRIÇÃO ===

Este projeto, realizado como Exercício Programa para a disciplina MAC0216 do
IME-USP, apresenta implementações e interfaces de duas bibliotecas em C:

1. Biblioteca estática 'hashliza', com uma série de funções, correspondentes a
uma sequência de passos, para geração de um hash em hexadecimal para a string
fornecida. Em conjunto, os passos/funções executam o mesmo algoritmo
implementado no EP1 de MAC0216;

2. Biblioteca dinâmica 'shannon', contendo uma função que calcula a Entropia de
Shannon para uma dada string, com a base de logaritmo especificada.

Ainda, o projeto inclui um programa de teste automatizado implementado no
arquivo testa.c e um script para compilação das bibliotecas e desse programa,
além da geração de uma documentação no padrão Doxygen.


=== COMO EXECUTAR ===

Para execução, deve-se compilar o programa utilizando o script compila.sh, mas
alguns cuidados devem ser tomados antes da execução desse script: é necessário
que este esteja com permissão de execução e também que o arquivo de configuração
da documentação Doxygen (chamado Doxyfile) tenha sido criado e editado com as
especificações desejadas. A criação do Doxyfile pode ser feita com:

$   doxygen -g

Agora, podemos compilar o programa rodando o script com o seguinte comando:

$   ./compila.sh

Antes de executar o script, ainda é preciso exportar o caminho para que o
ligador encontre a biblioteca dinâmica que acabamos de gerar, através do
comando:

$   export LD_LIBRARY_PATH="${PWD}:$LD_LIBRARY_PATH"

E, finalmente, é possível executar o programa que testa as bibliotecas:

$   ./testa


=== TESTES ===

Um conjunto de testes foi implementado no arquivo testa.c, consistindo em:

1. Para a biblioteca 'hashliza': utilizando o vetor mágico fornecido no EP1, um
caso de teste checando cada um dos passos/funções individualmente e outros três
casos de hash executando todo o processo; separadamente, testa-se a função de
geração de vetor mágico pseudo-aleatório.

2. Para a biblioteca 'shannon': oito casos de teste que foram construídos com
base no vídeo fornecido pelo enunciado, em calculadoras online ou confirmando
a saída com colegas (para bases diferentes de 2, visto que o vídeo e as
calculadoras encontradas trabalham apenas na base 2).

Para realizar essa série de testes, basta executar o programa 'testa', após
compilação, como especificado no item anterior. Caso algum teste falhe, uma
mensagem de erro correspondente será impressa na saída padrão.

O arquivo testa.c também apresenta uma função que mede o tempo de execução de
cada função das bibliotecas para 10 iterações, utilizando a função clock() da
biblioteca time.h, e apresenta seus tempos de execução médio, mínimo e máximo.
A chamada dessa função foi mantida comentada para evitar poluir a saída dos
testes, mas para realizar a medição basta descomentar a linha e recompilar antes
de executar o programa de teste.


=== DEPENDÊNCIAS ===

Compilador:     gcc (Ubuntu 9.4.0-1ubuntu1~20.04.2) 9.4.0
Bash:           GNU bash, version 5.0.17(1)-release (x86_64-pc-linux-gnu)
Doxygen:        Doxygen version 1.8.17
SO:             x86_64 GNU/Linux