main.out: Tetris.o jogoTetris.o
	g++ Tetris.o jogoTetris.o -lncurses

Tetris.o:
	g++ -c Tetris.cpp

jogoTetris.o:
	g++ -c jogoTetris.cpp
