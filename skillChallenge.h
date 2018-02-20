
motor[roller]=ROLLER_ANTIGRAVITY;


//holdFourBar(150);
mb_out(false);

holdFourBar(1030);
holdChainBar(4095);

wait1Msec(400);
moveWheels(49,true,1.25);
wait1Msec(500);
mb_in(true); // take the mobile goal

holdFourBar(630);
wait1Msec(300);

motor[roller]=-ROLLER_POWER; // drop the cone
wait1Msec(200);
holdFourBar(900);

moveWheels(-44,true,1.5); // back to 5 point zone

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

mobileGoal(2660,true,50);
wait1Msec(500);

mb_out(false);
moveWheels(-18,true,4);
//finish first mobile goal

wait1Msec(700);
mb_mid(false);
clearTimer(T1);
releaseWheels();
while (time1(T1)<1150){
moveLeftWheels(35);
moveRightWheels(35);
}

moveLeftWheels(0);
moveRightWheels(0);


turn(90);
wait1Msec(300);

moveWheels(12,true,2); // in 5 point zone

mb_out(false);
turn(95);

wait1Msec(300);

moveWheels(24,false,2); // go to mobile goal
wait1Msec(300);
mb_in(true);  // take the mobile goal
wait1Msec(300);

turn(-190);
wait1Msec(300);
mb_mid(false);
moveWheels(20,true,3);
wait1Msec(600);

mb_out(true);
wait1Msec(200);

moveWheels(-5);

//finish second mobile goal

mb_mid(false);
moveWheels(-27,true);
mb_out(false);
turn(-85);
moveWheels(35,true,2);
mb_in(true); // take the mobile goal
turn(80);
mb_mid(false);
moveWheels(47,true,2);
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
mb_mid(true); // take the mobile goal
moveWheels(30,true,2);
mb_out(true);
moveWheels(-10,true,2);

// finish fourth mobile goal (first one on the opposite side)

mb_mid(false);
moveWheels(-29,true);
mb_out(false);
turn(-80);
moveWheels(35,true,2);
mb_in(true); // take the mobile goal
turn(80);
mb_mid(false);
moveWheels(47,true,2);
mb_out(true);
moveWheels(-5,true,2);

//finish fifth mobile goal
