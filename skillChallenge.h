#include "autonomousTurnRight.h"

mb_out(false);
turn(90);
wait1Msec(300);


moveWheels(15,true,2);
turn(90);
wait1Msec(300);

moveWheels(15,false,1);
mb_in(true);
turn(-180);
wait1Msec(300);

moveWheels(20,true,1);
wait1Msec(300);

mobileGoal(3290,true,50);

wait1Msec(200);

moveWheels(-5);
