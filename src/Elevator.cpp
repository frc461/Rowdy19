/*
 * Elevator.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: hank
 */

#include <Elevator.h>
#include "Robot.h"

Elevator::Elevator() {
	elevator1 = new VictorSPX(Elevator1CAN);
	elevator2 = new VictorSPX(Elevator2CAN);
	elevator3 = new VictorSPX(Elevator3CAN);

	elevator2->Follow(*elevator1);
	elevator3->Follow(*elevator1);
	encoderVal = elevator1->GetSelectedSensorPosition(0);
}

void Elevator::goUp(){
	elevator1->Set(ControlMode::PercentOutput, elevateSpeed);
}

void Elevator::goDown(){
	elevator1->Set(ControlMode::PercentOutput, -elevateSpeed);
}

void Elevator::goToSwitchHeight(){
	if(encoderVal < switchHeight){
		goUp();
	}
}

void Elevator::goToScaleHeight(){
	if(elevator1->GetSelectedSensorPosition(0) < switchHeight){

	}
}

void Elevator::goToClimbHeight(){
	if(elevator1->GetSelectedSensorPosition(0) < switchHeight){

	}
}

void Elevator::goToIntakeExchangeHeight(){
	if(elevator1->GetSelectedSensorPosition(0) < switchHeight){

	}
}

void Elevator::haltMotion(){
	elevator1->Set(ControlMode::PercentOutput, 0.0);
}

void Elevator::resetEncoder(){}

void Elevator::postValues(){
	SmartDashboard::PutNumber("Elevator/elevateSpeed", elevateSpeed);
	SmartDashboard::PutNumber("Elevator/elevatorEncoder", encoderVal);

	SmartDashboard::PutNumber("Elevator/intakeExchangeHeight", intakeExchangeHeight);
	SmartDashboard::PutNumber("Elevator/switchHeight", switchHeight);
	SmartDashboard::PutNumber("Elevator/scaleHeight", scaleHeight);
	SmartDashboard::PutNumber("Elevatore/climbHeight", climbHeight);

}

void Elevator::periodicValues(){
	encoderVal = elevator1->GetSelectedSensorPosition(0);
	SmartDashboard::PutNumber("Elevator/elevateSpeed", elevateSpeed);
	SmartDashboard::PutNumber("Elevator/elevatorEncoder", encoderVal);

	elevateSpeed = SmartDashboard::GetNumber("Elevator/elevateSpeed", elevateSpeed);
	intakeExchangeHeight = SmartDashboard::GetNumber("Elevator/intakeExchangeHeight", intakeExchangeHeight);
	switchHeight = SmartDashboard::GetNumber("Elevator/switchHeight", switchHeight);
	scaleHeight = SmartDashboard::GetNumber("Elevator/scaleHeight", scaleHeight);
	climbHeight = SmartDashboard::GetNumber("Elevator/climbHeight", climbHeight);
}
