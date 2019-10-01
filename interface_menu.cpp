#include  <GL/glut.h>
#include <string>
#include <iostream>

#include "game.h"

struct Button {
    bool green, selected;
    std::string text;
    void *action;
    
    Button(std::string itext, bool g, bool s){
      this->green = g;
      this->selected = s;
      text = itext;
     }
};

void texto(const std::string &texto, int x, int y, double tamanhoX, double tamanhoY) {
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

Button buttons[] = { Button("INICIAR", true, true),
                    Button("NORMAL",false,false),
                    Button("RAPIDO",true,false ),
                    Button("TURBO", true,false ),
                    Button("20x10", false,false),
                    Button("30x15", true,false ),
                    Button("50x25", true,false ),
                    Button("CORES1",false,false),
                    Button("CORES2",true,false),
                    Button("CORES3",true,false),
                    Button("NORMAL",false,false),
                    Button("BEBADO",true,false),
                    Button("SAIR",  true,false) };//[0-12]


#include "interface_menu.h"

void handle_special_key(int key, int mousex, int mousey)
{
  int index = 0;
  bool selected[13];
  for(int i = 0; i < 13; i++){ //Verifica se já existe um botao selecionado
      if(buttons[i].selected == true){
          index = i;
          buttons[i].selected = false;
      } 
   }

  switch(key)//Determina qual o indice de opções deve-se ir com base na tecla pressionada
  {//Up Down muda de grupo, Left right avanca uma unidade no grupo
    case GLUT_KEY_RIGHT:
      if(index == 0){/*faz nada*/}      
      else if(index > 0 && index < 10)
        index = (index%3==0)?index-2:index+1;
      else if(index >= 10 && index < 12)
        index = (index==11)?index-1:index+1;
      else {/*do nothing*/}
      break;
    case GLUT_KEY_LEFT:
      if(index == 0){/*do nothing*/}
      else if(index > 0 && index < 10)
        index = (index%3==1)?index+2:index-1;
      else if(index >= 10 && index < 12)
        index = (index==10)?index+1:index-1;
      else {}
      break;

    case GLUT_KEY_DOWN:
      if(index == 0) index = index + 1;
      else if(index > 0 && index <10) index = index + 3;
      else if(index >= 10 && index < 12) index = 12;
      else index = 0;
      break;

    case GLUT_KEY_UP:
      if(index == 0) index = 12;
      else if(index > 0 && index <10) index = index - 3;
      else if(index >= 10 && index < 12) index = index = index - 2;
      else index = index = index - 2;
      break;

    case 13: //Enter key
      //Determina que acao tomar uma vez que se tem um indice e a tecla enter foi pressionada
      if (index == 0) //start game
      {
          bool options[13];
          for(int i = 0; i<13; i++) options[i] = !(buttons[i].green);
          glutDestroyWindow(glutGetWindow());
          game::start(options);
      }
      else if (index >= 1 && index <= 3){
         for(int i = 1; i<=3; i++)
            buttons[i].green = true;
      }
      else if (index >= 4 && index <= 6){
        for(int i = 4; i<=6; i++){
          buttons[i].green = true;
        }
      }

      else if (index >= 7 && index <= 9){
        for(int i = 7; i<=9; i++)
          buttons[i].green = true;
      }

      else if (index >= 10 && index <= 11){
        for(int i = 10; i<=11; i++)
          buttons[i].green = true;
      }

      else if (index == 12){
          glutDestroyWindow(glutGetWindow());
      }

      buttons[index].green = false;
      break;
  }//End of Switch
  index = (index>12)?12:index;
  index = (index<0)?0:index;
  buttons[index].selected = true;
    if(glutGetWindow()!=0)
        glutPostRedisplay();
}

//Faz com que a mesma função cuide das teclas ASCII e as teclas especiais
void handle_key(unsigned char key, int x, int y){
   handle_special_key((int) key, x, y);
}

//Desenha um Botão nas coordenadas (x,y)
void drawButton(Button &button,  int x, int y) {
    
    int height = glutGet(500)/20;
    int width = glutGet(500)/5;
    glBegin(GL_QUADS);
        if(button.selected){
          int offset = 3;//É o que determina a borda vermelha de selecao
          //Desenha-se um quadrado vermelho um pouco maior que o tamanho do botao
          glColor3f(1,0,0);
          glVertex2i(x-offset, y-offset);
          glVertex2i(x+width+offset, y-offset);
          glVertex2i(x+width+offset, y+height+offset);
          glVertex2i(x-offset, y+height+offset);
        }
        //]desenha um quadrado azul ou verde um pouco menor que o quadrado vermelho anterior
        //mas por cima dele. Isso provoca um efeito de borda
        if(button.green)
          glColor3f(0,1,0);
        else
          glColor3f(0,0,1);
        glVertex2i( x,  y);
        glVertex2i( x+width, y);
        glVertex2i( x+width, y+height);
        glVertex2i( x, y+height);
    glEnd();
       
    texto(button.text, x, y+height/4, 0.1 , 0.1);

}

void display(void)
{
/*  clear all pixels  */
    glClear (GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
        
    int xoffset = glutGet(500)/4;//espaco horizontal entre os botoes
    int yoffset = glutGet(500)/6;//espaco vertical entre os botoes
    
    //desenha o botao iniciar
    drawButton(buttons[0],(glutGet(GLUT_WINDOW_WIDTH)/2)- xoffset/2, glutGet(GLUT_WINDOW_HEIGHT)-yoffset);

    //Determina um inicio, entao desenha os 9 proximos botoes
    int xstart = glutGet(GLUT_WINDOW_WIDTH)/2-1.5*xoffset;
    int ystart = glutGet(GLUT_WINDOW_HEIGHT)-2*yoffset;


    int y = ystart;
    int x = xstart;
    for(int i = 1; i <= 9; i++){
        drawButton(buttons[i],x, y);
        x += xoffset;
        
        if(i%3==0) {
          y-= yoffset;
          x = xstart;
        }
    }
    //desenha os botoes de modo normal e bebado
    drawButton(buttons[10], x, y);
    drawButton(buttons[11], x+xoffset, y);
    //desenha o botão sair
    drawButton(buttons[12], x+xoffset, y-yoffset);
   
    int _x = glutGet(GLUT_WINDOW_WIDTH);
    int _y = glutGet(GLUT_WINDOW_HEIGHT);
    texto("Velocidade", _x/2-50, _y-1.5*yoffset, 0.1, 0.1);
    texto("Tamanho", (_x/2-50),_y-2.5*yoffset, 0.1, 0.1);
    texto("Cores",(_x/2-50), _y-3.5*yoffset, 0.1, 0.1);
    texto("Modo", (_x/2-50), _y-4.5*yoffset, 0.1,0.1);
   glFlush ();
}

void init (void)
{
/*  select clearing (background) color       */
    glClearColor (1.0, 1.0, 1.0, 1.0);

/*  initialize viewing values  */
}

void reshape(int w, int h){
  glViewport(0.0,0.0,(GLsizei) w , (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (glutGet(GLUT_SCREEN_WIDTH)/2  - 500/2, glutGet(GLUT_SCREEN_HEIGHT)/2 - 500/2);
    glutCreateWindow ("MENU");
    init ();
    glutKeyboardFunc(handle_key);
    glutSpecialFunc(handle_special_key);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;   /* ISO C requires main to return int. */
}

//Funcão que recria a janela de menu quando se sai do jogo
int menu::start(bool options[]){
    buttons[0].selected = true;
    for(int i =0; i< 12; i++){
      buttons[i].green = !options[i];
    }
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (glutGet(GLUT_SCREEN_WIDTH)/2  - 500/2, glutGet(GLUT_SCREEN_HEIGHT)/2 - 500/2);
    glutCreateWindow ("MENU");
    init ();
    glutKeyboardFunc(handle_key);
    glutSpecialFunc(handle_special_key);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    return 0;
    
}
int menu::start(){
  bool v[] = {false, true, false, false, true, false, false, true, false, false, true, false, false, false};
  return menu::start(v);
}
