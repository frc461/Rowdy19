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

	intakeInLeft = new VictorSPX(LeftInIntakeCAN);
	intakeInRight = new VictorSPX(RightInIntakeCAN);
	intakeOutLeft = new VictorSPX(LeftOutIntakeCAN);
	intakeOutRight = new VictorSPX(RightOutIntakeCAN);

	intakeInRight->Follow(*intakeInLeft);
	intakeInRight->SetInverted(true);

	intakeOutRight->Follow(*intakeOutLeft);
	intakeOutRight->SetInverted(true);
}

void Intake::takeInOuter(){
	intakeOutLeft->Set(ControlMode::PercentOutput, intakeSpeed);
}

void Intake::takeInInner(){
	intakeInLeft->Set(ControlMode::PercentOutput, intakeSpeed);
}

void Intake::takeInAll(){
	takeInOuter();
	takeInInner();
}

void Intake::outputOuter(){
	intakeOutLeft->Set(ControlMode::PercentOutput, -intakeSpeed);
}

void Intake::outputInner(){
	intakeInLeft->Set(ControlMode::PercentOutput, -intakeSpeed);
}

void Intake::outputAll(){
	outputOuter();
	outputInner();
}

void Intake::allOff(){
	intakeOutLeft->Set(ControlMode::PercentOutput, 0.0);
	intakeInLeft->Set(ControlMode::PercentOutput, 0.0);
}

void Intake::PostGetValues(){
	SmartDashboard::PutNumber("intakeSpeed", intakeSpeed);
	SmartDashboard::GetNumber("intakeSpeed", 0.8);

}
