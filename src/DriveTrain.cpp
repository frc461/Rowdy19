/*
 * DriveTrain.cpp
 *
 *  Created on: Jan 20, 2018
 *      Author: Hank Krutulis
 */

#include "DriveTrain.h"
#include "ctre/Phoenix.h"
#include <WPILib.h>

	DriveTrain::DriveTrain(Sensors& sensorsPass){

		pdp = new PowerDistributionPanel(0);

		rightDrive1 = new WPI_TalonSRX(RightDrive1CAN);
		rightDrive2 = new WPI_VictorSPX(RightDrive2CAN);
		rightDrive3 = new WPI_VictorSPX(RightDrive3CAN);
		leftDrive1  = new WPI_TalonSRX(LeftDrive1CAN);
		leftDrive2  = new WPI_VictorSPX(LeftDrive2CAN);
		leftDrive3  = new WPI_VictorSPX(LeftDrive3CAN);
		strafe1     = new VictorSPX(Strafe1CAN);
		strafe2     = new TalonSRX(Strafe2CAN);
		sensors = &sensorsPass;
		isStrafing = false;
		pidoutput = 0.0;
		pidAdd = 0.125;
		pidMax = 0.5;
		strafeTolerance = 10;
		strafeAngle = 0.0;

		SpeedControllerGroup *left  = new SpeedControllerGroup(*leftDrive1,  *leftDrive2,  *leftDrive3);
		SpeedControllerGroup *right = new SpeedControllerGroup(*rightDrive1, *rightDrive2, *rightDrive3);
		driveTrain = new DifferentialDrive(*left, *right);
		strafe2->Follow(*strafe1);
		InitPID();
		PutValues();
		GetValues();
	}

	void DriveTrain::PutValues(){
		SmartDashboard::PutBoolean("isStrafing", isStrafing);
		SmartDashboard::PutNumber("strafeSpeed", 0.8);
		SmartDashboard::PutNumber("driveSpeed", 0.8);
		SmartDashboard::PutNumber("turnSpeed", 0.6);
		SmartDashboard::PutData("StrafePID", pid);
		SmartDashboard::PutNumber("PIDOutput", pidoutput);
		SmartDashboard::PutNumber("PIDMax", pidMax);
		SmartDashboard::PutNumber("Gyro diff", strafeDifference);
		SmartDashboard::PutNumber("StrafeTolerance", strafeTolerance);
		SmartDashboard::PutNumber("StrafeAngle", strafeAngle);
	}

	void DriveTrain::GetValues(){
		strafeSpeed = SmartDashboard::GetNumber("strafeSpeed", 0.8);
		driveSpeed = SmartDashboard::GetNumber("driveSpeed", 0.8);
		turnSpeed = SmartDashboard::GetNumber("turnSpeed", 0.6);
		pidMax = SmartDashboard::GetNumber("PIDMax", 0.5);
		p = SmartDashboard::GetNumber("StrafePID/p", 0.0);
		i = SmartDashboard::GetNumber("StrafePID/i", 0.0);
		d = SmartDashboard::GetNumber("StrafePID/d", 0.0);
		strafeTolerance = SmartDashboard::GetNumber("StrafeTolerance", strafeTolerance);
		pid->SetPID(p, i, d);
	}

	void DriveTrain::ArcadeDrive(double forward, double rotate, double strafe){
		GetValues();
		PutValues();
		SmartDashboard::PutNumber("Strafe", strafe);

		strafeDifference = sensors->GetGyroAngle() - strafeAngle;

		pidsrc->set(strafeDifference);

		rotate += pidoutput;

		driveTrain->ArcadeDrive(-forward * driveSpeed, rotate * turnSpeed);

		strafe1->Set(ControlMode::PercentOutput, strafe * -strafeSpeed);
	}

	void DriveTrain::InitPID(){
		pidout = new SettablePIDOut();
		pidsrc = new SettablePIDSource();
		pid = new PIDController(p, i, d, pidsrc, pidout);
		pid->SetOutputRange(0.0, pidMax);
	}	

	void DriveTrain::TankDrive(double left, double right, double strafe){
		GetValues();
		driveTrain->TankDrive(-left * driveSpeed, -right * driveSpeed);
		strafe1->Set(ControlMode::PercentOutput, strafe * -strafeSpeed);
	}

	void DriveTrain::CalculateStrafeRotate(double strafe){
		if (!isStrafing && strafe != 0.0) {
			isStrafing = true;
		} else  {
			pid->Reset();
			pid->Enable();
			strafeAngle = sensors->GetGyroAngle();
			isStrafing = false;
		}
		if(isStrafing && (strafeDifference > strafeTolerance || strafeDifference < -strafeTolerance)){
			pidoutput = pidout->output < 0 ? pidout->output - pidAdd : pidout->output + pidAdd;
		} else {
			pidoutput = 0.0;
		}
	}

//	PowerDistributionPanel DriveTrain::GetPDP(){
//		return pdp;
//	}
