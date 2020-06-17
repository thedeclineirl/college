#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "BallAux.h"														//	Ken Shoemake's ArcBall								
#include "Ball.h"
#include "render.h"
#include "objects.h"

void idle();		// idle routine: calls animate
static GLfloat blackColour[4] = {0.0, 0.0, 0.0, 1.0};								//	black
static GLfloat whiteColour[4] = {1.0, 1.0, 1.0, 1.0};								//	white
static GLfloat greyColour[4] = {0.7, 0.7, 0.7, 1.0};								//	grey

int oldWindowWidth, oldWindowHeight;
int windowSize = 512;														//	size of the pane/view to devote to Voxel					
int windowWidth, windowHeight;												//	overall width & height of the window					
const float initialAspectRatio = 1.0;											//	the initial aspect ratio is 1:1							
float aspectRatio = 1.0;														//	the aspect ratio of the window							
const float maxAspectRatio = 2.5;												//	this will constrain width to 2.5 * height					

static float scale = 6.0;													//	scale for zooming									
static int animationOn = FALSE;

int clockTime = 0;
static GLfloat light_position[] = {-1.0, 1.0, 0.0, 0.0};							//	position of light source (at infinity)						

BallData ball;																//	the arcball											
static float offset_x = 0.0, offset_y = 0.0;										//	allows us to move the object around laterally				
const int dragBall = 0, dragObject = 1, dragScale = 2;								//	constants for which form of drag is being performed			
static int dragMode = 0;														//	start off in dragBall mode								
static float dragOld_x, dragOld_y;												//	previous x, y coordinates of drag							

static int isFullScreen = FALSE;												//	whether or not to display full screen
static int blackBackground = FALSE;											//	whether to use a black background						
int wireFrame = FALSE;														//	whether to make objects wireframe
static int smoothShading = TRUE;												//	whether to use smooth shading
static int showAxes = TRUE;													//	whether to draw the axes
static int showGrid = TRUE;													//	whether to draw a grid on the z-plane
static int nGridLines = 2;													//	size of ground-plane grid

void initInterface();														//	initialize the interface								

void display();															//	basic draw routine						
void reshape(int width, int height);											//	routine to call when window reshaped					
void mouse(int button, int state, int x, int y);									//	what to do when the mouse is down						
void mouseDrag(int x, int y);													//	what to do when mouse moved while held down			
void keydown(unsigned char key, int x, int y);									//	what to do when a key is struck							
void specialKeyDown(int key, int x, int y);										//	what to do when a special key is struck					
void rightKeyMenu(int value);													//	what to do when a menu item is chosen

void printHelp();
void drawAxes();															//	function to draw X, Y, Z axes
void drawGrid();															//	function to grid on z = 0 plane

void initInterface()														//	initialize the interface								
	{ // initInterface()
	GLfloat light1_specular[]={0.0,0.0,1.0,1.0};
	windowWidth = windowSize;												//	set the overall window width							
	windowHeight = windowSize;												//	and set the window height								
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);						//	start off with double-buffering, z-depth, &c					
	glutInitWindowSize(windowWidth, windowHeight);								//	set the initial window size								
	glutCreateWindow("COMP3003 Lab 2");										//	create a window						
	glutDisplayFunc(display);												//	set the display function								
	glutReshapeFunc(reshape);												//	set the reshape function								
	glutMouseFunc(mouse);													//	set the mouse function								
	glutMotionFunc(mouseDrag);												//	set the mouse-dragged function							
	glutKeyboardFunc(keydown);												//	set the keystroke function								
	glutSpecialFunc(specialKeyDown);											//	and one for special (i.e. non-ASCII) strokes, too				
	glutCreateMenu(rightKeyMenu);												//	create a menu for the right mouse button
	glutAddMenuEntry("Toggle Axes", 'a');
	glutAddMenuEntry("Toggle Black Background", 'b');
	glutAddMenuEntry("Toggle Full Screen", 'f');
	glutAddMenuEntry("Toggle Ground Plane Grid", 'g');
	glutAddMenuEntry("Make Grid Larger", '+');
	glutAddMenuEntry("Make Grid Smaller", '-');
	glutAddMenuEntry("Toggle Smooth Shading", 's');
	glutAddMenuEntry("Toggle Wireframe", 'w');
	glutAddMenuEntry("Dump Parameters to Console", 'd');
	glutAddMenuEntry("Print Help to Console", 'h');
	glutAddMenuEntry("Quit", 'q');
	glutAttachMenu(GLUT_RIGHT_BUTTON);	

	glutIdleFunc(idle);
	glMatrixMode(GL_PROJECTION);												//	first set up matrix for the viewing volume					
	glOrtho(-1.0, 1.0, -1.0, 1.0, 0.001, 100000.0);								//	set to orthogonal rendering							
	glTranslatef(0, 0, -20.0);												//	translate the model matrix									
 	glMatrixMode(GL_MODELVIEW);												//	switch to matrix for basis vectors at eye					
	glShadeModel(GL_SMOOTH);													//	use flat lighting										
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);							// 	specify the position of the light							
	glEnable(GL_LIGHT0);													// 	switch light #0 on									
	glEnable(GL_LIGHTING);		
	glEnable(GL_DEPTH_TEST);													//	make sure depth buffer is switched on					
	glEnable(GL_NORMALIZE);													//	normalize normal vectors for safety

	Ball_Init(&ball);														//	initialize the arcball									
	Ball_Place(&ball, qOne, 0.75);											//	place the arcball (at 3/4 of window size)					
	printHelp();
	} //	end of initInterface() 

