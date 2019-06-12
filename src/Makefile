CC := gcc

EXEC := notebook

CFLAGS :=	\
	-Wall	\
    -g		\


all:
	$(CC) $(CFLAGS) ma.c -o ma
	$(CC) $(CFLAGS) sv.c -o sv
	$(CC) $(CFLAGS) cv.c -o cv
	$(CC) $(CFLAGS) compact.c -o compact
	$(CC) $(CFLAGS) lerfich.c -o lerfich
	$(CC) $(CFLAGS) martelo.c -o martelo
	$(CC) $(CFLAGS) ag.c -o ag
	mkdir ./fich_ma/
	mkdir ./fich_ag/
	mkdir ./fich_sv/

e_ma:
	./ma
e_sv:
	./sv
e_cv:
	./cv
e_comp:
	./compact
e_lfich:
	./lerfich
e_ag:
	./ag
e_mart:
	./martelo
insereArt:
	./ma<./testes/insere
modiArt:
	./ma<./testes/modifica

PROG :=	\
	sv			\
    cv			\
	ma			\
	ag			\
	compact		\
	fifo_client	\
	fifo_server	\
	lerfich		\
	martelo 	\
	./fich_ma/* \
	./fich_ag/*	\
	./fich_sv/*	\


clean:
	rm $(PROG)
	rmdir ./fich_ma
	rmdir ./fich_ag
	rmdir ./fich_sv









