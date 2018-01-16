#ifndef Autonomous
#define Autonomous

zeroMobileGoalEncoders(500);
startTask(SmoothMobileGoalLift);

resetEncoders();


// Initializing
holdChainBar(2000);
holdFourBar(675);
motor[roller]=ROLLER_POWER;

moveToMobileGoalLevel(0);
absoluteMoveAllWheelsTo(2900);

wait1Msec(500);
moveToMobileGoalLevel(1);
motor[roller]= -ROLLER_POWER;
wait1Msec(500);


//rnClockwise(360);

//turnClockwise(360);

//this

absoluteMoveAllWheelsTo(300);


rollerZero();
turnClockwise180();
resetEncoders();
moveToMobileGoalLevel(3);

wait1Msec(500);
absoluteMoveAllWheelsTo(600);
moveToMobileGoalLevel(0);



holdFourBar(100);
wait1Msec(1000);
holdChainBar(1000);

wait1Msec(1000);
absoluteMoveAllWheelsTo(-200);

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
