
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

turn(-135);

holdChainBar(600);

wait1Msec(300);
holdFourBar(400);

moveWheels(23,true,2);
turn(-100);

mb_mid(false);

wait1Msec(300);
moveWheels(20,true,4);

clearTimer(T1);
while (time1(T1)<500){

	moveLeftWheels(127);
	moveRightWheels(127);
}

mobileGoal(2660,true,50);
wait1Msec(500);


mb_out(false);
moveWheels(-18,true,4);
