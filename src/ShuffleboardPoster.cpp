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
		secondChoice.AddDefault("Switch", Switch);
		secondChoice.AddDefault("Scale", Scale);
		secondChoice.AddDefault("Default", 0);
		SmartDashboard::PutData("Comp/secondChoice", &secondChoice);

		startingPosition.AddObject("Left Side", LeftPosition);
		startingPosition.AddDefault("Center", CenterPosition);
		startingPosition.AddObject("Right Side", RightPosition);
		SmartDashboard::PutData("Comp/Starting Position", &startingPosition);

		target.AddObject("Switch", Switch);
		target.AddDefault("Scale", Scale);
		target.AddObject("Default", 5);
		SmartDashboard::PutData("Comp/Target", &target);

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

int ShuffleboardPoster::getSecondChoice(){
	return secondChoice.GetSelected();
}

void ShuffleboardPoster::shufflePeriodic(){
	SmartDashboard::PutNumber("gyro", sensors->getGyroAngle());
	SmartDashboard::PutBoolean("ElevatorSwitch", sensors->getElevatorBottom());
	SmartDashboard::PutBoolean("IntakeInR", sensors->getIntakeButtonR());
	SmartDashboard::PutBoolean("IntakeInL", sensors->getIntakeButtonL());


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


