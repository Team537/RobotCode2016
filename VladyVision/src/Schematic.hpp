#ifndef SCHEMATIC_H
#define SCHEMATIC_H

#include "WPILib.h"
#include <math.h>
#include <cmath>

#define PI 3.14159268

#define PRIMARY_CONTROLLER 0



#define JOYSTICK_DEADBAND 0.20
#define RAMP_SPEED .1

#define SPEED_MULTIPLIER 0.5


#define WEBCAM_PIXEL_WIDTH 320
#define WEBCAM_PIXEL_HEIGHT 240
#define WEBCAM_FOV 68.5
#define TAN_FOV 0.414213 // tan(WEBCAM_FOV / 2) / ((2 * PI) * 360)

#define GOAL_GROUND_HEIGHT 368.3
#define GOAL_WIDTH 20.5

#define LEFT_AXIS 1
#define RIGHT_AXIS 3


#endif
