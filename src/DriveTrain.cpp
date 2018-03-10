/*
 * DriveTrain.cpp
 *
 *  Created on: Jan 20, 2018
 *      Author: Hank Krutulis - 461
 */

#include <WPILib.h>
#include "DriveTrain.h"
#include "ctre/Phoenix.h"

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
		pidMax = 0.6;
		p = 0.6;
		i = 0.0;
		d = 0.1;
		rotateTolerance = 0.2;
		strafeSpeedTolerance = 0.2;
		strafeAngleTolerance = 3;
		strafeAngle = 0.0;
		straightCorrection = 0.15;

		SpeedControllerGroup *left  = new SpeedControllerGroup(*leftDrive1,  *leftDrive2,  *leftDrive3);
		SpeedControllerGroup *right = new SpeedControllerGroup(*rightDrive1, *rightDrive2, *rightDrive3);
		driveTrain = new DifferentialDrive(*left, *right);
		strafe2->Follow(*strafe1);

		initPID();
		putValues();
		periodicValues();
	}

	void DriveTrain::putValues(){

		SmartDashboard::PutData("driveTrain", driveTrain);

		#ifdef DEBUGGING
				SmartDashboard::PutNumber("strafeSpeed", 1.0);
				SmartDashboard::PutNumber("driveSpeed", 1.0);
				SmartDashboard::PutNumber("turnSpeed", 1.0);
				SmartDashboard::PutNumber("strafeDrift", 0.3);
				SmartDashboard::PutBoolean("isStrafing", isStrafing);

				SmartDashboard::PutNumber("strafeDiff", strafeDifference);
				SmartDashboard::PutNumber("strafeAngleTolerance", strafeAngleTolerance);
				SmartDashboard::PutNumber("StrafeAngle", strafeAngle);
				SmartDashboard::PutNumber("StrafeSpeedTolerance", strafeSpeedTolerance);
				SmartDashboard::PutNumber("RotateTolerance", rotateTolerance);
		#endif
	}

	int DriveTrain::getEncoderVal(int sideSelect){
		if (sideSelect == LeftSide){
				return leftDrive1->GetSelectedSensorPosition(0);
		} else {
				return rightDrive1->GetSelectedSensorPosition(0);
		}
	}

	void DriveTrain::resetEncoders(){
		leftDrive1->SetSelectedSensorPosition(0,0,0);
		rightDrive1->SetSelectedSensorPosition(0,0,0);
	}

	void DriveTrain::periodicValues(){
		SmartDashboard::PutNumber("RightEncoderValue", getEncoderVal(RightSide));
		SmartDashboard::PutNumber("LeftEncoderValue", getEncoderVal(LeftSide));
#ifdef DEBUGGING
		SmartDashboard::PutData("StrafePID", pid);
		SmartDashboard::PutNumber("PIDOutput", pidoutput);
		strafeSpeed = SmartDashboard::GetNumber("strafeSpeed", 1.0);
		driveSpeed = SmartDashboard::GetNumber("driveSpeed", 1.0);
		turnSpeed = SmartDashboard::GetNumber("turnSpeed", 1.0);
		strafeDrift = SmartDashboard::GetNumber("strafeDrift", strafeDrift);

		pidMax = SmartDashboard::GetNumber("PIDMax", 0.8);
		p = SmartDashboard::GetNumber("StrafePID/p", 0.8);
		i = SmartDashboard::GetNumber("StrafePID/i", 0.0);
		d = SmartDashboard::GetNumber("StrafePID/d", 0.1);

		strafeSpeedTolerance = SmartDashboard::GetNumber("StrafeSpeedTolerance", 0.2);
		strafeAngleTolerance = SmartDashboard::GetNumber("strafeAngleTolerance", strafeAngleTolerance);
		rotateTolerance = SmartDashboard::GetNumber("RotateTolerance", rotateTolerance);
#endif
		pid->SetPID(p, i, d);
	}

	void DriveTrain::arcadeDrive(double forward, double rotate, double strafe){
		periodicValues();
		SmartDashboard::PutNumber("Strafe", strafe);
		if (rotate > rotateTolerance || rotate < -rotateTolerance){
			strafeAngle = sensors->getGyroAngle();
		}
		strafeDifference = sensors->getGyroAngle() - strafeAngle;
		pidsrc->set(strafeDifference);
		pid->SetOutputRange(-pidMax, pidMax);
		calculateStrafeRotate(strafe);
		rotate += pidoutput;
		driveTrain->ArcadeDrive(-forward * driveSpeed, rotate * turnSpeed);

		strafe1->Set(ControlMode::PercentOutput, strafe * -strafeSpeed);

	}

	void DriveTrain::haltMotion(){
		driveTrain->TankDrive(0.0,0.0);
	}

	void DriveTrain::initPID(){
		pidout = new SettablePIDOut();
		pidsrc = new SettablePIDSource();
		pid = new PIDController(p, i, d, pidsrc, pidout);
		pid->SetOutputRange(-pidMax, pidMax);
		SmartDashboard::PutNumber("PIDMax", pidMax);
	}	

	void DriveTrain::tankDrive(double left, double right, double strafe){
		periodicValues();
		driveTrain->TankDrive(-left, -right);
		strafe1->Set(ControlMode::PercentOutput, strafe * -strafeSpeed);
	}

	void DriveTrain::calculateStrafeRotate(double strafe){
		if (strafe > strafeSpeedTolerance || strafe < -strafeSpeedTolerance) {
			isStrafing = true;
		} else {
			pid->Reset();
			pid->Enable();
			strafeAngle = sensors->getGyroAngle();
			isStrafing = false;
		}

		if(isStrafing && (strafeDifference > strafeAngleTolerance || strafeDifference < -strafeAngleTolerance)){
			pidoutput = pidout->output;
		} else {
			pidoutput = 0.0;
		}
	}
