#include "OpenGL.h"

void main(int argc,char* argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WinWidth,WinHeight);
	//glutInitWindowPosition(200,200);
	glutCreateWindow("Ball");
	glutSpecialFunc(OnKeyboard);
	glutReshapeFunc(OnReshape);
	glutDisplayFunc(OnDisplay);

	Eye.x=0.0f;
	Eye.y=0.0f;
	Eye.z=10.0f;

	SetupLights();

	glutMainLoop();
}


void OnDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);

	glColor3f(0.0f,0.4f,0.8f);

	float r = 50;
	float r_z = r * sin(45*GL_PI/180);

	Point PTop = {0,r,0};
	Point PBotton = {0,-r,0};
	Point P1 = {r_z , 0 , -r_z};
	Point P2 = {-r_z , 0 , -r_z};
	Point P3 = {-r_z , 0 , r_z};
	Point P4 = {r_z , 0 , r_z};

	//Point d = distance(P1,PTop,r);
	//printf("d = (%f,%f,%f)\n",d.x,d.y,d.z);
	//printf("r= %f , r_z = %f , sin(45) = %f \n",r,r_z,cos(45*GL_PI/180));

	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	
	glBegin(GL_TRIANGLES);
		Level(P1,P2,PTop,r);
		Level(P2,P3,PTop,r);
		Level(P3,P4,PTop,r);
		Level(P4,P1,PTop,r);
		
		Level(P1,P2,PBotton,r);
		Level(P2,P3,PBotton,r);
		Level(P3,P4,PBotton,r);
		Level(P4,P1,PBotton,r);
		
	glEnd();

	glutSwapBuffers();
}

void OnReshape(int w,int h)
{
	GLfloat aspect = (GLfloat)w/(GLfloat)h;

	glViewport(0,0,w,h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(w<=h){
		glOrtho(-SIZE,SIZE,-SIZE/aspect,SIZE/aspect,-SIZE,SIZE);
	}
	else{
		glOrtho(-SIZE,SIZE,-SIZE*aspect,SIZE*aspect,-SIZE,SIZE);
	}

	//改變照相機位置和觀察點的位置
	//(x,y,z , x,y,z , x,u,z)
	gluLookAt(Eye.x,Eye.y,Eye.z,0,0,0,0,1,0);
}

void OnKeyboard(int key,int x ,int y)
{
	switch(key){
		case GLUT_KEY_LEFT:
			Eye.x -= 2.0f;
			break;
		case GLUT_KEY_RIGHT:
			Eye.x += 2.0f;
			break;
		case GLUT_KEY_DOWN:
			Eye.y -= 2.0f;
			break;
		case GLUT_KEY_UP:
			Eye.y += 2.0f;
			break;
		case GLUT_KEY_PAGE_DOWN:
			Eye.z -= 2.0f;
			break;
		case GLUT_KEY_PAGE_UP:
			Eye.z += 2.0f;
			break;
	}

	OnReshape(WinWidth,WinHeight);
	glutPostRedisplay();
}

void SetupLights()
{
	GLfloat ambientLight[] = {0.2f,0.2f,0.2f,1.0f};
	GLfloat diffuseLight[] = {0.9f,0.9f,0.9f,1.0f};
	GLfloat specularLight[] = {1.0f,1.0f,1.0f,1.0f};
	GLfloat lightPos[] = {50.0f,100.0f,80.0f,1.0f};

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specularLight);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specularLight);
	glMateriali(GL_FRONT,GL_SHININESS,100);
}

void Level(Point P1,Point P2,Point P3,float r)
{
		Point d1 = distance(P1,P2,r);
		Point d2 = distance(P1,P3,r);
		Point d3 = distance(P2,P3,r);

		glVertex3f(P1.x,P1.y,P1.z);
		glVertex3f(d1.x,d1.y,d1.z);
		glVertex3f(d2.x,d2.y,d2.z);
		
		glVertex3f(d1.x,d1.y,d1.z);
		glVertex3f(P2.x,P2.y,P2.z);
		glVertex3f(d3.x,d3.y,d3.z);

		glVertex3f(d1.x,d1.y,d1.z);
		glVertex3f(d2.x,d2.y,d2.z);
		glVertex3f(d3.x,d3.y,d3.z);

		glVertex3f(d2.x,d2.y,d2.z);
		glVertex3f(d3.x,d3.y,d3.z);
		glVertex3f(P3.x,P3.y,P3.z);
}

Point distance(Point A,Point B,float r)
{
	Point CenterP;
	float tx,ty,tz,length;
	
	tx = A.x-B.x;
	tx = tx*0.5 + B.x;
	ty = A.y-B.y;
	ty = ty*0.5 + B.y;
	tz = A.z-B.z;
	tz = tz*0.5 + B.z;

	length = sqrt(pow(tx,2)+pow(ty,2));
	length = sqrt(pow(length,2)+pow(tz,2));
	CenterP.x = tx/length*r;
	CenterP.y = ty/length*r;
	CenterP.z = tz/length*r;

	return CenterP;
}