void printHelp()
	{ // printHelp()
	printf("Button: Function:\n");
   	printf("Left:   Rotate (ArcBall control)\n");
    	printf("Middle: Zoom\n");
    	printf("Right:  Menu\n");
    	printf("Key:    Function:\n");
    	printf("Arrows: Translate Image\n");
	printf("a:      Toggle axes\n");
    	printf("b:      Toggle black / white background\n");
	printf("f:      Toggle full-screen\n");
	printf("g:      Toggle ground plane grid\n");
    	printf("s:      Toggle smooth shading\n");
    	printf("w:      Toggle wireframe rendering\n");
	printf("+/-:    Increase / decrease grid size\n");
	printf("</>:    Zoom in / out\n");
	printf("\n");
    	printf("d:      Dump parameters to print\n");
	printf("h:      Print this help\n");
	printf("q:      Quit\n");
	} // printHelp()

void mouse(int button, int state, int x, int y)									//	what to do when the mouse is down						
	{
	if ((button == GLUT_LEFT_BUTTON) && (glutGetModifiers() & GLUT_ACTIVE_SHIFT))		//	left button + shift
		button = GLUT_RIGHT_BUTTON;											//	convert to middle button
	else if ((button == GLUT_LEFT_BUTTON) && (glutGetModifiers() & GLUT_ACTIVE_CTRL))	//	left button + shift
		button = GLUT_MIDDLE_BUTTON;											//	convert to middle button
		
	if (button == GLUT_RIGHT_BUTTON)											//	on a right button click								
		{
		if (state == GLUT_DOWN)												//	and the button is down								
			{
			dragMode = dragObject;											//	drag the entire object										
			dragOld_x = x; dragOld_y = y;										//	set the initial coordinates of the drag						
			} // end of start object-dragging 
		} // end of shift-button 
	else if (button == GLUT_LEFT_BUTTON)										//	on a left button click									
		{
		if (state == GLUT_DOWN)												//	on a mouse down									
			{
			HVect vNow;													//	vector type for passing to ball functions					
			dragMode = dragBall;											//	drag the arcball to rotate									
			vNow.x = (2.0 * x - windowWidth)/windowWidth;						//	set the vector										
			vNow.y = -(2.0 * y - windowHeight)/windowHeight;						//	in both dimensions									
			Ball_Mouse(&ball, vNow);											//	and pass it to the Ball functions							
			Ball_BeginDrag(&ball);											//	start dragging										
			}
		if (state == GLUT_UP) 												//	on a mouse up										
			{
			Ball_EndDrag(&ball);											//	stop dragging										
			}
		glutPostRedisplay();												//	force a redisplay										
		} // end of ordinary drag case 
	else if (button == GLUT_MIDDLE_BUTTON)										//	middle-button click									
		{
		if (state == GLUT_DOWN)												//	and the button is down								
			{
			dragMode = dragScale;											//	drag the scale of the object									
			dragOld_y = y;													//	set the initial coordinates of the drag						
			} // end of start scale-dragging 
		} // end of drag scale case 
	}  // end of mouse() 

