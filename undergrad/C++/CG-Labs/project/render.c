#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "render.h"
#include "objects.h"
#include "texturePPM.h"

#ifndef PI
#define PI 3.1415926536
#endif

// Colour pallet

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

//texture variables
int isLoaded=0;
texture* tex;
texture* tex2;
texture* tex3;
texture* tex4;

//texture* tex3; is how a 3rd and subsequent texture is declared


/* variable for controlling length of animation cycle */
int cycleLength = 200;

/* Global body variables used to set the position of your character in space */
float BODY_THETA          = 0.0f;
float BODY_X              = -55.0f;
float BODY_Y              = 0.0f;

/* Upper body variables, used to set pose */
float LEFT_ARM_UPPER_THETA  = 0.0f;
float RIGHT_ARM_UPPER_THETA = 0.0f;
float LEFT_ARM_LOWER_THETA  = 0.0f;
float RIGHT_ARM_LOWER_THETA	= 0.0f;

/* Lower body variables, used to set pose */
float RIGHT_LEG_UPPER_THETA = 0.0f;
float LEFT_LEG_UPPER_THETA  = 0.0f;
float RIGHT_LEG_LOWER_THETA	= 0.0f;
float LEFT_LEG_LOWER_THETA  = 0.0f;

float DIRN=1;

void drawLight(){
	glDisable(GL_LIGHTING);
	
	
	
	
	glEnable(GL_LIGHTING);
	}


/* Functions locally build the man/woman and features */
void drawPelvis(){
	setColour(white_colour);
	glScalef( 5.0f,  2.7f, 2.0f );
	drawCube();
	glScalef( 0.2f,  (1.0f/2.7f), 0.5f );
}

void drawBody(){
	setColour(blue_colour);
	glScalef( 5.0f, 2.7f, 4.6f );
	drawCube();
	glScalef(0.2f, (1.0f/2.7f), (1.0f/4.6f));
}

void drawHead(){
	setColour(pink_colour);
	glScalef( 2.0f, 2.0f, 2.0f );
	drawSphere(30,30);	
	glScalef( 0.5f, 0.5f, 0.5f );
}

void drawEye(){
	setColour(white_colour);
	glScalef( 0.2f, 0.2f, 0.2f );
	drawSphere(30,30);	
	glScalef( 5.0f, 5.0f, 5.0f );
}

void drawNose(){
	setColour(pink_colour);
	glScalef( 0.2f, 0.5f, 0.2f );
	drawSphere(30,30);	
	glScalef( 5.0f, 2.5f, 5.0f );
}

void drawMouth(){
	setColour(red_colour);
	glScalef( 0.8f, 0.1f, 0.2f );
	drawSphere(30,30);	
	glScalef( (1.0f/0.8f), (1.0f/0.1f), (1.0f/0.2f) );
}

void drawJoint(){
	setColour(red_colour);
	glScalef( 0.8f, 0.8f, 0.8f );
	drawSphere(20, 20);
	glScalef( 1.25f, 1.25f, 1.25f );
}

void drawFoot(){
	setColour(black_colour);
	glScalef( 1.0f, 2.0f, 1.0f );
	drawCube();
	glScalef( 0.0f, 0.5f, 0.0f );
}

void drawHand(){
	setColour(pink_colour);
	glScalef( 1.2f, 0.5f, 1.6f );
	drawCube();
	glScalef( (1.0f/1.2f), (1.0f/0.5f), (1.0f/1.6f));
}

void drawLeftUpperLeg(){
	setColour(white_colour);
	glScalef( 1.5f, 1.5f, 1.5f );
	drawVertCylinder(30, 2.0, 0.4);
	glScalef( (1.0f/1.5f), (1.0f/1.5f), (1.0f/1.5f) );
}

void drawLeftLowerLeg(){
	setColour(pink_colour);
	glScalef( 1.5f, 1.5f, 1.5f );
	drawVertCylinder(30, 2.0, 0.4);
	glScalef( (1.0f/1.5f), (1.0f/1.5f), (1.0f/1.5f) );
}

void drawRightUpperLeg(){
	setColour(white_colour);
	glScalef( 1.5f, 1.5f, 1.5f );
	drawVertCylinder(30, 2.0, 0.4);
	glScalef( (1.0f/1.5f), (1.0f/1.5f), (1.0f/1.5f) );
}

void drawRightLowerLeg(){
	setColour(pink_colour);
	glScalef( 1.5f, 1.5f, 1.5f );
	drawVertCylinder(30, 2.0, 0.4);
	glScalef( (1.0f/1.5f), (1.0f/1.5f), (1.0f/1.5f) );
}

void drawLeftUpperArm(){
	setColour(blue_colour);
	glScalef( 1.5f, 1.5f, 1.5f );
	drawVertCylinder(30, 2.0, 0.4);
	glScalef( (1.0f/1.5f), (1.0f/1.5f), (1.0f/1.5f) );
}

