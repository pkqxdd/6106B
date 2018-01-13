#ifndef Autonomous
#define Autonomous

startTask(SmoothMobileGoalLift);

resetEncoders();

motor[roller]=ROLLER_POWER;
// Initializing
holdChainBar(1950);
holdFourBar(675);
moveToMobileGoalLevel(0);
absoluteMoveAllWheelsTo(3200);

wait1Msec(500);
moveToMobileGoalLevel(1);
rollerOut();
wait1Msec(1000);


//rnClockwise(360);

//turnClockwise(360);

//this

absoluteMoveAllWheelsTo(0);

turnClockwise(180);
resetEncoders();


wait1Msec(200);
absoluteMoveAllWheelsTo(200);
moveToMobileGoalLevel(0);
wait1Msec(1000);
absoluteMoveAllWheelsTo(200);

//or this

/*
absoluteMoveAllWheelsTo(-2000);
resetEncoders();
//TurnCW(180);
resetEncoders();
absoluteMoveAllWheelsTo(1500);
resetEncoders();
holdFourBar(100);
wait1Msec(100);
holdChainBar(1000);
wait1Msec(100);
holdFourBar(675);
AbsoluteMoveAllWheelsTo(-500);

*/

moveToMobileGoalLevel(3);

stopTask(SmoothMobileGoalLift);

/*

// Move to the mobile goal
AbsoluteMoveAllWheelsTo(3000);
wait1Msec(1000); // wait to stop

// lifting mobile goal while dropping the cone
moveToMobileGoalLevel(3);
rollerOut();
wait1Msec(2000); // wait for mobile goal lift

// go back to starting position
AbsoluteMoveAllWheelsTo(0);


*/



#endif
