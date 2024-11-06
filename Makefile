all: echo.o

echo: echo.c
	gcc -o echo echo.c

run: echo.o
	./echo -p 7

clean: 
	rm -f echo