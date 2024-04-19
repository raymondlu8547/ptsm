all: 
	gcc ptsm.c -o ptsm -fopenmp

clean:
	rm -f lab1.o *~