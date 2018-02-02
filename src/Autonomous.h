/*
 * Autonomous.h
 *
 *  Created on: Jan 23, 2018
 *      Author: hank
 */

#ifndef AUTONOMOUS_H_
#define AUTONOMOUS_H_
#include "DriveTrain.h"
#include "Robot.h"
#include "Sensors.h"

class Autonomous {
public:
	Autonomous(DriveTrain&, Sensors&);
	void AutonPostValues();
	void AutonPeriodicValues();
	void SwitchPeriodicValues();
	void ScalePeriodicValues();
	void PutShuffleboardValues();
	void SwitchRightAuto();
	void SwitchLeftAuto();
	void ScaleRightAuto();
	void ScaleLeftAuto();

	void DefaultCross();
	void SetAutoState(int);

private:
	int initDist = 2000,
	lTurn1 = -55,
	lTurn2 = 3000,
	lDrive3 = 55,
	lDrive2 = 2000,
	rTurn1 = 55,
	rTurn2 = -45,
	rDrive2 = 4000,
	rDrive3 = 2000,
	defaultDist = 1750,
	autoState = InitialStart;

	int drivePastDist = 7000,
	driveAwayDist = 15000;


	double autoDriveSpeed, autoTurnSpeed;

	DriveTrain* driveTrain;
	Sensors* sensors;
};

#endif /* AUTONOMOUS_H_ */
