#include<GL/glut.h>

struct coord{
	double x;
	double y;
};


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

bool under1(coord arr[])
{
	for(int i = 0; i < 4; i++)
	{
		if(arr[i].x < 1 || arr[i].y < 1)
			return true;
	}//for i
return false;
}//under1

void DrawFib()
{
	const double minlength = 0.001;//side length of first triangle
	int counter = 0;
	//starting square
	coord point[4];
	point[0].x = minlength;
	point[0].y = minlength;
	point[1].x = -minlength;
	point[1].y = minlength;
	point[2].x = -minlength;
	point[2].y = -minlength;
	point[3].x = minlength;
	point[3].y = -minlength;

	//starting sequence
	double prevlength[3] = {0, minlength * 2, 0};
	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	while(under1(point))
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
	}//while(under1)
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
