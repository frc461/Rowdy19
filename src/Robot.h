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
	DeployBlock,
	DrivePastSwitch,
	TurnTowardsScale,
	DriveTowardsScale,
	FaceScale
};

enum PWMChain{
	LeftInIntakePWM,
	RightInIntakePWM,
	LeftOutIntakePWM,
	RightOutIntakePWM
};

enum CanChain {
	RightDrive1CAN = 0,
	RightDrive2CAN,
	RightDrive3CAN,
	LeftDrive1CAN,
	LeftDrive2CAN,
	LeftDrive3CAN,
	Strafe1CAN,
	Strafe2CAN,
	Elevator1CAN,
	Elevator2CAN,
	Elevator3CAN
};

enum DIOPorts {
	Elevator1DIO1 = 0,
	Elevator1DIO2,
	Elevator2DIO1,
	Elevator3DIO1,
	Elevator3DIO2
};

enum actuationStatus{
	Undetermined = 0,
	Out,
	In
};

enum StructureData {
	DataError = 0,
	LeftSide,
	RightSide
};

#endif /* SRC_ROBOT_H_ */
