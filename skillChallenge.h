
motor[roller]=ROLLER_POWER;


mb_out(false);
outOfSize(500,1805);
moveWheels(49,true,2.2);
wait1Msec(500);
motor[roller]=-ROLLER_POWER; // drop first cone

mobileGoal(900,true,200);

moveWheels(5,true,1);

motor[roller]=ROLLER_POWER;
holdFourBar(50,10);
holdChainBar(1400,50);
wait1Msec(100);
motor[roller]=ROLLER_ANTIGRAVITY;
holdFourBar(150);
holdChainBar(2895,70);
motor[roller]=-ROLLER_POWER; //drop second cone


moveWheels(-48,true,1.5);//if 2 cones
wait1Msec(200);
motor[roller]=0;

turn(135);



//holdFourBar(600);

moveWheels(22.5,true,2.5);
wait1Msec(200);

turn(93);
wait1Msec(200);

mobileGoal(2070,false,50,200);
moveWheels(26,true,4);
//mb_mid(false);
mobileGoal(2500);
wait1Msec(500);


moveWheels(-18,true,2);


//finish first mobile goal (22 points)

mb_mid(false);
wait1Msec(600);
turn(90);
wait1Msec(300);

moveWheels(16,true,2); // move in 5 point zone
wait1Msec(400);
mb_out(false);
turn(90);

wait1Msec(400);

moveWheels(24,false,2); // go to mobile goal
wait1Msec(300);
mb_in(true);  // take the mobile goal
wait1Msec(300);

turn(-180);
wait1Msec(600);
mb_mid(false);
moveWheels(30,true,1.5);
mobileGoal(1800,false);
wait1Msec(600);
//finish second mobile goal (32 points)
moveWheels(-5,true,1);
wait1Msec(200);

turn(180);
wait1Msec(600);
mb_out(false);
moveWheels(42*sqrt(2)-4,true,2);

//mb_in(true); // take the mobile goal
mb_mid(false);
moveWheels(36*sqrt(2)-2,true,2);
mobileGoal(1800,false);
//finish third mobile goal (42 points)

moveWheels(-3,true,1);
wait1Msec(200);
turn(-135);

mb_out(false);
wait1Msec(600);

moveWheels(55,true,2);
mb_in(true);
wait1Msec(300);

moveWheels(-54,true,1.5);
wait1Msec(300);

turn(-155);

//holdChainBar(600);

wait1Msec(300);
//holdFourBar(400);

moveWheels(11.5,true,2.5);
wait1Msec(400);

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
wait1Msec(600);
turn(90);
wait1Msec(300);

moveWheels(16,true,2); // move in 5 point zone
wait1Msec(400);
mb_out(false);
turn(90);

wait1Msec(400);

moveWheels(24,false,2); // go to mobile goal
wait1Msec(300);
mb_in(true);  // take the mobile goal
wait1Msec(300);

turn(-180);
wait1Msec(600);
mb_mid(false);
moveWheels(30,true,1.5);
mobileGoal(1800,false);
wait1Msec(600);
//finish fifth mobile goal (72 points)
moveWheels(-5,true,1);
wait1Msec(200);

turn(180);
wait1Msec(600);
mb_out(false);
moveWheels(42*sqrt(2)-4,true,2);

//mb_in(true); // take the mobile goal
mb_mid(false);
moveWheels(36*sqrt(2)-2,true,2);
mobileGoal(1800,false);
//finish sixth mobile goal (82 points)