void mouseDrag(int x, int y)													//	what to do when mouse moved while held down			
	{		
	if (dragMode == dragBall)												//	if we are using the arcball to rotate						
		{
		HVect vNow;														//	vector type for passing to ball functions					
		vNow.x = (2.0 * x - windowWidth)/windowWidth;							//	set the vector										
		vNow.y = -(2.0 * y - windowHeight)/windowHeight;							//	in both dimensions									
		Ball_Mouse(&ball, vNow);												//	and pass it to the Ball functions							
		glutPostRedisplay();												//	force a redisplay										
		} // end of case of dragBall 
	else if (dragMode == dragObject)											//	if we are using it to translate							
		{
		int mhw = (windowHeight < windowWidth) ? windowHeight : windowWidth;			//	find the smaller of the two values						
		float pixelScale = (float)(scale *2.0)/mhw;								//	compute the "size" of a pixel							
		offset_x -= pixelScale * (x - dragOld_x);								//	change the x offset									
		offset_y += pixelScale * (y - dragOld_y);								//	and the y offset										
		dragOld_x = x; dragOld_y = y;											//	and update the stored values							
		reshape(windowWidth, windowHeight);									//	call reshape to update the projection matrix and window				
		} // end of case of dragObject 
	else if (dragMode == dragScale)											//	if we are in dragScale mode							
		{
		int mhw = (windowHeight < windowWidth) ? windowHeight : windowWidth;			//	find the smaller of the two values						
		float pixelScale = (float)4.0/mhw;										//	compute the "size" of a pixel							
		scale *= pow(10.0, pixelScale*(y - dragOld_y));							//	do a logarithmic scale								
		dragOld_y = y;														//	and update the stored value							
		reshape(windowWidth, windowHeight);									//	call reshape to update the projection matrix and window				
		}
	} // end of mouseDrag() 

void reshape(int width, int height)											//	routine to call when window reshaped					
	{
	windowWidth = width; windowHeight = height;									//	reset the stored values								
		
	if (width < 10) 														//	if the window is shrunk too far							
		{
		glutReshapeWindow(10, height);										//	reset the size										
		return;
		}
	if (height < 10) 														//	if the window is shrunk too far							
		{
		glutReshapeWindow(width, 10);											//	reset the size										
		return;
		}
	aspectRatio = (float)width/(float)height;									//	reset the aspect ratio									
	if (aspectRatio > maxAspectRatio)											//	if it is outside the legal range							
		{
		glutReshapeWindow((int) (maxAspectRatio * height), height);					//	ask for another resize									
		aspectRatio = maxAspectRatio;											//	and set the aspect ratio								
		} //	end of case outside range 
	if (aspectRatio < 1.0/maxAspectRatio)										//	if it is outside the legal range							
		{
		glutReshapeWindow((int) (maxAspectRatio * width), width);					//	ask for another resize									
		aspectRatio = 1.0/maxAspectRatio;										//	and set the aspect ratio								
		} //	end of case outside range 
	glMatrixMode(GL_PROJECTION);												//	first set up matrix for the viewing volume					
 	glLoadIdentity();														//	reset to I											
	glViewport(0, 0, windowWidth, windowHeight);									//	reset the viewport									
	if (aspectRatio > 1.0)													//	if width is greater									
		glOrtho(-scale, scale, (-scale/aspectRatio), (scale/aspectRatio), -scale*3.0, scale*3.0);		//	reset the projection matrix								
	else // i.e.  (aspectRatio < 1.0) 											//	if width is greater									
		glOrtho((-scale *aspectRatio), (scale *aspectRatio), -scale, scale, -scale*3.0, scale*3.0);	//	reset the projection matrix								
	glutPostRedisplay();													//	make sure that it displays to start with					
	} //	end of reshape() 

