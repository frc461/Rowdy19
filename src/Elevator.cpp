/*
 * Elevator.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: hank
 */

#include <Elevator.h>
#include "Robot.h"

Elevator::Elevator() {
	elevator1 = new TalonSRX(Elevator1CAN);
	elevator2 = new VictorSPX(Elevator2CAN);
	elevator3 = new VictorSPX(Elevator3CAN);
	elevatorBrake = new DoubleSolenoid(ElevatorBrake1, ElevatorBrake2);

	postValues();
	elevator2->Follow(*elevator1);
	elevator3->Follow(*elevator1);
	encoderVal = elevator1->GetSelectedSensorPosition(0);
}

void Elevator::goUp(){
	BrakeRelease();
	elevator1->Set(ControlMode::PercentOutput, -raiseSpeed);
}

void Elevator::move(double speed){
	BrakeRelease();
	elevator1->Set(ControlMode::PercentOutput, speed);
}

void Elevator::goDown(){
	BrakeRelease();
	elevator1->Set(ControlMode::PercentOutput, lowerSpeed);
}

void Elevator::Brake(){
	elevatorBrake->Set(DoubleSolenoid::kForward);
}

void Elevator::BrakeRelease(){
	elevatorBrake->Set(DoubleSolenoid::kReverse);
}

void Elevator::goToSwitchHeight(){
	if(encoderVal < switchHeight - heightTolerance){
		goUp();
	} else if(encoderVal > switchHeight + heightTolerance){
		goDown();
	} else {
		haltMotion();
	}
}

void Elevator::goToScaleHeight(){
	if(encoderVal < scaleHeight - heightTolerance){
		goUp();
	} else if(encoderVal > scaleHeight + heightTolerance){
		goDown();
	} else {
		haltMotion();
	}
}

void Elevator::goToClimbHeight(){
	if(encoderVal < climbHeight - heightTolerance){
		goUp();
	} else if(encoderVal > climbHeight + heightTolerance){
		goDown();
	} else {
		haltMotion();
	}
}

void Elevator::goToIntakeExchangeHeight(){
	if(encoderVal < intakeExchangeHeight - heightTolerance){
		goUp();
	} else if(encoderVal > intakeExchangeHeight + heightTolerance){
		goDown();
	} else {
		haltMotion();
	}
}

void Elevator::haltMotion(){
	elevator1->Set(ControlMode::PercentOutput, 0.0);
	Brake();
}

void Elevator::resetEncoder(){}

void Elevator::postValues(){
	SmartDashboard::PutNumber("Elevator/raiseSpeed", raiseSpeed);
	SmartDashboard::PutNumber("Elevator/lowerSpeed", lowerSpeed);
	SmartDashboard::PutNumber("Elevator/heightTolerance", heightTolerance);
	SmartDashboard::PutNumber("Elevator/elevatorEncoder", encoderVal);

	SmartDashboard::PutNumber("Elevator/intakeExchangeHeight", intakeExchangeHeight);
	SmartDashboard::PutNumber("Elevator/switchHeight", switchHeight);
	SmartDashboard::PutNumber("Elevator/scaleHeight", scaleHeight);
	SmartDashboard::PutNumber("Elevator/climbHeight", climbHeight);
	SmartDashboard::PutNumber("Elevator/EleEncoder", elevator1->GetSelectedSensorPosition(0));
}

void Elevator::periodicValues(){
	encoderVal = elevator1->GetSelectedSensorPosition(0);
	SmartDashboard::PutNumber("Elevator/elevatorEncoder", encoderVal);

	heightTolerance = SmartDashboard::GetNumber("Elevator/heightTolerance", heightTolerance);
	raiseSpeed = SmartDashboard::GetNumber("Elevator/raiseSpeed", raiseSpeed);
	lowerSpeed = SmartDashboard::GetNumber("Elevator/lowerSpeed", lowerSpeed);

	intakeExchangeHeight = SmartDashboard::GetNumber("Elevator/intakeExchangeHeight", intakeExchangeHeight);
	switchHeight = SmartDashboard::GetNumber("Elevator/switchHeight", switchHeight);
	scaleHeight = SmartDashboard::GetNumber("Elevator/scaleHeight", scaleHeight);
	climbHeight = SmartDashboard::GetNumber("Elevator/climbHeight", climbHeight);
}
