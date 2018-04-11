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
	printf("Running auto \n");
	autonPeriodicValues();
	if (target == 5) {
		if (startingPosition != CenterPosition){
			printf("Defaulting by choice \n");
			defaultCross();
		}
	} else if(target == Scale){
		if(startingPosition == ourScale){
			printf("Scale from same side");
			scaleFromSide();
		} else if (secondChoice == Scale){
			printf("Scale through alley");
			scaleFromOpposite();
		} else if (secondChoice == Switch){
			target = Switch;
			if(startingPosition ==  Switch){
				printf("Switch from side \n");
				switchFromSide();
			} else if (startingPosition != CenterPosition){
				printf("Defaulting by default \n");
				defaultCross();
			}
		}
	} else if(target == Switch){
		if(startingPosition == CenterPosition){
			if(ourSwitch == RightSide){
				printf("Switch right from center\n");
				newSwitchRightAuto();
			} else {
				printf("Switch left from center\n");
				newSwitchLeftAuto();
			}
		} else if(ourSwitch == startingPosition){
			printf("Switch from side\n");
			switchFromSide();
		} else {
			target = Scale;
			if (ourScale == startingPosition){
				printf("Scale from side\n");
				scaleFromSide();
			} else if(secondChoice == Scale){
				printf("Scale from opposite\n");
				scaleFromOpposite();
			} else if (startingPosition != CenterPosition){
				printf("Defaulting by default\n");
				defaultCross();
			}
		}
	} else {
		printf("Defaulting by default\n");
		defaultCross();
	}

}

void Autonomous::runAuto(){
	autonPeriodicValues();
	if(target == 5){
		defaultCross();
		printf("DefaultingByChoice\n");
	}else if(target == Scale && startingPosition == ourScale){
			scaleFromSide();
			printf("Scale\n");
	} else if(target == Switch && startingPosition == CenterPosition){
		if(ourSwitch == RightSide){
			switchRightAuto();
			printf("Switch right from center\n");
		} else{
			switchLeftAuto();
			printf("Switch left from center\n");
		}
	} else if (target == Switch && startingPosition == ourSwitch){
		switchFromSide();
		printf("Switch from side\n");
	} else if (startingPosition == ourScale) {
		target = Scale;
		scaleFromSide();
		printf("Other scale\n");
	} else if (startingPosition == ourSwitch) {
		target = Switch;
		switchFromSide();
		printf("Other switch\n");
	} else{
		defaultCross();
		printf("DefaultingBackUp\n");
	}
}

void Autonomous::setAutoState(int pAutoState){
	autoState = pAutoState;
}

void Autonomous::autonPostValues(){
	SmartDashboard::PutNumber("Auton/autoDriveSpeed", autoDriveSpeed);
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

	SmartDashboard::PutNumber("Auton/turnRightAngle", turnRightAngle);
	SmartDashboard::PutNumber("Auton/turnLeftAngle", turnLeftAngle);
	SmartDashboard::PutNumber("Auton/Opp/platformToDist", platformToDist);
	SmartDashboard::PutNumber("Auton/Opp/platformToOTherAlley", platformToOtherAlley);
	SmartDashboard::PutNumber("Auton/Opp/scaleAdjustOppLeft", scaleAdjustOppLeft);
	SmartDashboard::PutNumber("Auton/Opp/scaleAdjustOppRight", scaleAdjustOppRight);
	SmartDashboard::PutNumber("Auton/Opp/scaleBackOff", scaleBackOff);



#endif


}

