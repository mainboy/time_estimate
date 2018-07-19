
main: main.c clock.c
	gcc $^ -o main

clean:
	-rm -rf main
