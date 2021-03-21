# Fibonacci Sprial
I created this program to display the Fibonacci spiral expanding. I got the idea from [this](https://upload.wikimedia.org/wikipedia/commons/e/e9/GoldenSpiralLogarithmic_color_in.gif). I used freeGLUT to create this program and you can find the download [here](http://freeglut.sourceforge.net/).
Originally, I was going to use the formula of a quarter circle `y = sqrt(r^2 - x^2)`, however that was inaccurate to the correct curvature. Instead, I used the formula for a quadratic bezier curve, and that worked extremely well.

![Fibonacci Spiral](Fibonacci.gif)

CONTROLS:

	1 : zoom out

	2 : zoom in

	3 : crazy out

	4 : crazy in

	s : steel ball run colors

	r : tricolor rainbow 

	g : green and blue gradient colors

	b : black and white gradient colors

	t : tricolor blueish

	p : pause

	q : quit
