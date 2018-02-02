#ifndef Autonomous
#define Autonomous

//holdChainBar(600);
holdFourBar(150);
mobileGoal(3290);
turn(45,5);

wait1Msec(200);
moveWheels(48,true,1.25);

wait1Msec(1000);

mobileGoal(940,true);

wait1Msec(200);
turn(-180,5);
moveWheels(33,true,1.5);


turn(45);
wait1Msec(200);

moveWheels(30);
turn(-95);


mobileGoal(2000,true,50);
moveWheels(24,true,4);
wait1Msec(2000);

moveWheels(-20,5);
wait1Msec(2000);

releaseWheels();
#endif
