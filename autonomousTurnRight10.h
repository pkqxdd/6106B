
motor[roller]=ROLLER_POWER;


mb_out(false);
outOfSize(500,1805);
moveWheels(49,true,2.2);
wait1Msec(1000);
motor[roller]=-ROLLER_POWER; // drop first cone

mobileGoal(900,true,200);

moveWheels(5,true,1);

motor[roller]=ROLLER_POWER;
holdFourBar(50,10);
holdChainBar(1400,100);
wait1Msec(100);
motor[roller]=ROLLER_ANTIGRAVITY;
holdFourBar(125);
holdChainBar(2895,80);

motor[roller]=-ROLLER_POWER; //drop second cone
wait1Msec(150);
moveWheels(8,true,2);

motor[roller]=ROLLER_POWER;

holdFourBar(50);

holdChainBar(1300,100);

wait1Msec(100);

motor[roller]=ROLLER_ANTIGRAVITY;
holdFourBar(275);
holdChainBar(2895,70);
motor[roller]=-ROLLER_POWER; //drop second cone



moveWheels(-56,true,1.5);//if 3 cones
//moveWheels(-48,true,1.5);//if 2 cones
wait1Msec(200);
motor[roller]=0;

//turn(-135);
turn(-180);

//moveWheels(6,true,2);
//wait1Msec(100);

//turn(-90);
//wait1Msec(100);

//moveWheels(7,true,2);

mb_out(true);
moveWheels(-18,true,4);
