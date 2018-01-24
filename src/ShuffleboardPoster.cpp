/*
 * ShuffleboardPoster.cpp
 *
 *  Created on: Jan 21, 2018
 *      Author: hank
 */

#include "ShuffleboardPoster.h"
#include <Robot.h>
#include <WPILib.h>

ShuffleboardPoster::ShuffleboardPoster(Encoder& passLeft, Encoder& passRight, ADXRS450_Gyro& passGyro) {
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
    leftDriveEncoder = &passLeft;
	rightDriveEncoder = &passRight;
	gyro = &passGyro;
}

void ShuffleboardPoster::TeleopGet(){

}

void ShuffleboardPoster::ShufflePeriodic(){
	SmartDashboard::PutData("navxBoard", ShuffleboardPoster::gyro);
	SmartDashboard::PutData("LeftEncoder", ShuffleboardPoster::leftDriveEncoder);
	SmartDashboard::PutData("RightEncoder", ShuffleboardPoster::rightDriveEncoder);
//	SmartDashvoard::PutData("PDP", pdp);

}

int ShuffleboardPoster::GetOurSwitch(){
	if(gameData[0] == 'L'){
		return LeftSide;
	} else if(gameData[0] == 'R'){
		return RightSide;
	} else {
		return DataError;
	}
}


int ShuffleboardPoster::GetOurScale(){
	if(gameData[1] == 'L'){
		return LeftSide;
	} else if(gameData[1] == 'R'){
		return RightSide;
	} else {
		return DataError;
	}
}

int ShuffleboardPoster::GetTheirSideSwitch(){
	if(gameData[2] == 'L'){
		return LeftSide;
	} else if(gameData[2] == 'R'){
		return RightSide;
	} else {
		return DataError;
	}
}


