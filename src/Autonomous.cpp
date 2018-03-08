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
	secondChoice = board->getSecondChoice();

}

void Autonomous::smartRun(){
	autonPeriodicValues();
	if(target == Scale){
		if(startingPosition == ourScale){
			scaleFromSide();
		} else if (startingPosition == ourSwitch){
			switchFromSide();
		} else {
			defaultCross();
		}
	} else if(target == Switch){
		if(startingPosition == CenterPosition){
			if(board->getOurSwitch() == RightSide){
				switchRightAuto();
			} else{
				switchLeftAuto();
			}
		} else if(ourSwitch == startingPosition){
			switchFromSide();
		} else {
			if (ourScale == startingPosition){
				scaleFromSide();
			} else if(secondChoice == Switch){
				switchFromBack();
			}
		}
	}
}

void Autonomous::runAuto(){
	autonPeriodicValues();
	if(target == Scale && startingPosition == ourScale){
			scaleFromSide();
	} else if(target == Switch && startingPosition == CenterPosition){
		if(ourSwitch == RightSide){
			switchRightAuto();
			printf("Switch right from center\n");
		} else{
			switchLeftAuto();
			printf("Switch left from center");
		}
	} else if (startingPosition == ourSwitch && startingPosition == ourSwitch){
		switchFromSide();
		printf("Switch from side");
	} else {
		defaultCross();
		printf("Defaulting");
	}
}

void Autonomous::setAutoState(int pAutoState){
	autoState = pAutoState;
}

void Autonomous::autonPostValues(){
	SmartDashboard::PutNumber("Auton/autoDriveSpeed", -0.8);
	SmartDashboard::PutNumber("Auton/carpetConstant", carpetConstant);
	SmartDashboard::PutNumber("Auton/driftConstant", driftConstant);

#ifdef DEBUGGING
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

	SmartDashboard::PutNumber("Auton/Switch/switchSideDist", switchSideDist);
	SmartDashboard::PutNumber("Auton/Switch/faceSwitchAngleRight", faceSwitchAngleRight);
	SmartDashboard::PutNumber("Auton/Switch/faceSwitchAngleLeft", faceSwitchAngleLeft);
	SmartDashboard::PutNumber("Auton/Switch/driveToSwitchDist", driveToSwitchDist);

	SmartDashboard::PutNumber("Auton/Scale/scaleSideDist", scaleSideDist);
	SmartDashboard::PutNumber("Auton/Scale/faceScaleRight", faceScaleRight);
	SmartDashboard::PutNumber("Auton/Scale/faceScaleLeft", faceScaleLeft);
	SmartDashboard::PutNumber("Auton/Scale/scaleAdjustDist", scaleAdjustDist);

	SmartDashboard::PutNumber("Auton/Scale/drivePastDist", drivePastDist);
	SmartDashboard::PutNumber("Auton/Scale/driveAwayDist", driveAwayDist);
#endif
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

	switchSideDist = SmartDashboard::GetNumber("Auton/Switch/switchSideDist", switchSideDist);
	faceSwitchAngleRight = SmartDashboard::GetNumber("Auton/Switch/faceSwitchAngleRight", faceSwitchAngleRight);
	faceSwitchAngleLeft = SmartDashboard::GetNumber("Auton/Switch/faceSwitchAngleLeft", faceSwitchAngleLeft);
	driveToSwitchDist = SmartDashboard::GetNumber("Auton/Switch/driveToSwitchDist", driveToSwitchDist);

	scaleSideDist = SmartDashboard::GetNumber("Auton/Scale/scaleSideDist", scaleSideDist);
	faceScaleRight = SmartDashboard::GetNumber("Auton/Scale/faceScaleRight", faceScaleRight);
	faceScaleLeft = SmartDashboard::GetNumber("Auton/Scale/faceScaleLeft", faceScaleLeft);
	scaleAdjustDist = SmartDashboard::GetNumber("Auton/Scale/scaleAdjustDist", scaleAdjustDist);

	autoDriveSpeed = SmartDashboard::GetNumber("Auton/autoDriveSpeed", -0.8);
	autoTurnSpeed = SmartDashboard::GetNumber("Auton/autoTurnSpeed", -0.6);
	SmartDashboard::PutNumber("Auton/autoState", autoState);

	scaleHeight = SmartDashboard::GetNumber("Auton/scaleHeight", scaleHeight);
	switchHeight = SmartDashboard::GetNumber("Auton/scaleHeight", switchHeight);

	carpetConstant = SmartDashboard::GetNumber("Auton/carpetConstant", carpetConstant);

	ourSwitch = board->getOurSwitch();
	ourScale = board->getOurScale();

	driftConstant = SmartDashboard::GetNumber("Auton/driftConstant", driftConstant);
	encoderDist = driveTrain->getEncoderVal(LeftSide);
	gyroAngle = sensors->getGyroAngle();
	SmartDashboard::PutNumber("Auton/gyro", gyroAngle);
	SmartDashboard::PutBoolean("Auton/elevatorZeroed", elevatorZeroed);

}

