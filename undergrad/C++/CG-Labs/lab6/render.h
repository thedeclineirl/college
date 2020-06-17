#ifndef _RENDER_H
#define _RENDER_H

/* variable for controlling length of animation cycle */
extern int axesOn;

/** OpenGL lighting excercise:
  * 
  * This excercise will allow people to familiarise themselves with the openGL lighting model,
  * shading, colours and materials etc.
  *
  */

/* Part 1. No shading, no lighting, draw a cube with each vertex as a primary colour or a secondary colour
 *
 *	Primary Colours   : Red, Green, Blue
 *	Secondary Colours : Cyan, Magenta, Yellow
 *	All Colours Mixed : White
 *	Absence of Colour : Black
 *
 * This gives us a colour for each vertex of the cube
 *
 */

void DrawColourCube();


/* Part 2. shading and lighting enabled 
 *
 *	Primary Colours   : Red, Green, Blue
 *	Secondary Colours : Cyan, Magenta, Yellow
 *	All Colours Mixed : White
 *	Absence of Colour : Black
 *
 * Render a sphere at each vertex of the cube of each of the above colours
 *
 */

void DrawColourSpheres();

#endif

