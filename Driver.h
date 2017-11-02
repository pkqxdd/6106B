#ifndef drivers
#define drivers

// -----------------BEGIN Global Variables Configuration-------------------

const int MB_POWER = 80; // power to mobile goal lift
const int FOURBAR_POWER = 64; //power to fourbar
const int FOURBAR_ANTIGRAVITY = 20; //power to fourbar when it is in the "stop" position
const int MB_ANTIGRAVITY=5; //power to mobile goal lift when it is in the "stop" position

// ------------------END Global Variables Configuration----------------------
// -----------------BEGIN Keymap Configuration------------------

#define ButtonMobileGoalUp vexRT[Btn5U]
#define ButtonMobileGoalDown vexRT[Btn5D]
#define ButtonFourbarUp vexRT[Btn6U]
#define ButtonFourbarDown vexRT[Btn6D]
#define AxisLeftWheels vexRT[Ch3]
#define AxisRightWheels vexRT[Ch2]


// -----------------END Keymap Configuration----------------
// ------------------BEGIN Utility Functons---------------

void moveLeftWheels(int power)
{
	motor[front_left] = power;
	motor[back_left] = power;
}

void moveRightWheels(int power)
{
	motor[front_right] = power;
	motor[back_right] = power;
}

void mobileGoalUp()
{
	motor[mb_left] = MB_POWER;
	motor[mb_right] = MB_POWER;
}

void mobileGoalDown()
{
	motor[mb_left] = -MB_POWER;
	motor[mb_right] = -MB_POWER;
}

void mobileGoalStop(){
	motor[mb_left] = MB_ANTIGRAVITY;
	motor[mb_right] = MB_ANTIGRAVITY;
}

void fourBarUp()
{
	motor[fb_topleft] = FOURBAR_POWER;
	motor[fb_bottomleft] = FOURBAR_POWER;
	motor[fb_topright] = FOURBAR_POWER;
	motor[fb_bottomright] = FOURBAR_POWER;
}

void fourBarDown()
{

	motor[fb_topleft] = -FOURBAR_POWER;
	motor[fb_bottomleft] = -FOURBAR_POWER;
	motor[fb_topright] = -FOURBAR_POWER;
	motor[fb_bottomright] = -FOURBAR_POWER;
}

void fourBarStop()
{

	motor[fb_topleft] = FOURBAR_ANTIGRAVITY;
	motor[fb_bottomleft] = FOURBAR_ANTIGRAVITY;
	motor[fb_topright] = FOURBAR_ANTIGRAVITY;
	motor[fb_bottomright] = FOURBAR_ANTIGRAVITY;
}

//----------------END Utility Functions------------

task WheelControls()
{
	for (;;) // a foreverloop
	{
		moveLeftWheels(AxisLeftWheels);
		moveRightWheels(
		AxisRightWheels);
	}
}

task MobileGoalControls(){
	for (;;){
		while (ButtonMobileGoalDown) mobileGoalDown();
		while (ButtonMobileGoalUp) mobileGoalUp();
		mobileGoalStop();
	}
}

task FourBarControls(){
	for (;;){

		while (ButtonFourbarUp) fourBarUp();
		while (ButtonFourbarDown) fourBarDown();
		fourBarStop();
		}
}


#endif
