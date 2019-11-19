#include<GL/glut.h>
#include<windows.h>

struct coord{
	double x;
	double y;
};

//starting sequence

char direction[4] = {'r','d','l','u'};


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
	int counter = 0;
	//starting square
	coord point[4];
	point[0].x = 0.01;
	point[0].y = 0.01;
	point[1].x = -0.01;
	point[1].y = 0.01;
	point[2].x = -0.01;
	point[2].y = -0.01;
	point[3].x = 0.01;
	point[3].y = -0.01;

	double prevlength[3] = {0, 0.02, 0};
	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	for(int i = 0; i <  10; i++)
	{
		HolQuad(point[0], point[1], point[2], point[3]);

		
		//change position of square
		if(direction[counter%4] == 'r')
		{
			for(int i = 0; i < 4; i++)
			{
				point[i].x += prevlength[1];
			}//for i
			point[2].y -= prevlength[0];
			point[3].y -= prevlength[0];
			point[0].x += prevlength[0];
			point[3].x += prevlength[0];
		}//if r
		else if(direction[counter%4] == 'd')
		{
			for(int i = 0; i < 4; i++)
			{
				point[i].y -= prevlength[1];
			}//for i
			point[2].y -= prevlength[0];
			point[3].y -= prevlength[0];
			point[1].x -= prevlength[0];
			point[2].x -= prevlength[0];
		}//if d
		else if(direction[counter%4] == 'l')
		{
			for(int i = 0; i < 4; i++)
			{
				point[i].x -= prevlength[1];
			}//for i
			point[0].y += prevlength[0];
			point[1].y += prevlength[0];
			point[1].x -= prevlength[0];
			point[2].x -= prevlength[0];
		}//if l
		else if(direction[counter%4] == 'u')
		{
			for(int i = 0; i < 4; i++)
			{
				point[i].y += prevlength[1];
			}//for i
			point[0].y += prevlength[0];
			point[1].y += prevlength[0];
			point[0].x += prevlength[0];
			point[3].x += prevlength[0];
		}//if u

		prevlength[2] = prevlength[0] + prevlength[1];
		prevlength[0] = prevlength[1];
		prevlength[1] = prevlength[2];
		counter++;
	}
	glutSwapBuffers();
}//DrawFib


int main(int argc, char *argv[])
{
	//initialize
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition ( 0, 0 ) ;
	glutInitWindowSize ( 650, 650 ) ;
	glutCreateWindow( "Fibonacci Spiral" );

	//functions
	glutDisplayFunc(DrawFib);
	glutIdleFunc(DrawFib);


	//loop
	glutMainLoop();


	return 0;
}
