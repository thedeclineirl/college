#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "render.h"
#include "objects.h"

#ifndef PI
#define PI 3.1415926536
#endif

/* Colour pallet will help you build your man/woman */

static GLfloat black_colour[] 	= { 0.0, 0.0, 0.0 };
static GLfloat white_colour[] 	= { 1.0, 1.0, 1.0 };
static GLfloat grey_colour[] 	= { 0.5, 0.5, 0.5 };

static GLfloat red_colour[] 	= { 1.0, 0.0, 0.0 };
static GLfloat orange_colour[] 	= { 1.0, 0.5, 0.0 };
static GLfloat yellow_colour[] 	= { 1.0, 1.0, 0.0 };
static GLfloat green_colour[] 	= { 0.0, 1.0, 0.0 };
static GLfloat blue_colour[] 	= { 0.0, 0.0, 1.0 };
static GLfloat indigo_colour[] 	= { 0.0, 0.0, 0.5 };
static GLfloat violet_colour[] 	= { 0.5, 0.5, 0.5 };

static GLfloat cyan_colour[] 	= { 0.0, 1.0, 1.0 };
static GLfloat magenta_colour[] = { 1.0, 0.0, 1.0 };
static GLfloat brown_colour[] 	= { 0.5, 0.25, 0.0 };
static GLfloat dkgreen_colour[]	= { 0.0, 0.5, 0.0 };
static GLfloat pink_colour[] 	= { 1.0, 0.6, 0.6 };

/* variable for controlling length of animation cycle */
int cycleLength = 600;

/* Global body variables used to set the position of your character in space */
float BODY_THETA          = 0.0f;
float BODY_X              = 0.0f;
float BODY_Y              = 0.0f;

/* Upper body variables, used to set pose */
float LEFT_ARM_UPPER_THETA     = 0.0f;
float RIGHT_ARM_UPPER_THETA    = 0.0f;
float LEFT_ARM_LOWER_THETA     = 0.0f;
float RIGHT_ARM_LOWER_THETA    = 0.0f;

/* Lower body variables, used to set pose */
float RIGHT_LEG_UPPER_THETA   = 0.0f;
float LEFT_LEG_UPPER_THETA    = 0.0f;
//float RIGHT_LEG_LOWER_THETA = 0.0f;
float RIGHT_LEG_LOWER_THETA = 0.0f;
float LEFT_LEG_LOWER_THETA  = 0.0f;

float DIRN=1;

/* Functions locally build the man/woman and features */
void drawPelvis(){

	setColour(white_colour);
		glScalef( 5.0f,  2.7f, 2.0f );
		drawCube();
		glScalef( 0.2f,  (1.0f/2.7f), 0.5f );
	/** TO DO : CODE GOES HERE **/

}

void drawBody(){
		setColour(yellow_colour);
		glScalef( 5.0f, 2.7f, 4.6f );
		drawCube();
		glScalef(0.2f, (1.0f/2.7f), (1.0f/4.6f));
	// code goes here
}

void drawHead(){
		setColour(pink_colour);
		glScalef( 2.0f, 2.0f, 2.0f );
		drawSphere(30,30);
		glScalef( 0.5f, 0.5f, 0.5f );
}
void drawJoint(){
	setColour(blue_colour);
	glScalef( 0.8f, 0.8f, 0.8f );
	drawSphere(20, 20);
	glScalef( 1.25f, 1.25f, 1.25f );
}

void drawFoot(){
	setColour(yellow_colour);
	glScalef( 1.0f, 2.0f, 1.0f );
	drawCube();
	glScalef( 0.0f, 0.5f, 0.0f );
}

void drawHand(){
	setColour(indigo_colour);
	glScalef( 1.2f, 0.5f, 1.6f );
	drawCube();
	glScalef( (1.0f/1.2f), (1.0f/0.5f), (1.0f/1.6f));
}

