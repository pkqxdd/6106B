#ifndef drivers
#define drivers

// -----------------BEGIN Global Constants Configuration-------------------

const int MB_POWER = 90; // power to mobile goal lift
const int FOURBAR_POWER = 100; //power to fourbar
const int CHAINBAR_POWER=80; // power to chainbar
const int ROLLER_POWER=90; // power to chainbar
const int FOURBAR_ANTIGRAVITY = 10; //power to fourbar when it is in the "stop" position
const int MB_ANTIGRAVITY=20; //power to mobile goal lift when it is in the "stop" position
const int CHAINBAR_ANTIGRAVITY=20;
const int ROLLER_ANTIGRAVITY=4;

const int POT_CHAINBAR_MAX=950;
const int POT_CHAINBAR_MIN=3190;

const int POT_FOURBAR_MAX=700;
const int POT_FOURBAR_MIN=0;



// ------------------END Global Constants Configuration----------------------
// -----------------BEGIN Keymap Configuration------------------

//#include "KeymapXavier.h" // this file defines which button is bind to which key
#include "KeymapJack.h"

// -----------------END Keymap Configuration----------------
// ------------------BEGIN Utility Functons---------------



void moveLeftWheels(int power)
{
	motor[front_left] = power;
	motor[back_left] = power;
}

void moveRightWheels(int power)
{
	motor[front_right] = power;
	motor[back_right] = power;
}

void mobileGoalUp()
{
	motor[mb_left] = MB_POWER;
	motor[mb_right] = MB_POWER+20;
}

void mobileGoalZero()
{
	motor[mb_left] = 0;
	motor[mb_right] = 0;
}


void mobileGoalDown()
{
	motor[mb_left] = -MB_POWER;
	motor[mb_right] = -MB_POWER;
}

void mobileGoalStop(){
	motor[mb_left] = MB_ANTIGRAVITY;
	motor[mb_right] = MB_ANTIGRAVITY+10;
}

void fourBarUp()
{
	motor[fb_left] = FOURBAR_POWER+FOURBAR_ANTIGRAVITY+2;
	motor[fb_right] = FOURBAR_POWER+FOURBAR_ANTIGRAVITY;
}

void fourBarDown()
{
	motor[fb_left] = -FOURBAR_POWER+FOURBAR_ANTIGRAVITY-1;
	motor[fb_right] = -FOURBAR_POWER+FOURBAR_ANTIGRAVITY;
}

void fourBarStop()
{
	motor[fb_left] = FOURBAR_ANTIGRAVITY;
	motor[fb_right] = FOURBAR_ANTIGRAVITY;
}


void rollerIn(){
	motor[roller]=ROLLER_POWER;
}

void rollerOut(){
	clearTimer(T1);
	while (time1(T1)<2000) motor[roller]=-ROLLER_POWER/2;
	return;
}

void rollerStop(){
	motor[roller]=ROLLER_ANTIGRAVITY;
}

void rollerZero(){
	motor[roller]=0;
}

void chainBarUp(){
	motor[chainbar]=CHAINBAR_POWER+CHAINBAR_ANTIGRAVITY;
}

void chainBarMove(int power){
	motor[chainbar]=power;
}

void chainBarDown(){
	motor[chainbar]=-CHAINBAR_POWER+CHAINBAR_ANTIGRAVITY;
}

void chainBarStop(){
	motor[chainbar]=CHAINBAR_ANTIGRAVITY;
}

int chainbarTarget=0;
int fourbarTarget=0;
bool isFourBarLocked=false;
bool isChainBarLocked=false;
int fp;
int outp;
int outd;

task lockChainbar(){ // hold the chainbar in place. Call stoptask to release it
	#define currLoc SensorValue[pot_chainbar]
	const float kp=0.25; // proportional constant
	const float kd=0.5; // derivatie constant
	int lastErr,powerOutput=0;
	int err=0;

	for (;;){
		err=chainbarTarget-currLoc;
		powerOutput=
		CHAINBAR_ANTIGRAVITY+ //Base power
		err*kp+ // Proportional
		(lastErr-err)*kd+
		(currLoc>2705?-CHAINBAR_ANTIGRAVITY:0);
		//Derivative
		fp=powerOutput; //debug
		outp=err*kp; // debug
		outd=(lastErr-err)*kd; //debug
		lastErr=err;
		chainBarMove(powerOutput);
	}
#undef currLoc
	}

