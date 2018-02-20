

motor[roller]=ROLLER_ANTIGRAVITY;


//holdFourBar(150);
mb_out(false);

holdFourBar(1030);
holdChainBar(4095);

wait1Msec(400);
moveWheels(49,true,2.2);
wait1Msec(500);
mb_in(true);

holdFourBar(630);
wait1Msec(300);

motor[roller]=-ROLLER_POWER;
wait1Msec(200);
holdFourBar(900);

moveWheels(-44,true,1.5);
wait1Msec(500);
motor[roller]=0;

turn(135);

holdChainBar(600);

wait1Msec(500);
holdFourBar(400);

moveWheels(21.5,true,2);
wait1Msec(700);

turn(100);

mb_mid(false,200);

wait1Msec(300);
moveWheels(22,true,4);

mobileGoal(2660,true,50);
wait1Msec(500);


mb_out(false);
moveWheels(-18,true,4);
