/*
 * DriveTrain.h
 *
 *  Created on: Jan 20, 2018
 *      Author: Hank Krutulis
 */

#ifndef DRIVETRAIN_H_
#define DRIVETRAIN_H_
#include <WPILib.h>
#include "ctre/Phoenix.h"
#include "Sensors.h"
#include "Robot.h"
#include "SettablePIDOut.h"
#include "SettablePIDSource.hpp"

class DriveTrain {
public:
	DriveTrain(Sensors&);
	void ArcadeDrive(double, double, double);
	void TankDrive(double, double, double);
	void PutValues();
	void GetValues();
	void CalculateStrafeRotate(double);
	void InitPID();
//	PowerDistributionPanel GetPDP();
private:
	double driveSpeed, turnSpeed, strafeSpeed, strafeDifference, strafeTolerance, strafeAngle;
	bool isStrafing;
	double p, i, d, pidoutput, pidAdd, pidMax;
	PIDController* pid;
	SettablePIDOut* pidout;
	SettablePIDSource* pidsrc;

	Sensors* sensors;
	PowerDistributionPanel *pdp;
	DifferentialDrive *driveTrain;
	WPI_TalonSRX *rightDrive1;
	WPI_VictorSPX *rightDrive2;
	WPI_VictorSPX *rightDrive3;
	WPI_TalonSRX *leftDrive1;
	WPI_VictorSPX *leftDrive2;
	WPI_VictorSPX *leftDrive3;
	VictorSPX *strafe1;
	TalonSRX *strafe2;
};

#endif /* DRIVETRAIN_H_ */
