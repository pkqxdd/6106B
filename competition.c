#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl2,  ,               sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           mb_left,       tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           front_left,    tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_4)
#pragma config(Motor,  port3,           back_left,     tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_3)
#pragma config(Motor,  port4,           front_right,   tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port5,           back_right,    tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port6,           fb_topleft,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           fb_bottomleft, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           fb_topright,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           fb_bottomright, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          mb_right,      tmotorVex393_HBridge, openLoop)
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#define competition

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

#include "Driver.h"


void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}


task autonomous()
{
#include "Autonomous.h"
}

task usercontrol()
{
#include "UserControls.h"
}
