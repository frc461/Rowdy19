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
#include "Sensors.h"

Autonomous::Autonomous(DriveTrain& dt, Sensors& srs) {
	PutShuffleboardValues();
	GetShuffleboardValues();
	autoState = InitialStart;
	driveTrain = &dt;
	sensors = &srs;
}

void Autonomous::SetAutoState(int pAutoState){
	autoState = pAutoState;
}

void Autonomous::PutShuffleboardValues(){
	SmartDashboard::PutNumber("Auton/initDist",3000);
	SmartDashboard::PutNumber("Auton/lTurn2",45);
	SmartDashboard::PutNumber("Auton/lDrive2",5000);
	SmartDashboard::PutNumber("Auton/lDrive3",-500);
	SmartDashboard::PutNumber("Auton/rTurn1",55);
	SmartDashboard::PutNumber("Auton/rTurn2",-45);
	SmartDashboard::PutNumber("Auton/rDrive2",5000);
	SmartDashboard::PutNumber("Auton/rDrive3",-790);
	SmartDashboard::PutNumber("Auton/defaultDist", 2500);
	SmartDashboard::PutNumber("Auton/autoDriveSpeed", -0.75);
	SmartDashboard::PutNumber("Auton/autoTurnSpeed", -0.6);
}

void Autonomous::GetShuffleboardValues(){
	initDist = SmartDashboard::GetNumber("Auton/initDist",3000);
	lTurn2 =  SmartDashboard::GetNumber("Auton/lTurn2",45);
	lDrive2 = SmartDashboard::GetNumber("Auton/lDrive2",-1530);
	lDrive3 = SmartDashboard::GetNumber("Auton/lDrive3",-500);
	rTurn1 = SmartDashboard::GetNumber("Auton/rTurn1",55);
	rTurn2 = SmartDashboard::GetNumber("Auton/rTurn2",-45);
	rDrive2 = SmartDashboard::GetNumber("Auton/rDrive2", 5000);
	rDrive3 = SmartDashboard::GetNumber("Auton/rDrive3",2500);
	defaultDist = SmartDashboard::GetNumber("Auton/defaultDist", 2500);
	autoDriveSpeed = SmartDashboard::GetNumber("Auton/autoDriveSpeed", -0.75);
	autoTurnSpeed = SmartDashboard::GetNumber("Auton/autoTurnSpeed", -0.6);
	SmartDashboard::PutNumber("Auton/autoState", autoState);

}

void Autonomous::SwitchRightAuto(){
	int rightEncDist = driveTrain->GetEncoderVal(RightSide);
	int gyroAngle = sensors->GetGyroAngle();
    	switch (autoState) {
    		case (InitialStart):
    			if (rightEncDist < initDist) {
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    				break;
    			} else {
    				sensors->ResetGyro();
    				autoState = TurnDownMiddle;
    				break;
    			}
    		case (TurnDownMiddle):
    			if (gyroAngle < rTurn1) {
    				driveTrain->TankDrive(autoTurnSpeed, -autoTurnSpeed, 0.0);
    				break;
    			} else {
    				driveTrain->ResetEncoders();
    				autoState = DriveDiagonal;
    				break;
    			}
    		case (DriveDiagonal):
    			if (rightEncDist < rDrive2) {
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    				break;
    			} else {
    				sensors->ResetGyro();
    				autoState = FaceSwitch;
    				break;
    			}
    		case (FaceSwitch):
    			if (gyroAngle > rTurn2) {
    				driveTrain->TankDrive(-autoTurnSpeed, autoTurnSpeed, 0.0);
    				break;
    			} else {
    				driveTrain->ResetEncoders();
    				autoState = DriveSideSwitch;
    				break;
    			}
    		case (DriveSideSwitch):
    			if (rightEncDist < rDrive3) {
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

void Autonomous::SwitchLeftAuto(){
	int rightEncDist = driveTrain->GetEncoderVal(RightSide);
	int gyroAngle = sensors->GetGyroAngle();
    	switch (autoState) {
    		case (InitialStart):
    			if (rightEncDist < initDist) {
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    				break;
    			} else {
    				sensors->ResetGyro();
    				autoState = TurnDownMiddle;
    				break;
    			}
    		case (TurnDownMiddle):
    			if (gyroAngle > lTurn1) {
    				driveTrain->TankDrive(-autoTurnSpeed, autoTurnSpeed, 0.0);
    				break;
    			} else {
    				driveTrain->ResetEncoders();
    				autoState = DriveDiagonal;
    				break;
    			}
    		case (DriveDiagonal):
    			if (rightEncDist < lDrive2) {
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    				break;
    			}
    			else {
    				sensors->ResetGyro();
    				autoState = FaceSwitch;
    				break;
    			}
    		case (FaceSwitch):
    			if (gyroAngle < lTurn2) {
    				driveTrain->TankDrive(autoTurnSpeed, -autoTurnSpeed, 0.0);
    				break;
    			} else {
				driveTrain->ResetEncoders();
    				autoState = DriveSideSwitch;
    				break;
    			}
    		case (DriveSideSwitch):
    			if (rightEncDist < lDrive3){
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

void Autonomous::DefaultCross(){
	int rightEncDist = sensors->GetLeftEncoderDistance();
	if(rightEncDist < defaultDist){
		driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
	}
};
