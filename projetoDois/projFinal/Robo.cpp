	#include <GL/glut.h>
	#include <math.h>
	#define BASE_HEIGHT 4.0/2
	#define BASE_RADIUS 1.0/2
	#define HEAD_HEIGHT 1.25/2
	#define HEAD_RADIUS 0.75/2
	#define NECK_HEIGHT 0.5/2
	#define EYE_LEVEL 0.75/2
	#define NOSE_LENGTH 0.5/2
	#define LOWER_ARM_HEIGHT 2.0/2
	#define LOWER_ARM_WIDTH 0.5/2
	#define UPPER_ARM_HEIGHT 1.25/2
	#define UPPER_ARM_WIDTH 0.5/2
	#define ARM_TRANSLATION 0.22/2
	#define alpha 0.0
	#define pi 3.14159265
	static GLfloat theta[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	static GLint axis = 0;
	GLUquadricObj *p;
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat xpos = 0.0;
	GLfloat ypos = 0.0;
	GLfloat zpos = 0.0;
	GLfloat ambient[3];
	GLfloat diffuse[3];
	GLfloat specular[3];
	GLfloat shiness[] = {50.0f};
	float width = 500;
	float height = 500;
	void base(void);
	void head(void);
	void neck(void);
	void upper_rarm(void);
	void upper_larm(void);
	void lower_rarm(void);
	void lower_larm(void);
	void init(void);
	void display(void);
	void reshape (int width, int height);
	void keyboard(unsigned char, int, int);
	void processSpecialKeys(int, int, int);
	void jump (void);
	void lsphere (void);
	void init1 (void);

	void base (void) {
	double angle, angleInc;
	int i;
	angle = pi / 180;
	angleInc = angle;
	glPushMatrix();

	ambient[0] = 1.0; ambient[1] = 0.0; ambient[2] = 0.0;
	diffuse[0] = 1.0; diffuse[1] = 0.0; diffuse[2] = 0.0;
	specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shiness);

	glRotatef (-90.0, 1.0, 0.0, 0.0);
	gluQuadricDrawStyle(p, GLU_FILL);
	gluCylinder (p, BASE_RADIUS, BASE_RADIUS, BASE_HEIGHT, 20, 20);

	glPopMatrix();

	glPushMatrix();

	gluQuadricDrawStyle (p, GLU_FILL);
	glTranslatef (0.0, BASE_HEIGHT, 0.0);
	glRotatef (-90.0, 1.0, 0.0, 0.0);
	gluDisk (p, 0.0, BASE_RADIUS, 20, 20);
	glTranslatef (0.0, 0.0, -BASE_HEIGHT);
	gluDisk (p, 0.0, BASE_RADIUS, 20, 20);
	glPopMatrix();
	}


	void neck (void) {
	glPushMatrix();

	ambient[0] = 1.0; ambient[1] = 1.0; ambient[2] = 0.0;
	diffuse[0] = 1.0; diffuse[1] = 1.0; diffuse[2] = 0.0;
	specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shiness);

	glTranslatef(0.0, BASE_HEIGHT, 0.0);
	glRotatef (-90.0, 1.0, 0.0, 0.0);
	gluQuadricDrawStyle(p, GLU_FILL);
	gluCylinder (p, HEAD_RADIUS/2, HEAD_RADIUS/2, HEAD_HEIGHT, 8, 6);
	glPopMatrix();
	}

	void head (void) {
	glPushMatrix();

	ambient[0] = 1.0; ambient[1] = 0.0; ambient[2] = 1.0;
	diffuse[0] = 1.0; diffuse[1] = 0.0; diffuse[2] = 1.0;
	specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shiness);

	glRotatef (-90.0, 1.0, 0.0, 0.0);
	gluQuadricDrawStyle(p, GLU_FILL);
	gluCylinder (p, HEAD_RADIUS, HEAD_RADIUS, HEAD_HEIGHT, 20, 20);

	glPushMatrix();

	gluDisk (p, 0.0, HEAD_RADIUS, 20, 20);
	glTranslatef (0.0, 0.0, HEAD_HEIGHT);
	gluDisk (p, 0.0, HEAD_RADIUS, 20, 20);
	glPopMatrix();

	glPushMatrix(); 
	glTranslatef (0.25, -HEAD_RADIUS+0.12, EYE_LEVEL);

	ambient[0] = 1.0; ambient[1] = 1.0; ambient[2] = 1.0;
	diffuse[0] = 1.0; diffuse[1] = 1.0; diffuse[2] = 1.0;
	specular[0] = 0.5; specular[1] = 0.5; specular[2] = 0.5;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shiness);

	gluQuadricDrawStyle(p, GLU_FILL);
	gluSphere (p, 0.125, 6, 6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef (-0.25, -HEAD_RADIUS+0.12, EYE_LEVEL);
	ambient[0] = 1.0; ambient[1] = 1.0; ambient[2] = 1.0;
	diffuse[0] = 1.0; diffuse[1] = 1.0; diffuse[2] = 1.0;
	specular[0] = 0.5; specular[1] = 0.5; specular[2] = 0.5;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shiness);


	gluQuadricDrawStyle(p, GLU_FILL);
	gluSphere (p, 0.125, 6, 6);
	glPopMatrix();

	glPushMatrix();
	ambient[0] = 1.0; ambient[1] = 0.5; ambient[2] = 0.0;
	diffuse[0] = 1.0; diffuse[1] = 0.5; diffuse[2] = 0.0;
	specular[0] = 0.5; specular[1] = 0.5; specular[2] = 0.5;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shiness);
	glTranslatef(0.0, -HEAD_RADIUS, NOSE_LENGTH);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	gluQuadricDrawStyle(p, GLU_FILL);
	gluCylinder(p, 0.125, 0, NOSE_LENGTH, 8,6);
	glPopMatrix();

	glPopMatrix();
	}

	void lower_rarm(void) {
	glPushMatrix();

	ambient[0] = 0.0; ambient[1] = 1.0; ambient[2] = 0.0;
	diffuse[0] = 0.0; diffuse[1] = 1.0; diffuse[2] = 0.0;
	specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shiness);

	glTranslatef(0.0, 0.5 * LOWER_ARM_HEIGHT, ARM_TRANSLATION);
	glScalef(LOWER_ARM_WIDTH, LOWER_ARM_HEIGHT, LOWER_ARM_WIDTH);
	glutSolidCube(1.0);
	glPopMatrix();
	}

	void lower_larm(void) {
	glPushMatrix();

	ambient[0] = 0.0; ambient[1] = 1.0; ambient[2] = 0.0;
	diffuse[0] = 0.0; diffuse[1] = 1.0; diffuse[2] = 0.0;
	specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shiness);

	glTranslatef(0.0, 0.5 * LOWER_ARM_HEIGHT, -ARM_TRANSLATION);
	glScalef(LOWER_ARM_WIDTH, LOWER_ARM_HEIGHT, LOWER_ARM_WIDTH);
	glutSolidCube(1.0);
	glPopMatrix();
	}

	void upper_rarm(void) {
	glPushMatrix();

	ambient[0] = 0.0; ambient[1] = 0.0; ambient[2] = 1.0;
	diffuse[0] = 0.0; diffuse[1] = 0.0; diffuse[2] = 1.0;
	specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shiness);

	glTranslatef(0.0, 0.5 * UPPER_ARM_HEIGHT, ARM_TRANSLATION);
	glScalef(UPPER_ARM_WIDTH, UPPER_ARM_HEIGHT, UPPER_ARM_WIDTH);
	glutSolidCube(1.0);
	glPopMatrix();
	}

	void upper_larm(void) {
	glPushMatrix();

	ambient[0] = 0.0; ambient[1] = 0.0; ambient[2] = 1.0;
	diffuse[0] = 0.0; diffuse[1] = 0.0; diffuse[2] = 1.0;
	specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shiness);

	glTranslatef(0.0, 0.5 * UPPER_ARM_HEIGHT, -ARM_TRANSLATION);
	glScalef(UPPER_ARM_WIDTH, UPPER_ARM_HEIGHT, UPPER_ARM_WIDTH);
	glutSolidCube(1.0);
	glPopMatrix();
	}


	void init1(void){
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[] = {50.0};
	GLfloat light_position[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat white_light[] = {0.3, 0.3, 0.3, 1.0};
	GLfloat lmodel_ambient[] = {1.0, 1.0, 0.0, 1.0};
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	}

	void lsphere(void){
	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
	glutSolidSphere(1.0, 20, 16);
	glFlush();
	}

	void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.3, 5.3, 12.0, 0.0, 1.25, 0.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	ambient[0] = 1.0; ambient[1] = 0.3; ambient[2] = 0.3;
	diffuse[0] = 1.0; diffuse[1] = 1.0; diffuse[2] = 1.0;
	specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shiness);


	glTranslatef(0.0, 5.0, 0.0);
	lsphere();
	glPopMatrix();

	glPushMatrix();
	ambient[0] = 0.3; ambient[1] = 0.3; ambient[2] = 0.3;
	diffuse[0] = 0.0; diffuse[1] = 0.0; diffuse[2] = 1.0;
	specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shiness);

	glTranslatef(3.0, 0.5, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	ambient[0] = 0.3; ambient[1] = 0.3; ambient[2] = 0.3;
	diffuse[0] = 1.0; diffuse[1] = 0.0; diffuse[2] = 1.0;
	specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shiness);

	glTranslatef(-4.0, 0.5, 3.0);
	glutSolidCone(0.5, 1.5, 20, 15);
	glPopMatrix();

	glPushMatrix();
	ambient[0] = 0.3; ambient[1] = 0.3; ambient[2] = 0.3;
	diffuse[0] = 1.0; diffuse[1] = 0.0; diffuse[2] = 0.0;
	specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shiness);

	glTranslatef(-3.0, 0.5, -3.0);
	glutSolidTeapot(1.0);
	glPopMatrix();

	glPushMatrix();
	ambient[0] = 0.5; ambient[1] = 0.5; ambient[2] = 0.5;
	diffuse[0] = 1.0; diffuse[1] = 1.0; diffuse[2] = 1.0;
	specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shiness);

	glBegin(GL_POLYGON);
	glVertex3f(5.0, 0.0, 5.0);
	glVertex3f(5.0, 0.0, -5.0);
	glVertex3f(-5.0, 0.0, -5.0);
	glVertex3f(-5.0, 0.0, 5.0);
	glVertex3f(5.0, 0.0, 5.0);
	glEnd();

	glPopMatrix();

	glTranslatef (xpos, ypos, zpos);
	glRotatef(theta[0], 0.0, 1.0, 0.0);
	base();
	neck();

	glPushMatrix();
	glTranslatef(0.0, BASE_HEIGHT + HEAD_HEIGHT/2, 0.0);
	glRotatef(theta[2], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	head();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(BASE_RADIUS, BASE_HEIGHT - BASE_RADIUS / 2, 0.0);
	glRotatef(180.0, 0.0, 0.0, 1.0);
	glRotatef(270.0, 0.0, 1.0, 0.0);
	glRotatef(theta[4], 0.0, 0.0, 1.0);
	lower_rarm();
	glTranslatef(0.0, LOWER_ARM_HEIGHT, 0.0);
	glRotatef(0.0, 0.0, 0.0, 180.0);
	glRotatef(theta[6], 0.0, 0.0, 1.0);
	upper_rarm();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-BASE_RADIUS, BASE_HEIGHT - BASE_RADIUS / 2, 0.0);
	glRotatef(180.0, 0.0, 0.0, 1.0);
	glRotatef(270.0, 0.0, 1.0, 0.0);
	glRotatef(theta[3], 0.0, 0.0, 1.0);
	lower_larm();
	glTranslatef(0.0, LOWER_ARM_HEIGHT, 0.0);
	glRotatef(0.0, 0.0, 0.0, 180.0);
	glRotatef(theta[5], 0.0, 0.0, 1.0);
	upper_larm();
	glPopMatrix();


	glFlush();
	glutSwapBuffers();
	}

	void keyboard (unsigned char key, int x, int y) {
	switch (key) {
	case 'a': theta[1] += 5.0;
	if (theta[1] > 90.0)
	theta[1] = 90.0;
	break;

	case 'z': theta[1] -= 5.0;
	if (theta[1] < -90.0)
	theta[1] = -90.0;
	break;

	case 'o': theta[2] += 5.0;
	if (theta[2] > 45.0)
	theta[2] = 45.0;
	break;

	case 'p': theta[2] -= 5.0;
	if (theta[2] < -45.0)
	theta[2] = -45.0;
	break;

	case 'k': theta[3] -= 5.0; break;
	case 'l': theta[3] += 5.0; break;

	case 'h': theta[4] -= 5.0; break;
	case 'j': theta[4] += 5.0; break;

	case 'n': theta[5] -= 5.0; break;
	case 'm': theta[5] += 5.0; break;

	case 'v': theta[6] -= 5.0; break;
	case 'b': theta[6] += 5.0; break;

	case 'e': theta[0] = theta[1] = theta[2] = theta[3] = theta[4] = theta[5] = theta[6] = xpos = ypos = zpos = 0.0;
	break;

	case 'r': theta[0] = theta[1] = theta[2] = theta[3] = theta[4] = theta[5] = theta[6] = 0.0;
	break;

	case 'q': exit(0); break;
	}
	glutPostRedisplay();
	}


	void processSpecialKeys(int key, int x, int y) {
	switch(key) {
	case GLUT_KEY_UP:
	xpos -= cos(90 * pi/180 + theta[0] * pi/180);
	zpos += sin(90 * pi/180 + theta[0] * pi/180);
	if (xpos > 5)
	xpos = 5;
	if (zpos > 5)
	zpos = 5;
	if (xpos < -5)
	xpos = -5;
	if (zpos < -5)
	zpos = -5;
	break;
	case GLUT_KEY_DOWN:
	xpos += cos(90 * pi/180 + theta[0] * pi/180);
	zpos -= sin(90 * pi/180 + theta[0] * pi/180);
	if (xpos > 5)
	xpos = 5;
	if (zpos > 5)
	zpos = 5;
	if (xpos < -5)
	xpos = -5;
	if (zpos < -5)
	zpos = -5;
	break;
	case GLUT_KEY_LEFT: theta[0] -= 5.0; break;
	case GLUT_KEY_RIGHT: theta[0] += 5.0; break;
	case GLUT_KEY_PAGE_UP: ypos += 1.0; break;
	case GLUT_KEY_PAGE_DOWN: ypos -= 1.0; break;
	}
	glutPostRedisplay();
	}

	void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100.0, (GLfloat) w / (GLfloat) h, 0.5, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	}

	void init (void) {
	GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f}; 
	GLfloat light_position[] = {2.0f, 6.0f, 3.0f, 0.0f}; 

	glEnable(GL_LIGHTING); 
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	p = gluNewQuadric();
	}

	int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Robot");
	init();
	init1();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc (processSpecialKeys);
	glutMainLoop();
	return 0;
		}