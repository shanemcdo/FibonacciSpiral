#include<GL/glut.h>
#include<iostream>
#include<math.h>
#include"curve.h"

double zoomnum = 1;//how zoomed in it is. ya know.
int choice;
double speed = 0.96;

void input()
{
	std::cout << std::endl << "Fibonacci Spiral" << std::endl;
	std::cout << "1. Zoom out" << std::endl;
	std::cout << "2. Zoom in" << std::endl;
	std::cout << "3. Crazy" << std::endl;
	std::cout << "4. Inverse Crazy" << std::endl;
	std::cin >> choice;
}//input

void HolQuad(coord point1, coord point2, coord point3, coord point4, char dir)//print 4 lines in a quadralateral corrioding to the 4 points
{
	

	//change color (R,G,B) values
	if(dir == 'l')
	{
		glColor3f(0.486f, 0.988f, 0.0f);//color 1
	}//if r
	else if(dir == 'd')
	{
		glColor3f(0.118f, 0.565f, 1.0f);//color 2
	}//if d
	else if(dir == 'r')
	{
		glColor3f(1.0f, 0.0f, 1.0f);//color 3
	}//if l
	else if(dir == 'u')
	{
		glColor3f(1.0f, 0.843f, 0.2f);//color 4
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
	double minlength;
	int counter = 0;//used to determine direction
	char direction[4] = {'l','d','r','u'};//uses counter to tell direction

	if(choice == 1)
	{
		minlength = 0.0005 * zoomnum;//side length of first triangle zoom in
	}//if 1
	else if (choice == 2 || choice == 3 || choice == 4)
	{
		minlength = 0.0005 / zoomnum;//side length of first triangle zoom out
	}//else if 2


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
	const double N = (1.2/15.0);
	
	while(under1(point))
	{
		HolQuad(point[0], point[1], point[2], point[3], direction[counter % 4]);
		
		//change position and size of square and also print curve
		if(direction[counter%4] == 'l')
		{
			coord mid = {point[0].x - N * point[0].x, point[0].y - N * point[0].y};//this point is used to make the bezier curve look more like a quarter circle
			curve(point[3], mid, point[1]);	
			for(int i = 0; i < 4; i++)
			{
				point[i].x -= prevlength[1];
			}//for i
			point[1].x -= prevlength[0];
			point[2].x -= prevlength[0];
			point[2].y -= prevlength[0];
			point[3].y -= prevlength[0];
		}//if r
		else if(direction[counter%4] == 'd')
		{
			coord mid = {point[1].x - N * point[1].x, point[1].y - N * point[1].y};//this point is used to make the bezier curve look more like a quarter circle
			curve(point[0], mid, point[2]);	
			for(int i = 0; i < 4; i++)
			{
				point[i].y -= prevlength[1];
			}//for i
			point[0].x += prevlength[0];
			point[3].x += prevlength[0];
			point[2].y -= prevlength[0];
			point[3].y -= prevlength[0];
		}//if d
		else if(direction[counter%4] == 'r')
		{
			coord mid = {point[2].x + N * point[2].x, point[2].y - N * point[2].y};//this point is used to make the bezier curve look more like a quarter circle
			curve(point[1], mid, point[3]);	
			for(int i = 0; i < 4; i++)
			{
				point[i].x += prevlength[1];
			}//for i
			point[0].x += prevlength[0];
			point[3].x += prevlength[0];
			point[0].y += prevlength[0];
			point[1].y += prevlength[0];
		}//if l
		else if(direction[counter%4] == 'u')
		{
			coord mid = {point[3].x - N * point[3].x, point[3].y + N * point[3].y};//this point is used to make the bezier curve look more like a quarter circle
			curve(point[2], mid, point[0]);	
			for(int i = 0; i < 4; i++)
			{
				point[i].y += prevlength[1];
			}//for i
			point[1].x -= prevlength[0];
			point[2].x -= prevlength[0];
			point[0].y += prevlength[0];
			point[1].y += prevlength[0];
		}//if u

		//set length of squares
		prevlength[2] = prevlength[0] + prevlength[1];
		prevlength[0] = prevlength[1];
		prevlength[1] = prevlength[2];
		counter++;//increment
	}//while(under1)

	if(choice == 1|| choice == 2|| choice == 3)
	{
		zoomnum *= speed;
	}//if choice 1 2 or 3
	else if (choice == 4)
	{
		zoomnum /= speed;
	}//else if choice 4
	if(zoomnum <= 0.14705882352)//if one square has become the same size as the next biggest of the same color
	{
		zoomnum = 1;// reset scale
	}//if
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	//This is done so instead of infinitely increasing the size of a set number of squares, it increases the
	//size to until it is smaller than that big decimal ((5/34) => square/next biggest of same color)


	if(choice == 3 || choice == 4)
		speed += 0.0001;

}//DrawFib

void display()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );//I do as the sample code says

	DrawFib();

	glutSwapBuffers();//I do as sample code commands
}//display
int main(int argc, char *argv[])
{
	input();

	//initialize
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition ( 0, 0 ) ;
	glutInitWindowSize ( 675, 675 ) ;
	glutCreateWindow( "Fibonacci Spiral" );

	//functions
	glutDisplayFunc(display);
	glutIdleFunc(display);

//	glutDisplayFunc(temp);
//	glutIdleFunc(temp);

	//loop
	glutMainLoop();


	return 0;
}

