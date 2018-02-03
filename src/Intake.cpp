/*
 * Intake.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: hank
 */

#include <Intake.h>
#include "Robot.h"

Intake::Intake() {
	intakeExtension = new DoubleSolenoid(0,1);
	solenoidStatus = Undetermined;

	intakeInLeft = new Spark(LeftInIntakePWM);
	intakeInRight = new Spark(RightInIntakePWM);
	intakeOutLeft = new Talon(LeftOutIntakePWM);
	intakeOutRight = new Talon(RightOutIntakePWM);

}

void Intake::takeInOuter(){
	intakeOutLeft->Set(intakeSpeed);
	intakeOutRight->Set(-intakeSpeed);
}

void Intake::takeInInner(){
	intakeInLeft->Set(intakeSpeed);
	intakeInRight->Set(-intakeSpeed);
}

void Intake::takeInAll(){
	takeInOuter();
	takeInInner();
}

void Intake::outputOuter(){
	intakeOutLeft->Set(-intakeSpeed);
	intakeOutRight->Set(intakeSpeed);
}

void Intake::outputInner(){
	intakeInLeft->Set(-intakeSpeed);
	intakeInRight->Set(intakeSpeed);
}

void Intake::outputAll(){
	outputOuter();
	outputInner();
}

void Intake::actuateIntake(){
	if(solenoidStatus == Out){
		intakeExtension->Set(DoubleSolenoid::kReverse);
		solenoidStatus = In;
	} else {
		intakeExtension->Set(DoubleSolenoid::kForward);
		solenoidStatus = Out;
	}
}


void Intake::allOff(){
	intakeOutLeft->Set(0.0);
	intakeOutRight->Set(0.0);
	intakeInLeft->Set(0.0);
	intakeInRight->Set(0.0);
}

void Intake::PostGetValues(){
	SmartDashboard::PutNumber("intakeSpeed", intakeSpeed);
	intakeSpeed = SmartDashboard::GetNumber("intakeSpeed", 0.8);
}