void keydown(unsigned char key, int x, int y)									//	what to do when a key is struck							
	{
	switch (key)															//	switch, based on the key								
		{
		case 'b':
			blackBackground = !blackBackground;								//	toggle use of black background							
			break;
		case 'd': 	
		case 'D':															//	dump parameters to output							
			printf("Parameters are:\n");
			printf("Axes:              %s\n", showAxes ? "on" : "off");
			printf("Background:        %s\n", blackBackground ? "black" : "white");
			printf("Full Screen:       %s\n", isFullScreen ? "yes" : "no");
			printf("Grid:              %s\n", showGrid ? "yes" : "no");
			printf("Grid Size:         %d\n", nGridLines * 2 + 1);
			printf("Scale:             %f\n", scale);
			printf("Shading:           %s\n", smoothShading ? "smooth" : "flat");
			printf("Wireframe:         %s\n", wireFrame ? "on" : "off");
			break;
		case 'f':															//	full-screen toggle										
			isFullScreen = !isFullScreen;
			if (isFullScreen)
				{
				oldWindowWidth = windowWidth; oldWindowHeight = windowHeight;
				glutFullScreen();
				}
			else
				glutReshapeWindow(oldWindowWidth, oldWindowHeight);
			break;
		case 'q':															//	time to quit										
			if (isFullScreen)
				glutReshapeWindow(oldWindowWidth, oldWindowHeight);
			exit(0);														//	bail out of the program								
		case 's':
			smoothShading = !smoothShading;
			break;
		case 'w':
			wireFrame = !wireFrame;
			break;
		case 'h':
			printHelp();
			break;
		case 'g':
			showGrid = !showGrid;
			break;
		case 'a':
			showAxes = !showAxes;
			break;
		case ' ':
					animationOn = !animationOn;
					break;
		case '+':
			nGridLines++; 
			if (nGridLines > 100) nGridLines = 100;
			break;
		case '-':
			nGridLines--;
			if (nGridLines < 1) nGridLines = 0;
			break;
		case '>':
			scale *= 1.01;
			break;
		case '<':
			scale /= 1.01;
			break;
		} // end of switch 
	glutPostRedisplay();													//	force redisplay										
	} // end of keydown() 

void specialKeyDown(int key, int x, int y)										//	what to do when a special key is struck					
	{
	switch (key)															//	switch, based on the key								
		{
		case GLUT_KEY_UP:													//	up arrow							
			offset_y -= 0.01 * scale;
			break;
		case GLUT_KEY_DOWN:													//	down arrow							
			offset_y += 0.01 * scale;
			break;
		case GLUT_KEY_LEFT:													//	left arrow							
			offset_x += 0.01 * scale;
			break;
		case GLUT_KEY_RIGHT:												//	right arrow							
			offset_x -= 0.01 * scale;
			break;
		} // end of switch 
		glutPostRedisplay();												//	force redisplay										
	} // end of specialKeyDown() 

void display()																//	routine that describes what to draw						
	{
	GLfloat mNow[16];														//	local matrix for ball routines							
	glShadeModel(smoothShading ? GL_SMOOTH : GL_FLAT);							//	specify type of shading										
	Ball_Update(&ball);														//	update the data for the ball								
	Ball_Value(&ball, mNow);													//	retrieve the ball's position as a matrix						
	glMatrixMode(GL_MODELVIEW);												//	make sure that we are set to the model matrix				
	if (blackBackground) glClearColor(0.0, 0.0, 0.0, 1.0);							//	and set the "clear" colour to black						
	else glClearColor(1.0, 1.0, 1.0, 1.0);										//	or maybe that was white								
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);							//	clear the window to black								
	glPushMatrix();														//	push the GL stack to get a new matrix						
	glLoadIdentity();														//	load the identity matrix								
	glTranslatef((float)-offset_x, (float)-offset_y, 0);							//	offset the position									
	glMultMatrixf(mNow);													//	multiply by this matrix								
	glRotatef(-87.0, 1.0, 0.0, 0.0);
	if (showAxes) drawAxes();												//	draw axes if they are turned on
	if (showGrid) drawGrid();												//	ditto with ground plane grid
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, blackColour);						//	set default colour
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, greyColour);				//	but they do emit

	Render();																//	do the actual rendering
	glPopMatrix();															//	revert to the old matrix								
  	glutSwapBuffers();														//	swap buffers for smoother rendering						
	} //	end of display() 

void rightKeyMenu(int value)													//	what to do when a menu item is chosen
	{ // rightKeyMenu()
	keydown(value, 10, 10);													//	fake it by passing it through to keydown()
	} // rightKeyMenu()

//	main()
int main(int argc, char **argv)												//	the main routine that sets things running
	{
	glutInit(&argc, argv);													//	initialize the GLUT toolkit 							
	initInterface();														//	initialize the interface								
	glutMainLoop();														//	start up the event loop								
	return 0;																//	return a happy camper code							
	} //	end of main() 

