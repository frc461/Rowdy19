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

		rightDrive1 = new WPI_TalonSRX(RightDrive1CAN);
		rightDrive2 = new WPI_VictorSPX(RightDrive2CAN);
		rightDrive3 = new WPI_VictorSPX(RightDrive3CAN);
		leftDrive1  = new WPI_TalonSRX(LeftDrive1CAN);
		leftDrive2  = new WPI_VictorSPX(LeftDrive2CAN);
		leftDrive3  = new WPI_VictorSPX(LeftDrive3CAN);
		strafe1     = new TalonSRX(Strafe1CAN);
		strafe2     = new VictorSPX(Strafe2CAN);
		sensors = &sensorsPass;
		isStrafing = false;
		pidoutput = 0.0;
		pidAdd = 0.0;
		pidMax = 0.8;
		p = 0.8;
		i = 0.0;
		d = 0.1;
		strafeSpeedTolerance = 0.2;
		strafeAngleTolerance = 3;
		strafeAngle = 0.0;
		leftDrive1->ConfigSelectedFeedbackSensor(QuadEncoder, 0, 0);

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
		SmartDashboard::PutNumber("LeftEncoderValue", GetEncoderVal(LeftSide));
		SmartDashboard::PutNumber("LeftEncoderVelocity", leftDrive1->GetSelectedSensorVelocity(0));
		SmartDashboard::PutNumber("strafeSpeed", 0.8);
		SmartDashboard::PutNumber("driveSpeed", 0.8);
		SmartDashboard::PutNumber("turnSpeed", 0.6);
		SmartDashboard::PutData("StrafePID", pid);
		SmartDashboard::PutNumber("PIDOutput", pidoutput);
		SmartDashboard::PutNumber("PIDMax", pidMax);
		SmartDashboard::PutNumber("strafeDiff", strafeDifference);
		SmartDashboard::PutNumber("strafeAngleTolerance", strafeAngleTolerance);
		SmartDashboard::PutNumber("StrafeAngle", strafeAngle);
		SmartDashboard::PutNumber("StrafeSpeedTolerance", strafeSpeedTolerance);
	}

	int DriveTrain::GetEncoderVal(int sideSelect){
		switch(sideSelect){
			case (LeftSide):
					return leftDrive1->GetIntegralAccumulator(0);
					break;
			case (RightSide):
					return rightDrive1->GetSelectedSensorPosition(0);
					break;
		}
	}

	void DriveTrain::ResetEncoders(){
		leftDrive1->SetSelectedSensorPosition(0,0,0);
		rightDrive1->SetSelectedSensorPosition(0,0,0);
	}

	void DriveTrain::GetValues(){
		strafeSpeed = SmartDashboard::GetNumber("strafeSpeed", 0.8);
		driveSpeed = SmartDashboard::GetNumber("driveSpeed", 0.8);
		turnSpeed = SmartDashboard::GetNumber("turnSpeed", 0.6);
		pidMax = SmartDashboard::GetNumber("PIDMax", 0.5);
		p = SmartDashboard::GetNumber("StrafePID/p", 0.8);
		i = SmartDashboard::GetNumber("StrafePID/i", 0.0);
		d = SmartDashboard::GetNumber("StrafePID/d", 0.1);
		strafeSpeedTolerance = SmartDashboard::GetNumber("StrafeSpeedTolerance", 0.2);
		strafeAngleTolerance = SmartDashboard::GetNumber("strafeAngleTolerance", strafeAngleTolerance);
		pid->SetPID(p, i, d);
	}

	void DriveTrain::ArcadeDrive(double forward, double rotate, double strafe){
		GetValues();
		PutValues();
		SmartDashboard::PutNumber("Strafe", strafe);
		strafeDifference = sensors->GetGyroAngle() - strafeAngle;
		pidsrc->set(strafeDifference);
		pid->SetOutputRange(-pidMax, pidMax);
		CalculateStrafeRotate(strafe);
		rotate += pidoutput;
		driveTrain->ArcadeDrive(-forward * driveSpeed, rotate * turnSpeed);
		strafe1->Set(ControlMode::PercentOutput, strafe * -strafeSpeed);
	}

	void DriveTrain::InitPID(){
		pidout = new SettablePIDOut();
		pidsrc = new SettablePIDSource();
		pid = new PIDController(p, i, d, pidsrc, pidout);
		pid->SetOutputRange(-pidMax, pidMax);
	}	

	void DriveTrain::TankDrive(double left, double right, double strafe){
		GetValues();
		driveTrain->TankDrive(-left * driveSpeed, -right * driveSpeed);
		strafe1->Set(ControlMode::PercentOutput, strafe * -strafeSpeed);
	}

	void DriveTrain::CalculateStrafeRotate(double strafe){
		if (strafe > strafeSpeedTolerance || strafe < -strafeSpeedTolerance) {
			isStrafing = true;
		} else {
			pid->Reset();
			pid->Enable();
			strafeAngle = sensors->GetGyroAngle();
			isStrafing = false;
		}
		if(isStrafing && (strafeDifference > strafeAngleTolerance || strafeDifference < -strafeAngleTolerance)){
			pidoutput = pidout->output;
		} else {
			pidoutput = 0.0;
		}
	}

//	PowerDistributionPanel DriveTrain::GetPDP(){
//		return pdp;
//	}
