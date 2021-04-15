all: double_pendulum single_pendulum

double_pendulum:
	gcc -o double double_pendulum.c bresenham.c -lncurses -g -lm

single_pendulum:
	gcc -o single single_pendulum.c bresenham.c -lncurses -g -lm

clean:
	rm single double
