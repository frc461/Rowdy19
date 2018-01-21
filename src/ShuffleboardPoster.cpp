/*
 * ShuffleboardPoster.cpp
 *
 *  Created on: Jan 21, 2018
 *      Author: hank
 */

#include <ShuffleboardPoster.h>
#include <Robot.h>

ShuffleboardPoster::ShuffleboardPoster() {
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
}

ShuffleboardPoster::~ShuffleboardPoster() {
	// TODO Auto-generated destructor stub
}

void AutonGet(){
	initialDist    = SmartDashboard::GetNumber("Auton/initDist", -420);
	lTurn1         = SmartDashboard::GetNumber("Auton/lTurn1", -35);
	lTurn2         = SmartDashboard::GetNumber("Auton/lTurn2", 45);
	lDrive2        = SmartDashboard::GetNumber("Auton/lDrive2", -1530);
	lDrive3        = SmartDashboard::GetNumber("Auton/lDrive3", -500);
	rTurn1         = SmartDashboard::GetNumber("Auton/rTurn1", 55);
	rTurn2         = SmartDashboard::GetNumber("Auton/rTurn2", -45);
	rDrive2        = SmartDashboard::GetNumber("Auton/rDrive2", -1200);
	rDrive3        = SmartDashboard::GetNumber("Auton/rDrive3", -790);
	autoDriveSpeed = SmartDashboard::GetNumber("Auton/autoDriveSpeed", 0.8);
	autoTurnSpeed  = SmartDashboard::GetNumber("Auton/autoTurnSpeed", 0.65);
}

void TeleopGet(){

}

void ShufflePeriodic(){
	SmartDashboard::PutData("navxBoard", navxBoard);
}

void GetOurSwitch(){
	if(gameData[0] == 'L'){
		return LeftSide;
	} else if(gameData[0] == 'R'){
		return RightSide;
	} else {
		return DataError;
	}
}


void GetOurScale(){
	if(gameData[1] == 'L'){
		return LeftSide;
	} else if(gameData[1] == 'R'){
		return RightSide;
	} else {
		return DataError;
	}
}

void GetTheirScale(){
	if(gameData[2] == 'L'){
		return LeftSide;
	} else if(gameData[2] == 'R'){
		return RightSide;
	} else {
		return DataError;
	}
}


