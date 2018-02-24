

motor[roller]=ROLLER_ANTIGRAVITY;


//holdFourBar(150);
mb_out(false);

holdFourBar(1030);
holdChainBar(0);

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

holdChainBar(2850);

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

//finish first mobile goal (22 points)

mb_mid(false);
wait1Msec(400);
turn(90);
wait1Msec(300);

moveWheels(14,true,2); // move in 5 point zone

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

//finish second mobile goal (32 points)

turn(-180);
wait1Msec(600);
mb_out(false);
moveWheels(42*sqrt(2)-4,true);

mb_in(true); // take the mobile goal
mb_mid(false);
moveWheels(36*sqrt(2)-2,true,2);

//finish third mobile goal (42 points)

moveWheels(-3,true);
turn(225);
mb_out(false);
wait1Msec(400);

moveWheels(58,true,2);
mb_in(true);
moveWheels(49,true,2.2);
wait1Msec(500);
mb_in(true);

wait1Msec(300);

moveWheels(-41,true,1.5);
wait1Msec(500);

turn(-135);

holdChainBar(600);

wait1Msec(500);
holdFourBar(400);

moveWheels(21.5,true,2.5);
wait1Msec(700);

turn(-90);
wait1Msec(300);

mobileGoal(2270,false,50);
moveWheels(22,true,4);
mb_mid(false);

wait1Msec(500);


mb_out(false);
moveWheels(-18,true,2);

// finish fourth mobile goal (62 points)

mb_mid(false);
wait1Msec(400);
turn(-90);
wait1Msec(300);

moveWheels(14,true,2); // move in 5 point zone

mb_out(false);
turn(-90);

wait1Msec(300);

moveWheels(24,false,2); // go to mobile goal
wait1Msec(300);
mb_in(true);  // take the mobile goal
wait1Msec(300);

turn(180);
wait1Msec(600);
mb_mid(false);
moveWheels(22,true,3);
wait1Msec(600);
mobileGoal(1800,false);

//finish fifth mobile goal (72 points)
turn(-180);
wait1Msec(600);
mb_out(false);
moveWheels(42*sqrt(2)-4,true);

mb_in(true); // take the mobile goal
mb_mid(false);
moveWheels(36*sqrt(2)-2,true,2);
//finish sixth mobile goal (82 points)
