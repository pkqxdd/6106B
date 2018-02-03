#include "autonomousTurnLeft.h"

mb_out(false);
turn(90);
wait1Msec(300);


moveWheels(12,true,2);
turn(95);
wait1Msec(300);

moveWheels(22,false,2);
wait1Msec(300);
mb_in(true);
wait1Msec(300);

turn(-180);
wait1Msec(300);

moveWheels(20,true,1);
wait1Msec(300);

mobileGoal(3290,true,50);
wait1Msec(200);

moveWheels(-5);

//finish second mobile goal
mb_mid(false);
turn(-90);

moveWheels(40,true,2);
turn(-90);
mb_out(false);
moveWheels(15,true);

mb_in(true);

turn(180);

moveWheels(15,true);
mobileGoal(3290,true,50);
moveWheels(-5,true);
