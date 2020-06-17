
/* variable for controlling length of animation cycle */
extern int cycleLength;
extern int axesOn;

void drawPelvis();

void drawBody();

void drawHead();

void drawJoint();

void drawFoot();

void drawHand();

void drawLeftUpperLeg();

void drawLeftLowerLeg();

void drawRightUpperLeg();

void drawRightLowerLeg();

void drawLeftUpperArm();

void drawRightUpperArm();

void drawLeftForeArm();

void drawRightForeArm();

void drawMan();

void setPose(int time);

void Animate(int clockTime);

/* routine that actually does the rendering */
void Render();



