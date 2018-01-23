/*
 * Robot.h
 *
 *  Created on: Jan 20, 2018
 *      Author: hank
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

enum AutonomousStates {
	InitialStart = 0,
	TurnDownMiddle,
	DriveDiagonal,
	FaceSwitch,
	DriveSideSwitch,
	DeployBlock
};

enum CanChain {
	Strafe1CAN = 0,
	Strafe2CAN,
	RightDrive1CAN,
	LeftDrive1CAN,
	LeftDrive2CAN,
	LeftDrive3CAN,
	RightDrive2CAN,
	RightDrive3CAN,
	LeftOutIntakeCAN,
	RightOutIntakeCAN,
	LeftInIntakeCAN,
	RightInIntakeCAN,
	Elevator1CAN,
	Elevator2CAN,
	Elevator3CAN
};

enum DIOPorts {
	LeftEncoderDIO1 = 0,
	LeftEncoderDIO2,
	RightEncoderDIO1,
	RightEncoderDIO2
};

enum StructureData {
	DataError = 0,
	LeftSide,
	RightSide
};

int initialDist, lTurn1, lTurn2, lDrive3, lDrive2, rTurn1, rTurn2, rDrive3, rDrive2;
double autoDriveSpeed, autoTurnSpeed;
#endif /* SRC_ROBOT_H_ */