void drawRightUpperArm(){
	setColour(blue_colour);
	glScalef( 1.5f, 1.5f, 1.5f );
	drawVertCylinder(30, 2.0, 0.4);
	glScalef( (1.0f/1.5f), (1.0f/1.5f), (1.0f/1.5f) );
}

void drawLeftForeArm(){
	setColour(pink_colour);
	glScalef( 1.5f, 1.5f, 1.5f );
	drawVertCylinder(30, 2.0, 0.4);
	glScalef( (1.0f/1.5f), (1.0f/1.5f), (1.0f/1.5f) );
}

void drawRightForeArm(){
	setColour(pink_colour);
	glScalef( 1.5f, 1.5f, 1.5f );
	drawVertCylinder(30, 2.0, 0.4);
	drawVertCylinder(30, 2.0, 0.4);
	glScalef( (1.0f/1.5f), (1.0f/1.5f), (1.0f/1.5f) );
}

/* This function allows you to set an articulated model of Sponge Bob */
void drawMan(){
	/** draws the model of the man **/
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
		glTranslatef( BODY_X, BODY_Y, 0.0f );
		glRotatef( BODY_THETA, 0.0f, 0.0f, 1.0f );
		
		/*
		 * for the purpose of translations 
		 * relative to the any body part
		 * glTranslatef(left-right,in-out,up-down);
		 */
		
		glTranslatef( 15.0f, 0.0f, 10.0f );
		drawPelvis();	
		glPushMatrix();
			glTranslatef( 0.0f, 0.0f, 3.3f );
			drawBody();
			glPushMatrix();
				glTranslatef( 0.0f, 0.0f, 4.0f );
				drawHead();
				glPushMatrix();
					glTranslatef( 0.5f, -1.8f, 0.8f );
					drawEye();
					glPushMatrix();
						glTranslatef( -1.0f, 0.0f, 0.0f );
						drawEye();
					glPopMatrix();
					glPushMatrix();
						glTranslatef( -0.5f, 0.0f, -0.2f );
						drawNose();
						glPushMatrix();
							glTranslatef( 0.0f, -0.1f, -1.0f );
							drawMouth();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
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
	
	float thetaRad =((float)time / (float)cycleLength) * 12.0f * PI;
	/*
	 * changing the float between cyclelength and PI
	 * changes the speed the limbs move at,
	 * higher number equates to faster movement of the limbs
	 */
	
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
	BODY_X = cos(thetaRad)*-55.0f;
	BODY_Y = sin(thetaRad)*-55.0f;
	setPose(clockTime);

	if((clockTime%(cycleLength/4)==0)&&!((clockTime<3*cycleLength/4)&&(clockTime>cycleLength/4)))
		DIRN*=-1;
} /* Animate() */

void loadTexture(){
	// for assigning and loading all textures needed
   	tex = loadPPM("sign2.ppm");
  	tex2 = loadPPM("grass.ppm");
  	tex3 = loadPPM("tarmac.ppm");
  	tex4 = loadPPM("leaves.ppm");
  	if(tex3 == 0){
  		printf("tex3 is null n/");  		
  	}
  	if(tex4 == 0){
  		printf("tex4 is null n/");  		
  	}	
	isLoaded=1;
}

void drawScenery(){
	/* drawScenery()*/
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->width, tex->height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->texBytes);		
		/*draw the sign + sign posts*/
		glPushMatrix();
			glTranslatef( -1.0f, -7.0f, 1.0f );
			glEnable(GL_TEXTURE_2D);
			drawPanel();
			glDisable(GL_TEXTURE_2D);
		
			glPushMatrix();
				setColour(black_colour);
				glTranslatef( 0.0f, 0.0f, -1.0f );
				glScalef(0.2f, 0.2f, 2.0f);
				drawVertCylinder(30, 1.0, 0.4);
				
				glPushMatrix();
					glTranslatef( 10.0f, 0.0f, 0.0f );
					drawVertCylinder(30, 1.0, 0.4);
					
				glPopMatrix();		
				
			glPopMatrix();
			
		glPopMatrix();
			
		glPushMatrix();
			glRotatef(120.0, 0.0, 0.0, 1.0);
			glTranslatef( -1.0f, -7.0f, 1.0f );
			glEnable(GL_TEXTURE_2D);
			drawPanel();
			glDisable(GL_TEXTURE_2D);
		
			glPushMatrix();
				setColour(black_colour);
				glTranslatef( 0.0f, 0.0f, -1.0f );
				glScalef(0.2f, 0.2f, 2.0f);
				drawVertCylinder(30, 1.0, 0.4);
			
				glPushMatrix();
					glTranslatef( 10.0f, 0.0f, 0.0f );
					drawVertCylinder(30, 1.0, 0.4);
				
				glPopMatrix();
				
			glPopMatrix();
			
		glPopMatrix();
		
		glPushMatrix();
			glRotatef(240.0, 0.0, 0.0, 1.0);
			glTranslatef( -1.0f, -7.0f, 1.0f );
			glEnable(GL_TEXTURE_2D);
			drawPanel();
			glDisable(GL_TEXTURE_2D);
		
			glPushMatrix();
				setColour(black_colour);
				glTranslatef( 0.0f, 0.0f, -1.0f );
				glScalef(0.2f, 0.2f, 2.0f);
				drawVertCylinder(30, 1.0, 0.4);
			
				glPushMatrix();
					glTranslatef( 10.0f, 0.0f, 0.0f );
					drawVertCylinder(30, 1.0, 0.4);
				
			glPopMatrix();
				
			glPopMatrix();
			
		glPopMatrix();
		/*^draw the sign + sign posts*/
		
		/*draw the roundabout*/
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex2->width, tex2->height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex2->texBytes);
		
		glPushMatrix();
			glScalef(10.0f, 10.0f, 0.7f);
			glEnable(GL_TEXTURE_2D);
				drawSphere(36, 36);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		/*draw the roundabout*/
			
} /* drawScenery()*/

