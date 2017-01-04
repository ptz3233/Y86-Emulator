all:
	gcc y86emul.c -g -Wall -o y86emul
	gcc y86dis.c -g -Wall -o y86dis
y86emul:
	gcc y86emul.c -g -Wall -o y86emul
y86dis:
	gcc y86dis.c -g -Wall -o y86dis
clean:
	rm y86emul
	rm y86dis