void drawLeftUpperLeg(){
	setColour(pink_colour);
	glScalef( 1.5f, 1.5f, 1.5f );
	drawVertCylinder(30, 2.0, 0.4);
	glScalef( (1.0f/1.5f), (1.0f/1.5f), (1.0f/1.5f) );
}

void drawLeftLowerLeg(){
	setColour(green_colour);
	glScalef( 1.5f, 1.5f, 1.5f );
	drawVertCylinder(30, 2.0, 0.4);
	glScalef( (1.0f/1.5f), (1.0f/1.5f), (1.0f/1.5f) );
}

void drawRightUpperLeg(){
	setColour(pink_colour);
	glScalef( 1.5f, 1.5f, 1.5f );
	drawVertCylinder(30, 2.0, 0.4);
	glScalef( (1.0f/1.5f), (1.0f/1.5f), (1.0f/1.5f) );
}

void drawRightLowerLeg(){
	setColour(green_colour);
	glScalef( 1.5f, 1.5f, 1.5f );
	drawVertCylinder(30, 2.0, 0.4);
	glScalef( (1.0f/1.5f), (1.0f/1.5f), (1.0f/1.5f) );
}

void drawLeftUpperArm(){
	setColour(red_colour);
	glScalef( 1.5f, 1.5f, 1.5f );
	drawVertCylinder(30, 2.0, 0.4);
	glScalef( (1.0f/1.5f), (1.0f/1.5f), (1.0f/1.5f) );
}

void drawRightUpperArm(){
	setColour(red_colour);
	glScalef( 1.5f, 1.5f, 1.5f );
	drawVertCylinder(30, 2.0, 0.4);
	glScalef( (1.0f/1.5f), (1.0f/1.5f), (1.0f/1.5f) );
}

void drawLeftForeArm(){
	setColour(yellow_colour);
	glScalef( 1.5f, 1.5f, 1.5f );
	drawVertCylinder(30, 2.0, 0.4);
	glScalef( (1.0f/1.5f), (1.0f/1.5f), (1.0f/1.5f) );
}

