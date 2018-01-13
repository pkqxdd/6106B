#ifndef LCD
#define LCD



float getBatterPowerBackup(){ // return [backup,left,right]

	float raw=BackupBatteryLevel;
	return raw;
}

float getBatterPowerLeft(){
		float raw=SensorValue[left_battery];
		return raw/70.8;
}

float getBatterPowerRight(){
	float raw=nAvgBatteryLevel;
		return raw;
}

void resetLCD(){
	clearLCDLine(0);
	clearLCDLine(1);
}

void printToLCD(const int line,const string s ){
	displayLCDString(line,0,s);
}

void printBatteryPower(){
	resetLCD();
	float b,l,r;
	b=getBatterPowerBackup();
	l=getBatterPowerLeft()*1000;
	r=getBatterPowerRight();
displayLCDString(0,0,"Bckup Left Right");
displayLCDNumber(1,0,b,2);
displayLCDNumber(1,6,l,2);
displayLCDNumber(1,11,r,2);

}

task LCDControls(){
	int b;
	string msg;
while (true){
	b=nLCDButtons;
switch(b){
case 0:
	msg="None";
	break;
case 1:
	msg="Left";
	break:
case 2:
	msg="Middle";
	break;
case 3:
	msg="Middle&Left";
	break;
case 4:
	msg="Right";
	break;
case 5:
	msg="Left&Right";
	break;
case 6:
	msg="Middle&Right";
	break;
case 7:
	msg="All";
	break;

}
printToLCD(0,msg);
abortTimeslice();
}

}

#endif
