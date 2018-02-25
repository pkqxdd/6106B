motor[roller]=ROLLER_ANTIGRAVITY;



mb_out(false);
holdFourBar(700);
holdChainBar(100);
wait1Msec(800);
holdFourBar(300);
holdChainBar(2005);
moveWheels(49,true,2.2);
wait1Msec(500);
motor[roller]=-ROLLER_POWER;
mb_in(true);
/*
holdFourBar(630);
wait1Msec(300);

motor[roller]=-ROLLER_POWER;
wait1Msec(200);
holdFourBar(900);
*/
moveWheels(-44,true,1.5);

motor[roller]=0;

turn(180);
wait1Msec(100);

moveWheels(10,true,1.5);
//probably need more than this
mb_out(true);

moveWheels(-50, true, 1);