void drawRightForeArm(){
	setColour(yellow_colour);
	glScalef( 1.5f, 1.5f, 1.5f );
	drawVertCylinder(30, 2.0, 0.4);
	drawVertCylinder(30, 2.0, 0.4);
	glScalef( (1.0f/1.5f), (1.0f/1.5f), (1.0f/1.5f) );
}
/* This function allows you to set an articulated model of Sponge Bob */
void drawMan(){
	/** CONSTRUCT YOUR ARTICULATED MODEL HERE **/
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
		glTranslatef( BODY_X, BODY_Y, 0.0f );
		glRotatef( BODY_THETA, 0.0f, 0.0f, 1.0f );
		
		if(axesOn) drawAxes();
		glTranslatef( 6.0f, 0.0f, 10.0f );
		drawPelvis();	
		glPushMatrix();
			glTranslatef( 0.0f, 0.0f, 3.3f );
			drawBody();
			glPushMatrix();
				glTranslatef( 0.0f, 0.0f, 4.0f );
				drawHead();
			glPopMatrix();	
					
			glPushMatrix(); //Draws left arm
				glTranslatef( 3.0f, 0.0f, 2.0f );
				glRotatef(LEFT_ARM_UPPER_THETA, 1.0,0.0,0.0);
				drawJoint(); //left shoulder
				glPushMatrix();
					glTranslatef( 0.0f, 0.0f, -3.5f );
					drawLeftUpperArm();
					glPushMatrix();
						glTranslatef( 0.0f, 0.0f, -0.5f );
						drawJoint(); //left elbow
						glPushMatrix();
							glTranslatef( 0.0f, 0.0f, -3.5f );
							drawLeftForeArm();
							glPushMatrix();
								glTranslatef( 0.0f, 0.0f, -0.7f );
								drawHand(); //left hand
							glPopMatrix();
						glPopMatrix(); 
					glPopMatrix();
				glPopMatrix(); 
			glPopMatrix();

			glPushMatrix(); //Draws right arm
				glTranslatef( -3.0f, 0.0f, 2.0f );
				glRotatef(RIGHT_ARM_UPPER_THETA, 1.0,0.0,0.0);
				drawJoint(); //right shoulder
				glPushMatrix();
					glTranslatef( 0.0f, 0.0f, -3.5f );
					drawRightUpperArm();
					glPushMatrix();
						glTranslatef( 0.0f, 0.0f, -0.5f );
						drawJoint(); //right elbow	
						glPushMatrix();
							glTranslatef( 0.0f, 0.0f, -3.5f );
							drawRightForeArm();
							glPushMatrix();
								glTranslatef( 0.0f, 0.0f, -0.7f );
								drawHand(); //right hand
							glPopMatrix();
						glPopMatrix(); 
					glPopMatrix();
				glPopMatrix(); 
			glPopMatrix();		
		glPopMatrix(); 
				
		glPushMatrix(); //draws left leg
			glTranslatef( 1.6f, 0.0f, -1.5f );
			glRotatef(LEFT_LEG_UPPER_THETA, 1.0,0.0,0.0);
			drawJoint(); //left hip
			glPushMatrix();
				glTranslatef( 0.0f, 0.0f, -3.5f );
				drawLeftUpperLeg();
				glPushMatrix();
					glTranslatef( 0.0f, 0.0f, -0.5f );
					drawJoint(); //left knee
					glPushMatrix();
						glTranslatef( 0.0f, 0.0f, -3.5f );
						drawLeftLowerLeg();
						glPushMatrix();
							glTranslatef( 0.0f, -0.5f, -0.5f );
							drawFoot(); //draws left foot
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
			
		glPushMatrix(); //draws right leg
			glTranslatef( -1.6f, 0.0f, -1.5f );
			glRotatef(RIGHT_LEG_UPPER_THETA, 1.0,0.0,0.0);
			drawJoint(); //right hip
			glPushMatrix();
				glTranslatef( 0.0f, 0.0f, -3.5f );
				drawRightUpperLeg();
				glPushMatrix();
					glTranslatef( 0.0f, 0.0f, -0.5f );
					drawJoint(); //right knee
					glPushMatrix();
						glTranslatef( 0.0f, 0.0f, -3.5f );
						drawRightLowerLeg();
						glPushMatrix();
							glTranslatef( 0.0f, -0.5f, -0.5f );
							drawFoot(); //draws right foot
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

/* This function manipulates the pose of the character that depends on the time step */
void setPose(int time){
	
	float thetaRad =((float)time / (float)cycleLength) * 2.0f * PI;
	
	//upper body variables
	LEFT_ARM_UPPER_THETA = sin(thetaRad)*25;
	RIGHT_ARM_UPPER_THETA = -sin(thetaRad)*25;
	LEFT_ARM_LOWER_THETA     = 0.0f;
	RIGHT_ARM_LOWER_THETA    = 0.0f;

	// Lower body variables
	RIGHT_LEG_UPPER_THETA   = sin(thetaRad)*25;
	LEFT_LEG_UPPER_THETA    = -sin(thetaRad)*25;
	RIGHT_LEG_LOWER_THETA = 0.0f;
	LEFT_LEG_LOWER_THETA  = 0.0f; 
}

void Animate(int clockTime){ /* Animate() */
	float thetaRad =((float)clockTime / (float)cycleLength) * 2.0f * PI;
	BODY_THETA = ((float)clockTime/(float)cycleLength)*360.0f;
	BODY_X = cos(thetaRad)*-10.0f;
	BODY_Y = sin(thetaRad)*-10.0f;
	setPose(clockTime);

	if((clockTime%(cycleLength/4)==0)&&!((clockTime<3*cycleLength/4)&&(clockTime>cycleLength/4)))
		DIRN*=-1;
} /* Animate() */

/* routine that actually does the rendering */
void Render()
    { /* Render() */
	drawMan();
	drawTeapot();
		
	/** you can also build more objects and put them in your scene **/

    } /* Render() */
