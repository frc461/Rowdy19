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
}

void Intake::takeInOuter(){}
void Intake::takeInInner(){}
void Intake::takeInAll(){}

void Intake::outputOuter(){}
void Intake::outputInner(){}
void Intake::outputAll(){}

void Intake::allOff(){}

