/*
 * Autonomous.cpp
 *
 *  Created on: Jan 23, 2018
 *      Author: Hank Krutulis - 461
 */

#include "Autonomous.h"

Autonomous::Autonomous(DriveTrain& dt, Sensors& srs, ShuffleboardPoster& boardHandler, Elevator& elevatorP, Intake& intakeP) {

	autoState = InitialStart;
	driveTrain = &dt;
	sensors = &srs;
	elevator = &elevatorP;
	board = &boardHandler;
	intake = &intakeP;
	AutonPostValues();
	AutonPeriodicValues();
	target = board->GetTarget();
	startingPosition = board->GetStartingPosition();
}

void Autonomous::RunAuto(){
	AutonPeriodicValues();
	if(target == Scale){
		if(startingPosition == CenterPosition){
			ScaleFromCenter();
			printf("Scale from center");
		} else {
			ScaleFromSide();
			printf("Scale from side\n");
		}
	} else if(target == autoTarget::Switch){
		if(startingPosition == CenterPosition){
			if(board->GetOurSwitch() == RightSide){
				SwitchRightAuto();
				printf("Switch right from center\n");
			} else{
				SwitchLeftAuto();
				printf("Switch left from center");
			}
		} else {
			SwitchFromSide();
			printf("Switch from side");
		}
	} else {
		DefaultCross();
		printf("Defaulting");
	}
}

void Autonomous::SetAutoState(int pAutoState){
	autoState = pAutoState;
}

void Autonomous::AutonPostValues(){
	SmartDashboard::PutNumber("Auton/initDist", initDist);
	SmartDashboard::PutNumber("Auton/autoDriveSpeed", -0.8);

	SmartDashboard::PutNumber("Auton/Switch/lTurn1", lTurn1);
	SmartDashboard::PutNumber("Auton/Switch/lDrive2", lDrive2);
	SmartDashboard::PutNumber("Auton/Switch/lTurn2", lTurn2);
	SmartDashboard::PutNumber("Auton/Switch/lDrive3", lDrive3);
	SmartDashboard::PutNumber("Auton/Switch/rTurn1", rTurn1);
	SmartDashboard::PutNumber("Auton/Switch/rDrive2", rDrive2);
	SmartDashboard::PutNumber("Auton/Switch/rTurn2", rTurn2);
	SmartDashboard::PutNumber("Auton/Switch/rDrive3", rDrive3);
	SmartDashboard::PutNumber("Auton/Switch/defaultDist", defaultDist);

	SmartDashboard::PutNumber("Auton/Switch/faceSwitchAngleRight", faceSwitchAngleRight);
	SmartDashboard::PutNumber("Auton/Switch/faceSwitchAngleLeft", faceSwitchAngleLeft);
	SmartDashboard::PutNumber("Auton/Switch/driveToSwitchDist", driveToSwitchDist);

	SmartDashboard::PutNumber("Auton/Scale/scaleSideDist", scaleSideDist);
	SmartDashboard::PutNumber("Auton/Scale/faceScaleAngle", faceScaleAngle);
	SmartDashboard::PutNumber("Auton/Scale/scaleAdjustDist", scaleAdjustDist);

	SmartDashboard::PutNumber("Auton/Scale/drivePastDist", drivePastDist);
	SmartDashboard::PutNumber("Auton/Scale/driveAwayDist", driveAwayDist);

}



void Autonomous::AutonPeriodicValues(){
	initDist = SmartDashboard::GetNumber("Auton/initDist", initDist);
	lTurn1 = SmartDashboard::GetNumber("Auton/Switch/lTurn1", lTurn1);
	lTurn2 =  SmartDashboard::GetNumber("Auton/Switch/lTurn2", lTurn2);
	lDrive2 = SmartDashboard::GetNumber("Auton/Switch/lDrive2", lDrive2);
	lDrive3 = SmartDashboard::GetNumber("Auton/Switch/lDrive3", lDrive3);
	rTurn1 = SmartDashboard::GetNumber("Auton/Switch/rTurn1", rTurn1);
	rTurn2 = SmartDashboard::GetNumber("Auton/Switch/rTurn2", rTurn2);
	rDrive2 = SmartDashboard::GetNumber("Auton/Switch/rDrive2", rDrive2);
	rDrive3 = SmartDashboard::GetNumber("Auton/Switch/rDrive3",rDrive3);
	defaultDist = SmartDashboard::GetNumber("Auton/defaultDist", defaultDist);

	scaleSideDist = SmartDashboard::GetNumber("Auton/Scale/scaleSideDist", scaleSideDist);
	faceScaleAngle = SmartDashboard::GetNumber("Auton/Scale/faceScaleAngle", faceScaleAngle);
	scaleAdjustDist = SmartDashboard::GetNumber("Auton/Scale/scaleAdjustDist", scaleAdjustDist);

	autoDriveSpeed = SmartDashboard::GetNumber("Auton/autoDriveSpeed", -0.75);
	autoTurnSpeed = SmartDashboard::GetNumber("Auton/autoTurnSpeed", -0.6);
	SmartDashboard::PutNumber("Auton/autoState", autoState);
	SmartDashboard::PutNumber("gyro", sensors->GetGyroAngle());

	ourSwitch = board->GetOurSwitch();
	ourScale = board->GetOurScale();

	encoderDist = driveTrain->GetEncoderVal(RightSide);
	gyroAngle = sensors->GetGyroAngle();
	target = board->GetTarget();
	startingPosition = board->GetStartingPosition();
}

