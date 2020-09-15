sources=addsub.c multiplication.c division.c squareroot.c complex.c arbprecision.h
objects=addsub.o multiplication.o division.o squareroot.o

default:run

addsub.o:addsub.c
	@gcc -c addsub.c
multiplication.o:multiplication.c
	@gcc -c multiplication.c
division.o:division.c
	@gcc -c division.c
squareroot.o:squareroot.c
	@gcc -c squareroot.c

libarbprecision.a : $(objects)
	@ar cr libarbprecision.a addsub.o multiplication.o division.o squareroot.o

mainfile:complex.c libarbprecision.a arbprecision.h
	@gcc -o mainfile complex.c -L. -larbprecision -lm

run:mainfile

.Phony : run
