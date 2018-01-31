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
	void GetShuffleboardValues();
	void PutShuffleboardValues();
	void SwitchRightAuto();
	void SwitchLeftAuto();
	void DefaultCross();
	void SetAutoState(int);

private:
	int initDist, lTurn1, lTurn2, lDrive3, lDrive2, rTurn1,
	rTurn2, rDrive3, rDrive2, defaultDist, autoState, ourSwitch;
	double autoDriveSpeed, autoTurnSpeed;

	DriveTrain* driveTrain;
	Sensors* sensors;
};

#endif /* AUTONOMOUS_H_ */
