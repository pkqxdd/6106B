#ifndef Autonomous
#define Autonomous

startTask(SmoothMobileGoalLift);

resetEncoders();

// Initializing
holdChainBar(1950);
holdFourBar(675);
moveToMobileGoalLevel(0);

// Move to the mobile goal
AbsoluteMoveAllWheelsTo(3000);
wait1Msec(1000); // wait to stop

// lifting mobile goal while dropping the cone
moveToMobileGoalLevel(3);
rollerOut();
wait1Msec(2000); // wait for mobile goal lift

// go back to starting position
AbsoluteMoveAllWheelsTo(0); 



stopTask(SmoothMobileGoalLift);


#endif
