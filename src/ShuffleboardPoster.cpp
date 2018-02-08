/*
 * ShuffleboardPoster.cpp
 *
 *  Created on: Jan 21, 2018
 *      Author: hank
 */

#include "ShuffleboardPoster.h"
#include <Robot.h>
#include <WPILib.h>
#include "Sensors.h"

ShuffleboardPoster::ShuffleboardPoster(DriveTrain& dt, Sensors& srs) {
	driveTrain = &dt;
	sensors = &srs;
	SendableChooser<int> startingPosition;
	startingPosition.AddDefault("Left Side", LeftPosition);
	startingPosition.AddDefault("Center", CenterPosition);
	startingPosition.AddDefault("Right Side", RightPosition);
//	SmartDashboard::PutData("Starting Position", startingPosition);
}

void ShuffleboardPoster::TeleopGet(){

}

void ShuffleboardPoster::ShufflePeriodic(){
//	SmartDashboard::PutNumber("gyro", sensors->GetGyroAngle());
//	SmartDashboard::PutNumber("LeftEncoderDist", sensors->GetLeftEncoderDistance());
//	SmartDashboard::PutNumber("RightEncoderDist", sensors->GetRightEncoderDistance());
//	SmartDashboard::PutData("PDP", driveTrain->GetPDP());

}

int ShuffleboardPoster::GetOurSwitch(){
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
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


