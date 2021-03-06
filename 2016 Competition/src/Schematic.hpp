#pragma once

#include <WPILib.h>
#include "AHRS.h"
#include <math.h>
#include <cmath>

#include <IAutonomous.hpp>
#include <IComponent.hpp>

class Schematic
{
    public:
        static void Init(Joystick* primary, Joystick* secondary, Joystick* tertiary, AHRS* ahrs);
        static Joystick* GetPrimary();
        static Joystick* GetSecondary();
        static Joystick* GetTertiary();
        static AHRS* GetGyro();
    private:
        static Joystick* joystickPrimary;
        static Joystick* secondaryPrimary;
        static Joystick* secondaryTertiary;
        static AHRS* gryo;
};

#define PI 3.14159
#define G -9.80665

#define COLLECTOR_SPEED 1.0f

#define DRIVE_ARCADE_MODE false
#define DRIVE_IN_TO_ENCODER 504.0163 // 1000 Edges Per Revolution: ((ticks / 1rev) * (3rev / 1rev) * (64revs / 20rev) * (1rev / 19.047in))
#define DRIVE_ANGLE_TOLERANCE 1.25
#define DRIVE_DISTANCE_TOLERANCE 250
#define DRIVE_SPEED_MULTIPLIER 1.00
#define DRIVE_PRIMARY_CLIMBING_MULTIPLIER 1.00
#define DRIVE_SECONDARY_CLIMBING_MULTIPLIER 0.45
#define DRIVE_TIMED_SPEED 0.75
#define DRIVE_DEFENSE_LOW_BAR 1.6
#define DRIVE_DEFENSE_RAMP_PARTS 1.4
#define DRIVE_DEFENSE_MOAT 2.7
#define DRIVE_DEFENSE_ROCK_WALL 2.7
#define DRIVE_DEFENSE_ROUGH_TERRAIN 1.6

#define SHOOTER_SPEED_TOLERANCE 50
#define SHOOTER_ANGLE 45 // TODO

#define WEBCAM_BOT_ANGLE 0 // TODO
#define WEBCAM_BOT_HEIGHT 18 // TODO
#define WEBCAM_PIXEL_WIDTH 320
#define WEBCAM_PIXEL_HEIGHT 240
#define WEBCAM_FOV 68.5
#define WEBCAM_TAN_FOV 0.414213 // tan(WEBCAM_FOV / 2) / ((2 * PI) * 360)

#define GOAL_GROUND_HEIGHT 368.3
#define GOAL_WIDTH 20.5

#define JOYSTICK_PRIMARY 0
#define JOYSTICK_SECONDARY 1
#define JOYSTICK_TERTIARY 3
#define JOYSTICK_DEADBAND 0.10
#define NEW_JOYSTICK true

#if NEW_JOYSTICK
#define JOYSTICK_A 1
#define JOYSTICK_B 2
#define JOYSTICK_X 3
#define JOYSTICK_Y 4
#define JOYSTICK_BUMPER_LEFT 5
#define JOYSTICK_BUMPER_RIGHT 6
#define JOYSTICK_BACK 7
#define JOYSTICK_START 8
#define JOYSTICK_BUTTON_LEFT 9
#define JOYSTICK_BUTTON_RIGHT 10
#define JOYSTICK_AXIS_LEFT_X 0
#define JOYSTICK_AXIS_LEFT_Y 1
#define JOYSTICK_TRIGGER_LEFT 2
#define JOYSTICK_TRIGGER_RIGHT 3
#define JOYSTICK_AXIS_RIGHT_X 4
#define JOYSTICK_AXIS_RIGHT_Y 5
#else
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
#define JOYSTICK_BUTTON_LEFT 11
#define JOYSTICK_BUTTON_RIGHT 12
#define JOYSTICK_AXIS_LEFT_X 0
#define JOYSTICK_AXIS_LEFT_Y 1
#define JOYSTICK_AXIS_RIGHT_X 2
#define JOYSTICK_AXIS_RIGHT_Y 3
#endif
