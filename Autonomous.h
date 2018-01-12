#ifndef Autonomous
#define Autonomous

holdChainBar(440);
holdFourBar(1000);

nMotorEncoder(front_left)=0;
nMotorEncoder(front_right)=0;
nMotorEncoder(back_left)=0;
nMotorEncoder(back_right)=0;

//rollerStop();
// move the robot to be in front of the stationary goal
int dis[4]={0,0,0,0}; //record for the distance of wheels


while ((abs(nMotorEncoder(front_left))+abs(nMotorEncoder(back_left))+abs(nMotorEncoder(front_right))+abs(nMotorEncoder(back_right)))/4//absolute average of four motors
	<3500){ //if average of four wheels...

	dis[0]=nMotorEncoder(front_left);
	dis[1]=nMotorEncoder(front_right);
	dis[2]=nMotorEncoder(back_left);
	dis[3]=nMotorEncoder(back_right);
	moveLeftWheels(80);
	moveRightWheels(100);

	//avg=(abs(dis[0])+abs(dis[1])+abs(dis[2])+abs(dis[3]))/4;
}

moveLeftWheels(0);
moveRightWheels(0);
//pick up the mobile goal
wait1Msec(7500);
mobileGoalUp();
wait1Msec(500);
mobileGoalStop();

//turn around
//moveLeftWheels(-100);
//moveRightWheels(100);
//wait1Msec(1000);


	moveLeftWheels(-80);
	moveRightWheels(-100);
	wait1Msec(3000)

	//avg=(abs(dis[0])+abs(dis[1])+abs(dis[2])+abs(dis[3]))/4;



mobileGoalDown();
wait1Msec(400);

moveLeftWheels(-80);
moveRightWheels(100);
wait1Msec(100);
moveLeftWheels(-60);
moveRightWheels(-60);
wait1Msec(200);

moveLeftWheels(0);
moveRightWheels(0);
/*
clearTimer(T1);
while (time1(T1)<200){
	chainBarDown();
	moveLeftWheels(-40);
	moveRightWheels(-40);
}
moveLeftWheels(0); //stop the wheels
moveRightWheels(0);

wait1Msec(500);
// rise the chainbar to dropoff location
holdFourBar(1200);
wait1Msec(500);
holdChainBar(1850);

wait1Msec(1000);
rollerOut();
rollerOut();
wait1Msec(500);
holdChainBar(2300);

wait1Msec(500);


//back off to starting position
while (abs(nMotorEncoder(front_left))>600){ //if average of four wheels...
	moveLeftWheels(-80);
	moveRightWheels(-80);
}


moveLeftWheels(0); //stop the wheels
moveRightWheels(0);




//drop the four bar

wait1Msec(500);

releaseChainBar();
releaseFourBar();
rollerZero();
*/

#endif
