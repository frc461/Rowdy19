/*
 * Autonomous.cpp
 *
 *  Created on: Jan 23, 2018
 *      Author: hank
 */

#include "Autonomous.h"
#include <WPILib.h>
#include "Robot.h"
#include "ShuffleboardPoster.h"

Autonomous::Autonomous() {
	GetShuffleboardValues();
}

void GetShuffleboardValues(){
	initDist = SmartDashboard::GetNumber("Auton/initDist",420);
	lTurn2 =  SmartDashboard::GetNumber("Auton/lTurn2",45);
	lDrive2 = SmartDashboard::GetNumber("Auton/lDrive2",-1530);
	lDrive3 = SmartDashboard::GetNumber("Auton/lDrive3",-500);
	rTurn1 = SmartDashboard::GetNumber("Auton/rTurn1",55);
	rTurn2 = SmartDashboard::GetNumber("Auton/rTurn2",-45);
	rDrive2 = SmartDashboard::GetNumber("Auton/rDrive2",-1200);
	rDrive3 = SmartDashboard::GetNumber("Auton/rDrive3",-790);
	autoDriveSpeed = SmartDashboard::GetNumber("Auton/autoDriveSpeed", 0.75);
	autoTurnSpeed = SmartDashboard::GetNumber("Auton/autoTurnSpeed", 0.6);
}

void SwitchRightAuto(double leftEncDist, double gyroAngle){
    	switch (autoState) {
    		case (InitialStart):
    			if (leftEncDist > initialDist) {
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    				break;
    			} else {
    				navxBoard->Reset();
    				autoState = TurnDownMiddle;
    				break;
    			}
    		case (TurnDownMiddle):
    			if (ourSwitch == RightSide && gyroAngle < rTurn1) {
    				driveTrain->TankDrive(autoTurnSpeed, -autoTurnSpeed, 0.0);
    				break;
    			} else {
    				EncoderReset();
    				autoState = DriveDiagonal;
    				break;
    			}
    		case (DriveDiagonal):
    			if (ourSwitch == RightSide && leftEncDist > rDrive2) {
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    				break;
    			} else {
    				navxBoard->Reset();
    				autoState = FaceSwitch;
    				break;
    			}
    		case (FaceSwitch):
    			if (ourSwitch == RightSide && gyroAngle > rTurn2) {
    				driveTrain->TankDrive(-autoTurnSpeed, autoTurnSpeed, 0.0);
    				break;
    			} else {
    				EncoderReset();
    				autoState = DriveSideSwitch;
    				break;
    			}
    		case (DriveSideSwitch):
    			if (ourSwitch == RightSide && leftEncDist > rDrive3) {
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    				break;
    			} else {
    				autoState = DeployBlock;
    				break;
    			}
    		case (DeployBlock):
    			break;
    	}
	
}

void SwitchLeftAuto(double leftEncDist, double gyroAngle){ 
    	switch (autoState) {
    		case (InitialStart):
    			if (leftEncDist > initialDist) {
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    				break;
    			} else {
    				navxBoard->Reset();
    				autoState = TurnDownMiddle;
    				break;
    			}
    		case (TurnDownMiddle):
    			if (ourSwitch == LeftSide && gyroAngle > lTurn1) {
    				driveTrain->TankDrive(-autoTurnSpeed, autoTurnSpeed, 0.0);
    				break;
    			} else {
    				EncoderReset();
    				autoState = DriveDiagonal;
    				break;
    			}
    		case (DriveDiagonal):
    			if (ourSwitch == LeftSide && leftEncDist > lDrive2) {
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    				break;
    			}
    			else {
    				navxBoard->Reset();
    				autoState = FaceSwitch;
    				break;
    			}
    		case (FaceSwitch):
    			if (ourSwitch == LeftSide && gyroAngle < lTurn2) {
    				driveTrain->TankDrive(autoTurnSpeed, -autoTurnSpeed, 0.0);
    				break;
    			} else {
    				EncoderReset();
    				autoState = DriveSideSwitch;
    				break;
    			}
    		case (DriveSideSwitch):
    			if (ourSwitch == LeftSide && leftEncDist > lDrive3){
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    				break;
    			}
    			else {
    				autoState = DeployBlock;
    				break;
    			}
    		case (DeployBlock):
    			break;
    	}
}
