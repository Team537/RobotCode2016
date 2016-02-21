#ifndef SCHEMATIC_H
#define SCHEMATIC_H

#include <WPILib.h>
#include "AHRS.h"
#include <math.h>
#include <cmath>

#include <IAutonomous.hpp>
#include <IComponent.hpp>

#define PI 3.14159265358
#define G -9.80665

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

#define DRIVE_FT_TO_ENCODER 504.0163 // 1000 Edges Per Revolution: ((ticks / 1rev) * (3rev / 1rev) * (64revs / 20rev) * (1rev / 19.047in))
#define DRIVE_ANGLE_TOLERENCE 1.25
#define DRIVE_DISTANCE_TOLERENCE 250
#define DRIVE_SPEED_MULTIPLIER 1.00
#define DRIVE_CLIMBING_MULTIPLIER 0.25
#define DRIVE_DEFENCE_MOAT 1.35
#define DRIVE_DEFENCE_ROCK_WALL 1.15
#define DRIVE_DEFENCE_ROUGH_TERRAIN 1.0
#define DRIVE_DEFENCE_RAMP_PARTS 1.25

#define SHOOTER_SPEED_DEADBAND 0.07
#define SHOOTER_ANGLE 45 // TODO
#define MS_TO_SPEED 0.0375 // TODO

#define COLLECTOR_SPEED 0.75f

#define JOYSTICK_X 1
#define JOYSTICK_A 2
#define JOYSTICK_B 3
#define JOYSTICK_Y 4
#define JOYSTICK_BUMPER_LEFT 5
#define JOYSTICK_BUMPER_RIGHT 6
#define JOYSTICK_TRIGGER_LEFT 7
#define JOYSTICK_TRIGGER_RIGHT 8
#define JOYSTICK_BACK 9
#define JOYSTICK_START 10
#define JOYSTICK_AXIS_BUTTON_LEFT 11
#define JOYSTICK_AXIS_BUTTON_RIGHT 12
#define JOYSTICK_AXIS_LEFT_X 0
#define JOYSTICK_AXIS_LEFT_Y 1
#define JOYSTICK_AXIS_RIGHT_X 2
#define JOYSTICK_AXIS_RIGHT_Y 3

#endif
