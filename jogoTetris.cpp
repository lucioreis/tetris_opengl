#include <iostream>
#include <cstdlib>
#include <ncurses.h>
#include <unistd.h>
#include "Tetris.h"

using namespace std;


void exibeJogo(const Tetris &jogoComPecaCaindo,int larguraJogo,int alturaMaximaJogo) {
	for(int i=0;i<alturaMaximaJogo;i++) {
		mvprintw(i, 0, "|");
		for(int j=0;j<larguraJogo;j++) {
			mvprintw(i, j+1, "%c",jogoComPecaCaindo.get(j,alturaMaximaJogo-i-1));
		}
		mvprintw(i, larguraJogo+1, "|");
	}
	for(int j=0;j<larguraJogo;j++) {
			mvprintw(alturaMaximaJogo, j+1, "-");
			mvprintw(alturaMaximaJogo+1, j+1, "%d", jogoComPecaCaindo.getAltura(j)/10);
			mvprintw(alturaMaximaJogo+2, j+1, "%d", jogoComPecaCaindo.getAltura(j)%10);
	}
}

int main() {


	//Observacoes: jogo implementado sem muitos cuidados!
	//Exemplo: o tempo de espera entre cada iteracao depende ligeiramente do tempo que o programa gasta
	//processando (o certo seria descontar tal tempo...)

	//Essa implementacao nao funciona de forma exatamente igual a do Tetris
	//colisao --> peca para de descer!
	//se colisao eh devido a mover lateralmente --> desconsiderar?


	const int possiveisRotacoes[] = {0,90,180,270};
	const int larguraJogo = 16;
	const int alturaMaximaJogo = 20;
	Tetris jogo(larguraJogo);
	Tetris jogoComPecaCaindo(larguraJogo);

	int alturaPecaAtual=alturaMaximaJogo;
	char idPecaAtual;
	int posicaoPecaAtual,rotacaoPecaAtual;

	int ultimaTecla = -1;

	idPecaAtual = "IJLOSTZ"[rand()%7];
	posicaoPecaAtual = larguraJogo/2-2;
	alturaPecaAtual = alturaMaximaJogo;
	rotacaoPecaAtual = 0;


	initscr(); 
	noecho(); 
	curs_set(false);
	keypad(stdscr,true);
	cbreak(); 
	//raw();
	int tecla;

	//Ideia basica do jogo:
	//o objeto "jogo" representa o status atual da tela (com as pecas fixas)
	//o objeto "jogoComPecaCaindo" simula as pecas caindo
	//-- Basicamente em cada iteracao ele comeca com uma copia da parte fixa do jogo
	//-- Entao, a peca que esta caindo e' adicionada a ele em uma posicao mais baixa (em cada passo a altura dela diminui)

	while(true) {		
		jogoComPecaCaindo = jogo;

		
 		if(ultimaTecla==KEY_LEFT) { 			
 			Tetris jogoTeste = jogoComPecaCaindo; 			
 			if(jogoTeste.adicionaForma(posicaoPecaAtual-1,alturaPecaAtual,idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]))
 				posicaoPecaAtual--;
 		} else if(ultimaTecla==KEY_RIGHT){
 			Tetris jogoTeste = jogoComPecaCaindo; 			
 			if(jogoTeste.adicionaForma(posicaoPecaAtual+1,alturaPecaAtual,idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]))
 				posicaoPecaAtual++;
 		} else if(ultimaTecla==' '){ //a tecla de espaco e' utilizada para rodar a peca...
 			Tetris jogoTeste = jogoComPecaCaindo; 			
 			if(jogoTeste.adicionaForma(posicaoPecaAtual,alturaPecaAtual,idPecaAtual, possiveisRotacoes[(rotacaoPecaAtual+1)%4]))
 				rotacaoPecaAtual = (rotacaoPecaAtual+1)%4;
 		} 

 		//Antes de diminuirmos a altura de uma peca, tentamos adiciona-la nessa nova altura
 		// Se a funcao retornar true --> significa que podemos diminuir
 		// Senao --> isso significa que apeca colidiria (ocuparia o mesmo espaco que) com alguma peca fixa --> a peca devera parar na altura anterior 
 		// e uma nova peca deve comecar a cair
		if(jogoComPecaCaindo.adicionaForma(posicaoPecaAtual,alturaPecaAtual-1,idPecaAtual, possiveisRotacoes[rotacaoPecaAtual])) {
			alturaPecaAtual--;
		}
		else {
			//adiciona a peca a posicao onde ela ficara fixada
			jogo.adicionaForma(posicaoPecaAtual,alturaPecaAtual,idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]);
			jogoComPecaCaindo = jogo;

			//sorteia uma nova peca, define a altura como sendo o topo da tela, etc...
			idPecaAtual = "IJLOSTZ"[rand()%7];
			posicaoPecaAtual = larguraJogo/2-2;
			alturaPecaAtual = alturaMaximaJogo;
			rotacaoPecaAtual = rand()%4;
			jogoComPecaCaindo.removeLinhasCompletas();	
			jogo = jogoComPecaCaindo;	
		}

		exibeJogo(jogoComPecaCaindo,larguraJogo,alturaMaximaJogo);
		
 		ultimaTecla = getch();
 		halfdelay(5);

 		
 		refresh();
	}
	endwin();
}