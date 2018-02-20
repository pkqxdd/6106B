

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

moveWheels(-41,true,1.5);
wait1Msec(500);
motor[roller]=0;

turn(135);

holdChainBar(600);

wait1Msec(500);
holdFourBar(400);

moveWheels(21.5,true,2.5);
wait1Msec(700);

turn(90);
wait1Msec(300);

mobileGoal(2270,false,50);
moveWheels(22,true,4);
mb_mid(false);

wait1Msec(500);


mb_out(false);
moveWheels(-18,true,2);

//finish first mobile goal

mb_mid(false);
wait1Msec(400);
turn(90);
wait1Msec(300);

moveWheels(14,true,2); // in 5 point zone

mb_out(false);
turn(90);

wait1Msec(300);

moveWheels(24,false,2); // go to mobile goal
wait1Msec(300);
mb_in(true);  // take the mobile goal
wait1Msec(300);

turn(-180);
wait1Msec(600);
mb_mid(false);
moveWheels(22,true,3);
wait1Msec(600);
mobileGoal(1800,false);

//finish second mobile goal

turn(-180);
wait1Msec(600);
mb_out(false);
moveWheels(42*sqrt(2)-4,true);

mb_in(true); // take the mobile goal
mb_mid(false);
moveWheels(36*sqrt(2)-2,true,2);
stopAllTasks();

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
