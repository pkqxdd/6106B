
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
holdFourBar(120);
holdChainBar(2895,70);
motor[roller]=-ROLLER_POWER; //drop second cone


/*
holdFourBar(630);
wait1Msec(300);

motor[roller]=-ROLLER_POWER;
wait1Msec(200);
holdFourBar(900);
*/
moveWheels(-48,true,1.5);
wait1Msec(200);
motor[roller]=0;

turn(135);



//holdFourBar(600);

moveWheels(22.5,true,2.5);
wait1Msec(200);

turn(90);
wait1Msec(200);

mobileGoal(2270,false,50);
moveWheels(24,true,5);
mb_mid(false);

wait1Msec(500);


mb_out(false);
moveWheels(-18,true,4);
