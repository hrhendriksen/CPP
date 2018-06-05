all: use_vectors use_matrices use_gmres

#For debugging
OPT=-g -Wall
#For optimistaion
#OPT=-O

#All objects (except main) come from cpp and hpp 
%.o:	%.cpp %.hpp
	g++ ${OPT} -c -o $@ $<
#use_vectors relies on objects which rely on headers
use_vectors:	use_vectors.cpp Vector.o Exception.o
		g++ ${OPT} -o use_vectors use_vectors.cpp Vector.o Exception.o

use_matrices: use_matrices.cpp Matrix.o Exception.o
		g++ ${OPT} -o use_matrices use_matrices.cpp Vector.o Matrix.o Exception.o

use_gmres: use_gmres.cpp gmres.cpp Exception.o
	g++ ${OPT} -o use_gmres use_gmres.cpp Vector.o Matrix.o Exception.o

clean:
	rm -f *.o *~ use_vectors, use_matrices