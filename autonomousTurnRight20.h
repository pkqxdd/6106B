
motor[roller]=ROLLER_POWER;

mb_out(false);
outOfSize(500,1805);
motor[roller]=ROLLER_ANTIGRAVITY;
moveWheels(49,true,2.2);
wait1Msec(500);
motor[roller]=-ROLLER_POWER;//drops first cone before putting mobile goal in

mobileGoal(900,true,200);

moveWheels(5,true,1);//moves forward to pick up second cone

motor[roller]=ROLLER_POWER;
holdFourBar(100); //should move 4 bar down
holdChainBar(2000); //should move chain bar
//both of these lock the code in place and dont move past it
//if both commented out the rest runs as it should
wait1Msec(500);
motor[roller]=ROLLER_ANTIGRAVITY;
holdChainBar(4095,25);
motor[roller]=-ROLLER_POWER;


/*
holdFourBar(630);
wait1Msec(300);

motor[roller]=-ROLLER_POWER;
wait1Msec(200);
holdFourBar(900);
*/
moveWheels(-47,true,1.5);
wait1Msec(500);
motor[roller]=0;

turn(-135);

holdChainBar(4000);

wait1Msec(500);
//holdFourBar(600);

moveWheels(21.5,true,2.5);
wait1Msec(700);

turn(-90);
wait1Msec(300);

mobileGoal(2270,false,50);
moveWheels(22,true,4);
mb_mid(false);

wait1Msec(500);


mb_out(false);
moveWheels(-18,true,4);
