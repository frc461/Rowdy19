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
	elevator4 = new VictorSPX(Elevator4CAN);
	elevatorBrake = new DoubleSolenoid(ElevatorBrake1, ElevatorBrake2);
	sensors = &srs;

	elevator2->Follow(*elevator1);
	elevator3->Follow(*elevator1);
	elevator4->Follow(*elevator2);

	// TODO: Check on competition bot whether new motor is backwards
	elevator4->SetInverted(true);
	encoderVal = elevator1->GetSelectedSensorPosition(0);
	postValues();
}

void Elevator::goUp(){

	double distFromTop = elevatorTop - encoderVal, actualSpeed = raiseSpeed;
	if(distFromTop < slowTopThreshold){
//		actualSpeed =  distFromTop / slowTopThreshold * slowDownMultiplierTop;
		actualSpeed = slowDownMultiplierTop;
	}

	if(encoderVal < elevatorTop){
		brakeRelease();
		elevator1->Set(ControlMode::PercentOutput, -actualSpeed);
	} else {
		haltMotion();
	}
}

void Elevator::move(double speed){
	if((speed > 0 && !sensors->getElevatorBottom())
	|| (speed < 0 && encoderVal < elevatorTop)){
		brakeRelease();
		elevator1->Set(ControlMode::PercentOutput, speed);
	}
	else {
		haltMotion();
	}
}

void Elevator::goDown(){
	double  actualSpeed = lowerSpeed;
	if(encoderVal < slowBottomThreshold){
		actualSpeed = slowDownMultiplierBottom;
	}

	if(!sensors->getElevatorBottom()){
		brakeRelease();
		elevator1->Set(ControlMode::PercentOutput, actualSpeed);
	} else {
		haltMotion();
	}
}

void Elevator::brake(){
	elevatorBrake->Set(DoubleSolenoid::kForward);
}

void Elevator::brakeRelease(){
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
	brake();
}

int Elevator::encoderValue(){
	return encoderVal;
}

void Elevator::resetEncoder(){
	elevator1->SetSelectedSensorPosition(0,0,0);
}

void Elevator::postValues(){
	SmartDashboard::PutNumber("Comp/raiseSpeed", raiseSpeed);
	SmartDashboard::PutNumber("Comp/lowerSpeed", lowerSpeed);

#ifdef DEBUGGING
	SmartDashboard::PutNumber("Elevator/heightTolerance", heightTolerance);

	SmartDashboard::PutNumber("Elevator/intakeExchangeHeight", intakeExchangeHeight);
	SmartDashboard::PutNumber("Elevator/switchHeight", switchHeight);
	SmartDashboard::PutNumber("Elevator/scaleHeight", scaleHeight);
	SmartDashboard::PutNumber("Elevator/climbHeight", climbHeight);
	SmartDashboard::PutNumber("Elevator/elevatorTop", elevatorTop);
	SmartDashboard::PutNumber("Elevator/slowTopThreshold", slowTopThreshold);
	SmartDashboard::PutNumber("Elevator/slowBottomThreshold", slowBottomThreshold);
	SmartDashboard::PutNumber("Elevator/slowDownMultiplierTop", slowDownMultiplierTop);
	SmartDashboard::PutNumber("Elevator/slowDownMultiplierBottom", slowDownMultiplierBottom);
#endif //Debugging

}

void Elevator::autonStart(){
	elevator1->SetSelectedSensorPosition(startHeight, 0,0);
}

void Elevator::periodicValues(){
	if(sensors->getElevatorBottom()){
		resetEncoder();
	}

	encoderVal = elevator1->GetSelectedSensorPosition(0);
	SmartDashboard::PutNumber("Comp/elevatorEncoder", encoderVal);
	raiseSpeed = SmartDashboard::GetNumber("Comp/raiseSpeed", raiseSpeed);
	lowerSpeed = SmartDashboard::GetNumber("Comp/lowerSpeed", lowerSpeed);

#ifdef DEBUGGING
	heightTolerance = SmartDashboard::GetNumber("Elevator/heightTolerance", heightTolerance);

	slowTopThreshold = SmartDashboard::GetNumber("Elevator/slowTopThreshold", slowTopThreshold);
	slowBottomThreshold = SmartDashboard::GetNumber("Elevator/slowBottomThreshold", slowBottomThreshold);
	slowDownMultiplierTop = SmartDashboard::GetNumber("Elevator/slowDownMultiplierTop", slowDownMultiplierTop);
	slowDownMultiplierBottom = SmartDashboard::GetNumber("Elevator/slowDownMultiplierBottom", slowDownMultiplierBottom);

	elevatorTop = SmartDashboard::GetNumber("Elevator/elevatorTop", elevatorTop);
	intakeExchangeHeight = SmartDashboard::GetNumber("Elevator/intakeExchangeHeight", intakeExchangeHeight);
	switchHeight = SmartDashboard::GetNumber("Elevator/switchHeight", switchHeight);
	scaleHeight = SmartDashboard::GetNumber("Elevator/scaleHeight", scaleHeight);
	climbHeight = SmartDashboard::GetNumber("Elevator/climbHeight", climbHeight);
#endif //Debugging
}
