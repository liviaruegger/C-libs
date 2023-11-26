entrega = hashliza.h hashliza.c shannon.h shannon.c testa.c compila.sh LEIAME.txt docs/relatorio.pdf

all:
	./compila.sh

test: all
	./testa

tar:
	mkdir ep3-ana_livia_saldanha
	cp $(entrega) ep3-ana_livia_saldanha/
	tar zcvf ep3-ana_livia_saldanha.tar.gz ep3-ana_livia_saldanha
	rm -r ep3-ana_livia_saldanha