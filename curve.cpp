#include<GL/glut.h>
#include<iostream>
#include<math.h>

struct coord{//literally the simplest struct.
	double x;
	double y;
};


void curve(coord p0, coord p1, coord p2)//p1 is angle p0 and p2 are ends
{
	glLineWidth(2.5f);//bigger line width
	
	//PRINT CURVE(bezier)
	coord c, prev;

	for(double t = 0; t <= 1; t += 0.01)
	{
		c.x = (pow((1 - t),2) * p0.x + 2 * (1 - t) * t * p1.x + pow(t, 2) * p2.x);
		c.y = (pow((1 - t),2) * p0.y + 2 * (1 - t) * t * p1.y + pow(t, 2) * p2.y);
		//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		//formula for quadratic bezier curve. shamelessly stolen.
		

		glBegin(GL_LINES);
			glVertex2d(prev.x, prev.y);
			glVertex2d(c.x, c.y);
		glEnd();

		prev.x = c.x;
		prev.y = c.y;
	}//int t

	
	glLineWidth(1.0f);//line width default
}//curve

void temp()
{
       glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );//I do as the sample code says

       coord point[3];
       point[0].x = 0;
       point[0].y = 1;
       point[1].x = 0;
       point[1].y = 0;
       point[2].x = 1;
       point[2].y = 0;


       curve(point[0], point[1], point[2]);

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
