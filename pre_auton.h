
// ------------BEGIN correcting mobile goal lift encoder reading---------
void zeroMobileGoalEncoders(const int t){
motor[mb_left]=MB_POWER;
motor[mb_right]=MB_POWER;
nMotorEncoder[mb_left]=0;
nMotorEncoder[mb_right]=0;

clearTimer(T1);
while (time1(T1)<t) {
	mobileGoalUp();
}



motor[mb_left]=0;
motor[mb_right]=0;

wait1Msec(200);


nMotorEncoder[mb_left]=0;
nMotorEncoder[mb_right]=0;
return;
}
// ------------END correcting mobile goal lift encoder reading---------
