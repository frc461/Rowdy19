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
	autonPostValues();
	autonPeriodicValues();
	target = board->getTarget();
	startingPosition = board->getStartingPosition();
}

void Autonomous::runAuto(){
	autonPeriodicValues();
	if(target == Scale){
		if(startingPosition == CenterPosition){
			scaleFromCenter();
			printf("Scale from center");
		} else {
			scaleFromSide();
			printf("Scale from side\n");
		}
	} else if(target == autoTarget::Switch){
		if(startingPosition == CenterPosition){
			if(board->getOurSwitch() == RightSide){
				switchRightAuto();
				printf("Switch right from center\n");
			} else{
				switchLeftAuto();
				printf("Switch left from center");
			}
		} else {
			switchFromSide();
			printf("Switch from side");
		}
	} else {
		defaultCross();
		printf("Defaulting");
	}
}

void Autonomous::setAutoState(int pAutoState){
	autoState = pAutoState;
}

void Autonomous::autonPostValues(){
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
	SmartDashboard::PutNumber("Auton/Scale/faceScaleRight", faceScaleRight);
	SmartDashboard::PutNumber("Auton/Scale/faceScaleLeft", faceScaleLeft);
	SmartDashboard::PutNumber("Auton/Scale/scaleAdjustDist", scaleAdjustDist);

	SmartDashboard::PutNumber("Auton/Scale/drivePastDist", drivePastDist);
	SmartDashboard::PutNumber("Auton/Scale/driveAwayDist", driveAwayDist);

}

void Autonomous::autonPeriodicValues(){
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
	faceScaleRight = SmartDashboard::GetNumber("Auton/Scale/faceScaleRight", faceScaleRight);
	faceScaleLeft = SmartDashboard::GetNumber("Auton/Scale/faceScaleLeft", faceScaleLeft);
	scaleAdjustDist = SmartDashboard::GetNumber("Auton/Scale/scaleAdjustDist", scaleAdjustDist);

	autoDriveSpeed = SmartDashboard::GetNumber("Auton/autoDriveSpeed", -0.75);
	autoTurnSpeed = SmartDashboard::GetNumber("Auton/autoTurnSpeed", -0.6);
	SmartDashboard::PutNumber("Auton/autoState", autoState);

	scaleHeight = SmartDashboard::GetNumber("Auton/scaleHeight", scaleHeight);
	switchHeight = SmartDashboard::GetNumber("Auton/scaleHeight", switchHeight);

	ourSwitch = board->getOurSwitch();
	ourScale = board->getOurScale();

	encoderDist = driveTrain->getEncoderVal(RightSide);
	gyroAngle = sensors->getGyroAngle();
	SmartDashboard::PutNumber("Auton/gyro", gyroAngle);
	SmartDashboard::PutBoolean("Auton/elevatorZeroed", elevatorZeroed);

}

