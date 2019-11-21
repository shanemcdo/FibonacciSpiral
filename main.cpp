#include<GL/glut.h>
#include<iostream>
#include<math.h>

double zoomnum = 1;//how zoomed in it is. ya know.
char direction[4] = {'r','d','l','u'};//uses counter to tell direction

struct coord{//literally the simplest struct.
	double x;
	double y;
};

void cleanarr(coord a[], int count, int iter, double r)
{
		if(direction[count % 4] == 'd')
		{
			a[iter].x -= abs(r);	
		}//if d
		else if(direction[count % 4] == 'l')
		{
			a[iter].x -= abs(r);
			a[iter].y += abs(r);
		}//if l
		else if(direction[count % 4] == 'u')
		{
			a[iter].y += abs(r);
		}//if u
}//cleanarr

void curve(coord point1, coord point2, int count)
{
	glLineWidth(2.5f);//bigger line width
	
	//PRINT CURVE
	double r = abs(point1.y - point2.y);//find radius

	std::cout << "Radius: " << r << std::endl << std::endl;

	coord c;
	coord arr[11];

	c.x = abs(point1.x);
	for(int i = 0; i < 11;i++)
	{
		c.y = sqrt(pow(r,2) - pow(c.x,2));	

		if(direction[count % 4] == 'r')
		{
			c.x = abs(c.x) * -1;
			c.y = abs(c.y);
		}//if r
		else if(direction[count % 4] == 'd')
		{

			c.x = abs(c.x);
			c.y = abs(c.y);
			r = (abs(r) * -1);
		}//if d
		else if(direction[count % 4] == 'l')
		{
			c.x = abs(c.x);
			c.y = abs(c.y) * -1;
			r = (abs(r) * -1);
		}//if l
		else if(direction[count % 4] == 'u')
		{
			c.x = abs(c.x) * -1;
			c.y = abs(c.y) * -1;
		}//if u


		arr[i].x = c.x;
		arr[i].y = c.y;
		cleanarr(arr, count, i ,r);
		std::cout << "point " << i << ": " << c.x << " " << c.y << std::endl;
		c.x += r/10;
	}//for c.x
	for(int i = 1; i < 10; i++)
	{
		glBegin(GL_LINES);
			glVertex2d(arr[i].x, arr[i].y);
			glVertex2d(arr[i + 1].x, arr[i + 1].y);
		glEnd();
	}//for i

	//SECOND HALF
	r = abs(point1.y - point2.y);//find radius

	c.y = abs(point1.y);
	for(int i = 0; i < 10;i++)
	{
		c.x = (sqrt(pow(r,2) - pow(c.y,2)) * -1);	

		if(direction[count % 4] == 'r')
		{
			c.x = abs(c.x) * -1;
			c.y = abs(c.y);
		}//if r
		else if(direction[count % 4] == 'd')
		{
			c.x = abs(c.x);
			c.y = abs(c.y);
		}//if d
		else if(direction[count % 4] == 'l')
		{
			c.x = abs(c.x);
			c.y = abs(c.y) * -1;
			r = abs(r) * -1;
		}//if l
		else if(direction[count % 4] == 'u')
		{
			c.x = abs(c.x) * -1;
			c.y = abs(c.y) * -1;
			r = abs(r) * -1;
		}//if u

		arr[i].x = c.x;
		arr[i].y = c.y;
		cleanarr(arr, count, i, r);
		std::cout << "point " << i << ": " << c.x << " " << c.y << std::endl;
		c.y += r/10;
	}//for c.y

	for(int i = 0; i < 9; i++)
	{
		glBegin(GL_LINES);
			glVertex2d(arr[i].x, arr[i].y);
			glVertex2d(arr[i + 1].x, arr[i + 1].y);
		glEnd();
	}//for i



	


	glLineWidth(1.0f);//line width default
}//curve

void temp()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );//I do as the sample code says

	coord point[3];
	point[0].x = -0.5;
	point[0].y = 0;
	point[1].x = 0;
	point[1].y = 0.5;

	curve(point[0], point[1], 0);
	curve(point[0], point[1], 1);
	curve(point[0], point[1], 2);
	curve(point[0], point[1], 3);
	
	glBegin(GL_LINES);
		glVertex2d(0,1);
		glVertex2d(0,-1);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(1,0);
		glVertex2d(-1,0);
	glEnd();



	glutSwapBuffers();//I do as sample code commands
}//temp

void HolQuad(coord point1, coord point2, coord point3, coord point4, int num)//print 4 lines in a quadralateral corrioding to the 4 points
{
	

	//change color
	if(direction[num%4] == 'r')
	{
		glColor3f(1.0f, 0.0f, 0.0f);//color 1 red
	}//if r
	else if(direction[num%4] == 'd')
	{
		glColor3f(0.0f, 1.0f, 0.0f);//color 2 green
	}//if d
	else if(direction[num%4] == 'l')
	{
		glColor3f(0.0f, 0.0f, 1.0f);//color 3 blue
	}//if l
	else if(direction[num%4] == 'u')
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
		HolQuad(point[0], point[1], point[2], point[3], counter);
		//curve(point[2], point[0], counter);
		
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
	
	//glutDisplayFunc(temp);
	//glutIdleFunc(temp);


	//loop
	glutMainLoop();


	return 0;
}
