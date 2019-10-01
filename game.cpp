//#ingure -clude <GL/gl.h>
#include "game.h"
#include "Tetris.h"
#include "interface_menu.h"
#include <string>
#define KEY_UP 1
#define KEY_DOWN  2
#define KEY_LEFT  3
#define KEY_RIGHT 4
#define KEY_SPACE 5
#define BORDA 0
#define BACK 2
#define BLOCK 1

 //Declaração de variaveis globais
int possiveisRotacoes[] = {0, 90, 180, 270};
int largura;
int maxAltura;
int speed;
int cor;
int modo;
GLclampf cores[3][3][3] = {{{1., 0.,0.}, {0.,0.,0.},{1.,1.,1.}},{{0.,1.,0.},{1.,1.,1.},{0.,0.,0.}},{{0.,0.,1.},{1.,0.,0.},{1.,0.,1.}}};

Tetris jogo(0);
Tetris jogoComPecaCaindo(0);

int alturaPecaAtual = maxAltura;
char idPecaAtual="IJLOSTZ"[rand()%7];
int posicaoPecaAtual = largura/2 - 2;
int rotacaoPecaAtual = 0;
GLint side;
bool options[13];
bool game_over = false;

void game::text(const std::string &texto, int x, int y, double tamanhoX, double tamanhoY) {
   glPushMatrix();
   glLoadIdentity();
   glViewport(0,0,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
   glColor3f(1.0,0.0,0.0);
   glTranslatef(x, y, 0);
   glScalef(tamanhoX, tamanhoY, 1.0);
   for(int i = 0; i < texto.length(); ++i) {
       glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, texto[i]);
   }

   glPopMatrix();
}


//Funcao que lida coma classe Tetris, basicamente copiada e colada dos arquivos fornecidos
void game::game(int key){   
   
   jogoComPecaCaindo = jogo;
   if(jogo.getAltura() >= maxAltura) {
      game_over = true;
      return;
   }
   if(key == KEY_RIGHT){
        Tetris jogoTeste = jogoComPecaCaindo;
        if(jogoTeste.adicionaForma(posicaoPecaAtual-1, alturaPecaAtual, idPecaAtual, possiveisRotacoes[rotacaoPecaAtual])) posicaoPecaAtual--;
   }
   else if(key==KEY_LEFT){
 			Tetris jogoTeste = jogoComPecaCaindo; 			
 			if(jogoTeste.adicionaForma(posicaoPecaAtual+1,alturaPecaAtual,idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]))
 				posicaoPecaAtual++;
 	 }
   else if(key==KEY_SPACE){ //a tecla de espaco e' utilizada para rodar a peca...
 			Tetris jogoTeste = jogoComPecaCaindo; 			
      if(jogoTeste.adicionaForma(posicaoPecaAtual,alturaPecaAtual,idPecaAtual, possiveisRotacoes[(rotacaoPecaAtual+1)%4]))
 			rotacaoPecaAtual = (rotacaoPecaAtual+1)%4;
 		} 	

    if(jogoComPecaCaindo.adicionaForma(posicaoPecaAtual,alturaPecaAtual-1,idPecaAtual, possiveisRotacoes[rotacaoPecaAtual])) {
			alturaPecaAtual--;
		}
		else {
			//adiciona a peca a posicao onde ela ficara fixada
			jogo.adicionaForma(posicaoPecaAtual,alturaPecaAtual,idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]);
			jogoComPecaCaindo = jogo;

			//sorteia uma nova peca, define a altura como sendo o topo da tela, etc...
			idPecaAtual = "IJLOSTZ"[rand()%7];
			posicaoPecaAtual = largura/2-2;
			alturaPecaAtual = maxAltura;
			rotacaoPecaAtual = rand()%4;
			jogoComPecaCaindo.removeLinhasCompletas();	
			jogo = jogoComPecaCaindo;	
		}

    glutPostRedisplay();//Ao final recarrega o display
}

//
void game::handle_key(unsigned char key, int mousex, int mousey)
{

  switch(key)
  {
    case 'a':  case 'A' : game::game(KEY_LEFT); break;
    case 'w': case 'W' : game::game(KEY_UP); break;
    case 'd': case 'D' : game::game(KEY_RIGHT); break;
    case 's': case 'S' : game::game(KEY_DOWN); break;
    case ' ': game::game(KEY_SPACE); break;
    case 27: //codigo da tecla escape
             game_over = false;
             glutDestroyWindow(glutGetWindow()); //Destroi a janela atual
             menu::start(options);//retorna para o menu
             break;


  }
  if(glutGetWindow() != 0)//Checa se a janela existe
     //Redesenha após mudanca
    glutPostRedisplay();
}

void game::handle_special_key(int key, int x, int y){
  switch(key)
  {
    case  GLUT_KEY_UP : game::game(KEY_UP); break;
    case  GLUT_KEY_LEFT : game::game(KEY_LEFT); break;
    case  GLUT_KEY_RIGHT : game::game(KEY_RIGHT); break;
    case  GLUT_KEY_DOWN : game::game(KEY_DOWN); break;
  }
}

