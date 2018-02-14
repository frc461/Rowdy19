/*
 * Elevator.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: Hank Krutulis - 461
 */
#include <Elevator.h>


Elevator::Elevator(Sensors &srs) {
	elevator1 = new TalonSRX(Elevator1CAN);
	elevator2 = new VictorSPX(Elevator2CAN);
	elevator3 = new VictorSPX(Elevator3CAN);
	elevatorBrake = new DoubleSolenoid(ElevatorBrake1, ElevatorBrake2);
	sensors = &srs;

	elevator2->Follow(*elevator1);
	elevator3->Follow(*elevator1);
	encoderVal = elevator1->GetSelectedSensorPosition(0);
	postValues();
}

void Elevator::goUp(){

	double distFromTop = elevatorTop - encoderVal, actualSpeed = raiseSpeed;
	if(distFromTop < slowTopThreshold){
//		actualSpeed =  distFromTop / slowTopThreshold * slowDownMultiplierTop;
		actualSpeed = slowDownMultiplierTop;
	}

	if(encoderVal < 23000){
		BrakeRelease();
		elevator1->Set(ControlMode::PercentOutput, -actualSpeed);
	} else {
		haltMotion();
	}
}

void Elevator::move(double speed){
	BrakeRelease();
	elevator1->Set(ControlMode::PercentOutput, speed);
}

void Elevator::goDown(){
	double  actualSpeed = lowerSpeed;
		if(encoderVal < slowBottomThreshold){
//			actualSpeed = encoderVal / slowBottomThreshold * slowDownMultiplierBottom;
			actualSpeed = slowDownMultiplierBottom;
		}

	if(!sensors->getElevatorBottom()){
		BrakeRelease();
		elevator1->Set(ControlMode::PercentOutput, actualSpeed);
	} else {
		haltMotion();
	}
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

void Elevator::resetEncoder(){
	elevator1->SetSelectedSensorPosition(0,0,0);
}

void Elevator::postValues(){
	SmartDashboard::PutNumber("Elevator/raiseSpeed", raiseSpeed);
	SmartDashboard::PutNumber("Elevator/lowerSpeed", lowerSpeed);
	SmartDashboard::PutNumber("Elevator/heightTolerance", heightTolerance);
	SmartDashboard::PutNumber("Elevator/encoderVal", encoderVal);

	SmartDashboard::PutNumber("Elevator/intakeExchangeHeight", intakeExchangeHeight);
	SmartDashboard::PutNumber("Elevator/switchHeight", switchHeight);
	SmartDashboard::PutNumber("Elevator/scaleHeight", scaleHeight);
	SmartDashboard::PutNumber("Elevator/climbHeight", climbHeight);
	SmartDashboard::PutNumber("Elevator/elevatorTop", elevatorTop);
	SmartDashboard::PutNumber("Elevator/eleEncoder", elevator1->GetSelectedSensorPosition(0));
	SmartDashboard::PutNumber("Elevator/slowTopThreshold", slowTopThreshold);
	SmartDashboard::PutNumber("Elevator/slowBottomThreshold", slowBottomThreshold);
	SmartDashboard::PutNumber("Elevator/slowDownMultiplierTop", slowDownMultiplierTop);
	SmartDashboard::PutNumber("Elevator/slowDownMultiplierBottom", slowDownMultiplierBottom);

}

void Elevator::periodicValues(){
	if(sensors->getElevatorBottom()){
		resetEncoder();
	}

	encoderVal = elevator1->GetSelectedSensorPosition(0);
	SmartDashboard::PutNumber("Elevator/elevatorEncoder", encoderVal);


	heightTolerance = SmartDashboard::GetNumber("Elevator/heightTolerance", heightTolerance);
	raiseSpeed = SmartDashboard::GetNumber("Elevator/raiseSpeed", raiseSpeed);
	lowerSpeed = SmartDashboard::GetNumber("Elevator/lowerSpeed", lowerSpeed);

	slowTopThreshold = SmartDashboard::GetNumber("Elevator/slowTopThreshold", slowTopThreshold);
	slowBottomThreshold = SmartDashboard::GetNumber("Elevator/slowBottomThreshold", slowBottomThreshold);
	slowDownMultiplierTop = SmartDashboard::GetNumber("Elevator/slowDownMultiplierTop", slowDownMultiplierTop);
	slowDownMultiplierBottom = SmartDashboard::GetNumber("Elevator/slowDownMultiplierBottom", slowDownMultiplierBottom);


	elevatorTop = SmartDashboard::GetNumber("Elevator/elevatorTop", elevatorTop);
	intakeExchangeHeight = SmartDashboard::GetNumber("Elevator/intakeExchangeHeight", intakeExchangeHeight);
	switchHeight = SmartDashboard::GetNumber("Elevator/switchHeight", switchHeight);
	scaleHeight = SmartDashboard::GetNumber("Elevator/scaleHeight", scaleHeight);
	climbHeight = SmartDashboard::GetNumber("Elevator/climbHeight", climbHeight);
}
