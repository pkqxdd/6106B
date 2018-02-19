motor[roller]=ROLLER_ANTIGRAVITY;


//holdFourBar(150);
mb_out(false);

holdFourBar(1030);
holdChainBar(4095);

wait1Msec(400);
moveWheels(49,true,2.2);
wait1Msec(200);
mb_in(true);

holdFourBar(630);
wait1Msec(300);

motor[roller]=-ROLLER_POWER;
wait1Msec(200);
holdFourBar(900);

moveWheels(-44,true,1.5);

motor[roller]=0;

turn(180);
wait1Msec(100);

moveWheels(10,true,1.5);
//probably need more than this
mb_out(true);

moveWheels(-50, true, 1)