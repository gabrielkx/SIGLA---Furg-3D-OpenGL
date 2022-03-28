

#include <gl/glut.h>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



GLfloat angle, fAspect,button, state;

void Desenha(void);
void Inicializa (void);
void EspecificaParametrosVisualizacao(void);
void AlteraTamanhoJanela(GLsizei w, GLsizei h);
void letra_f();
void letra_g();
void letra_r();
void letra_u();



void Transposta(float matrix[4][4]) {
float aux;
   for (int i = 0; i < 4; i++) {
      for (int j = i; j >= 0;j--) {
          aux = matrix[i][j];
          matrix[i][j] = matrix[j][i];
          matrix[j][i] = aux;
      }
   }
}

void Translate(float dx, float dy, float dz) {
float matrix[4][4] = {{1,0,0,0},
                      {0,1,0,0},
                      {0,0,1,0},
                      {0,0,0,1}};
   matrix[0][3] = dx;
   matrix[1][3] = dy;
   matrix[2][3] = dz;
   Transposta(matrix);
   glMultMatrixf((float *) matrix);
}

void RotateX(float ang) {
float matrix[4][4] = {{1,0,0,0},
                      {0,1,0,0},
                      {0,0,1,0},
                      {0,0,0,1}};
   matrix[1][1] = cos(ang*M_PI/180);
   matrix[1][2] = -sin(ang*M_PI/180);
   matrix[2][1] = sin(ang*M_PI/180);
   matrix[2][2] = cos(ang*M_PI/180);
   Transposta(matrix);
   glMultMatrixf((float *) matrix);
}

void RotateY(float ang) {
float matrix[4][4] = {{1,0,0,0},
                      {0,1,0,0},
                      {0,0,1,0},
                      {0,0,0,1}};
   matrix[0][0] = cos(ang*M_PI/180);
   matrix[0][2] = sin(ang*M_PI/180);
   matrix[2][0] = -sin(ang*M_PI/180);
   matrix[2][2] = cos(ang*M_PI/180);
   Transposta(matrix);
   glMultMatrixf((float *) matrix);
}

void RotateZ(float ang) {
float matrix[4][4] = {{1,0,0,0},
                      {0,1,0,0},
                      {0,0,1,0},
                      {0,0,0,1}};

   matrix[0][0] = cos(ang*M_PI/180.0);
   matrix[0][1] = -sin(ang*M_PI/180.0);
   matrix[1][0] = sin(ang*M_PI/180.0);
   matrix[1][1] = cos(ang*M_PI/180.0);
   Transposta(matrix);
   glMultMatrixf((float *) matrix);
}



void Desenha (void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
    Translate(170, -218,0);
	letra_g();
	glPopMatrix();

    glPushMatrix();
    Translate(40,1,0);
    glScalef(1,-1,1);
    letra_r();
    glPopMatrix();

    glPushMatrix();

    glPushMatrix();
    glScalef( 1, -1, 1);
	letra_f();
    glPopMatrix();

    Translate(30,-245,0);
    RotateZ(90);
	glScalef( 1.65,0.8, 1);

    letra_u();
    glPopMatrix();


    glFlush();
	glutSwapBuffers();

}
void initLights(){
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
	GLfloat luzDifusa[4]={0.7,0.7,0.7,-.2};	   // "cor"
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho"
	GLfloat posicaoLuz[4]={0.0, -100.0, 250.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 60;
	// Define a refletância do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
	GLfloat mat_transparent[] = { 0.0, 0.8, 0.8, 0.6 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_transparent);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
	// Habilita a definição da cor do material
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
}
// Inicializa par�metros de rendering
void Inicializa (void)
{
 	// Especifica que a cor de fundo da janela ser� preta

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	angle=90; // angulo de visao

	//glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glShadeModel(GL_SMOOTH); // gourand



	// inicia configurações de iluminação
	initLights();

	// configura buffer de profundidade
	glEnable(GL_DEPTH_TEST);//visibilidade
}

// Fun��o usada para especificar o volume de visualiza��o
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();



	// Especifica a proje��o perspectiva(angulo,aspecto,zMin,zMax)
    glOrtho(-500.0, 500.0, -500.0, 500.0, 0.0, 2000);

	//gluPerspective(angle,fAspect,0.5,2000);

	gluLookAt(0,200,500, 0,0,0, 0,1,0);



   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();


}

