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
	generateSelectors();
}

void ShuffleboardPoster::generateSelectors(){
		startingPosition.AddObject("Left Side", LeftPosition);
		startingPosition.AddDefault("Center", CenterPosition);
		startingPosition.AddObject("Right Side", RightPosition);
		SmartDashboard::PutData("Auton/Starting Position", &startingPosition);

		target.AddDefault("Switch", Switch);
		target.AddObject("Scale", Scale);
		SmartDashboard::PutData("Auton/Target", &target);

		SmartDashboard::Delete("Warning");
}

void ShuffleboardPoster::teleopGet(){

}

int ShuffleboardPoster::getStartingPosition(){
	return startingPosition.GetSelected();
}

int ShuffleboardPoster::getTarget(){
	return target.GetSelected();
}

void ShuffleboardPoster::shufflePeriodic(){
	SmartDashboard::PutNumber("gyro", sensors->getGyroAngle());
	SmartDashboard::PutBoolean("ElevatorSwitch", sensors->getElevatorBottom());
	SmartDashboard::PutNumber("LeftEncoderDist", driveTrain->getEncoderVal(LeftSide));
	SmartDashboard::PutNumber("RightEncoderDist", driveTrain->getEncoderVal(RightSide));
//	SmartDashboard::PutData("PDP", driveTrain->GetPDP());
}

int ShuffleboardPoster::getOurSwitch(){
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
	if(gameData[0] == 'L'){
		return LeftSide;
	} else if(gameData[0] == 'R'){
		return RightSide;
	} else {
		return DataError;
	}
}


int ShuffleboardPoster::getOurScale(){
	if(gameData[1] == 'L'){
		return LeftSide;
	} else if(gameData[1] == 'R'){
		return RightSide;
	} else {
		return DataError;
	}
}

int ShuffleboardPoster::getTheirSideSwitch(){
	if(gameData[2] == 'L'){
		return LeftSide;
	} else if(gameData[2] == 'R'){
		return RightSide;
	} else {
		return DataError;
	}
}


