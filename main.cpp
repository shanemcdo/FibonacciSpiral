#include<GL/glut.h>
#include<windows.h>

struct coord{
	double x;
	double y;
} point[4];

bool first = true;

//starting sequence
double prevlength[3] = {0, 0.01, 0};



char direction[4] = {'r','d','l','u'};
int counter = 0;

void HolQuad(coord point1, coord point2, coord point3, coord point4)
{
	glBegin(GL_LINES);
		glVertex2d(point1.x, point1.y);
		glVertex2d(point2.x, point2.y);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(point2.x, point2.y);
		glVertex2d(point3.x, point3.y);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(point3.x, point3.y);
		glVertex2d(point4.x, point4.y);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(point4.x, point4.y);
		glVertex2d(point1.x, point1.y);
	glEnd();
}//HolQuad

void DrawFib()
{
	if(first)
	{
		//starting square
		point[0].x = 0.01;
		point[0].y = 0.01;
		point[1].x = -0.01;
		point[1].y = 0.01;
		point[2].x = -0.01;
		point[2].y = -0.01;
		point[3].x = 0.01;
		point[3].y = -0.01;
		first = false;
	}//if first
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	HolQuad(point[0], point[1], point[2], point[3]);

	prevlength[2] = prevlength[0] + prevlength[1];
	prevlength[0] = prevlength[1];
	prevlength[1] = prevlength[2];
	
	if(direction[counter%4] == 'r')
	{
		for(int i = 0; i < 4; i++)
		{
			point[i].x += prevlength[1];
		}//for i
	}//if r
	if(direction[counter%4] == 'd')
	{
		for(int i = 0; i < 4; i++)
		{
			point[i].y -= prevlength[1];
		}//for i
	}//if d
	if(direction[counter%4] == 'l')
	{
		for(int i = 0; i < 4; i++)
		{
			point[i].x -= prevlength[1];
		}//for i
	}//if l
	if(direction[counter%4] == 'u')
	{
		for(int i = 0; i < 4; i++)
		{
			point[i].y += prevlength[1];
		}//for i
	}//if u

	counter++;
	Sleep(500);
	glutSwapBuffers();
}//DrawFib


int main(int argc, char *argv[])
{
	//initialize
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition ( 0, 0 ) ;
	glutInitWindowSize ( 700, 700 ) ;
	glutCreateWindow( "Fibonacci Spiral" );

	//functions
	glutDisplayFunc(DrawFib);
	glutIdleFunc(DrawFib);


	//loop
	glutMainLoop();


	return 0;
}
