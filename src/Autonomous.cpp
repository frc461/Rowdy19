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
	autoState = InitialStart;
	driveTrain = &dt;
	sensors = &srs;
	AutonPostValues();
	SwitchPeriodicValues();
	ScalePeriodicValues();
}

void Autonomous::SetAutoState(int pAutoState){
	autoState = pAutoState;
}

void Autonomous::AutonPostValues(){
	SmartDashboard::PutNumber("Auton/initDist", initDist);
	SmartDashboard::PutNumber("Auton/Switch/lTurn1", lTurn1);
	SmartDashboard::PutNumber("Auton/Switch/lDrive2", lDrive2);
	SmartDashboard::PutNumber("Auton/Switch/lTurn2", lTurn2);
	SmartDashboard::PutNumber("Auton/Switch/lDrive3", lDrive3);
	SmartDashboard::PutNumber("Auton/Switch/rTurn1", rTurn1);
	SmartDashboard::PutNumber("Auton/Switch/rDrive2", rDrive2);
	SmartDashboard::PutNumber("Auton/Switch/rTurn2", rTurn2);
	SmartDashboard::PutNumber("Auton/Switch/rDrive3", rDrive3);
	SmartDashboard::PutNumber("Auton/Switch/defaultDist", defaultDist);

	SmartDashboard::PutNumber("Auton/Scale/drivePastDist", drivePastDist);
	SmartDashboard::PutNumber("Auton/Scale/driveAwayDist", driveAwayDist);

}

void Autonomous::SwitchPeriodicValues(){
	initDist = SmartDashboard::GetNumber("Auton/initDist", initDist);
	lTurn1 = SmartDashboard::GetNumber("Auton/Switch/lTurn1", lTurn1);
	lTurn2 =  SmartDashboard::GetNumber("Auton/Switch/lTurn2", lTurn2);
	lDrive2 = SmartDashboard::GetNumber("Auton/Switch/lDrive2", lDrive2);
	lDrive3 = SmartDashboard::GetNumber("Auton/Switch/lDrive3", lDrive3);
	rTurn1 = SmartDashboard::GetNumber("Auton/Switch/rTurn1", rTurn1);
	rTurn2 = SmartDashboard::GetNumber("Auton/Switch/rTurn2", rTurn2);
	rDrive2 = SmartDashboard::GetNumber("Auton/Switch/rDrive2", rDrive2);
	rDrive3 = SmartDashboard::GetNumber("Auton/Switch/rDrive3",rDrive3);
	defaultDist = SmartDashboard::GetNumber("Auton/defaultDist", 2500);
	AutonPeriodicValues();
}

void Autonomous::AutonPeriodicValues(){
	autoDriveSpeed = SmartDashboard::GetNumber("Auton/autoDriveSpeed", -0.75);
	autoTurnSpeed = SmartDashboard::GetNumber("Auton/autoTurnSpeed", -0.6);
	SmartDashboard::PutNumber("Auton/autoState", autoState);
	SmartDashboard::PutNumber("gyro", sensors->GetGyroAngle());
}

void Autonomous::ScalePeriodicValues(){
	SmartDashboard::PutNumber("Auton/Scale/autoDriveSpeed", -0.8);
}

void Autonomous::ScaleRightAuto(){

}

void Autonomous::ScaleLeftAuto(){

	switch (autoState) {
		case(InitialStart):
			break;
		case(TurnDownMiddle):
			break;

	}
}

void Autonomous::SwitchRightAuto(){

	SwitchPeriodicValues();
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
    				driveTrain->ResetEncoders();
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
	SwitchPeriodicValues();

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
    				driveTrain->ResetEncoders();
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
