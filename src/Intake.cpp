/*
 * Intake.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: hank
 */

#include <Intake.h>

Intake::Intake() {
	intakeExtension = new DoubleSolenoid(Intake1, Intake2);
	intakeInLeft = new Talon(LeftInIntakePWM);
	intakeInRight = new Talon(RightInIntakePWM);
	intakeOutLeft = new Spark(LeftOutIntakePWM);
	intakeOutRight = new Spark(RightOutIntakePWM);
	putValues();
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
//	intakeExtension->Set(DoubleSolenoid::kReverse);
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
	SmartDashboard::PutNumber("Intake/intakeSpeed", intakeSpeed);
}

void Intake::periodicValues(){
	intakeSpeed = SmartDashboard::PutNumber("Intale/intakeSpeed", 0.8);
}
