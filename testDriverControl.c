#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Sensor, in1,    pot_fourbar_left, sensorPotentiometer)
#pragma config(Sensor, in2,    pot_fourbar_right, sensorPotentiometer)
#pragma config(Sensor, in3,    pot_chainbar,   sensorPotentiometer)
#pragma config(Sensor, in5,    pot_mb,         sensorPotentiometer)
#pragma config(Sensor, in6,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  en_front_left,  sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  en_front_right, sensorQuadEncoder)
#pragma config(Motor,  port1,           mb,            tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           front_left,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           front_right,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           fb_left,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           fb_right,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           roller,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           chainbar,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           back_left,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           back_right,    tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "Driver.h"

task main
{
#include "UserControls.h"
}