void Autonomous::autonPeriodicValues(){
#ifdef DEBUGGING
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

	autoDriveSpeed = SmartDashboard::GetNumber("Auton/autoDriveSpeed", autoDriveSpeed);
	autoTurnSpeed = SmartDashboard::GetNumber("Auton/autoTurnSpeed", autoTurnSpeed);

	scaleHeight = SmartDashboard::GetNumber("Auton/scaleHeight", scaleHeight);
	switchHeight = SmartDashboard::GetNumber("Auton/scaleHeight", switchHeight);

	turnRightAngle = SmartDashboard::GetNumber("Auton/turnRightAngle", turnRightAngle);
	turnLeftAngle = SmartDashboard::GetNumber("Auton/turnLeftAngle", turnLeftAngle);
	platformToDist = SmartDashboard::GetNumber("Auton/Opp/platformToDist", platformToDist);
	platformToOtherAlley = SmartDashboard::GetNumber("Auton/Opp/platformToOTherAlley", platformToOtherAlley);
	scaleAdjustOppLeft = SmartDashboard::GetNumber("Auton/Opp/scaleAdjustOppLeft", scaleAdjustOppLeft);
	scaleAdjustOppRight = SmartDashboard::GetNumber("Auton/Opp/scaleAdjustOppRight", scaleAdjustOppRight);
	scaleBackOff = SmartDashboard::GetNumber("Auton/Opp/scaleBackOff", scaleBackOff);

	SmartDashboard::PutNumber("Auton/gyro", gyroAngle);
	SmartDashboard::PutBoolean("Auton/elevatorZeroed", elevatorZeroed);
#endif

	carpetConstant = SmartDashboard::GetNumber("Auton/carpetConstant", carpetConstant);
	driftConstant = SmartDashboard::GetNumber("Auton/driftConstant", driftConstant);

	SmartDashboard::PutNumber("Auton/autoState", autoState);
	ourScale = board->getOurScale();
	ourSwitch = board->getOurSwitch();
	secondChoice = board->getSecondChoice();

	gyroAngle = sensors->getGyroAngle();
	encoderDist = driveTrain->getEncoderVal(RightSide);
	SmartDashboard::PutNumber("RightEncoderValue", encoderDist);

}

