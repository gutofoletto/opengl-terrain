/**
*   Antônio Augusto Foletto
*   gutofoletto@gmail.com
*
*   √ Implmentar um terreno com matrizes
*   √ Implementar uma camera com gluLookAt() que possa se mover
*   √ Projeção em perspectiva
*   √ Visualização em Wireframe do Terreno
**/

#if defined(__APPLE__) && defined(__MACH__)
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "terrain.h"

#define SCREEN_X 800
#define SCREEN_Y 600

int   polygonMode = 0;
float rx = 0.0f, rz = 0.0f;

float abertura = 140.0f;
float znear  = 1.0f;
float zfar   = 20.0f;
float aspect = 1.0f;

int r, c;

Terrain *t = new Terrain(50, 50);



void init() {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluPerspective(abertura, aspect, znear, zfar);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(0, 0, 0, 1);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING) ;
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    //glColorMaterial(GL_FRONT,GL_DIFFUSE);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );

    gluPerspective(abertura, aspect, znear, zfar);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity( );
    gluLookAt(
        0, 3, 10,  //from. Posicao onde a camera esta posicionada
        0, 0, 0,  //to. Posicao absoluta onde a camera esta vendo
        0, 1, 0
    ); //up. Vetor Up.

    glRotatef ((GLfloat) rx, 0.0f, 1.0f, 0.0f);
    glRotatef ((GLfloat) rz, 1.0f, 0.0f, 0.0f);

    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glColor3f(.1, .9, .1);
    r = -(t->rows/2);
    for(int x = 0; x < t->rows-1; x++){
        c = -(t->cols/2);
        for(int z = 0; z < t->cols-1; z++){
            glNormal3f(0, t->points[x][z], 0);
            glVertex3f(r, t->points[x][z], c);
            //glNormal3f(0, t->points[x+1][z], 0);
            glVertex3f(r+1, t->points[x+1][z], c);
            //glNormal3f(0, t->points[x+1][z+1], 0);
            glVertex3f(r+1, t->points[x+1][z+1], c+1);
            //glNormal3f(0, t->points[x][z+1], 0);
            glVertex3f(r, t->points[x][z+1], c+1);
            c++;
        }
        r++;
    }
    glEnd();

    glutSwapBuffers();
}


//faz a leitura da entrada do usuario
void keyboard(unsigned char key, int x, int y) {
    //printf("%d", key);
    //key = tolower(key);
    switch(key)
    {
        case 27:
            exit(0);
            break;
        case 200:
            //left
            break;
        case 201:
            //up
            break;
        case 202:
            //right
            break;
        case 203:
            //down
            break;
        case 'w':
            //wireframe
            if(polygonMode==1) {
                polygonMode=0;
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
            else{
                polygonMode=1;
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            } break;
        case '+':
            abertura++;
            break;
        case '-':
            abertura--;
            break;
    }
}

void MotionFunc(int x, int y) {
    rx = x;
    rz = y;
}

void MouseFunc(int botao, int estado, int x, int y) {
    //printf("\n%d %d %d %d", botao, estado, x, y);
}

int main () {
    int  argc=1;
    char *argv[1] = {"teste"};
    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    glutInitWindowSize (SCREEN_X, SCREEN_Y);
    glutInitWindowPosition (450, 10);
    /* create window */
    glutCreateWindow ("Terrain OpenGL");
    printf("Digite W para mudar o modo de visualizacao: wireframe/fill");

    glutDisplayFunc(display);
    glutMotionFunc(MotionFunc);
    glutMouseFunc(MouseFunc);
    glutIdleFunc(display);
    glutKeyboardFunc(keyboard);

    init();
    glutMainLoop();
    return 0;
}
