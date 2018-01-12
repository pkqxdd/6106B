#ifndef autonomousHelpers
#define autonomousHelpers
#include "Driver.h"


void AbsoluteMoveWheelsTo(int target){

int dis[4]={0,0,0,0}; //record for the distance of wheels


while ((abs(nMotorEncoder(front_left))+abs(nMotorEncoder(back_left))+abs(nMotorEncoder(front_right))+abs(nMotorEncoder(back_right)))/4//absolute average of four motors
	<target){ //if average of four wheels...

	dis[0]=nMotorEncoder(front_left);
	dis[1]=nMotorEncoder(front_right);
	dis[2]=nMotorEncoder(back_left);
	dis[3]=nMotorEncoder(back_right);
	moveLeftWheels(100);
	moveRightWheels(100);

}

moveLeftWheels(0);
moveRightWheels(0);

}




#endif
