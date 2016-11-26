#include <GL/glut.h>
void Square(float,float,float,float);
void Qube(float,float,float,float,float,float);

GLfloat light0pos[] = {3.0,4.0,3.0,1.0};

GLfloat red[] = {0.8, 0.2, 0.2,1.0};
GLfloat green[] = {0.2, 0.8, 0.2, 1.0};

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green);
	Square(0.0, 0.0, 2.0, 2.0);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
	
	glTranslated(-0.25, 0, -0.25);
	Qube(0.0, 0.0, 0.0, 0.5, 0.5, 0.5);
	glFlush();
}

void resize(int w,int h){
	glViewport(0, 0, w, h);
	
	glLoadIdentity();
	gluPerspective(30.0, (double)w/(double)h, 1.0,100);
	gluLookAt(-1.0,3.0,4.0,0.0,0.0,0.0,0.0,1.0,0.0);
}

void Square(float x, float z, float w, float h){
	glBegin(GL_POLYGON);
	glVertex3d(x+w/2, 0.0, z+h/2);
	glVertex3d(x-w/2, 0.0, z+h/2);
	glVertex3d(x-w/2, 0.0, z-h/2);
	glVertex3d(x+w/2, 0.0, z-h/2);
	glEnd();
}

void Qube(float x,float y, float z, float w, float h, float d){
	
	int i = 0, j = 0;

	GLdouble vertex[][3] = {
		{x, y, z},
		{x+w, y, z},
		{x+w, y+h, z},
		{x, y+h, z},
		{x, y, z+d},
		{x+w, y, z+d},
		{x+w, y+h, z+d},
		{x, y+h, z+d}
	};

	int edge[][2] = {
		{0,1},{1,2},{2,3},{3,0},
		{4,5},{5,6},{6,7},{7,4},
		{0,4},{1,5},{2,6},{3,7}
	};

	int face[][4] = {
		{0, 1, 2, 3},{1, 5, 6, 2},{5, 4, 7, 6},
		{4, 0, 3, 7},{4, 5, 1, 0},{3, 2, 6, 7}
	};

	GLdouble normal[][3] = {
		{0.0, 0.0, -1.0},{1.0, 0.0, 0.0},{0.0, 0.0, 1.0},
		{-1.0, 0.0, 0.0},{0,0 -1.0, 0.0},{0.0, 1.0, 0.0}
	};
	
	glColor3d(1,0,0);
	glBegin(GL_QUADS);
	for(j=0; j<6; j++){
		glNormal3dv(normal[j]);
		for(i=0; i<4; i++){
			glVertex3dv(vertex[face[j][i]]);
		}
	}
	glEnd();
}

void init(void){
	glClearColor(0.827,0.827,0.827,1.0);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

int main(int argc, char *argv[]){
	glutInitWindowSize(500,500);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	init();
	glutMainLoop();
	return 0;
}
