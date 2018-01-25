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
		PutSpeedValues();
		GetSpeedValues();
	}

	void DriveTrain::PutSpeedValues(){
		SmartDashboard::PutNumber("strafeSpeed", 0.8);
		SmartDashboard::PutNumber("driveSpeed", 0.8);
		SmartDashboard::PutNumber("turnSpeed", 0.6);
	}

	void DriveTrain::GetSpeedValues(){
		strafeSpeed = SmartDashboard::GetNumber("strafeSpeed", 0.8);
		driveSpeed = SmartDashboard::GetNumber("driveSpeed", 0.8);
		turnSpeed = SmartDashboard::GetNumber("turnSpeed", 0.6);
	}

	void DriveTrain::ArcadeDrive(double forward, double rotate, double strafe){
		GetSpeedValues();
		driveTrain->ArcadeDrive(forward * driveSpeed, rotate * turnSpeed);
		strafe1->Set(ControlMode::PercentOutput, strafe * strafeSpeed);
	}

	void DriveTrain::TankDrive(double left, double right, double strafe){
		GetSpeedValues();
		driveTrain->TankDrive(left * driveSpeed, right * driveSpeed);
		strafe1->Set(ControlMode::PercentOutput, strafe * strafeSpeed);
	}
	
//	PowerDistributionPanel DriveTrain::GetPDP(){
//		return pdp;
//	}
