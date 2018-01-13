#ifndef Autonomous
#define Autonomous
startTask(SmoothMobileGoalLift);



holdChainBar(1950);
holdFourBar(675);

moveToMobileGoalLevel(0);


AbsoluteMoveAllWheelsTo(3200);
wait1Msec(500);
moveToMobileGoalLevel(3);
rollerOut();
ClearEncoders();
wait1Msec(200);
//this
AbsoluteMoveAllWheelsTo(-3000);
ClearEncoders();
moveToMobileGoalLevel(0);
TurnCW(90);
ClearEncoders();
AbsoluteMoveAllWheelsTo(400);
//or this
/*
AbsoluteMoveAllWheelsTo(-2000);
ClearEncoders();
TurnCW(180);
ClearEncoders();
AbsoluteMoveAllWheelsTo(1500);
ClearEncoders();
holdFourBar(100);
wait1Msec(100);
holdChainBar(1000);
wait1Msec(100);
holdFourBar(675);
AbsoluteMoveAllWheelsTo(-500);
*/


stopTask(SmoothMobileGoalLift);

#endif
