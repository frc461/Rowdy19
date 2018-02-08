/*
 * Intake.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: hank
 */

#include <Intake.h>
#include "Robot.h"

Intake::Intake() {
	intakeExtension = new DoubleSolenoid(Intake1, Intake2);
	intakeInLeft = new Talon(LeftInIntakePWM);
	intakeInRight = new Talon(RightInIntakePWM);
	intakeOutLeft = new Spark(LeftOutIntakePWM);
	intakeOutRight = new Spark(RightOutIntakePWM);
}

void Intake::takeInOuter(){
	intakeOutLeft->Set(-intakeSpeed);
	intakeOutRight->Set(intakeSpeed);
}

void Intake::takeInInner(){
	intakeInLeft->Set(-intakeSpeed);
	intakeInRight->Set(intakeSpeed);
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
	intakeOutLeft->Set(-intakeSpeed);
	intakeOutRight->Set(-intakeSpeed);
	takeInInner();
}

void Intake::spinLeft(){
	intakeOutLeft->Set(intakeSpeed);
	intakeOutRight->Set(intakeSpeed);
	takeInInner();
}

void Intake::extendIntake(){
	intakeExtension->Set(DoubleSolenoid::kForward);
}

void Intake::retractIntake(){
	intakeExtension->Set(DoubleSolenoid::kReverse);
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

void Intake::PostGetValues(){
	SmartDashboard::PutNumber("Intake/intakeSpeed", intakeSpeed);
	intakeSpeed = SmartDashboard::GetNumber("Intake/intakeSpeed", 0.8);
}
