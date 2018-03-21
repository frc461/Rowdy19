/*
 * Robot.h
 *
 *  Created on: Jan 20, 2018
 *      Author: Hank Krutulis - 461
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

enum AutonomousStates {
	InitialStart = 0,
	TurnDownMiddle,
	DriveDiagonal,
	FaceSwitch,
	DriveSideSwitch,
	RaiseElevator,
	DeployCube,
	DrivePastSwitch,
	TurnTowardsScale,
	DriveTowardsScale,
	FaceScale,
	TurnToBlock,
	DriveAtBlock,
	TurnDownPlatformZone,
	DriveThruPlatformZone,
	BackOffScale,
	ScaleAdjust,
	BackOff,
	FaceAlley,
	DriveDownAlley,

};

enum PWM{
	LeftInIntakePWM = 0,
	RightInIntakePWM,
	LeftOutIntakePWM,
	RightOutIntakePWM,

};

enum CanChain {
	RightDrive1CAN = 0,
	RightDrive2CAN,
	RightDrive3CAN,
	LeftDrive1CAN ,
	LeftDrive2CAN,
	LeftDrive3CAN,
	Strafe1CAN,
	Strafe2CAN,
	Elevator1CAN,
	Elevator2CAN,
	Elevator3CAN
};

enum PCM{
	Intake1 = 0,
	Intake2 = 1,
	ElevatorBrake1 = 2,
	ElevatorBrake2 = 3,
};

enum DIOPorts {
	Elevator1DIO1 = 0,
	Elevator1DIO2,
	Elevator2DIO1,
	Elevator3DIO1,
	Elevator3DIO2
};

enum startingPositions {
	CenterPosition = 0,
	LeftPosition,
	RightPosition
};

enum autoTarget{
	Switch = 0,
	Scale
};

enum StructureData {
	DataError = 0,
	LeftSide,
	RightSide
};

#define DEBUGGING


#endif /* SRC_ROBOT_H_ */
