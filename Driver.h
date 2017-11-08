#ifndef drivers
#define drivers

// -----------------BEGIN Global Variables Configuration-------------------

const int MB_POWER = 90; // power to mobile goal lift
const int FOURBAR_POWER = 100; //power to fourbar
const int CHAINBAR_POWER=80; // power to chainbar
const int ROLLER_POWER=80; // power to chainbar
const int FOURBAR_ANTIGRAVITY = 0; //power to fourbar when it is in the "stop" position
const int MB_ANTIGRAVITY=0; //power to mobile goal lift when it is in the "stop" position
const int CHAINBAR_ANTIGRAVITY=20;
const int ROLLER_ANTIGRAVITY=30;

// ------------------END Global Variables Configuration----------------------
// -----------------BEGIN Keymap Configuration------------------

#include "KeymapXavier.h" // this file defines which button is bind to which key

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

short wheelRecordLeft[100];
short wheelRecordRight[100];

short index=0;
short getRecordIndex(){
	if (index == 99)
	{
		index=0;
		return index;
	}
	else {
	return index++;
}
}

short getAverageWheelHistoryLeft(){
	int sum=0;
	for (short i=index;i>=0;i--)
	{
	sum+=wheelRecordLeft[i];
}
return sum/index;

}


short getAverageWheelHistoryRight(){
	int sum=0;
	for (short i=index;i>=0;i--)
	{
	sum+=wheelRecordRight[i];
}
return sum/index;

}

void bufferedWheelsControls(int powerLeft, int powerRight){
short tmpIndex=getRecordIndex();
if (powerLeft <= 0 || powerRight <=0 ){
	wheelRecordLeft[tmpIndex]=powerLeft;
	wheelRecordRight[tmpIndex]=powerRight;
	moveLeftWheels(powerLeft);
	moveRightWheels(powerRight);
	return;
} else {
short history[2]={getAverageWheelHistoryLeft(),getAverageWheelHistoryRight()};
if (history[0] <= -20 && history[1] <=-20){ // decrease the power to wheels overtime in this case
	wheelRecordLeft[tmpIndex]=powerLeft/log10(abs(history[0]));
	wheelRecordRight[tmpIndex]=powerRight/log10(abs(history[1]));
	moveLeftWheels(powerLeft/log10(abs(history[0])));
	moveRightWheels(powerRight/log10(abs(history[1])));
}
else {
	wheelRecordLeft[tmpIndex]=powerLeft;
	wheelRecordRight[tmpIndex]=powerRight;
	moveLeftWheels(powerLeft);
	moveRightWheels(powerRight);
	return;
}
}

}


void mobileGoalUp()
{
	motor[mb_left] = MB_POWER;
	motor[mb_right] = MB_POWER;
}

void mobileGoalDown()
{
	motor[mb_left] = -MB_POWER;
	motor[mb_right] = -MB_POWER;
}

void mobileGoalStop(){
	motor[mb_left] = MB_ANTIGRAVITY;
	motor[mb_right] = MB_ANTIGRAVITY;
}

void fourBarUp()
{
	motor[fb_left] = FOURBAR_POWER+FOURBAR_ANTIGRAVITY;
	motor[fb_right] = FOURBAR_POWER+FOURBAR_ANTIGRAVITY;
}

void fourBarDown()
{

	motor[fb_left] = -FOURBAR_POWER+FOURBAR_ANTIGRAVITY;
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
	motor[roller]=-ROLLER_POWER;
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

void chainBarDown(){
	motor[chainbar]=-CHAINBAR_POWER+CHAINBAR_ANTIGRAVITY;
}

void chainBarStop(){
	motor[chainbar]=CHAINBAR_ANTIGRAVITY;
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

task MobileGoalControls()
{
	for (;;){
		while (ButtonMobileGoalDown) mobileGoalDown();
		while (ButtonMobileGoalUp) mobileGoalUp();
		mobileGoalStop();
	}
}

task FourBarControls()
{
	for (;;){
		while (ButtonFourbarUp) fourBarUp();
		while (ButtonFourbarDown) fourBarDown();
		fourBarStop();
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
}}

task ChainBarControls()
{
	for (;;){
		while (ButtonChainBarUp) chainBarUp();
		while (ButtonChainBarDown) chainBarDown();
		chainBarStop();
}
}


#endif
