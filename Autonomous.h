#ifndef Autonomous
#define Autonomous




nMotorEncoder(front_left)=0;
nMotorEncoder(front_right)=0;
nMotorEncoder(back_left)=0;
nMotorEncoder(back_right)=0;

rollerStop();
// move the robot to be in front of the stationary goal
int dis[4]={0,0,0,0}; //record for the distance of wheels


while (abs(nMotorEncoder(front_left))<1050){ //if average of four wheels...
	dis[0]=nMotorEncoder(front_left);
	dis[1]=nMotorEncoder(front_right);
	dis[2]=nMotorEncoder(back_left);
	dis[3]=nMotorEncoder(back_right);
	moveLeftWheels(40);
	moveRightWheels(40);

	//avg=(abs(dis[0])+abs(dis[1])+abs(dis[2])+abs(dis[3]))/4;
}
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

   moveChainBarTo(1000);
   holdChainBar(1000);

wait1Msec(1000);
rollerOut();
wait1Msec(500);
moveChainBarTo(800);
holdChainBar(800);

wait1Msec(500);


//back off to starting position
while (abs(nMotorEncoder(front_left))>600){ //if average of four wheels...
	moveLeftWheels(-80);
	moveRightWheels(-80);
}


moveLeftWheels(0); //stop the wheels
moveRightWheels(0);

moveFourBarTo(200);
holdFourBar(200);


//drop the four bar

wait1Msec(500);

releaseChainBar();
releaseFourBar();
rollerZero();

#endif
