
motor[roller]=ROLLER_ANTIGRAVITY;

mb_out(false);

holdFourBar(1030);
holdChainBar(2100);

wait1Msec(400);
moveWheels(49,true,1.25);

mb_in(true);

holdFourBar(630);
wait1Msec(300);

motor[roller]=-ROLLER_POWER;
moveWheels(-44,true,1.5);

holdFourBar(900);
motor[roller]=0;

turn(135);

holdChainBar(600);

wait1Msec(300);
holdFourBar(400);

moveWheels(23,true,2);
turn(100);

mb_mid(false);

wait1Msec(300);
moveWheels(20,true,4);


clearTimer(T1);
while (time1(T1)<500){

	moveLeftWheels(127);
	moveRightWheels(127);
}

mobileGoal(2760,true,50);
wait1Msec(500);


mb_out(false);
moveWheels(-18,true,4);
//finish first mobile goal

wait1Msec(700);
mb_mid(false);
clearTimer(T1);
releaseWheels();
while (time1(T1)<1300){
moveLeftWheels(35);
moveRightWheels(35)';
}

moveLeftWheels(0);
moveRightWheels(0);


mb_out(false);
turn(90);
wait1Msec(300);

moveWheels(16,true,2);
turn(95);

wait1Msec(300);

moveWheels(22,false,2);
wait1Msec(300);
mb_in(true);
wait1Msec(300);

turn(-185);
wait1Msec(300);
mb_mid(false);
moveWheels(22,true,2);
wait1Msec(300);

mb_out(true);
wait1Msec(200);

moveWheels(-5);

//finish second mobile goal

mb_mid(false);
moveWheels(-29,true);
mb_out(false);
turn(-80);
moveWheels(35,true,2);
mb_in(true);
turn(80);
mb_mid(false);
moveWheels(45,true,2);
mb_out(true);
moveWheels(-5,true,2);
//finish third mobile goal
mb_in(false);
turn(-175);
moveWheels(-2,true,1);

clearTimer(T1);
releaseWheels();
while (time1(T1)<1300){
moveLeftWheels(-35);
moveRightWheels(-35);
}
mb_out(false);
moveWheels(60,true,2);
mb_mid(true);
moveWheels(30,true,2);
mb_out(true);
moveWheels(-10,true,2);
