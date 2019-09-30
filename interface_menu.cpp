//#ingure -clude <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "INF390.h"


double scale = 1;
bool reflectX = 0;
bool reflectY = 0;
double offsetX = 0;
double offsetY = 0;
double rot=0;

void handle_key(unsigned char key, int mousex, int mousey)
{

  switch(key)
  {
    case 'a':  case 'A' : if(scale<10) scale+=1; break;
//    case ('d' or 'D') : /*reduz escala ... */break;


  }

  //Redesenha após atualizar valor da escala
  glutPostRedisplay();
}

void testeFunc(){
  std::cout << "It's working!" << std::endl;
}

struct Button {
    bool green, selected;
    std::string text;
    void *action;
    
    Button(std::string text, bool g, bool s, void (*func)()){
      this->green = g;
      this->selected = s;
      this->text = text;
     *action = func;
    }
};

Button buttons[] = { Button("INICIAR", false, false, testeFunc),
                    Button("NORMAL",false,false, testeFunc),
                    Button("RAPIDO",false,false, testeFunc),
                    Button("TURBO",false,false, testeFunc),
                    Button("20x10",false,false, testeFunc),
                    Button("30x15",false,false, testeFunc),
                    Button("50x25",false,false, testeFunc),
                    Button("CORES1",false,false, testeFunc),
                    Button("CORES2",false,false, testeFunc),
                    Button("CORES3",false,false, testeFunc),
                    Button("NORMAL",false,false, testeFunc),
                    Button("BEBADO",false,false, testeFunc),
                    Button("SAIR",false,false, testeFunc) };//[0-12]

void drawButton(Button &button,  int x, int y) {
    
    button.action();
    int height, width;
    height=10;
    width=35;
    glLineWidth(1);
    std::cout << button.text << std::endl; 
    glBegin(GL_QUADS);
        if(button.selected){
          int offset = 1;
          glColor3f(1,0,0);
          glVertex2i(x-offset, y-offset);
          glVertex2i(x+width+offset, y-offset);
          glVertex2i(x+width+offset, y+height+offset);
          glVertex2i(x-offset, y+height+offset);
        } 
        if(button.green)
          glColor3f(0,1,0);
        else
          glColor3f(0,0,1);
        glVertex2i( x,  y);
        glVertex2i( x+width, y);
        glVertex2i( x+width, y+height);
        glVertex2i( x, y+height);
        glEnd();
        glColor3f(1,1,1);
        INF390::texto(button.text, x, y, width, height);

}

void display(void)
{
/*  clear all pixels  */
    glClear (GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
        
    int xoffset = 40;
    int yoffset = 40;

    drawButton(buttons[0], -20, 80);

    int xstart = -50, ystart = 60;
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
    drawButton(buttons[10], x, y);
    drawButton(buttons[11], x+xoffset, y);
    drawButton(buttons[12], x+xoffset, y+yoffset);
    INF390::texto("Velocidade", 0,0, 10, 30);
   glFlush ();
}

void init (void)
{
/*  select clearing (background) color       */
    glClearColor (1.0, 1.0, 1.0, 1.0);

/*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Menu");
    init ();
    glutKeyboardFunc(handle_key);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;   /* ISO C requires main to return int. */
}