void drawGround(){

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex3->width, tex3->height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex3->texBytes);
	
	/*draw ground*/
	glPushMatrix();
		setColour(grey_colour);
		glScalef(20.0f, 20.0f, 0.1f);
		glEnable(GL_TEXTURE_2D);
			drawSphere(36, 36);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
/* draws a path into the roundabout  */
 	glPushMatrix();
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glRotatef(25.0, 0.0, 1.0, 0.0);
		glTranslatef( 18.0f, 0.0f, -3.0f );
		glScalef(40.0f, 20.0f, 7.0f);
		glEnable(GL_TEXTURE_2D);
		drawPanel();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
//*/	
	/*draw ground*/	
}

void drawTree(){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex4->width, tex4->height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex4->texBytes);
	
	/*draws a tree*/
	glPushMatrix();
		//draw trunk
		setColour(brown_colour);
		glScalef(0.5f, 0.5f, 7.5f);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glTranslatef( 0.0f, 0.5f, 0.0f );
		drawCylinder(40);
	glPopMatrix();
	
	
	glPushMatrix();
		//draw leaves
		setColour(green_colour);
		glTranslatef( 0.0f, 0.0f, 7.5f );
		glScalef(4.0f, 4.0f, 4.0f);
		glEnable(GL_TEXTURE_2D);
			drawSphere(36, 36);
		glDisable(GL_TEXTURE_2D);	
	glPopMatrix();
	/*draw a tree*/
	
}


/* routine that actually does the rendering */
void Render()
    { /* Render() */
	if(!isLoaded){
			loadTexture();
		}
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		//printf("texBytes: %c \n", tex->texBytes);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->width, tex->height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->texBytes);
		//changes texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	
	
	glPushMatrix();
		glScalef(0.3, 0.3, 0.3);
		drawMan();
	glPopMatrix();
	
	glPushMatrix();
		drawScenery(); //draws the roundabout & chevron sign	
	glPopMatrix();
		
	glPushMatrix();
		drawTree();	//draws a tree in the centre of the roundabout
		
		glPushMatrix();
			glTranslatef( 0.0f, 20.0f, 0.0f );
			glScalef(0.5f, 0.5f, 0.5f);
			drawTree();	//draws a tree
			
			glPushMatrix();
				glRotatef(90.0, 0.0, 0.0, 3.0);
				glScalef(1.5f, 1.5f, 2.0f);
				glTranslatef( 0.0f, 17.0f, 0.0f );
				drawTree();	//draws a tree
			glPopMatrix();	
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef( 22.0f, 0.0f, 0.0f );
			glScalef(2.0f, 1.5f, 2.5f);
			drawTree();	//draws a tree				
		glPopMatrix();
		
		glPushMatrix();
			glRotatef(90.0, 0.0, 0.0, 3.0);
			glScalef(0.5f, 0.5f, 0.5f);
			glTranslatef( 11.0f, -3.5f, 0.0f );
			drawTree();	//draws a tree
		glPopMatrix();
		
		glPushMatrix();
			glRotatef(90.0, 0.0, 0.0, 3.0);
			glScalef(2.7f, 1.9f, 2.3f);
			glTranslatef( 8.0f, 10.5f, 0.0f );
			drawTree();	//draws a tree
		glPopMatrix();
		
	glPopMatrix();
		
	glPushMatrix();
		
		drawGround();	//draws a flat circular plain around the roundabout
	glPopMatrix();

    } /* Render() */
