main:
	gcc main.c utils.c messages.c compile.c -o brain

clean:
	rm brain
