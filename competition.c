#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Sensor, in1,    pot_fourbar_left, sensorPotentiometer)
#pragma config(Sensor, in2,    pot_fourbar_right, sensorPotentiometer)
#pragma config(Sensor, in3,    pot_chainbar,   sensorPotentiometer)
#pragma config(Sensor, in5,    pot_mb,         sensorPotentiometer)
#pragma config(Sensor, in6,    gyro_right,     sensorGyro)
#pragma config(Sensor, in7,    gyro_left,      sensorGyro)
#pragma config(Sensor, dgtl1,  en_front_left,  sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  en_front_right, sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  en_back_left,   sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  en_back_right,  sensorQuadEncoder)
#pragma config(Motor,  port1,           mb,            tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           front_left,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           front_right,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           fb_left,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           fb_right,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           chainbar_right,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           chainbar_left,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           back_left,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           back_right,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,           roller,    tmotorVex393_MC29, openLoop, reversed)

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define ever ;;
#define competition

#pragma platform(VEX2)

#pragma competitionControl(Competition)

#include "Vex_Competition_Includes.c"

#include "Driver.h"


int autonSel=0;
const int nAutons=5;
const string autonNames[5]={"Left 20 Points","Right 20 Points","Left 10 Points","Right 10 Points","Skill Challenge"};


void pre_auton() {
	bLCDBacklight=true;
	bStopTasksBetweenModes = true;
	bool wasPressed=false;
	for(ever){

		if (nLCDButtons)

		if (not wasPressed){
			if (nLCDButtons==0b001){
				if (autonSel>0) autonSel--;
				} else if (nLCDButtons==0b100){
				if (autonSel<nAutons-1) autonSel++;
			}
			wasPressed=true;
		}

		else {
			wasPressed=false;
		}
		if  (not bIfiRobotDisabled) return;
		displayLCDString(0,0,autonNames[autonSel]);
		displayLCDString(1,0,"Prev      Next");
		wait1Msec(100);

	}

}
#include "autonomousHelpers.h"

task autonomous() {
switch (autonSel){

case 0:
#include "autonomousTurnLeft20.h"
break;
case 1:
#include "autonomousTurnRight20.h"
break;
case 2:
#include "autonomousTurnLeft10.h"
break;
case 3:
#include "autonomousTurnRight10.h"
break;
case 4:
#include "skillChallenge.h"
break;

}
}

task usercontrol() {
		releaseWheels();
#include "UserControls.h"
}
