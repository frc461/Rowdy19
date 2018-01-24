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

Autonomous::Autonomous(DriveTrain& dt, Encoder&passEnc, ADXRS450_Gyro& passGyro) {
	GetShuffleboardValues();
	autoState = InitialStart;
	driveTrain = &dt;
	gyro = &passGyro;
	driveEnc = &passEnc;
}

void Autonomous::GetShuffleboardValues(){
	initDist = SmartDashboard::GetNumber("Auton/initDist",420);
	lTurn2 =  SmartDashboard::GetNumber("Auton/lTurn2",45);
	lDrive2 = SmartDashboard::GetNumber("Auton/lDrive2",-1530);
	lDrive3 = SmartDashboard::GetNumber("Auton/lDrive3",-500);
	rTurn1 = SmartDashboard::GetNumber("Auton/rTurn1",55);
	rTurn2 = SmartDashboard::GetNumber("Auton/rTurn2",-45);
	rDrive3 = SmartDashboard::GetNumber("Auton/rDrive3",-790);
	defaultDist = SmartDashboard::GetNumber("Auton/defaultDist", 2500);
	autoDriveSpeed = SmartDashboard::GetNumber("Auton/autoDriveSpeed", 0.75);
	autoTurnSpeed = SmartDashboard::GetNumber("Auton/autoTurnSpeed", 0.6);
}

void Autonomous::SwitchRightAuto(){
	int leftEncDist = driveEnc->GetDistance();
	int gyroAngle = gyro->GetAngle();
    	switch (autoState) {
    		case (InitialStart):
    			if (leftEncDist > initDist) {
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    				break;
    			} else {
    				gyro->Reset();
    				autoState = TurnDownMiddle;
    				break;
    			}
    		case (TurnDownMiddle):
    			if (gyroAngle < rTurn1) {
    				driveTrain->TankDrive(autoTurnSpeed, -autoTurnSpeed, 0.0);
    				break;
    			} else {
    				driveEnc->Reset();
    				autoState = DriveDiagonal;
    				break;
    			}
    		case (DriveDiagonal):
    			if (leftEncDist > rDrive2) {
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    				break;
    			} else {
    				gyro->Reset();
    				autoState = FaceSwitch;
    				break;
    			}
    		case (FaceSwitch):
    			if (gyroAngle > rTurn2) {
    				driveTrain->TankDrive(-autoTurnSpeed, autoTurnSpeed, 0.0);
    				break;
    			} else {
    				driveEnc->Reset();
    				autoState = DriveSideSwitch;
    				break;
    			}
    		case (DriveSideSwitch):
    			if (leftEncDist > rDrive3) {
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
	int leftEncDist = driveEnc->GetDistance();
	int gyroAngle = gyro->GetAngle();
    	switch (autoState) {
    		case (InitialStart):
    			if (leftEncDist > initDist) {
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    				break;
    			} else {
    				gyro->Reset();
    				autoState = TurnDownMiddle;
    				break;
    			}
    		case (TurnDownMiddle):
    			if (gyroAngle > lTurn1) {
    				driveTrain->TankDrive(-autoTurnSpeed, autoTurnSpeed, 0.0);
    				break;
    			} else {
    				driveEnc->Reset();
    				autoState = DriveDiagonal;
    				break;
    			}
    		case (DriveDiagonal):
    			if (leftEncDist > lDrive2) {
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    				break;
    			}
    			else {
    				gyro->Reset();
    				autoState = FaceSwitch;
    				break;
    			}
    		case (FaceSwitch):
    			if (gyroAngle < lTurn2) {
    				driveTrain->TankDrive(autoTurnSpeed, -autoTurnSpeed, 0.0);
    				break;
    			} else {
    				driveEnc->Reset();
    				autoState = DriveSideSwitch;
    				break;
    			}
    		case (DriveSideSwitch):
    			if (leftEncDist > lDrive3){
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
	int leftEncDist = driveEnc->GetDistance();
	if(leftEncDist < defaultDist){
		driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
	}
};