task lockFourBar(){ // hold the fourbar in place. Call stoptask to release it
	for (;;){/*
		if (SensorValue(pot_fourbar)>fourbar_position){
			motor[fb_left]=-19;
			motor[fb_right]=-19;
			} else if (SensorValue(pot_fourbar)<fourbar_position){
			motor[fb_left]=19;
			motor[fb_right]=19;
			} else {
			motor[fb_left]=0;
			motor[fb_right]=0;*/
		}
	}




void holdChainBar(int target){
	chainbarTarget=target;
	if (!isChainBarLocked){
		isChainBarLocked=true;
		startTask(lockChainbar);
		return;
	}
}

void holdFourBar(int position){
	fourbarTarget=position;
	if (!isFourBarlocked){
		isFourBarLocked=true;
		startTask(lockFourBar);
		return;
	}
}

void releaseChainBar(){
	isChainBarLocked=false;
	stopTask(lockChainbar);
}

void releaseFourBar(){
	isFourBarLocked=false;
	stopTask(lockFourBar);
}



void moveFourBarTo(int position){

	if (isFourBarLocked) releaseFourBar();
	while (position>SensorValue[pot_fourbar]){
		fourBarUp();
	}
	while (position<SensorValue[pot_fourbar]){
		fourBarDown();
	}
}

void moveChainBarTo(int position){
	if (isChainBarLocked) releaseChainBar();
	holdChainbar(position);
}


//----------------END Utility Functions------------

task WheelControls()
{
	for (;;) // a foreverloop
	{
		moveLeftWheels(AxisLeftWheels);
		moveRightWheels(AxisRightWheels);
		//bufferedWheelsControls(AxisLeftWheels,AxisRightWheels);
	}
}

task ArcadeWheelsControls(){
	for(;;){
	int left=vexRT[Ch2]+vexRT[Ch1];
	int right=vexRT[Ch2]-vexRT[Ch1];
/*
	if (left>127||right>127){
	left/=2;
	right/=2;

}
*/

	moveLeftWheels(left);
	moveRightWheels(right);
}
}

task MobileGoalControls()
{
	bool shouldStop=true;
	for (;;){
		if (ButtonMobileGoalDown){
			mobileGoalDown();
			shouldStop=true;
		}
		else if (ButtonMobileGoalUp){
			mobileGoalUp();
			shouldStop=false;
		}
		else
		{
			if (shouldStop) mobileGoalZero();
			else mobileGoalStop();
	}}

}

task FourBarControls()
{
	for (;;){
		while (ButtonFourbarUp){
			if (isFourBarLocked) releaseFourBar();
			fourBarUp();
		}
		while (ButtonFourbarDown) {
			if (isFourBarLocked) releaseFourBar();
			fourBarDown();
		}
		if (!isFourBarLocked) fourBarStop();
	}
}

/*
task FourBarControls()
{
for (;;){
while (ButtonFourbarUp){
fourBarUp();
}
while (ButtonFourbarDown) {
fourBarDown();
}
fourBarStop();
}
}
*/

task RollerControls()
{
	bool shouldStop=true;
	for (;;){
		if (ButtonRollerIn){
			rollerIn();
			shouldStop=false;
		}
		else if (ButtonRollerOut){
			rollerOut();
			shouldStop=true;
		}
		else
		{
			if (shouldStop) rollerZero();
			else rollerStop();
		}
}}

task ChainBarControls()
{
	for (;;){
		//if (SensorValue[pot_chainbar]<=350)
		//{
		//  moveChainBarTo(400);
		//  holdChainBar(400);
		//}
		while (ButtonChainBarUp) {
			if (isChainBarLocked) releaseChainBar();
			chainBarUp();
		}
		while (ButtonChainBarDown) {
			if (isChainBarLocked) releaseChainBar();
			chainBarDown();
		}
		if (!isChainBarLocked) chainBarStop();
	}
}
/*
struct SpecialLocation {
int chainbar;
int fourbar;
};
*/
//SpecialLocation manualLoader{1530,80};

// special pick loading fourbar: 80, chainbar 1530


task SpecialControls(){
	for(;;){
		if (ButtonSpecialPickUp){
			holdChainBar(1650);
		}
		if (ButtonSpecialDropOffLow){
			holdChainBar(980);
		}
		if (ButtonSpecialDropOffHigh){
			holdChainBar(2810);
		}
	}
}





#endif
