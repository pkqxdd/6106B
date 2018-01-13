#ifndef Autonomous
#define Autonomous
startTask(SmoothMobileGoalLift);

nMotorEncoder[front_left]=0;
nMotorEncoder[front_right]=0;
nMotorEncoder[back_left]=0;
nMotorEncoder[back_right]=0;

holdChainBar(1950);
holdFourBar(675);
moveToMobileGoalLevel(0);


AbsoluteMoveAllWheelsTo(3000);
wait1Msec(500);
moveToMobileGoalLevel(3);
rollerOut();
wait1Msec(2000);
AbsoluteMoveAllWheelsTo(0);







stopTask(SmoothMobileGoalLift);
#endif