void Autonomous::switchFromSide(){
//		if(!elevatorZeroed){
//			elevator->goDown();
//			if(sensors->getElevatorBottom()){
//				elevatorZeroed = true;
//			}
//		} else if (elevator->encoderValue() < switchHeight) {
//			elevator->goUp();
//		} else {
//			elevator->haltMotion();
//		}
	elevatorAutoRun();

	if(ourSwitch == startingPosition){
		switch (autoState) {
		case(InitialStart):
				if(encoderDist > -switchSideDist){
					driveTrain->arcadeDrive(autoDriveSpeed, 0.0, 0.0);
				} else {
					autoState = FaceSwitch;
					sensors->resetGyro();
				}
				break;
		case(FaceSwitch):
				if(ourSwitch == RightSide && gyroAngle < faceSwitchAngleRight){
					driveTrain->arcadeDrive(0.0, autoTurnSpeed, 0.0);
				} else if (ourSwitch == LeftSide && gyroAngle > -faceSwitchAngleLeft){
					driveTrain->arcadeDrive(0.0, -autoTurnSpeed, 0.0);
				} else {
					autoState = DriveSideSwitch;
					driveTrain->resetEncoders();
				}
			break;
		case(DriveSideSwitch):
				if(encoderDist < driveToSwitchDist){
					driveTrain->arcadeDrive(autoDriveSpeed, 0.0, 0.0);
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

void Autonomous::switchRightAuto(){
	elevatorAutoRun();

    	switch (autoState) {
    		case (InitialStart):
    			if (encoderDist > -initDist) {
    				driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    			} else {
    				sensors->resetGyro();
    				autoState = TurnDownMiddle;
    			}
    			break;

    		case (TurnDownMiddle):
    			if (gyroAngle < rTurn1) {
    				driveTrain->tankDrive(autoTurnSpeed, -autoTurnSpeed, 0.0);
    			} else {
    				driveTrain->resetEncoders();
    				autoState = DriveDiagonal;
    			}
    			break;

    		case (DriveDiagonal):
    			if (encoderDist > -rDrive2) {
    				driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    			} else {
    				sensors->resetGyro();
    				driveTrain->resetEncoders();
    				autoState = FaceSwitch;
    			}
			break;

    		case (FaceSwitch):
    			if (gyroAngle > rTurn2) {
    				driveTrain->tankDrive(-autoTurnSpeed, autoTurnSpeed, 0.0);
    				driveTrain->resetEncoders();
    			} else {
    				driveTrain->resetEncoders();
    				autoState = DriveSideSwitch;
    			}
			break;

    		case (DriveSideSwitch):
    			if (encoderDist > -rDrive3) {
    				driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    			} else {
    				driveTrain->tankDrive(0.0, 0.0, 0.0);
    				autoState = DeployCube;
    			}
			break;

    		case (DeployCube):
    				intake->spitCube();
    			break;
    	}
	
}

void Autonomous::switchLeftAuto(){
	elevatorAutoRun();

    	switch (autoState) {
    		case (InitialStart):
    			if (encoderDist > -initDist) {
    				driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    			} else {
    				sensors->resetGyro();
    				autoState = TurnDownMiddle;
    			}
			break;

    		case (TurnDownMiddle):
    			if (gyroAngle > lTurn1) {
    				driveTrain->tankDrive(-autoTurnSpeed, autoTurnSpeed, 0.0);
    			} else {
    				driveTrain->resetEncoders();
    				autoState = DriveDiagonal;
    			}
			break;

    		case (DriveDiagonal):
    			if (encoderDist > -lDrive2) {
    				driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    			}
    			else {
    				driveTrain->resetEncoders();
    				sensors->resetGyro();
    				autoState = FaceSwitch;
    			}
    			break;

    		case (FaceSwitch):
    			if (gyroAngle < lTurn2) {
    				driveTrain->tankDrive(autoTurnSpeed, -autoTurnSpeed, 0.0);
    			} else {
    				driveTrain->resetEncoders();
    				autoState = DriveSideSwitch;
    			}
			break;

    		case (DriveSideSwitch):
    			if (encoderDist > -lDrive3){
    				driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
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

void Autonomous::scaleFromCenter(){

}

void Autonomous::scaleFromSide(){
	elevatorAutoRun();

	switch (autoState) {
		case(InitialStart):
			if(encoderDist > -scaleSideDist){
				driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed /** (1.015 + (gyroAngle / 45))*/, 0.0);
			} else {
				autoState = TurnTowardsScale;
				sensors->resetGyro();
			}
			break;
		case(TurnTowardsScale):
			if(ourScale == LeftSide && gyroAngle < faceScaleLeft){
				driveTrain->tankDrive(autoTurnSpeed, -autoTurnSpeed, 0.0);
				driveTrain->resetEncoders();
			} else if (ourScale == RightSide && gyroAngle > faceScaleRight){
				driveTrain->tankDrive(-autoTurnSpeed, autoTurnSpeed, 0.0);
				driveTrain->resetEncoders();
			} else {
				autoState = DriveTowardsScale;
				driveTrain->resetEncoders();
			}
			break;
		case(DriveTowardsScale):
				if(encoderDist > -scaleAdjustDist){
					driveTrain->tankDrive(-0.6, -0.6, 0.0);
				} else {
					driveTrain->tankDrive(-0.0, -0.0, 0.0);
					autoState = DeployCube;
					sensors->resetGyro();
				}
			break;
		case(DeployCube):
			intake->spitCube();
			break;
	}
}

void Autonomous::elevatorAutoRun(){
	if(!elevatorZeroed){
		printf("Going down!\n");
		elevator->goDown();
		if(sensors->getElevatorBottom()){
			elevatorZeroed = true;
		}
	} else if (!heightReached && elevator->encoderValue() < targetHeight()) {
		elevator->goUp();
		printf("Going up!\n");
	} else {
		elevator->haltMotion();
		heightReached = true;
		printf("Height reached!\n");
	}
}

int Autonomous::targetHeight(){
	if (target == Switch){
		return switchHeight;
	} else if (target == Scale){
		return scaleHeight;
	}
	return 0;
}

void Autonomous::resetZeroed(){
	elevatorZeroed = false;
	heightReached = false;
}

void Autonomous::updateStarts(){
	target = board->getTarget();
	startingPosition = board->getStartingPosition();
}

void Autonomous::defaultCross(){

};
