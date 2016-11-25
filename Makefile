FLAGS = -Wall
DRIVER = driver

all: Driver.o Pinball.o
	g++ $(FLAGS) Driver.o Pinball.o -o a.out

Driver.o: $(DRIVER).cpp words.h Pinball.h
	g++ $(FLAGS) -c $(DRIVER).cpp -o Driver.o

Pinball.o: Pinball.cpp Pinball.h
	g++ $(FLAGS) -c Pinball.cpp


run:
	./a.out $(INPUT) $(FLAG)

test:
	clear
	make clean
	make
	valgrind ./a.out

save:
	scp -r . end1@gl.umbc.edu:proj4/src

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#
	rm -f temp.txt