void drawAxes()															//	render the axes of the coordinate system
	{ // drawAxes()
	GLfloat *axisColour = blackBackground ? whiteColour : blackColour;				//  choose the colour of the axes
	
	glMatrixMode(GL_MODELVIEW);												//	switch to modelview
	glPushMatrix();														//	push a matrix on the stack
//	glTranslatef(-xVoxels+1, -yVoxels+1, -zVoxels+1);								//  offset to put axes in right place
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blackColour);				//	edges don't reflect
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, axisColour);						//	but they do emit
	glBegin(GL_LINES);														//	start drawing lines
	glVertex3f(0.0, 0.0, 0.0);	glVertex3f(nGridLines + 1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);	glVertex3f(0.0, nGridLines + 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);	glVertex3f(0.0, 0.0, nGridLines + 1.0);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, blackColour);						//	reset emissive colour
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteColour);				//	set reflective colour
	glMatrixMode(GL_MODELVIEW);												//	switch to modelview
	glPushMatrix();														//	push a matrix on the stack
	glTranslatef(0.0, 0.0, nGridLines + 1.0);									//	move to end of z axis
	glutSolidCone(0.02*nGridLines, 0.1*nGridLines, 10, 2);							//	draw a solid cone for the z-axis
	glRotatef(90.0, 0.0, 1.0, 0.0);											//	rotate to draw in z=0 plane
	glTranslatef(0.0, 0.1*nGridLines, 0.0);										//	move away slightly
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blackColour);				//	edges don't reflect
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, axisColour);						//	but they do emit
	glScalef(0.001*nGridLines, 0.001*nGridLines, 0.001*nGridLines);					//	scale down
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'Z');									//	and draw the letter Z
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, blackColour);						//	but they do emit
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteColour);				//	set reflective colour
	glPopMatrix();															//	pop matrix off stack
	glPushMatrix();														//	push a matrix on the stack
	glTranslatef(0.0, nGridLines + 1.0, 0.0);									//	move to end of y axis
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.02*nGridLines, 0.1*nGridLines, 10, 2);							//	draw a solid cone for the z-axis
	glRotatef(90.0, 1.0, 0.0, 0.0);											//	rotate to draw in y=0 plane
	glTranslatef(0.1*nGridLines, 0.0, 0.0);										//	move away slightly
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blackColour);				//	edges don't reflect
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, axisColour);						//	but they do emit
	glScalef(0.001*nGridLines, 0.001*nGridLines, 0.001*nGridLines);					//	scale down
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'Y');									//	and draw the letter Z
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, blackColour);						//	but they do emit
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteColour);				//	set reflective colour
	glPopMatrix();															//	pop matrix off stack
	glPushMatrix();														//	push a matrix on the stack
	glTranslatef(nGridLines + 1.0, 0.0, 0.0);									//	move to end of x axis
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glutSolidCone(0.02*nGridLines, 0.1*nGridLines, 10, 2);							//	draw a solid cone for the x-axis
	glRotatef(90.0, 0.0, 1.0, 0.0);											//	rotate to draw in x=0 plane
	glTranslatef(0.0, 0.1*nGridLines, 0.0);										//	move away slightly
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blackColour);				//	edges don't reflect
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, axisColour);						//	but they do emit
	glScalef(0.001*nGridLines, 0.001*nGridLines, 0.001*nGridLines);					//	scale down
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'X');									//	and draw the letter X
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, blackColour);						//	but they do emit
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteColour);				//	set reflective colour
	glPopMatrix();															//	pop matrix off stack
	glMatrixMode(GL_MODELVIEW);												//	switch to modelview
	glPopMatrix();															//	pop matrix off stack
	} // drawAxes()

void drawGrid()															//	function to grid on z = 0 plane
	{ // drawGrid()
	int x, y;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blackColour);				//	edges don't reflect
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, greyColour);						//	but they do emit

	glMatrixMode(GL_MODELVIEW);												//	switch to the modelview
	glPushMatrix();														//	make a copy of the matrix	
	for (x = -nGridLines; x <= nGridLines; x++)									
		{ // for each x
		if (x % 5)
			glLineWidth(1.0);
		else
			glLineWidth(4.0);
		glBegin(GL_LINES);
		glVertex3i(x, -nGridLines, 0);
		glVertex3i(x, +nGridLines, 0);
		glEnd();
		} // for each x	
	for (y = -nGridLines; y <= nGridLines; y++)									
		{ // for each y
		if (y % 5)
			glLineWidth(1.0);
		else
			glLineWidth(4.0);
		glBegin(GL_LINES);
		glVertex3i(-nGridLines, y, 0);
		glVertex3i(+nGridLines, y, 0);
		glEnd();
		} // for each y	
	glLineWidth(1.0);
	glPopMatrix();	
	} // drawGrid()

void idle()
	{ // idle() 
	if (! animationOn) return;
	clockTime++; if (clockTime > cycleLength) clockTime = 0;
	Animate(clockTime);
	glutPostRedisplay();
	} // idle() 