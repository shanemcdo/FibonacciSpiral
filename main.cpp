#include<GL/glut.h>

struct coord{
	double x;
	double y;
};

double zoomnum = 1;
char direction[4] = {'r','d','l','u'};

void curve(coord point1, coord point2)
{
	glBegin(GL_LINES);
		glVertex2d(point1.x, point1.y);	
		glVertex2d(point2.x, point2.y);	
	glEnd();
}//curve

void HolQuad(coord point1, coord point2, coord point3, coord point4, int num)//print 4 lines in a quadralateral corrioding to the 4 points
{
	

	//change color
	if(direction[num%4] == 'r')
	{
		glColor3f(1.0f, 0.0f, 0.0f);//color 1
	}//if r
	else if(direction[num%4] == 'd')
	{
		glColor3f(0.0f, 1.0f, 0.0f);//color 2
	}//if d
	else if(direction[num%4] == 'l')
	{
		glColor3f(0.0f, 0.0f, 1.0f);//color 3
	}//if l
	else if(direction[num%4] == 'u')
	{
		glColor3f(0.0f, 0.0f, 0.0f);//color 4
	}//if u


	glBegin(GL_QUADS);
		glVertex2d(point1.x, point1.y);
		glVertex2d(point2.x, point2.y);
		glVertex2d(point3.x, point3.y);
		glVertex2d(point4.x, point4.y);
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);
	
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
	double minlength = 0.0005 / zoomnum;//side length of first triangle
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
		HolQuad(point[0], point[1], point[2], point[3], counter);
		
		//change position and size of square
		if(direction[counter%4] == 'r')
		{
			curve(point[2], point[0]);
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
			curve(point[1], point[3]);
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
			curve(point[2], point[0]);
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
			curve(point[1], point[3]);
			for(int i = 0; i < 4; i++)
			{
				point[i].y += prevlength[1];
			}//for i
			point[0].y += prevlength[0];
			point[1].y += prevlength[0];
			point[0].x += prevlength[0];
			point[3].x += prevlength[0];
		}//if u

		prevlength[2] = prevlength[0] + prevlength[1]; //set length of squares
		prevlength[0] = prevlength[1];
		prevlength[1] = prevlength[2];
		counter++;
	}//while(under1)

	zoomnum *= 0.999;
	if(zoomnum <= 0.14705882352)//one full loop around the square
	{
		zoomnum = 1;
	}//if

	glutSwapBuffers();
}//DrawFib


int main(int argc, char *argv[])
{
	//initialize
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition ( 0, 0 ) ;
	glutInitWindowSize ( 675, 675 ) ;
	glutCreateWindow( "Fibonacci Spiral" );

	//functions
	glutDisplayFunc(DrawFib);
	glutIdleFunc(DrawFib);


	//loop
	glutMainLoop();


	return 0;
}
