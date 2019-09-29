#include <GL/freeglut.h>
#include "INF390.h"

void INF390::texto(const std::string &texto, int x, int y, double tamanhoX, double tamanhoY) {
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(x, y, 0);
    glScalef(tamanhoX, tamanhoY, 1.0);
    for(int i = 0; i < texto.length(); ++i) {
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, texto[i]);
    }
    glPopMatrix();
}