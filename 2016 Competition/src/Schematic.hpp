#ifndef SCHEMATIC_H
#define SCHEMATIC_H

#include <WPILib.h>
#include <math.h>
#include <cmath>

#include <IAutonomous.hpp>
#include <IComponent.hpp>

#define PI 3.14159268

#define CONTROLLER_PRIMARY 0
#define CONTROLLER_SECONDARY 1

#define JOYSTICK_DEADBAND 0.20

#define WEBCAM_PIXEL_WIDTH 320
#define WEBCAM_PIXEL_HEIGHT 240
#define WEBCAM_FOV 68.5
#define WEBCAM_TAN_FOV 0.414213 // tan(WEBCAM_FOV / 2) / ((2 * PI) * 360)

#define GOAL_GROUND_HEIGHT 368.3
#define GOAL_WIDTH 20.5

#define DRIVE_ANGLE_ERROR 0.05
#define DRIVE_DISTANCE_ERROR 0.09
#define DRIVE_FT_TO_ENCODER 2124 // TODO: FT to Encoder ticks!

#define DRIVE_AXIS_LEFT 1
#define DRIVE_AXIS_RIGHT 3
#define DRIVE_RAMP_SPEED 0.1
#define DRIVE_SPEED_MULTIPLIER 0.5

#endif