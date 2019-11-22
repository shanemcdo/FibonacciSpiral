#include<GL/glut.h>
#include<iostream>
#include<math.h>

double zoomnum = 1;//how zoomed in it is. ya know.
//TODO: replace the counter inputs in the functions with just a char.
// - Make direction a local variable
// - make curve in a seperate file.


struct coord{//literally the simplest struct.
	double x;
	double y;
};

void curve(coord p0, coord p1, coord p2);
void temp();

void HolQuad(coord point1, coord point2, coord point3, coord point4, char dir)//print 4 lines in a quadralateral corrioding to the 4 points
{
	

	//change color
	if(dir == 'r')
	{
		glColor3f(1.0f, 0.0f, 0.0f);//color 1 red
	}//if r
	else if(dir == 'd')
	{
		glColor3f(0.0f, 1.0f, 0.0f);//color 2 green
	}//if d
	else if(dir == 'l')
	{
		glColor3f(0.0f, 0.0f, 1.0f);//color 3 blue
	}//if l
	else if(dir == 'u')
	{
		glColor3f(0.0f, 0.0f, 0.0f);//color 4 black
	}//if u


	glBegin(GL_QUADS);//print colored quad
		glVertex2d(point1.x, point1.y);
		glVertex2d(point2.x, point2.y);
		glVertex2d(point3.x, point3.y);
		glVertex2d(point4.x, point4.y);
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);//white	

	//print hollow quad
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
	int counter = 0;//used to determine direction
	char direction[4] = {'r','d','l','u'};//uses counter to tell direction

	//starting square initial points
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
	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );//I do as the sample code says
	while(under1(point))
	{
		HolQuad(point[0], point[1], point[2], point[3], direction[counter % 4]);
		
		//change position and size of square and also print curve
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

		//set length of squares
		prevlength[2] = prevlength[0] + prevlength[1];
		prevlength[0] = prevlength[1];
		prevlength[1] = prevlength[2];
		counter++;//increment
	}//while(under1)

	zoomnum *= 0.999;//zoom in
	if(zoomnum <= 0.14705882352)//if one square has become the same size as the next biggest of the same color
	{
		zoomnum = 1;// reset scale
	}//if
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	//This is done so instead of infinitely increasing the size of a set number of squares, it increases the
	//size to until it is smaller than that big decimal ((5/34) => square/next biggest of same color)

	glutSwapBuffers();//I do as sample code commands
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

//	glutDisplayFunc(temp);
//	glutIdleFunc(temp);

	//loop
	glutMainLoop();


	return 0;
}

