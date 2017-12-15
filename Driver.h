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
const int ROLLER_ANTIGRAVITY=8;

const int POT_CHAINBAR_MIN=1052;
const int POT_CHAINBAR_MAX=3190;

const int POT_FOURBAR_LEFT_MAX=2100;
const int POT_FOURBAR_LEFT_MIN=970;

const int POT_FOURBAR_RIGHT_MAX=2050;
const int POT_FOURBAR_RIGHT_MIN=875;

const int RIGHT_MB_START=0; //I2C 6
const int RIGHT_MB_TRAVEL=375;
const int RIGHT_MB_MAX=1220;

const int LEFT_MB_START=0; //I2C 5
const int LEFT_MB_TRAVEL=-375;
const int LEFT_MB_MAX=-1220;



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

void fourBarLeftUp()
{
	motor[fb_left] = FOURBAR_POWER+FOURBAR_ANTIGRAVITY;
}

void fourBarRightUp()
{
	motor[fb_right] = FOURBAR_POWER+FOURBAR_ANTIGRAVITY+.25*(SensorValue[pot_fourbar_left]-SensorValue[pot_fourbar_right]-17);
}

void fourBarMove(int power)
{
	motor[fb_left] = power;
	motor[fb_right] = power+FOURBAR_ANTIGRAVITY+.25*(SensorValue[pot_fourbar_left]-SensorValue[pot_fourbar_right]-17);
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
	clearTimer(T1);
	while (time1(T1)<500) motor[roller]=ROLLER_POWER;
}

void rollerOut(){
	clearTimer(T1);
	while (time1(T1)<2500) motor[roller]=-ROLLER_POWER/2;
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
		lastErr=err;
		chainBarMove(powerOutput);
	}
#undef currLoc
}

task lockFourBar(){ // hold the fourbar in place. Call stoptask to release it

#define currLoc SensorValue[pot_fourbar_right]
	const float kp=0.25; // proportional constant
	const float kd=0.5; // derivatie constant
	int lastErr,powerOutput=0;
	int err=0;

	for (;;){
		err=fourbarTarget-currLoc;
		powerOutput=
		FOURBAR_ANTIGRAVITY+ //Base power
		err*kp+ // Proportional
		(lastErr-err)*kd;
		lastErr=err;
		fourBarMove(powerOutput);
	}
#undef currLoc

}

void releaseChainBar(){
	isChainBarLocked=false;
	stopTask(lockChainbar);
}

void releaseFourBar(){
	isFourBarLocked=false;
	stopTask(lockFourBar);
}

void holdChainBar(int target){
	chainbarTarget=target;
	if (isChainBarLocked){
		stopTask(lockChainbar);
		} else {
		isChainBarLocked=true;
	}
	startTask(lockChainbar);
	return;

}

void holdFourBar(int position){
	fourbarTarget=position;
	if (isFourBarLocked){
		stopTask(lockFourBar);
		} else {
		isFourBarLocked=true;
	}
	startTask(lockFourBar);
	return;
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
			shouldStop=true;
			}else if (vexRT[Btn8L]){
			nMotorEncoder[mb_left]=0;
			nMotorEncoder[mb_right]=0;
		}
		else
		{
			if (shouldStop){
				mobileGoalZero();
			}
			else {
				mobileGoalStop();
			}
		}
	}
}
task FourBarControls()
{
	for (;;){
		while (ButtonFourbarUp){
			if (isFourBarLocked) releaseFourBar();
			fourBarLeftUp();
			fourBarRightUp();
		}
		while (ButtonFourbarDown) {
			if (isFourBarLocked) releaseFourBar();
			fourBarDown();
		}
		if (!isFourBarLocked) fourBarStop();
	}
}

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
	}
}

