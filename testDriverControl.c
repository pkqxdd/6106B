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

#include "Driver.h"

task main
{
#include "UserControls.h"
}
