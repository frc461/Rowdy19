/*
 * Intake.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: Hank Krutulis - 461
 */

#include <Intake.h>

Intake::Intake() {
	intakeExtension = new DoubleSolenoid(Intake1, Intake2);
	intakeInLeft = new Victor(LeftInIntakePWM);
	intakeInRight = new Victor(RightInIntakePWM);
	intakeOutLeft = new Spark(LeftOutIntakePWM);
	intakeOutRight = new Spark(RightOutIntakePWM);
	resetSpitCount();
	putValues();
}

void Intake::takeInOuter(){
	intakeOutLeft->Set(-outputSpeed);
	intakeOutRight->Set(outputSpeed);
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
	intakeOutLeft->Set(intakeSpeed);
	intakeOutRight->Set(-intakeSpeed);
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

void Intake::spitCube(){
	if (spitCount < 10){
		outputAll();
		spitCount++;
	} else {
		allOff();
	}
}

void Intake::extendIntake(){
	intakeExtension->Set(DoubleSolenoid::kReverse);
}

void Intake::retractIntake(){
//	intakeExtension->Set(DoubleSolenoid::kForward);
}


void Intake::spitInner(){
	outputInner();
	takeInOuter();
}


int Intake::getSolenoid(){
	return intakeExtension->Get();
}

void Intake::allOff(){
	intakeOutLeft->Set(0.0);
	intakeOutRight->Set(0.0);
	intakeInLeft->Set(0.0);
	intakeInRight->Set(0.0);
}

void Intake::putValues(){
	SmartDashboard::PutNumber("Elevator/intakeSpeed", intakeSpeed);
	SmartDashboard::PutNumber("Elevator/spinSpeed", spinSpeed);
}

void Intake::periodicValues(){
	intakeSpeed = SmartDashboard::GetNumber("Elevator/intakeSpeed", intakeSpeed);
	spinSpeed = SmartDashboard::GetNumber("Elevator/spinSpeed", spinSpeed);
}
