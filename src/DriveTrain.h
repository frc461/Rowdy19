/*
 * DriveTrain.h
 *
 *  Created on: Jan 20, 2018
 *      Author: Hank Krutulis - 461
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

	//Drive methods
	void arcadeDrive(double, double, double);
	void tankDrive(double, double, double);
	void autonTankDrive(double, double);
	void haltMotion();

	void putValues();
	void periodicValues();
	void calculateStrafeRotate(double);
	void initPID();
	int getEncoderVal(int);
	void resetEncoders();

private:
	double driveSpeed,
	strafeDrift,
	driftConstant = 45,
	straightCorrection,
	turnSpeed,
	strafeSpeed,
	strafeDifference,
	strafeSpeedTolerance,
	strafeAngleTolerance,
	strafeAngle,
	rotateTolerance;

	bool isStrafing;
	double p, i, d, pidoutput, pidAdd, pidMax;;
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
	SensorCollection *leftDriveEncoder;
	SensorCollection *rightDriveEncoder;

	VictorSPX *strafe2;
	TalonSRX *strafe1;
};

#endif /* DRIVETRAIN_H_ */
