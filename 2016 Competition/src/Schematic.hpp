#ifndef SCHEMATIC_H
#define SCHEMATIC_H

#include <WPILib.h>
#include "AHRS.h"
#include <math.h>
#include <cmath>

#include <IAutonomous.hpp>
#include <IComponent.hpp>

#define PI 3.14159265358

#define CONTROLLER_PRIMARY 0
#define CONTROLLER_SECONDARY 1
#define CONTROLLER_DEADBAND 0.10

#define GYRO_PORT 0

#define WEBCAM_PIXEL_WIDTH 320
#define WEBCAM_PIXEL_HEIGHT 240
#define WEBCAM_FOV 68.5
#define WEBCAM_TAN_FOV 0.414213 // tan(WEBCAM_FOV / 2) / ((2 * PI) * 360)

#define GOAL_GROUND_HEIGHT 368.3
#define GOAL_WIDTH 20.5

#define DRIVE_ANGLE_ERROR 0.05
#define DRIVE_DISTANCE_ERROR 0.09

#define DRIVE_FT_TO_ENCODER 12.60 // 256 Ticks Per Revolution: ((ticks / 1rev) * (3rev / 1rev) * (20rev / 64revs) * (1rev / 19.047in))
#define SHOOTER_SPEED_DEADBAND 0.10

#define DRIVE_ANGLE_TOLERENCE 0.05
#define DRIVE_RAMP_SPEED 0.1 // TODO: better ramp
#define DRIVE_SPEED_MULTIPLIER 1.00
#define DRIVE_SPEED_ROCK_WALL 0.7
#define DRIVE_SPEED_ROUGH_TERRAIN 0.5
#define DRIVE_DISTANCE_PID 0.04, 0, 0

#define JOYSTICK_X 1
#define JOYSTICK_A 2
#define JOYSTICK_B 3
#define JOYSTICK_Y 4
#define JOYSTICK_TRIGGER_LEFT 7
#define JOYSTICK_TRIGGER_RIGHT 8
#define JOYSTICK_BUMPER_LEFT 5
#define JOYSTICK_BUMPER_RIGHT 6
#define JOYSTICK_BACK 9
#define JOYSTICK_START 10
#define JOYSTICK_AXIS_BUTTON_LEFT 11
#define JOYSTICK_AXIS_BUTTON_RIGHT 12
#define JOYSTICK_AXIS_LEFT_X 0
#define JOYSTICK_AXIS_LEFT_Y 1
#define JOYSTICK_AXIS_RIGHT_X 2
#define JOYSTICK_AXIS_RIGHT_Y 3

#endif