void Autonomous::switchFromSide(){
	if(ourSwitch == startingPosition){
		switch (autoState) {
		case(InitialStart):
				if(encoderDist > -(switchSideDist + carpetConstant)){
					driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
				} else {
					driveTrain->tankDrive(0.0,0.0,0.0);
					autoState = FaceSwitch;
					sensors->resetGyro();
				}
				break;
		case(FaceSwitch):
				driveTrain->resetEncoders();
				if(ourSwitch == RightSide && gyroAngle > faceSwitchAngleRight){
					driveTrain->tankDrive(-autoTurnSpeed, autoTurnSpeed, 0.0);
				} else if (ourSwitch == LeftSide && gyroAngle < faceSwitchAngleLeft){
					driveTrain->tankDrive(autoTurnSpeed, -autoTurnSpeed, 0.0);
				} else {
					autoState = DriveSideSwitch;
				}
			break;
		case(DriveSideSwitch):
				if(encoderDist > -driveToSwitchDist){
					driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
				} else {
					autoState = DeployCube;
					driveTrain->tankDrive(0.0, 0.0, 0.0);

				}
			break;
		case(DeployCube):
    	    	    		driveTrain->tankDrive(0.0, 0.0, 0.0);
				intake->spitCube();

			break;
		}
	}
}

void Autonomous::switchRightAuto(){

    	switch (autoState) {
    		case (InitialStart):
    			if (encoderDist > -(initDist + carpetConstant)) {
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
				driveTrain->tankDrive(0.0, 0.0, 0.0);
    				intake->spitCube();
    			break;
    	}
	
}

void Autonomous::switchLeftAuto(){

    	switch (autoState) {
    		case (InitialStart):
    			if (encoderDist > -(initDist + carpetConstant)) {
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
    	    			driveTrain->tankDrive(0.0, 0.0, 0.0);
    				autoState = DeployCube;
    			}
    			break;

    		case (DeployCube):
    	    		driveTrain->tankDrive(0.0, 0.0, 0.0);
    			intake->spitCube();
    			break;
    	}
}

void Autonomous::scaleFromCenter(){

}

void Autonomous::scaleFromSide(){
	switch (autoState) {
		case(InitialStart):
			if(encoderDist > -(scaleSideDist + carpetConstant)){
				driveTrain->tankDrive(autoDriveSpeed , autoDriveSpeed - (sensors->getGyroAngle() / driftConstant), 0.0);
			} else {
				autoState = TurnTowardsScale;
				sensors->resetGyro();
			}
			break;
		case(TurnTowardsScale):
			if(ourScale == LeftSide && gyroAngle < faceScaleLeft){
				driveTrain->tankDrive(autoTurnSpeed, -autoTurnSpeed, 0.0);
				driveTrain->resetEncoders();
			} else if (ourScale == RightSide && gyroAngle > -faceScaleRight){
				driveTrain->tankDrive(-autoTurnSpeed, autoTurnSpeed, 0.0);
				driveTrain->resetEncoders();
			} else {
				autoState = RaiseElevator;
				driveTrain->resetEncoders();
			}
			break;
		case(RaiseElevator):
			if (!heightReached && elevator->encoderValue() < targetHeight()) {
				elevator->goUp();
				printf("Going up!\n");
			} else {
				elevator->haltMotion();
				heightReached = true;
				autoState = DriveTowardsScale;
				printf("Height reached!\n");
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

void Autonomous::switchFromBack(){
	printf("Switch from back\n");
}

void Autonomous::scaleFromOpposite(){
	printf("Scale from back\n");
	switch (autoState){
		case(InitialStart):
			if (encoderDist > -platformToDist){
				driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
			} else {
				driveTrain->haltMotion();
				autoState = TurnDownPlatformZone;
			}
			break;
		case(TurnDownPlatformZone):
			if (ourScale == RightSide && gyroAngle < platformTurnToRight){
				driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
			} else if (ourScale == LeftSide && gyroAngle > -platformTurnToLeft){
				driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
			} else {
				driveTrain->haltMotion();
				autoState = DriveThruPlatformZone;
			}
			break;
		case(DriveThruPlatformZone):
			if (encoderDist > -platformToDist){
				driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
			} else {
				driveTrain->haltMotion();
				autoState = TurnDownPlatformZone;
			}
			break;
		case(FaceScale):
				if (ourScale == RightSide && gyroAngle < platformTurnToRight){
					driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
				} else if (ourScale == LeftSide && gyroAngle > -platformTurnToLeft){
					driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
				} else {
					driveTrain->haltMotion();
					autoState = DriveThruPlatformZone;
				}
				break;



	}

}

void Autonomous::elevatorAutoRun(){
	if (!heightReached && elevator->encoderValue() < targetHeight()) {
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
	switch (autoState){
			case(InitialStart):
				if(encoderDist > -drivePastDist){
					driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
				} else {
					driveTrain->tankDrive(0.0,0.0,0.0);
				}
				break;
	}
};
