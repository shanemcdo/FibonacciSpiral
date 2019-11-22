#include<GL/glut.h>
#include<iostream>
#include<math.h>

struct coord{//literally the simplest struct.
	double x;
	double y;
};
const int size = 50;

void trans(coord a[], char dir, double r)
{
	for(int i = 0; i <= size; i++)
	{
		if(dir == 'r')
		{
			a[i].x *= -1;
			a[i].x += r;
		}//if r
		else if(dir == 'd')
		{
			a[i].y *= -1;
			a[i].y += r;
		}//else if d
		else if(dir == 'l')
		{
			a[i].x *= -1;
			a[i].y *= -1;
			a[i].x += r;
			a[i].y += r;
		}//else if l
		else if(dir == 'u')
		{
		}//else if u
	}//for i
}//trans

void curve(coord point1, coord point2, char dir)
{
	glLineWidth(2.5f);//bigger line width
	
	//PRINT CURVE
	double r = abs(point1.y - point2.y);//find radius
	coord c, arr[102];
	int count = 0;
	for(c.x = point1.x; count <= size ; c.x += r/size)
	{
		c.y = sqrt(pow(r,2) - pow(c.x,2));
		if(count == size)
			c.y = 0;
		arr[count].x = c.x;
		arr[count].y = c.y;
		count++;
	}//for c.x

	trans(arr, dir, r);

	for(int i = 1; i <= size ; i++)
	{
		glBegin(GL_LINES);
			glVertex2d(arr[i].x, arr[i].y);
			glVertex2d(arr[i - 1].x, arr[i - 1].y);
		glEnd();
	}//for i

	glLineWidth(1.0f);//line width default
}//curve

void temp()
{
       glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );//I do as the sample code says

       coord point[3];
       point[0].x = 0;
       point[0].y = 1;
       point[1].x = 1;
       point[1].y = 0;

       curve(point[0], point[1], 'u');
       curve(point[0], point[1], 'r');
       curve(point[0], point[1], 'd');
       curve(point[0], point[1], 'l');

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