task ChainBarControls()
{
	for (;;){
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

int coneCount=0;

task SpecialControls(){
	for(;;){
		if (ButtonSpecialPickUp){
			holdChainBar(1650);
		}
#ifdef ButtonSpecialDropOffLow
		if (ButtonSpecialDropOffLow){
			holdChainBar(980);
		}
#endif
#ifdef ButtonSpecialDropOffHigh
		if (ButtonSpecialDropOffHigh){
			holdChainBar(2810);
		}
#endif
		/*
		if (vexRT[Btn8L]){ //cone loader, for temp test only
		holdChainBar(1870);
		holdFourBar(1095);
		*/
	}

#ifdef ButtonConeCountIncrement //Added this bunch of ifdef so that even if those buttons are not bound to anything, there is no compiler error
#ifdef ButtonConeCountDecrement
	if (ButtonConeCountIncrement) coneCount++;
	if (ButtonConeCountDecrement) coneCount--;
#ifdef ButtonConeCountReset
	if (ButtonConeCountReset) coneCount=0;
#endif
#ifdef ButtonSpeicalDropOff
	if (ButtonSpecialDropOff){
		switch(coneCount){
		case 0:
			holdChainBar();
			holdFourBar();
			break;
		case 1:
			holdChainBar();
			holdFourBar();
			break;
		case 2:
			holdChainBar();
			holdFourBar();
			break;
		case 3:
			holdChainBar();
			holdFourBar();
			break;
		case 4:
			holdChainBar();
			holdFourBar();
			break;
		case 5:
			holdChainBar();
			holdFourBar();
			break;
		case 6:
			holdChainBar();
			holdFourBar();
			break;
		case 7:
			holdChainBar();
			holdFourBar();
			break;
		case 8:
			holdChainBar();
			holdFourBar();
			break;
		case 9:
			holdChainBar();
			holdFourBar();
			break;
		case 10:
			holdChainBar();
			holdFourBar();
			break;

		}
	}
#endif
#endif
#endif

}


task FourbarLeftPassiveFollow(){
	if (!ButtonFourbarDown && !ButtonFourbarUp){

#define currLoc SensorValue[pot_fourbar_left]
#define Target SensorValue[pot_fourbar_right]+25
		const float kp=1.5; // proportional constant
		const float kd=5; // derivatie constant
		int lastErr,powerOutput=0;
		int err=0;

		for (;;){
			err=Target-currLoc;
			powerOutput=
			FOURBAR_ANTIGRAVITY+ //Base power
			err*kp+ // Proportional
			(lastErr-err)*kd;
			lastErr=err;
			motor[fb_left]=powerOutput;
		}
#undef currLoc
#undef Target

	}
}

int level=3;
int target=0;
int lastErrLeft,lastErrRight,powerOutputLeft,powerOutputRight=0;
int errLeft,errRight=0;

task SmoothMobileGoalLift(){
#define left (nMotorEncoder[mb_left]) //assuming left side has the negative reading
#define right (nMotorEncoder[mb_right])

	bool wasPressed=false;
	const float kp=0.5; // proportional constant
	const float kd=-5; // derivatie constant
	//int lastErrLeft,lastErrRight,powerOutputLeft,powerOutputRight=0;
	//int errLeft,errRight=0;
	//int level,target=0; //level is 0,1,2,3
	int mapLevelToTarget[4]={1300,857,450,0};
	bool Up=false;
	bool Down=false;
	for (;;){
		if (ButtonMobileGoalUp){ //so the target don't get shoot into some absurd valule
			if (level<3) level+=1;
			Up=true;
			Down=false;
		}
		else if (ButtonMobileGoalDown){
			if (!wasPressed){
				wasPressed=true;
				if (level>0){
					level-=1;
				}
				Up=false;
				Down=true;
			}
		}
		else {
			Up=false;
			Down=false;
		}

		target=mapLevelToTarget[level];

		/*
		errLeft=left-target;
		errRight=right-target;
		powerOutputLeft=errLeft*kp+(lastErrLeft-errLeft)*kd;
		powerOutputRight=errRight*kp+(lastErrRight-errRight)*kd;
		lastErrLeft=errLeft;
		lastErrRight=errRight;
		motor[mb_left]=powerOutputLeft;
		motor[mb_right]=powerOutputRight; //smoothing both sides to make them balance
		*/

		if (Up){
			if (left>target) {
				motor[mb_left]=4*(left-target);
			}
			if(right>target) {
				motor[mb_right]=4*(right-target);
			}
		}
		else if (Down){
			if ( left<target) {
				motor[mb_left]=4*(left-target);
			}
			if(right<target ) {
				motor[mb_right]=4*(right-target);
			}
		}
		else {
			errLeft=left-target;
			errRight=right-target;
			powerOutputLeft=errLeft*kp+(lastErrLeft-errLeft)*kd;
			powerOutputRight=errRight*kp+(lastErrRight-errRight)*kd;
			lastErrLeft=errLeft;
			lastErrRight=errRight;
			motor[mb_left]=powerOutputLeft;
			motor[mb_right]=powerOutputRight; //smoothing both sides to make them balance
		}
	}
}

#undef right
#undef left



#endif
