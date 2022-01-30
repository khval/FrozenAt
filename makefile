

all: init.o
	gcc init.o FrozenAt.c -o FrozenAt

clean:
	delete (#?.o|FrozenAt)