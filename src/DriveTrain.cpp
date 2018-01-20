/*
 * DriveTrain.cpp
 *
 *  Created on: Jan 20, 2018
 *      Author: Hank Krutulis
 */

#include "DriveTrain.h"
#include "ctre/Phoenix.h"
#include <WPILib.h>

	DriveTrain::DriveTrain(int rightDrive1CAN, int rightDrive2CAN, int rightDrive3CAN, int leftDrive1CAN,
		int leftDrive2CAN, int leftDrive3CAN, int strafe1CAN, int strafe2CAN){
		rightDrive1 = new WPI_TalonSRX(rightDrive1CAN);
		rightDrive2 = new WPI_VictorSPX(rightDrive2CAN);
		rightDrive3 = new WPI_VictorSPX(rightDrive3CAN);
		leftDrive1  = new WPI_VictorSPX(leftDrive1CAN);
		leftDrive2  = new WPI_VictorSPX(leftDrive2CAN);
		leftDrive3  = new WPI_VictorSPX(leftDrive3CAN);
//		strafe1     = new WPI_TalonSRX(strafe1CAN);
//		strafe2     = new WPI_TalonSRX(strafe2CAN);

		SpeedControllerGroup *left  = new SpeedControllerGroup(*leftDrive1,  *leftDrive2,  *leftDrive3);
		SpeedControllerGroup *right = new SpeedControllerGroup(*rightDrive1, *rightDrive2, *rightDrive3);
		driveTrain = new DifferentialDrive(*left, *right);
//		strafe2->Follow(*strafe1);
	}

	void DriveTrain::ArcadeDrive(double forward, double rotate, double strafe){
		driveTrain->ArcadeDrive(forward * DRIVE_SPEED, rotate * TURN_SPEED);
//		strafe1->Set(strafe * STRAFE_SPEED);
	}

	void DriveTrain::TankDrive(double left, double right, double strafe){
		driveTrain->TankDrive(left * DRIVE_SPEED, right * DRIVE_SPEED);
//		strafe1->Set(strafe * STRAFE_SPEED);
	}

	DriveTrain::~DriveTrain() {
		// TODO Auto-generated destructor stub
	}
