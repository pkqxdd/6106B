
motor[roller]=ROLLER_ANTIGRAVITY;


holdFourBar(150);
mb_out(false);

//turn(-47.5,5);
wait1Msec(400);
moveWheels(49,true,1.25);

//wait1Msec(500);

//mobileGoal(940,true);


mb_in(true);
//turn(178,5);

wait1Msec(300);
holdFourBar(0);
holdChainBar(400);

moveWheels(-44,true,1.5);
//motor[roller]=-ROLLER_POWER;

turn(135);

wait1Msec(300);


moveWheels(23,true,2);
turn(100);
motor[roller]=0;

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
moveWheels(-18,true,2);

//finish first mobile goal

wait1Msec(700);
mb_mid(false);
clearTimer(T1);
releaseWheels();
while (time1(T1)<1400){
moveLeftWheels(36);
moveRightWheels(36);
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
turn(-83);
moveWheels(26,true);
mb_in(true);
turn(90);
mb_mid(false);
moveWheels(40,true);
mb_out(true);
//finish third mobile goal