void Autonomous::switchFromSide(){
elevatorAutoRun();
	if(ourSwitch == startingPosition){
		printf("State: %d\n", autoState);
		switch (autoState) {
			case(InitialStart):
					if(encoderDist > -(switchSideDist + carpetConstant)){
						driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed - (sensors->getGyroAngle() / driftConstant), 0.0);
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
					printf("Count:%d\n",dropCounter);
				if (ourSwitch == LeftSide && encoderDist > -driveToSwitchDist && dropCounter < 50){
						driveTrain->tankDrive(autoTurnSpeed, autoTurnSpeed, 0.0);
						dropCounter++;
				} else if (ourSwitch == RightSide && encoderDist > -driveToSwitchRight && dropCounter < 50){
					driveTrain->tankDrive(autoTurnSpeed, autoTurnSpeed, 0.0);
					dropCounter++;
				} else {
					driveTrain->tankDrive(0.0, 0.0, 0.0);
					autoState = DeployCube;
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
		elevatorAutoRun();
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
    			if (encoderDist > -rDrive3 && dropCounter < 100){
    				driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    				dropCounter++;
    				printf("Count:%d\n",dropCounter);
    			}
    			else{
    	    			driveTrain->tankDrive(0.0, 0.0, 0.0);
    	    			autoState = DeployCube;
    			}
    			break;

    		case (DeployCube):
				driveTrain->tankDrive(0.0, 0.0, 0.0);
    			driveTrain->resetEncoders();
    			if(intake->spitCube()){
    				autoState = BackOffSwitch;
    			}
    			break;
    	}
}

void Autonomous::switchLeftAuto(){
		elevatorAutoRun();

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
    			if (encoderDist > -lDrive3 && dropCounter < 100){
    				driveTrain->tankDrive(autoTurnSpeed, autoTurnSpeed, 0.0);
    				dropCounter++;
    				printf("Count:%d\n",dropCounter);
    			}
    			else{
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
//elevatorAutoRun();
intake->wristForward();
	switch (autoState) {
		case(InitialStart):
			if(encoderDist > -(scaleSideDist + carpetConstant)){
				driveTrain->autonTankDrive(autoDriveSpeed , autoDriveSpeed);
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
			} else if (waitCount++ < 30){
				driveTrain->tankDrive(-0.0, -0.0, 0.0);
			} else {
				autoState = ScaleAdjust;
				driveTrain->tankDrive(-0.0, -0.0, 0.0);
				driveTrain->resetEncoders();
			}
			break;
		case(RaiseElevator):
			if (!heightReached){
				elevatorAutoRun();
				driveTrain->resetEncoders();
			} else {
				autoState = ScaleAdjust;
			}
			break;
		case(ScaleAdjust):
			printf("Adjusting towards scale \n");
			dropCounter++;
			if(ourScale == LeftSide && encoderDist > -scaleAdjustDist){
				driveTrain->tankDrive(-0.6, -0.6, 0.0);
			} else if (ourScale == RightSide && encoderDist > -scaleAdjustRight){
				driveTrain->tankDrive(-0.6, -0.6, 0.0);
			}
			else {
				driveTrain->tankDrive(-0.0, -0.0, 0.0);
				autoState = DeployCube;
			}
			break;
		case(DeployCube):
			driveTrain->resetEncoders();
			if(intake->spitCube()){
				autoState = BackOff;
			}
			break;
		case(BackOff):
			printf("Backing off \n");
			if(encoderDist < scaleBackOff){
				driveTrain->tankDrive(-autoTurnSpeed, -autoTurnSpeed, 0.0);
			} else {
				driveTrain->haltMotion();
			}
	}
}

void Autonomous::switchFromOpposite(){
	elevatorAutoRun();
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
			if (ourSwitch == LeftSide && gyroAngle > -turnLeftAngle){
				driveTrain->tankDrive(-autoDriveSpeed, autoDriveSpeed, 0.0);
			} else if (ourSwitch == RightSide && gyroAngle < turnRightAngle){
				driveTrain->tankDrive(autoDriveSpeed, -autoDriveSpeed, 0.0);
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
				autoState = FaceAlley;
			}
			break;
		case(FaceAlley):
				if (ourSwitch == RightSide && gyroAngle < turnRightAngle){
					driveTrain->tankDrive(autoDriveSpeed, -autoDriveSpeed, 0.0);
				} else if (ourScale == LeftSide && gyroAngle > -turnLeftAngle){
					driveTrain->tankDrive(-autoDriveSpeed, autoDriveSpeed, 0.0);
				} else {
					driveTrain->haltMotion();
					autoState = DriveDownAlley;
				}
				break;
		case(DriveDownAlley):
				if (ourScale == RightSide && encoderDist > -scaleAdjustOppRight){
					driveTrain->tankDrive(autoTurnSpeed, autoTurnSpeed, 0.0);
				} else if (ourScale == LeftSide && encoderDist && encoderDist > -scaleAdjustOppLeft){
					driveTrain->tankDrive(autoTurnSpeed, autoTurnSpeed, 0.0);
				} else {
					driveTrain->haltMotion();
					autoState = DeployCube;
				}
			break;
		case(FaceSwitch):
				if (ourSwitch == RightSide && gyroAngle < turnRightAngle){
					driveTrain->tankDrive(autoDriveSpeed, -autoDriveSpeed, 0.0);
				} else if (ourScale == LeftSide && gyroAngle > -turnLeftAngle){
					driveTrain->tankDrive(-autoDriveSpeed, autoDriveSpeed, 0.0);
				} else {
					driveTrain->haltMotion();
					autoState = DriveThruPlatformZone;
				}
				break;
		case(DriveSideSwitch):
				printf("Count:%d\n",dropCounter);
				if (ourSwitch == LeftSide && encoderDist > -leftSwitchAdjust && dropCounter < 80){
						driveTrain->tankDrive(autoTurnSpeed, autoTurnSpeed, 0.0);
						dropCounter++;
					}
				else if (ourSwitch == RightSide && encoderDist > -rightSwitchAdjust && dropCounter < 80){
					driveTrain->tankDrive(autoTurnSpeed, autoTurnSpeed, 0.0);
					dropCounter++;
				}
				else{
						driveTrain->tankDrive(0.0, 0.0, 0.0);
						autoState = DeployCube;
				}
				break;
			case(DeployCube):
					driveTrain->tankDrive(0.0, 0.0, 0.0);
					intake->spitCube();
				break;
	}
}

void Autonomous::scaleFromOpposite(){
	switch (autoState){
		case(InitialStart):
			if (encoderDist > -platformToDist){
				driveTrain->autonTankDrive(autoDriveSpeed, autoDriveSpeed);
			} else {
				driveTrain->haltMotion();
				autoState = TurnDownPlatformZone;
			}
			break;
		case(TurnDownPlatformZone):
				driveTrain->resetEncoders();
			if (ourScale == LeftSide && gyroAngle > -turnLeftAngle){
				driveTrain->tankDrive(-autoDriveSpeed, autoDriveSpeed, 0.0);
			} else if (ourScale == RightSide && gyroAngle < turnRightAngle){
				driveTrain->tankDrive(autoDriveSpeed, -autoDriveSpeed, 0.0);
			} else {
				driveTrain->haltMotion();
				//autoState = DriveThruPlatformZone;
			}
			break;
		case(DriveThruPlatformZone):
			if (encoderDist > -platformToOtherAlley){
				driveTrain->autonTankDrive(autoDriveSpeed, autoDriveSpeed);
			} else {
				driveTrain->haltMotion();
				autoState = TurnDownPlatformZone;
			}
			break;
		case(FaceScale):
				if (ourScale == RightSide && gyroAngle > -turnLeftAngle){
					driveTrain->tankDrive(-autoDriveSpeed, autoDriveSpeed, 0.0);
				} else if (ourScale == LeftSide && gyroAngle < turnRightAngle){
					driveTrain->tankDrive(autoDriveSpeed, -autoDriveSpeed, 0.0);
				} else {
					driveTrain->haltMotion();
					autoState = DriveThruPlatformZone;
				}
				break;
		case(RaiseElevator):
				if (!heightReached){
					elevatorAutoRun();
					driveTrain->resetEncoders();
				} else {
					autoState = ScaleAdjust;
				}
				break;
		case(ScaleAdjust):
				dropCounter++;
				if (dropCounter < 150 && ourScale == RightSide && encoderDist > -scaleAdjustOppRight){
					driveTrain->tankDrive(autoTurnSpeed, autoTurnSpeed, 0.0);
				} else if (dropCounter < 150 && ourScale == LeftSide && encoderDist && encoderDist > -scaleAdjustOppLeft){
					driveTrain->tankDrive(autoTurnSpeed, autoTurnSpeed, 0.0);
				} else {
					driveTrain->haltMotion();
					autoState = DeployCube;
				}
			break;
		case(DeployCube):
				driveTrain->resetEncoders();
				if(intake->spitCube()){
					autoState = BackOff;
				}
			break;
		case(BackOff):
				if(encoderDist < scaleBackOff){
					driveTrain->tankDrive(-autoTurnSpeed, -autoTurnSpeed, 0.0);
				} else {
					driveTrain->haltMotion();
				}
	}

}

void Autonomous::elevatorAutoRun(){
if(!heightReached && elevator->encoderValue() < targetHeight()) {
		elevatorZeroed = true;
		elevator->goUp();
		printf("Going up!\n");
	} else {
		elevator->haltMotion();
		heightReached = true;
		printf("Height reached!\n");
	}
}

bool Autonomous::elevatorRunDirection(bool direction){
	if(direction && !heightReached && elevator->encoderValue() < targetHeight()){
		elevator->goUp();
	} else if (!direction && !heightReached && !sensors->getElevatorBottom()){
		elevator->goDown();
	} else {
		heightReached = true;
		elevator->haltMotion();
	}
	return false;
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
	dropCounter = 0;
	wristCount = 0;
	waitCount = 0;
}

void Autonomous::shuffleCheck(){
	if(postCount > 200){
	printf("Target: %d\n", target);
	printf("Starting Position: %d\n", startingPosition);
	printf("ourScale: %d\n", ourScale);
	printf("Second Choice: %d\n", secondChoice);
	postCount = 0;
	} else {
		postCount++;
	}
}

void Autonomous::updateStarts(){
	target = board->getTarget();
	startingPosition = board->getStartingPosition();
}

void Autonomous::driveStraight(){

}

void Autonomous::turnRight(){

}

void Autonomous::turnLeft(){

}

void Autonomous::defaultCross(){
	printf("Defaulting\n");
	switch (autoState){
			case(InitialStart):
				if(encoderDist > -drivePastDist){
					driveTrain->autonTankDrive(autoDriveSpeed, autoDriveSpeed);
				} else {
					driveTrain->tankDrive(0.0,0.0,0.0);
				}
				break;
	}
};

void Autonomous::newSwitchRightAuto(){
	switch (autoState) {
    		case (InitialStart):
    			elevatorAutoRun();
    			if (encoderDist > -(initDist + carpetConstant)) {
    				driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    			} else {
    				sensors->resetGyro();
    				autoState = TurnDownMiddle;
    			}
    			break;

    		case (TurnDownMiddle):
    			elevatorAutoRun();
    			if (gyroAngle < rTurn1) {
    				driveTrain->tankDrive(autoTurnSpeed, -autoTurnSpeed, 0.0);
    			} else {
    				driveTrain->resetEncoders();
    				autoState = DriveDiagonal;
    			}
    			break;

    		case (DriveDiagonal):
    			elevatorAutoRun();
    			if (encoderDist > -rDrive2) {
    				driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    			} else {
    				sensors->resetGyro();
    				driveTrain->resetEncoders();
    				autoState = FaceSwitch;
    			}
			break;

    		case (FaceSwitch):
				elevatorAutoRun();
    			if (gyroAngle > rTurn2) {
    				driveTrain->tankDrive(-autoTurnSpeed, autoTurnSpeed, 0.0);
    				driveTrain->resetEncoders();
    			} else {
    				driveTrain->resetEncoders();
    				autoState = DriveSideSwitch;
    			}
			break;

    		case (DriveSideSwitch):
				elevatorAutoRun();
    			if (encoderDist > -rDrive3 && dropCounter < 100){
    				driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    				dropCounter++;
    				printf("Count:%d\n",dropCounter);
    			}
    			else{
    	    			driveTrain->tankDrive(0.0, 0.0, 0.0);
    	    			autoState = DeployCube;
    			}
    			break;

    		case (DeployCube):
				driveTrain->tankDrive(0.0, 0.0, 0.0);
    			driveTrain->resetEncoders();
    			sensors->resetGyro();
    			if(intake->spitCube()){
    				autoState = BackOffSwitch;
    			}
    			break;
    		case (BackOffSwitch):
    			if(encoderDist < backOffSwitch){
    				driveTrain->tankDrive(-autoDriveSpeed, -autoDriveSpeed, 0.0);
    				counter = 0;
    			} else if (counter++ < 50){
    				driveTrain->haltMotion();
    			} else {
    				autoState = FaceCube;
    			}
    			break;
    		case (FaceCube):
				elevator->goDown();
    			intake->extendIntake();
    			if(gyroAngle > -turnToCubeRight){
    				driveTrain->tankDrive(-autoTurnSpeed, autoTurnSpeed, 0.0);
    				counter = 0;
    			} else if (counter++ < 30){
    				driveTrain->resetEncoders();
    				driveTrain->haltMotion();
    			} else {
    				autoState = PickUpCube;
    				driveTrain->resetEncoders();
    				counter = 0;
    			}
				break;
    		case (PickUpCube):
				if(intake->intakeWithRaise() && counter++ < 150){
					driveTrain->tankDrive(autoTurnSpeed, autoTurnSpeed, 0.0);
				} else if (counter++ > 6){
					autoState = BackOffWithCube;
				}
				break;
    		case (BackOffWithCube):
    			heightReached = false;
    			intake->intakeWithRaise();
				if(encoderDist < 0 - 2000){
					driveTrain->tankDrive(-autoTurnSpeed, -autoTurnSpeed, 0.0);
					counter = 0;
				} else if (counter++ > 6){
					autoState = FaceSwitchWithCube;
				}
    			break;
    		case (FaceSwitchWithCube):
				if(gyroAngle < turnSwitchRight){
					driveTrain->tankDrive(autoTurnSpeed, -autoTurnSpeed, 0.0);
					counter = 0;
				} else if (!heightReached){
	    			elevatorAutoRun();
					intake->retractIntake();
					driveTrain->haltMotion();
				} else {
					autoState = SwitchAdjust;
				}
				break;
    		case (SwitchAdjust):
				if(encoderDist > -switchAdjustRight){
					driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
					counter = 0;
				} else if (counter++ < 6){
					driveTrain->haltMotion();
					intake->resetSpitCount();
				} else {
					autoState = DeploySecondCube;
				}
    			break;
    		case (DeploySecondCube):
    			if(intake->spitCube()){
    				driveTrain->haltMotion();
    			}
			break;
    	}

}

void Autonomous::newSwitchLeftAuto(){
	switch(autoState){
		case (InitialStart):
			elevatorAutoRun();
			if (encoderDist > -(initDist + carpetConstant)) {
				driveTrain->tankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
			} else {
				sensors->resetGyro();
				autoState = TurnDownMiddle;
			}
		break;

		case (TurnDownMiddle):
			elevatorAutoRun();
			if (gyroAngle > lTurn1) {
				driveTrain->tankDrive(-autoTurnSpeed, autoTurnSpeed, 0.0);
			} else {
				driveTrain->resetEncoders();
				autoState = DriveDiagonal;
			}
		break;

		case (DriveDiagonal):
			elevatorAutoRun();
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
			elevatorAutoRun();
			if (gyroAngle < lTurn2) {
				driveTrain->tankDrive(autoTurnSpeed, -autoTurnSpeed, 0.0);
			} else {
				driveTrain->resetEncoders();
				autoState = DriveSideSwitch;
			}
		break;

		case (DriveSideSwitch):
			if (encoderDist > -lDrive3 && dropCounter < 100){
				driveTrain->tankDrive(-0.7, -0.7, 0.0);
				dropCounter++;
				printf("Count:%d\n",dropCounter);
			}
			else{
					driveTrain->tankDrive(0.0, 0.0, 0.0);
					autoState = DeployCube;
			}
		break;

		case (DeployCube):
			driveTrain->tankDrive(0.0, 0.0, 0.0);
			driveTrain->resetEncoders();
			sensors->resetGyro();
			if(intake->spitCube()){
				autoState = BackOffSwitch;
			}
			break;

		case (BackOffSwitch):
			if(encoderDist < backOffSwitch){
				driveTrain->tankDrive(0.8, 0.8, 0.0);
				counter = 0;
			} else if (counter++ < 50){
				driveTrain->haltMotion();
			} else {
				autoState = FaceCube;
			}
			break;
		case (FaceCube):
			elevator->goDown();
			intake->extendIntake();
			if(gyroAngle < turnToCubeLeft){
				driveTrain->tankDrive(autoTurnSpeed, -autoTurnSpeed, 0.0);
				counter = 0;
			} else if (counter++ < 30){
				driveTrain->resetEncoders();
				driveTrain->haltMotion();
			} else {
				autoState = PickUpCube;
				driveTrain->resetEncoders();
				counter = 0;
			}
			break;
		case (PickUpCube):
			if(intake->intakeWithRaise() && counter++ < 150){
				driveTrain->tankDrive(autoTurnSpeed, autoTurnSpeed, 0.0);
			} else if (counter++ < 200){
				driveTrain->haltMotion();
				intake->intakeWithRaise();
			} else {
				autoState = BackOffWithCube;
			}
			break;
		case (BackOffWithCube):
			heightReached = false;
			intake->allOff();
			if(encoderDist < 0 - 3000){
				driveTrain->tankDrive(-autoTurnSpeed, -autoTurnSpeed, 0.0);
				counter = 0;
			} else if (counter++ > 50){
				elevatorAutoRun();
				intake->retractIntake();
				autoState = FaceSwitchWithCube;
			}
			break;
		case (FaceSwitchWithCube):
			if(gyroAngle < -turnSwitchLeft){
				driveTrain->tankDrive(-autoTurnSpeed, autoTurnSpeed, 0.0);
				counter = 0;
			} else if (counter++ < 20){
				driveTrain->haltMotion();
			} else {
				autoState = SwitchAdjust;
			}
			break;
		case (SwitchAdjust):
			if(encoderDist > -switchAdjustLeft){
				driveTrain->tankDrive(-0.7, -0.7, 0.0);
				counter = 0;
			} else if (counter++ < 6){
				driveTrain->haltMotion();
				intake->resetSpitCount();
			} else {
				autoState = DeploySecondCube;
			}
			break;
		case (DeploySecondCube):
			if(intake->spitCube()){
				driveTrain->haltMotion();
			}
		break;
	}
}