//Desenha um quadrado com bordas, cada um com uma cor
void game::drawSquare(int x, int y){
    side = (GLint) glutGet(GLUT_WINDOW_HEIGHT)/maxAltura;
    glLineWidth(1);
    glBegin(GL_QUADS);
      glColor3f(cores[cor][BORDA][0],cores[cor][BORDA][1],cores[cor][BORDA][2]);
      glVertex2i(x*side-1, y*side-1);
      glVertex2i(x*side+side+1, y*side-1);
      glVertex2i(x*side+side+1,y*side+side+1);
      glVertex2i(x*side-1, y*side+side+1);
    glEnd();
    glBegin(GL_QUADS);
      glColor3f(cores[cor][BLOCK][0], cores[cor][BLOCK][1], cores[cor][BLOCK][2]);
      glVertex2i(x*side, y*side);
      glVertex2i(x*side+side, y*side);
      glVertex2i(x*side+side, y*side+side);
      glVertex2i(x*side, y*side+side);
    glEnd();

}

//]utilizando a funcao anterior ddesenha todos os quadrados na tela
void game::drawSquares(const Tetris &jogoComPecaCaindo,int largura,int maxAltura){
    for(int i=0;i<maxAltura;i++) {
		    for(int j=0;j<largura;j++) {
            char c = jogoComPecaCaindo.get(j, maxAltura-i-1);
            if (c != ' ')
			          game::drawSquare(largura-j, maxAltura-i);
		    }
	  }
}
int grau = 0;
void game::display(void)
{
/*  clear all pixels  */
    glClear (GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    int x = glutGet(GLUT_WINDOW_WIDTH);
    int y = glutGet(GLUT_WINDOW_HEIGHT);

    if(game_over){ glLoadIdentity();

      int x = glutGet(GLUT_WINDOW_WIDTH);
      int y = glutGet(GLUT_WINDOW_HEIGHT);
      game::text("Voce Perdeu!", x/2-250, y/2, 0.4, 0.4);

    }else{ glLoadIdentity();

       if(modo==1)//modo bebado
          glRotatef(grau,0,0,1);
          //glTranslatef(x/2 , y/2, 0);
    }
      drawSquares(jogoComPecaCaindo, largura, maxAltura);
    glFlush ();
}

void game::init (void)
{
/*  select clearing (background) color       */

    glTranslatef(-250250,0 ,0);
    glClearColor (cores[cor][BACK][0], cores[cor][BACK][1], cores[cor][BACK][2], 1.0);
    game_over = false;
/*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, -100, 0.0, -100);
    side = (GLint) glutGet(GLUT_WINDOW_HEIGHT)/maxAltura;//define o side(lado) de cada quadrado proporcional a altura da tela
   //glViewport(0, 0 ,-200 , -400);
    glTranslatef(0,0,-290);
}
//Retirado do arquivo de aulas prática casinha.cpp aula viewPort
//com modificacao para centralizar o viewPort
void game::reshape(int w, int h){
  glViewport(w/2-largura*side/2,0.0,(GLsizei) w , (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
}

void game::timer(int)
{
  game::game(-1);
  glutPostRedisplay();
  glutTimerFunc(1000/speed, timer, 0);
}

//Começa uma janela de jogo. O parametro _options é um vetor com as opções que foram escolhidas no
//menu 
int game::start(bool _options[])
{
    for(int i =0; i<13; i++)
        options[i] = _options[i];
    setup(options);
    
    jogo = Tetris(largura);
    jogoComPecaCaindo = Tetris(largura);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (glutGet(GLUT_SCREEN_WIDTH)/2  - 500/2, glutGet(GLUT_SCREEN_HEIGHT)/2 - 500/2);
    glutCreateWindow ("Tetris");
    game::init ();
    glutKeyboardFunc(game::handle_key);
    glutSpecialFunc(game::handle_special_key);
    glutDisplayFunc(game::display);
    glutReshapeFunc(game::reshape);
    glutTimerFunc(1000.0/60.0, game::timer, 0);//game com aproximadamente 60 frames por segundo

    glutMainLoop();
    return 0; 
}

//Configura as variaveis de acordo com as opções escolhidas
void setup(bool options[]){
    if(options[1]){
        speed = 1;
    } if(options[2]){
        speed = 5;
    } if(options[3]){
        speed = 10;
    } if(options[4]){
        maxAltura = 20;
        largura = 10;
    } if(options[5]){
        maxAltura = 30;
        largura = 15;
    } if(options[6]){
        maxAltura = 50;
        largura = 25;
    } if(options[7]){
        cor = 0;
    } if(options[8]){
        cor = 1;
    } if(options[9]){
        cor = 2;
    } if(options[10]){
        modo = 0;
    } if(options[11]){
        modo = 1;
    }
}
