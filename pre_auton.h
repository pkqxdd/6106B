
// ------------BEGIN correcting mobile goal lift encoder reading---------
motor[mb_left]=MB_POWER;
motor[mb_right]=MB_POWER;
nMotorEncoder[mb_left]=0;
nMotorEncoder[mb_right]=0;

clearTimer(T1);
while (time1(T1)<2000) {
	mobileGoalUp();
}



motor[mb_left]=0;
motor[mb_right]=0;

wait1Msec(500);


nMotorEncoder[mb_left]=0;
nMotorEncoder[mb_right]=0;
// ------------END correcting mobile goal lift encoder reading---------
