CC = gcc
CFLAGS = -Wall -std=c99

all: questions 

questions:
	$(CC) $(CFLAGS) questions.c test1.c -o test1

trees:
	$(CC) $(CFLAGS) questions.c qtree.c test2.c -o test2

categorizers:
	$(CC) $(CFLAGS) questions.c qtree.c categorizer.c -o categorizer
    
clean:  
	rm test1 