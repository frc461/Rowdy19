/*
 * Intake.h
 *
 *  Created on: Jan 27, 2018
 *      Author: hank
 */
#include <WPILib.h>
#include "ctre/Phoenix.h"

#ifndef SRC_INTAKE_H_
#define SRC_INTAKE_H_

class Intake {
public:
	Intake();

	void takeInOuter();
	void takeInInner();
	void takeInAll();

	void outputOuter();
	void outputInner();
	void outputAll();

	void actuateIntake();

	void PostGetValues();

	void allOff();

private:
	double intakeSpeed = 0.8;
	int solenoidStatus;

	DoubleSolenoid* intakeExtension;
	Spark* intakeInLeft;
	Spark* intakeInRight;
	Talon* intakeOutLeft;
	Talon* intakeOutRight;
};

#endif /* SRC_INTAKE_H_ */
