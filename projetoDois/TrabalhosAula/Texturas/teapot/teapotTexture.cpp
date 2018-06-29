#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>

/* globals */
GLint Width;
GLint Height;

static GLfloat spin = 0.0;

GLfloat origin_x = 0.0;
GLfloat origin_y = 0.0;
GLfloat origin_z = 0.0;

// textura
GLuint      texture[3], indiceTextura=0;
int LoadGLTextures() // Load Bitmaps And Convert To Textures
{
    /* load an image file directly as a new OpenGL texture */
    texture[0] = SOIL_load_OGL_texture ( "c:\\utfpr.jpg",
        SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texture[1] = SOIL_load_OGL_texture ( "c:\\grass.bmp",
        SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texture[2] = SOIL_load_OGL_texture ( "c:\\cap.jpg",
        SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    if(texture[0] == 0 || texture[1] == 0 || texture[2] == 0){
        return false;
    }
    // Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	glEnable(GL_TEXTURE_2D);			    // Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);			    // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Black Background
	glClearDepth(1.0f);						// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);				// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);					// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

    return true; // Return Success
}

void cubo(void){
  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  glBindTexture ( GL_TEXTURE_2D, texture[0] );
  glBegin(GL_QUADS);
    //Frente
    glTexCoord2f(0.0f, 0.0f);glVertex3f(-0.5,-0.5,0.5);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(-0.5,0.5,0.5);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(0.5,0.5,0.5);
    glTexCoord2f(0.0f, 1.0f);glVertex3f(0.5,-0.5,0.5);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture ( GL_TEXTURE_2D, texture[1] );
  glBegin(GL_QUADS);
    // Tras:
    glTexCoord2f(1.0f, 0.0f);glVertex3f(-0.5,-0.5,-0.5);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(0.5,-0.5,-0.5);
    glTexCoord2f(0.0f, 1.0f);glVertex3f(0.5,0.5,-0.5);
    glTexCoord2f(0.0f, 0.0f);glVertex3f(-0.5,0.5,-0.5);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture ( GL_TEXTURE_2D, texture[2] );
  glBegin(GL_QUADS);
    //Topo:
    glTexCoord2f(0.0f, 1.0f);glVertex3f(-0.5,0.5,-0.5);
    glTexCoord2f(0.0f, 0.0f);glVertex3f(0.5,0.5,-0.5 );
    glTexCoord2f(1.0f, 0.0f);glVertex3f(0.5,0.5,0.5);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(-0.5,0.5,0.5);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture ( GL_TEXTURE_2D, texture[0] );
  glBegin(GL_QUADS);
    // baixo:
    glTexCoord2f(1.0f, 1.0f);glVertex3f(-0.5,-0.5,-0.5);
    glTexCoord2f(0.0f, 1.0f);glVertex3f(-0.5,-0.5,0.5);
    glTexCoord2f(0.0f, 0.0f);glVertex3f(0.5,-0.5,0.5);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(0.5,-0.5,-0.5);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture ( GL_TEXTURE_2D, texture[1] );
  glBegin(GL_QUADS);
    //Esquerda
    glTexCoord2f(1.0,0.0);glVertex3f(-0.5,-0.5,-0.5);
    glTexCoord2f(1.0,1.0);glVertex3f(-0.5,0.5,-0.5);
    glTexCoord2f(0.0,1.0);glVertex3f(-0.5,0.5,0.5);
    glTexCoord2f(0.0,0.0);glVertex3f(-0.5,-0.5,0.5);
  glEnd();
  glDisable(GL_TEXTURE_2D);


  glEnable(GL_TEXTURE_2D);
  glBindTexture ( GL_TEXTURE_2D, texture[2] );
  glBegin(GL_QUADS);
    //Direita
    glTexCoord2f(0.0,0.0);glVertex3f(0.5,-0.5,-0.5);
    glTexCoord2f(1.0,0.0);glVertex3f(0.5,-0.5,0.5);
    glTexCoord2f(1.0,1.0);glVertex3f(0.5,0.5,0.5);
    glTexCoord2f(0.0,1.0);glVertex3f(0.5,0.5,-0.5);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  glPopMatrix();
 }

// fim mudancas textura
// ---------------------------------------------------------------------
// draw a teapot
//---------------------------------------------------------------------

void teapot(void)
{
    glPushMatrix();
    glTranslatef(origin_x, origin_y, origin_z);
 //   glColor3f(1.0, 0.0, 0.0);

	glBindTexture(GL_TEXTURE_2D, texture[indiceTextura]);

	glutSolidTeapot(2.0);
    glPopMatrix();
}

// ---------------------------------------------------------------------
// re-draw the scene afer spinning
//---------------------------------------------------------------------

void spinDisplay(void)
{
   spin = spin + 2.0;
   if (spin > 360.0)
      spin = spin - 360.0;
   glutPostRedisplay();
}

// ---------------------------------------------------------------------
// set up one light source (LIGHT0) for shading purposes
//---------------------------------------------------------------------

void initLighting(void)
{
    /*GLfloat lightposition[] = { 3.0, -3.0, 3.0, 0.0 };


    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_POSITION, lightposition);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0.0, 0.0, 1.0, 0.0);*/
}

// ---------------------------------------------------------------------
// re-shape callback
//---------------------------------------------------------------------

void reshape(int width, int height)
{
    Width = width;
    Height = height;


    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-3.0, 3.0, -3.0, 3.0, 64, 256);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -200.0);
}

// ---------------------------------------------------------------------
// drawing callback
//---------------------------------------------------------------------

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	// top left: top view
	glViewport(0, Height/2, Width/2, Height/2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3.0, 3.0, -3.0, 3.0, 1.0, 50.0);
	gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	teapot();

	// top right: right view
	glViewport( Width/2, Height/2,  Width/2, Height/2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3.0, 3.0, -3.0, 3.0, 1.0, 50.0);
	gluLookAt(5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	teapot();

	// bottom left: front view
	glViewport(0, 0,  Width/2, Height/2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3.0, 3.0, -3.0, 3.0, 1.0, 50.0);
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	teapot();

	// bottom right: rotating perspective view
	glViewport(Width/2, 0, Width/2,  Height/2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0, 1.0, 1, 50);
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(45.0, 1.0, 0.0, 0.0);

	glRotatef(spin, 0.0, 0.0, 1.0);
	//teapot();
	cubo();

	glPopMatrix();

	glutSwapBuffers();
}

// ---------------------------------------------------------------------
// input callback
//---------------------------------------------------------------------

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
	{
		case '1': indiceTextura = 0;
		          break;
		case '2': indiceTextura = 1;
		          break;
		case '3': indiceTextura = 2;
		          break;
		case 27:
				exit(0);
				break;
		default:
			return;
    }

}

// ---------------------------------------------------------------------
// main program
//---------------------------------------------------------------------

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize( 800,800 );
    glutCreateWindow("Teapot in 4 views");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
	glutIdleFunc(spinDisplay);

	initLighting();

    if (!LoadGLTextures()){
		return 1; // If Texture Didn't Load Return FALSE
	}

    glutMainLoop();

	return 0;
}
