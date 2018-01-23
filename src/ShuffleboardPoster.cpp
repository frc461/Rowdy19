/*
 * ShuffleboardPoster.cpp
 *
 *  Created on: Jan 21, 2018
 *      Author: hank
 */

#include <ShuffleboardPoster.h>
#include <Robot.h>

ShuffleboardPoster::ShuffleboardPoster(Encoder* leftDriveEncoder, Encoder* right, AHRS* navxBoard) {
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
    ShuffleboardPoster::leftDriveEncoder = leftDriveEncoder;
	ShuffleboardPoster::rightDriveEncoder = rightDriveEncoder;
	ShuffleboardPoster::navxBoard = navxBoard;
}

ShuffleboardPoster::~ShuffleboardPoster() {} void AutonGet(){
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
	SmartDashboard::PutData("LeftEncoder", leftDriveEncoder);
	SmartDashboard::PutData("RightEncoder", rightDriveEncoder);
	SmartDashvoard::PutData("PDP", pdp);

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


