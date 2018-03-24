/*
 * Intake.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: Hank Krutulis - 461
 */

#include <Intake.h>

Intake::Intake(Sensors& sensorsPass) {
	intakeExtension = new DoubleSolenoid(Intake1, Intake2);
	intakeInLeft = new Victor(LeftInIntakePWM);
	intakeInRight = new Victor(RightInIntakePWM);
	wristMotor = new Spark(WristPWM);
	sensors = &sensorsPass;
	resetSpitCount();
	putValues();
}

void Intake::takeInOuter(){
}

void Intake::takeInInner(){
	intakeInLeft->Set(-outputSpeed);
	intakeInRight->Set(outputSpeed);
}

void Intake::slowOutput(){
	intakeInLeft->Set(slowOutputSpeed);
	intakeInRight->Set(-slowOutputSpeed);
}

void Intake::takeInAll(){
	takeInOuter();
	takeInInner();
}

void Intake::outputOuter(){
}

void Intake::outputInner(){
	intakeInLeft->Set(intakeSpeed);
	intakeInRight->Set(-intakeSpeed);
}

void Intake::outputAll(){
	outputOuter();
	outputInner();
}

void Intake::spinRight(){
	intakeInLeft->Set(spinSpeed);
	intakeInRight->Set(-spinSpeed);

}

void Intake::spinLeft(){
	intakeInLeft->Set(spinSpeed);
	intakeInRight->Set(-spinSpeed);
}

void Intake::resetSpitCount(){
	spitCount = 0;
}

bool Intake::spitCube(){
	if (spitCount < 10){
		outputAll();
		spitCount++;
		return false;
	} else {
		allOff();
		return true;
	}
}

void Intake::wristHalt(){
	wristMotor->Set(0.0);
}

void Intake::wristRotate(int reversed){
	wristMotor->Set(reversed * wristSpeed);
}

void Intake::wristForward(){
	if(wristAngle < downLimit - bandWidth){
		wristMotor->Set(wristSpeed);
		printf("Wrist moving fast forward\n");

	} else if (wristAngle < downLimit){
		printf("Wrist moving slow forward\n");

		wristMotor->Set(slowWristSpeed);
	} else {
		printf("Wrist not moving forward\n");
		wristHalt();
	}
}

void Intake::wristBack(){
	if(wristAngle > upwardLimit + bandWidth) {
		wristMotor->Set(-wristSpeed);
		printf("Wrist moving fast back\n");
	} else if (wristAngle > upwardLimit) {
		wristMotor->Set(-slowWristSpeed);
		printf("Wrist moving slow back\n");
	} else {
		wristHalt();
		printf("wrist not moving back\n");
	}
}

void Intake::goToFourtyFive(){
	if (wristAngle > tiltWristAngle + wristTolerance) {
		wristForward();
	} else if (wristAngle < tiltWristAngle - wristTolerance) {
		wristBack();
	} else {
		wristHalt();
	}
}

void Intake::extendIntake(){
	intakeExtension->Set(DoubleSolenoid::kReverse);
}

void Intake::retractIntake(){
	intakeExtension->Set(DoubleSolenoid::kForward);
}


void Intake::spitInner(){
	outputInner();
	takeInOuter();
}


int Intake::getSolenoid(){
	return intakeExtension->Get();
}

void Intake::allOff(){
	intakeInLeft->Set(0.0);
	intakeInRight->Set(0.0);
}

void Intake::putValues(){
	SmartDashboard::PutNumber("Elevator/intakeSpeed", intakeSpeed);
	SmartDashboard::PutNumber("Elevator/spinSpeed", spinSpeed);
	SmartDashboard::PutNumber("Comp/wristSpeed", wristSpeed);
	SmartDashboard::PutNumber("Comp/slowWristSpeed", slowWristSpeed);
	SmartDashboard::PutNumber("Comp/bandWidth", bandWidth);
	SmartDashboard::PutNumber("Comp/downLimit", downLimit);
	SmartDashboard::PutNumber("Comp/upwardLimit", upwardLimit);
	SmartDashboard::PutNumber("Comp/spitCount", spitCount);
}

void Intake::periodicValues(){
	intakeSpeed = SmartDashboard::GetNumber("Elevator/intakeSpeed", intakeSpeed);
	spinSpeed = SmartDashboard::GetNumber("Elevator/spinSpeed", spinSpeed);
	wristSpeed = SmartDashboard::GetNumber("Comp/wristSpeed", wristSpeed);
	slowWristSpeed = SmartDashboard::GetNumber("Comp/slowWristSpeed", slowWristSpeed);
	bandWidth = SmartDashboard::GetNumber("Comp/bandWidth", bandWidth);
	downLimit = SmartDashboard::GetNumber("Comp/downLimit", downLimit);
	upwardLimit = SmartDashboard::GetNumber("Comp/upwardLimit", upwardLimit);
	spitCount = SmartDashboard::GetNumber("Comp/spitCount", spitCount);

	wristAngle = ((int) sensors->getWristAngle() + offset) % 360;
	SmartDashboard::PutNumber("Comp/wristAngle", wristAngle);
}