// Fun��o callback chamada quando o tamanho da janela � alterado
 void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divis�o por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimens�es da viewport
	glViewport(0, 0, w, h);

	// Calcula a corre��o de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}





void keyboard2(unsigned char key, int x, int y)
{


	switch (key) {
		case 27:
			exit(0);
			break;
		case '1':
			// desliga luzes
			glDisable(GL_LIGHTING);
			break;
		case '2':
			// liga luzes
			glEnable(GL_LIGHTING);

			EspecificaParametrosVisualizacao();
			break;
}

   glutPostRedisplay();
}

void Keyboard(int key, int x, int y){
    if(key == GLUT_KEY_UP) {
		RotateX(5); // em x
    }
    else if(key == GLUT_KEY_DOWN) {
		RotateX(-5); // em -x
    }
	else if(key == GLUT_KEY_RIGHT) {
		RotateY(5); // em y
    }
	else if(key == GLUT_KEY_LEFT) {
		RotateY(-5); // em -y
    }

    glutPostRedisplay();
}



int main(int argc, char **argv){
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000,1000);
	glutCreateWindow("1� Trabalho - Letra E");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	glutSpecialFunc(Keyboard);
    glutKeyboardFunc(keyboard2);
	Inicializa();
	glutMainLoop();
}






void letra_f(void)
{



	glTranslatef(-300,0,0);


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(20.0, 10.0, 10.0);
		  glVertex3f(140.0, 10.0, 10.0);
		 glVertex3f(140.0, 10.0, -10.0);
		  glVertex3f(20.0, 10.0, -10.0);
	glEnd();


	// Parte 2


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(20.0, 10.0, -10.0);
		  glVertex3f(140.0, 10.0, -10.0);
		  glVertex3f(140.0, 40.0, -10.0);
		 glVertex3f(50.0, 40.0, -10.0);
	glEnd();


	// Parte 3

	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		 glVertex3f(20.0, 10.0, 10.0);
		  glVertex3f(140.0, 10.0, 10.0);
		  glVertex3f(140.0, 40.0, 10.0);
		  glVertex3f(50.0, 40.0, 10.0);
	glEnd();

	// Parte 4


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(140.0, 40.0, 10.0);
		  glVertex3f(140.0, 10.0, 10.0);
		  glVertex3f(140.0, 40.0, -10.0);
		 glVertex3f(140.0, 10.0, -10.0);
	glEnd();

	// Parte 5

	glBegin (GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
		 glVertex3f(140.0, 10.0, -10.0);
		  glVertex3f(140.0, 10.0, 10.0);
		  glVertex3f(140.0, 40.0, 10.0);
		  glVertex3f(140.0, 40.0, -10.0);
	glEnd();

	// Parte 6


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(140.0, 40.0, 10.0);
		  glVertex3f(50.0, 40.0, 10.0);
		   glVertex3f(50.0, 40.0, -10.0);
		   glVertex3f(140.0, 40.0, -10.0);
	glEnd();



	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(20.0, 10.0, -10.0);
		  glVertex3f(20.0, 10.0, 10.0);
		 glVertex3f(50.0, 40.0, 10.0);
		  glVertex3f(50.0, 40.0, -10.0);
	glEnd();


	//Parte 2



	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(50.0, 40.0, 10.0);
		   glVertex3f(50.0, 40.0,-10.0);
		   glVertex3f(50.0, 210.0,-10.0);
		  glVertex3f(50.0, 210.0,10.0);
	glEnd();

	//Parte 3



	glBegin (GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
		   glVertex3f(20.0, 210.0,10.0);
		  glVertex3f(20.0, 10.0,10.0);
		   glVertex3f(20.0, 10.0,-10.0);
		   glVertex3f(20.0, 210.0,-10.0);
	glEnd ();

	// Parte 4



	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(20.0, 210.0,10.0);
		  glVertex3f(20.0, 210.0,-10.0);
		   glVertex3f(50.0, 210.0,-10.0);
		   glVertex3f(50.0, 210.0,10.0);
	glEnd();

	// Parte 5 -



	glBegin (GL_QUADS);
		   glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(20.0, 10.0, -10.0);
		   glVertex3f(50.0, 40.0, -10.0);
		  glVertex3f(50.0, 210.0, -10.0);
	glEnd ();

	// Parte 6



	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
		  glVertex3f(20.0, 10.0, 10.0);
		   glVertex3f(50.0, 40.0, 10.0);
		   glVertex3f(50.0, 210.0, 10.0);
		   glVertex3f(20.0, 210.0, 10.0);
	glEnd ();



	// Parte 1
	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
		  glVertex3f(50.0, 130.0, 10.0);
		   glVertex3f(140.0, 130.0, 10.0);
		   glVertex3f(140.0, 100.0, 10.0);
		   glVertex3f(20.0, 100.0, 10.0);
	glEnd ();


	// Parte 2 -

	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(50.0, 130.0, -10.0);
		   glVertex3f(140.0, 130.0, -10.0);
		   glVertex3f(140.0, 100.0, -10.0);
		  glVertex3f(20.0, 100.0, -10.0);
	glEnd ();

	// Parte 3 -

	glBegin (GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
		  glVertex3f(140.0, 100.0, -10.0);
		   glVertex3f(140.0, 100.0, 10.0);
		   glVertex3f(140.0, 130.0, 10.0);
		   glVertex3f(140.0, 130.0, -10.0);
	glEnd();

	// Parte 4 -

	glBegin (GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
		   glVertex3f(140.0, 130.0, 10.0);
		   glVertex3f(140.0, 100.0, 10.0);
		   glVertex3f(140.0, 130.0, -10.0);
		  glVertex3f(140.0, 100.0, -10.0);
	glEnd();


		// Parte 5 -

   glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(20.0, 130.0, 10.0);
		  glVertex3f(140.0, 130.0, 10.0);
		   glVertex3f(140.0, 130.0, -10.0);
		   glVertex3f(20.0, 130.0, -10.0);
	glEnd ();

	// Parte 6

	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(20.0, 100.0, 10.0);
		   glVertex3f(140.0, 100.0, 10.0);
		  glVertex3f(140.0, 100.0, -10.0);
		   glVertex3f(20.0, 100.0, -10.0);
	glEnd ();
	glFlush ();
}

void letra_u(void){

glBegin (GL_QUADS);



        glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(20.0, 10.0, 10.0);
		  glVertex3f(140.0, 10.0, 10.0);
		 glVertex3f(140.0, 10.0, -10.0);
		  glVertex3f(20.0, 10.0, -10.0);
	glEnd();




	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(20.0, 10.0, -10.0);
		  glVertex3f(140.0, 10.0, -10.0);
		  glVertex3f(140.0, 40.0, -10.0);
		 glVertex3f(40.0, 40.0, -10.0);
	glEnd();




	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		 glVertex3f(20.0, 10.0, 10.0);
		  glVertex3f(140.0, 10.0, 10.0);
		  glVertex3f(140.0, 40.0, 10.0);
		  glVertex3f(40.0, 40.0, 10.0);
	glEnd();



	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(140.0, 40.0, 10.0);
		  glVertex3f(140.0, 10.0, 10.0);
		  glVertex3f(140.0, 40.0, -10.0);
		 glVertex3f(140.0, 10.0, -10.0);
	glEnd();



	glBegin (GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
		 glVertex3f(140.0, 10.0, -10.0);
		  glVertex3f(140.0, 10.0, 10.0);
		  glVertex3f(140.0, 40.0, 10.0);
		  glVertex3f(140.0, 40.0, -10.0);
	glEnd();


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(140.0, 40.0, 10.0);
		  glVertex3f(40.0, 40.0, 10.0);
		   glVertex3f(40.0, 40.0, -10.0);
		   glVertex3f(140.0, 40.0, -10.0);
	glEnd();



	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(20.0, 10.0, -10.0);
		  glVertex3f(20.0, 10.0, 10.0);
		 glVertex3f(40.0, 40.0, 10.0);
		  glVertex3f(40.0, 40.0, -10.0);
	glEnd();




	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(40.0, 40.0, 10.0);
		   glVertex3f(40.0, 40.0,-10.0);
		   glVertex3f(40.0, 210.0,-10.0);
		  glVertex3f(40.0, 210.0,10.0);
	glEnd();



	glBegin (GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
		   glVertex3f(20.0, 210.0,10.0);
		  glVertex3f(20.0, 10.0,10.0);
		   glVertex3f(20.0, 10.0,-10.0);
		   glVertex3f(20.0, 210.0,-10.0);
	glEnd ();



	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(20.0, 210.0,10.0);
		  glVertex3f(20.0, 210.0,-10.0);
		   glVertex3f(40.0, 210.0,-10.0);
		   glVertex3f(40.0, 210.0,10.0);
	glEnd();



	glBegin (GL_QUADS);
		   glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(20.0, 10.0, -10.0);
		   glVertex3f(40.0, 40.0, -10.0);
		  glVertex3f(40.0, 210.0, -10.0);
	glEnd ();


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
		  glVertex3f(20.0, 10.0, 10.0);
		   glVertex3f(50.0, 40.0, 10.0);
		   glVertex3f(50.0, 210.0, 10.0);
		   glVertex3f(20.0, 210.0, 10.0);
	glEnd ();


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
		  glVertex3f(20.0, 210.0, 10.0);
		   glVertex3f(140.0, 210.0, 10.0);
		   glVertex3f(140.0, 180.0, 10.0);
		   glVertex3f(50.0, 180.0, 10.0);
	glEnd ();



	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(20.0, 210.0, -10.0);
		   glVertex3f(140.0, 210.0, -10.0);
		   glVertex3f(140.0, 180.0, -10.0);
		  glVertex3f(50.0, 180.0, -10.0);
	glEnd ();


	glBegin (GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
		  glVertex3f(140.0, 180.0, -10.0);
		   glVertex3f(140.0, 180.0, 10.0);
		   glVertex3f(140.0, 210.0, 10.0);
		   glVertex3f(140.0, 210.0, -10.0);
	glEnd();


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(140.0, 210.0, 10.0);
		   glVertex3f(140.0, 180.0, 10.0);
		   glVertex3f(140.0, 210.0, -10.0);
		  glVertex3f(140.0, 180.0, -10.0);
	glEnd();


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(20.0, 210.0, 10.0);
		  glVertex3f(140.0, 210.0, 10.0);
		   glVertex3f(140.0, 210.0, -10.0);
		   glVertex3f(20.0, 210.0, -10.0);
	glEnd ();


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(20.0, 180.0, 10.0);
		   glVertex3f(140.0, 180.0, 10.0);
		  glVertex3f(140.0, 180.0, -10.0);
		  glVertex3f(20.0, 180.0, -10.0);
	glEnd ();

   glFlush();

}





void letra_r (){
    glPushMatrix();
    RotateZ(-10);
    Translate(-25,5,0);

        glBegin (GL_QUADS);
        glNormal3f(0.0, 0.0, -1.0);
		  glVertex3f(80.0, 120, 10.0);
		   glVertex3f(110.0, 220, 10.0);
		   glVertex3f(110.0, 220, 10.0);
		   glVertex3f(80.0, 120, 10.0);
	glEnd ();


         // parte 1

    glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(80.0, 120, -10.0);
		  glVertex3f(80.0, 120, 10.0);
		 glVertex3f(110.0, 220.0, 10.0);
		  glVertex3f(110.0, 220.0, -10.0);
	glEnd();


            // parte 2

	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(110.0, 120, 10.0);
		   glVertex3f(110.0, 120.0,-10.0);
		   glVertex3f(110.0, 220.0,-10.0);
		  glVertex3f(110.0, 220.0,10.0);
	glEnd();

                // parte 3
	glBegin (GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
		   glVertex3f(80.0, 220,10.0);
		  glVertex3f(80.0, 120,10.0);
		   glVertex3f(80.0, 120,-10.0);
		   glVertex3f(80.0, 220,-10.0);
	glEnd ();


            // parte 4
	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(80.0, 220.0,10.0);
		  glVertex3f(80.0, 220.0,-10.0);
		   glVertex3f(110.0, 220.0,-10.0);
		   glVertex3f(110.0, 220.0,10.0);
	glEnd();


            // parte 5
	glBegin (GL_QUADS);
		   glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(80.0, 120, -10.0);
		   glVertex3f(110.0, 120.0, -10.0);
		  glVertex3f(110.0, 220, -10.0);
	glEnd ();


        // parte 6
	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
		  glVertex3f(80.0, 120, 10.0);
		   glVertex3f(110.0, 120.0, 10.0);
		   glVertex3f(110.0, 220.0, 10.0);
		   glVertex3f(80.0, 220, 10.0);


	glEnd ();

    glPopMatrix();

    //parte 1


    glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(80.0, 40.0, -10.0);
		  glVertex3f(80.0, 40.0, 10.0);
		 glVertex3f(110.0, 100.0, 10.0);
		  glVertex3f(110.0, 100.0, -10.0);
	glEnd();


	//Parte 2


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(110.0, 40.0, 10.0);
		   glVertex3f(110.0, 40.0,-10.0);
		   glVertex3f(110.0, 100.0,-10.0);
		  glVertex3f(110.0, 100.0,10.0);
	glEnd();

	//Parte 3


	glBegin (GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
		   glVertex3f(80.0, 100.0,10.0);
		  glVertex3f(80.0, 40.0,10.0);
		   glVertex3f(80.0, 40.0,-10.0);
		   glVertex3f(80.0, 100.0,-10.0);
	glEnd ();

	// Parte 4


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(80.0, 40.0,10.0);
		  glVertex3f(80.0, 40.0,-10.0);
		   glVertex3f(110.0, 100.0,-10.0);
		   glVertex3f(110.0, 100.0,10.0);
	glEnd();

	// Parte 5 -


	glBegin (GL_QUADS);
		   glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(80.0, 40.0, -10.0);
		   glVertex3f(110.0, 40.0, -10.0);
		  glVertex3f(110.0, 100, -10.0);
	glEnd ();

	// Parte 6 -


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
		  glVertex3f(80.0, 40.0, 10.0);
		   glVertex3f(110.0, 40.0, 10.0);
		   glVertex3f(110.0, 100.0, 10.0);
		   glVertex3f(80.0, 100.0, 10.0);
	glEnd ();





    // parte 1


        glBegin (GL_QUADS);
        glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(20.0, 10.0, 10.0);
		  glVertex3f(110.0, 10.0, 10.0);
		 glVertex3f(110.0, 10.0, -10.0);
		  glVertex3f(20.0, 10.0, -10.0);
        glEnd();


	// Parte 2
	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(50.0, 10.0, -10.0);
		  glVertex3f(110.0, 10.0, -10.0);
		  glVertex3f(110.0, 40.0, -10.0);
		 glVertex3f(50.0, 40.0, -10.0);
	glEnd();


	// Parte 3

	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		 glVertex3f(20.0, 10.0, 10.0);
		  glVertex3f(110.0, 10.0, 10.0);
		  glVertex3f(110.0, 40.0, 10.0);
		  glVertex3f(50.0, 40.0, 10.0);
	glEnd();

	// Parte 4


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(110, 40.0, 10.0);
		  glVertex3f(110.0, 10.0, 10.0);
		  glVertex3f(110.0, 40.0, -10.0);
		 glVertex3f(110.0, 10.0, -10.0);
	glEnd();

	// Parte 5


	glBegin (GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
		 glVertex3f(110, 10.0, -10.0);
		  glVertex3f(110.0, 10.0, 10.0);
		  glVertex3f(110.0, 40.0, 10.0);
		  glVertex3f(110.0, 40.0, -10.0);
	glEnd();

	// Parte 6



	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(110.0, 40.0, 10.0);
		  glVertex3f(50.0, 40.0, 10.0);
		   glVertex3f(50.0, 40.0, -10.0);
		   glVertex3f(110.0, 40.0, -10.0);


glEnd();




	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(20.0, 10.0, -10.0);
		  glVertex3f(20.0, 10.0, 10.0);
		 glVertex3f(50.0, 40.0, 10.0);
		  glVertex3f(50.0, 40.0, -10.0);
	glEnd();


	//Parte 2 -


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(50.0, 40.0, 10.0);
		   glVertex3f(50.0, 40.0,-10.0);
		   glVertex3f(50.0, 210.0,-10.0);
		  glVertex3f(50.0, 210.0,10.0);
	glEnd();

	//Parte 3 -


	glBegin (GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
		   glVertex3f(20.0, 210.0,10.0);
		  glVertex3f(20.0, 10.0,10.0);
		   glVertex3f(20.0, 10.0,-10.0);
		   glVertex3f(20.0, 210.0,-10.0);
	glEnd ();

	// Parte 4


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(20.0, 210.0,10.0);
		  glVertex3f(20.0, 210.0,-10.0);
		   glVertex3f(50.0, 210.0,-10.0);
		   glVertex3f(50.0, 210.0,10.0);
	glEnd();

	// Parte 5 -


	glBegin (GL_QUADS);
		   glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(20.0, 10.0, -10.0);
		   glVertex3f(50.0, 40.0, -10.0);
		  glVertex3f(50.0, 210.0, -10.0);
	glEnd ();

	// Parte 6

	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
		  glVertex3f(20.0, 10.0, 10.0);
		   glVertex3f(50.0, 40.0, 10.0);
		   glVertex3f(50.0, 210.0, 10.0);
		   glVertex3f(20.0, 210.0, 10.0);
	glEnd ();

        // parte 1//
        glBegin (GL_QUADS);
	    //glPushMatrix();
	    //Translate(100,1,1);

	glNormal3f(0.0, 0.0, -1.0);
		  glVertex3f(50.0, 130.0, 10.0);
		   glVertex3f(110.0, 130.0, 10.0);
		   glVertex3f(110.0, 100.0, 10.0);
		   glVertex3f(20.0, 100.0, 10.0);
	glEnd ();


	// Parte 2

	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(50.0, 130.0, -10.0);
		   glVertex3f(110.0, 130.0, -10.0);
		   glVertex3f(110.0, 100.0, -10.0);
		  glVertex3f(20.0, 100.0, -10.0);
	glEnd ();

	// Parte 3

	glBegin (GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
		  glVertex3f(110.0, 100.0, -10.0);
		   glVertex3f(110.0, 100.0, 10.0);
		   glVertex3f(110.0, 130.0, 10.0);
		   glVertex3f(110.0, 130.0, -10.0);
	glEnd();

	// Parte 4

	glBegin (GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
		   glVertex3f(110.0, 130.0, 10.0);
		   glVertex3f(110.0, 100.0, 10.0);
		   glVertex3f(110.0, 130.0, -10.0);
		  glVertex3f(110.0, 100.0, -10.0);
	glEnd();


		// Parte 5

   glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(20.0, 130.0, 10.0);
		  glVertex3f(110.0, 130.0, 10.0);
		   glVertex3f(110.0, 130.0, -10.0);
		   glVertex3f(20.0, 130.0, -10.0);
	glEnd ();

	// Parte 6

	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(20.0, 100.0, 10.0);
		   glVertex3f(110.0, 100.0, 10.0);
		  glVertex3f(110.0, 100.0, -10.0);
		   glVertex3f(20.0, 100.0, -10.0);
	glEnd ();
    glPopMatrix();


	glFlush ();

}


void letra_g(void){




    glPushMatrix();
    RotateZ(90);
    Translate(0,-150,0);
    glBegin (GL_QUADS);
            // parte 1
	glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(20.0, 10.0, 10.0);
		  glVertex3f(100.0, 10.0, 10.0);
		 glVertex3f(100.0, 10.0, -10.0);
		  glVertex3f(20.0, 10.0, -10.0);
	glEnd();


	// Parte 2 - Parte de Trás


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(20.0, 10.0, -10.0);
		  glVertex3f(100.0, 10.0, -10.0);
		  glVertex3f(100.0, 40.0, -10.0);
		 glVertex3f(40.0, 40.0, -10.0);
	glEnd();


	// Parte 3 - Parte de Frente


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		 glVertex3f(20.0, 10.0, 10.0);
		  glVertex3f(100.0, 10.0, 10.0);
		  glVertex3f(100.0, 40.0, 10.0);
		  glVertex3f(40.0, 40.0, 10.0);
	glEnd();

	// Parte 4 - Parte do lado direito


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(100.0, 40.0, 10.0);
		  glVertex3f(100.0, 10.0, 10.0);
		  glVertex3f(100.0, 40.0, -10.0);
		 glVertex3f(100.0, 10.0, -10.0);
	glEnd();

            // parte 5

	glBegin (GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
		 glVertex3f(100.0, 10.0, -10.0);
		  glVertex3f(100.0, 10.0, 10.0);
		  glVertex3f(100.0, 40.0, 10.0);
		  glVertex3f(100.0, 40.0, -10.0);
	glEnd();



            //parte 6
	glBegin (GL_QUADS);

	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(100.0, 40.0, 10.0);
		  glVertex3f(40.0, 40.0, 10.0);
		   glVertex3f(40.0, 40.0, -10.0);
		   glVertex3f(100.0, 40.0, -10.0);
	glEnd();
glPopMatrix();

glPushMatrix();
Translate(0,80,0);

//              parte1
glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(20.0, 10.0, 10.0);
		  glVertex3f(140.0, 10.0, 10.0);
		 glVertex3f(140.0, 10.0, -10.0);
		  glVertex3f(20.0, 10.0, -10.0);
	glEnd();


	// Parte 2 - Parte de Trás



	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(20.0, 10.0, -10.0);
		  glVertex3f(140.0, 10.0, -10.0);
		  glVertex3f(140.0, 40.0, -10.0);
		 glVertex3f(40.0, 40.0, -10.0);
	glEnd();


	// Parte 3
	;

	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		 glVertex3f(20.0, 10.0, 10.0);
		  glVertex3f(140.0, 10.0, 10.0);
		  glVertex3f(140.0, 40.0, 10.0);
		  glVertex3f(40.0, 40.0, 10.0);
	glEnd();

	// Parte 4


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(140.0, 40.0, 10.0);
		  glVertex3f(140.0, 10.0, 10.0);
		  glVertex3f(140.0, 40.0, -10.0);
		 glVertex3f(140.0, 10.0, -10.0);
	glEnd();



	glBegin (GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
		 glVertex3f(140.0, 10.0, -10.0);
		  glVertex3f(140.0, 10.0, 10.0);
		  glVertex3f(140.0, 40.0, 10.0);
		  glVertex3f(140.0, 40.0, -10.0);
	glEnd();



            //parte 6 */
	glBegin (GL_QUADS);

	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(140.0, 40.0, 10.0);
		  glVertex3f(40.0, 40.0, 10.0);
		   glVertex3f(40.0, 40.0, -10.0);
		   glVertex3f(140.0, 40.0, -10.0);
	glEnd();
glPopMatrix();
                    //parte 1
	glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(20.0, 10.0, 10.0);
		  glVertex3f(140.0, 10.0, 10.0);
		 glVertex3f(140.0, 10.0, -10.0);
		  glVertex3f(20.0, 10.0, -10.0);
	glEnd();


	// Parte 2 - Parte de Trás


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(20.0, 10.0, -10.0);
		  glVertex3f(140.0, 10.0, -10.0);
		  glVertex3f(140.0, 40.0, -10.0);
		 glVertex3f(40.0, 40.0, -10.0);
	glEnd();


	// Parte 3 - Parte de Frente


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		 glVertex3f(20.0, 10.0, 10.0);
		  glVertex3f(140.0, 10.0, 10.0);
		  glVertex3f(140.0, 40.0, 10.0);
		  glVertex3f(40.0, 40.0, 10.0);
	glEnd();

	// Parte 4 - Parte do lado direito


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(140.0, 40.0, 10.0);
		  glVertex3f(140.0, 10.0, 10.0);
		  glVertex3f(140.0, 40.0, -10.0);
		 glVertex3f(140.0, 10.0, -10.0);
	glEnd();

	// Parte 5 - Parte do lado esquerdo (para tapar a zona do traço)


	glBegin (GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
		 glVertex3f(140.0, 10.0, -10.0);
		  glVertex3f(140.0, 10.0, 10.0);
		  glVertex3f(140.0, 40.0, 10.0);
		  glVertex3f(140.0, 40.0, -10.0);
	glEnd();

	// Parte 6 - Parte de cima


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(140.0, 40.0, 10.0);
		  glVertex3f(40.0, 40.0, 10.0);
		   glVertex3f(40.0, 40.0, -10.0);
		   glVertex3f(140.0, 40.0, -10.0);
	glEnd();



	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		  glVertex3f(20.0, 10.0, -10.0);
		  glVertex3f(20.0, 10.0, 10.0);
		 glVertex3f(40.0, 40.0, 10.0);
		  glVertex3f(40.0, 40.0, -10.0);
	glEnd();




	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(40.0, 40.0, 10.0);
		   glVertex3f(40.0, 40.0,-10.0);
		   glVertex3f(40.0, 210.0,-10.0);
		  glVertex3f(40.0, 210.0,10.0);
	glEnd();

	//Parte 3 - Parte do lado esquerdo


	glBegin (GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
		   glVertex3f(20.0, 210.0,10.0);
		  glVertex3f(20.0, 10.0,10.0);
		   glVertex3f(20.0, 10.0,-10.0);
		   glVertex3f(20.0, 210.0,-10.0);
	glEnd ();

	// Parte 4 - Parte de cima


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(20.0, 210.0,10.0);
		  glVertex3f(20.0, 210.0,-10.0);
		   glVertex3f(40.0, 210.0,-10.0);
		   glVertex3f(40.0, 210.0,10.0);
	glEnd();

	// Parte 5 - Parte de Trás


	glBegin (GL_QUADS);
		   glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(20.0, 10.0, -10.0);
		   glVertex3f(40.0, 40.0, -10.0);
		  glVertex3f(40.0, 210.0, -10.0);
	glEnd ();

	// Parte 6 - Parte de Frente


	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
		  glVertex3f(20.0, 10.0, 10.0);
		   glVertex3f(50.0, 40.0, 10.0);
		   glVertex3f(50.0, 210.0, 10.0);
		   glVertex3f(20.0, 210.0, 10.0);
	glEnd ();



	// Parte 1 - Parte de Frente

	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
		  glVertex3f(20.0, 210.0, 10.0);
		   glVertex3f(140.0, 210.0, 10.0);
		   glVertex3f(140.0, 180.0, 10.0);
		   glVertex3f(50.0, 180.0, 10.0);
	glEnd ();

	// Parte 2 - Parte de Trás

	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(20.0, 210.0, -10.0);
		   glVertex3f(140.0, 210.0, -10.0);
		   glVertex3f(140.0, 180.0, -10.0);
		  glVertex3f(50.0, 180.0, -10.0);
	glEnd ();

	// Parte 3 - Parte do Lado Esquerdo

	glBegin (GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
		  glVertex3f(140.0, 180.0, -10.0);
		   glVertex3f(140.0, 180.0, 10.0);
		   glVertex3f(140.0, 210.0, 10.0);
		   glVertex3f(140.0, 210.0, -10.0);
	glEnd();

	// Parte 4 - Parte do Lado Direito

	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(140.0, 210.0, 10.0);
		   glVertex3f(140.0, 180.0, 10.0);
		   glVertex3f(140.0, 210.0, -10.0);
		   glVertex3f(140.0, 180.0, -10.0);
	glEnd();

	// Parte 5 - Parte de Cima

	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(20.0, 210.0, 10.0);
		  glVertex3f(140.0, 210.0, 10.0);
		   glVertex3f(140.0, 210.0, -10.0);
		   glVertex3f(20.0, 210.0, -10.0);
	glEnd ();

	// Parte 6 - Parte de Baixo

	glBegin (GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
		   glVertex3f(20.0, 180.0, 10.0);
		   glVertex3f(140.0, 180.0, 10.0);
		  glVertex3f(140.0, 180.0, -10.0);
		  glVertex3f(20.0, 180.0, -10.0);
	glEnd ();

   glFlush();

}


