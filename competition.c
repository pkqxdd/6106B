#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    pot_fourbar_left, sensorNone)
#pragma config(Sensor, in2,    pot_fourbar_right, sensorPotentiometer)
#pragma config(Sensor, in3,    pot_chainbar,   sensorPotentiometer)
#pragma config(Sensor, in4,    left_battery,   sensorAnalog)
#pragma config(Sensor, dgtl2,  ,               sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_5,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_6,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           mb_right,      tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port2,           front_left,    tmotorVex393_MC29, openLoop, encoderPort, I2C_4)
#pragma config(Motor,  port3,           front_right,   tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_3)
#pragma config(Motor,  port4,           fb_left,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           fb_right,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           roller,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           chainbar,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           back_left,     tmotorVex393_MC29, openLoop, encoderPort, I2C_5)
#pragma config(Motor,  port9,           back_right,    tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port10,          mb_left,       tmotorVex393_HBridge, openLoop, encoderPort, I2C_6)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


#define competition

#pragma platform(VEX2)


#pragma competitionControl(Competition)

#include "Vex_Competition_Includes.c"

#include "Driver.h"

void pre_auton() {
 bStopTasksBetweenModes = true;
#include "pre_auton.h"
}

#include "autonomousHelpers.h"

task autonomous() {

#include "Autonomous.h"
}

task usercontrol() {
//	stopTask(autonomous);
#include "UserControls.h"
}
