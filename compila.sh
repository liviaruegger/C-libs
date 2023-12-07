# Compilar a biblioteca estática 'hashliza' (.a)
gcc -c -o hashliza.o hashliza.c || exit 1
ar -rcv libhashliza.a hashliza.o > /dev/null || exit 1

# Compilar a biblioteca dinâmica 'shannon' (.so)
gcc -c -fPIC -o shannon.o shannon.c || exit 1
gcc -o libshannon.so -shared shannon.o -lm || exit 1

# Compilar o programa de testes "testa.c"
gcc -c -o testa.o testa.c || exit 1
gcc -o testa testa.o -L${PWD} -lshannon -lhashliza || exit 1

# Gerar documentação com doxygen
# TODO

# Tudo certo
exit 0