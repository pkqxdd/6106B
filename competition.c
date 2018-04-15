#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Sensor, in1,    pot_lift_left, sensorPotentiometer)
#pragma config(Sensor, in2,    pot_lift_right, sensorPotentiometer)
#pragma config(Sensor, in3,    pot_chainbar,   sensorPotentiometer)
#pragma config(Sensor, in5,    pot_mg,         sensorPotentiometer)
#pragma config(Sensor, in6,    gyro_right,     sensorGyro)
#pragma config(Sensor, in7,    gyro_left,      sensorGyro)
#pragma config(Sensor, dgtl1,  en_left_base,  sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  en_right_base, sensorQuadEncoder)
#pragma config(Motor,  port1,           mg,            tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           left_fourbar,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           left_lift_1,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           right_lift_1,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           left_base,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           right_base,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           left_lift_2,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           right_lift_2,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           right_fourbar,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          roller,        tmotorVex393_HBridge, openLoop, reversed)

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define ever ;;
#define competition

#pragma platform(VEX2)

#pragma competitionControl(Competition)

#include "Vex_Competition_Includes.c"

#include "Driver.h"


int autonSel=0;
const int nAutons=7;
const string autonNames[7]={"Left 20 Points","Right 20 Points","Left 10 Points","Right 10 Points","Left 5 Points ","Right 5 Points ","Skill Challenge"};


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
#include "autonomousTurnRight5.h"
break;
case 5:
#include "autonomousTurnLeft5.h"
break;
case 6:
#include "skillChallenge.h"
break;

}
}

task usercontrol() {
		releaseWheels();
#include "UserControls.h"
}
