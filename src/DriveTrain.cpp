/*
 * DriveTrain.cpp
 *
 *  Created on: Jan 20, 2018
 *      Author: Hank Krutulis
 */

#include "DriveTrain.h"
#include "ctre/Phoenix.h"
#include <WPILib.h>
#include "Robot.h"


double const DRIVE_SPEED = 0.8;
double const TURN_SPEED = 0.6;
double const STRAFE_SPEED = 0.4;

	DriveTrain::DriveTrain(){

		pdp = new PowerDistributionPanel(0);

		rightDrive1 = new WPI_TalonSRX(RightDrive1CAN);
		rightDrive2 = new WPI_VictorSPX(RightDrive2CAN);
		rightDrive3 = new WPI_VictorSPX(RightDrive3CAN);
		leftDrive1  = new WPI_VictorSPX(LeftDrive1CAN);
		leftDrive2  = new WPI_VictorSPX(LeftDrive2CAN);
		leftDrive3  = new WPI_VictorSPX(LeftDrive3CAN);
		strafe1     = new WPI_TalonSRX(Strafe1CAN);
		strafe2     = new WPI_TalonSRX(Strafe2CAN);

		SpeedControllerGroup *left  = new SpeedControllerGroup(*leftDrive1,  *leftDrive2,  *leftDrive3);
		SpeedControllerGroup *right = new SpeedControllerGroup(*rightDrive1, *rightDrive2, *rightDrive3);
		driveTrain = new DifferentialDrive(*left, *right);
		strafe2->Follow(*strafe1);
	}

	void DriveTrain::ArcadeDrive(double forward, double rotate, double strafe){
		driveTrain->ArcadeDrive(forward * DRIVE_SPEED, rotate * TURN_SPEED);
		strafe1->Set(strafe * STRAFE_SPEED);
	}

	void DriveTrain::TankDrive(double left, double right, double strafe){
		driveTrain->TankDrive(left * DRIVE_SPEED, right * DRIVE_SPEED);
		strafe1->Set(strafe * STRAFE_SPEED);
	}
	
//	PowerDistributionPanel DriveTrain::GetPDP(){
//		return pdp;
//	}