void Autonomous::SwitchFromSide(){
	if(ourSwitch == startingPosition){
		switch (autoState) {
		case(InitialStart):
				if(encoderDist > -switchSideDist){
					driveTrain->ArcadeDrive(autoDriveSpeed, 0.0, 0.0);
				} else {
					autoState = FaceSwitch;
					sensors->ResetGyro();
				}
				break;
		case(FaceSwitch):
				if(ourSwitch == RightSide && gyroAngle < faceSwitchAngleRight){
					driveTrain->ArcadeDrive(0.0, autoTurnSpeed, 0.0);
				} else if (ourSwitch == LeftSide && gyroAngle > -faceSwitchAngleLeft){
					driveTrain->ArcadeDrive(0.0, -autoTurnSpeed, 0.0);
				} else {
					autoState = DriveSideSwitch;
					driveTrain->ResetEncoders();
				}
			break;
		case(DriveSideSwitch):
				if(encoderDist < driveToSwitchDist){
					driveTrain->ArcadeDrive(autoDriveSpeed, 0.0, 0.0);
				} else {
					autoState = DeployCube;

				}
			break;
		case(RaiseElevator):
				if(true){
					elevator->goUp();
				} else {
					autoState = DeployCube;
				}
			break;
		case(DeployCube):
				intake->spitCube();

			break;
		}
	}
}

void Autonomous::ScaleFromCenter(){

}

void Autonomous::ScaleFromSide(){
	if(!elevatorZeroed){
		elevator->goDown();
		if(sensors->getElevatorBottom()){
			elevatorZeroed = true;
		}
	} else if (elevator->encoderValue() < scaleHeight) {
		elevator->goUp();
	} else {
		elevator->haltMotion();
	}

	switch (autoState) {
		case(InitialStart):
			if(encoderDist > -scaleSideDist){
				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed * (1.025 + (gyroAngle / 45)), 0.0);
			} else {
				autoState = TurnTowardsScale;
				sensors->ResetGyro();
			}
			break;
		case(TurnTowardsScale):
			if(ourScale == LeftSide && gyroAngle < faceScaleAngle){
				driveTrain->TankDrive(autoTurnSpeed, -autoTurnSpeed, 0.0);
				driveTrain->ResetEncoders();
			} else {
				autoState = DriveTowardsScale;
				driveTrain->ResetEncoders();
			}
			break;
		case(DriveTowardsScale):
				if(encoderDist > -scaleAdjustDist){
					driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
				} else {
					autoState = DeployCube;
					sensors->ResetGyro();
				}
			break;
		case(DeployCube):
			intake->spitCube();
			break;

	}
}

void Autonomous::SwitchRightAuto(){

	AutonPeriodicValues();
	int rightEncDist = driveTrain->GetEncoderVal(RightSide);
	int gyroAngle = sensors->GetGyroAngle();

    	switch (autoState) {
    		case (InitialStart):
    			if (rightEncDist > -initDist) {
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    			} else {
    				sensors->ResetGyro();
    				autoState = TurnDownMiddle;
    			}
    			break;

    		case (TurnDownMiddle):
    			if (gyroAngle < rTurn1) {
    				driveTrain->TankDrive(autoTurnSpeed, -autoTurnSpeed, 0.0);
    			} else {
    				driveTrain->ResetEncoders();
    				autoState = DriveDiagonal;
    			}
    			break;

    		case (DriveDiagonal):
    			if (rightEncDist > -rDrive2) {
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    			} else {
    				sensors->ResetGyro();
    				driveTrain->ResetEncoders();
    				autoState = FaceSwitch;
    			}
			break;

    		case (FaceSwitch):
    			if (gyroAngle > rTurn2) {
    				driveTrain->TankDrive(-autoTurnSpeed, autoTurnSpeed, 0.0);
    				driveTrain->ResetEncoders();
    			} else {
    				driveTrain->ResetEncoders();
    				autoState = DriveSideSwitch;
    			}
			break;

    		case (DriveSideSwitch):
    			if (rightEncDist > -rDrive3) {
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    			} else {
    				driveTrain->TankDrive(0.0, 0.0, 0.0);
    				autoState = DeployCube;
    			}
			break;

    		case (DeployCube):
    				intake->spitCube();
    			break;
    	}
	
}

void Autonomous::SwitchLeftAuto(){
	int rightEncDist = driveTrain->GetEncoderVal(RightSide);
	int gyroAngle = sensors->GetGyroAngle();
	AutonPeriodicValues();

    	switch (autoState) {
    		case (InitialStart):
    			if (rightEncDist > -initDist) {
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    			} else {
    				sensors->ResetGyro();
    				autoState = TurnDownMiddle;
    			}
			break;

    		case (TurnDownMiddle):
    			if (gyroAngle > lTurn1) {
    				driveTrain->TankDrive(-autoTurnSpeed, autoTurnSpeed, 0.0);
    			} else {
    				driveTrain->ResetEncoders();
    				autoState = DriveDiagonal;
    			}
			break;

    		case (DriveDiagonal):
    			if (rightEncDist > -lDrive2) {
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    			}
    			else {
    				driveTrain->ResetEncoders();
    				sensors->ResetGyro();
    				autoState = FaceSwitch;
    			}
    			break;

    		case (FaceSwitch):
    			if (gyroAngle < lTurn2) {
    				driveTrain->TankDrive(autoTurnSpeed, -autoTurnSpeed, 0.0);
    			} else {
    				driveTrain->ResetEncoders();
    				autoState = DriveSideSwitch;
    			}
			break;

    		case (DriveSideSwitch):
    			if (rightEncDist > -lDrive3){
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    			}
    			else {
    				autoState = DeployCube;
    			}
    			break;

    		case (DeployCube):
    			intake->spitCube();
    			break;
    	}
}

void Autonomous::ResetZeroed(){
	elevatorZeroed = false;
}

void Autonomous::DefaultCross(){

};
