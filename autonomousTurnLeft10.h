motor[roller]=ROLLER_ANTIGRAVITY;


holdFourBar(150);
mb_out(false);

//turn(-47.5,5);
wait1Msec(400);
moveWheels(49,true,1.25);

wait1Msec(500);

//mobileGoal(940,true);


mb_in(true);
turn(179,5);

wait1Msec(300);
holdFourBar(0);
holdChainBar(400);

moveWheels(40,true,1.5);
//motor[roller]=-ROLLER_POWER;

wait1Msec(300);


mb_out(true);

moveWheels(-10,true,2);
