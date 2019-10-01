main.out: tetris.o interface_menu.o game.o
	g++ tetris.o interface_menu.o game.o -lglut -lGL -lGLU -lm -o main.out

tetris.o:
	g++ -c tetris.cpp

interface_menu.o:
	g++ -c interface_menu.cpp -lglut -lGL -lGLU -lm

game.o:
	g++ -c game.cpp -lglut -lGL -lGLU -lm

clear:
	rm *.o *.out
