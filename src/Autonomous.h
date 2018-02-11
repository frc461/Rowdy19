/*
 * Autonomous.h
 *
 *  Created on: Jan 23, 2018
 *      Author: hank
 */

#ifndef AUTONOMOUS_H_
#define AUTONOMOUS_H_
#include <WPILib.h>
#include "DriveTrain.h"
#include "Robot.h"
#include "Sensors.h"
#include "ShuffleboardPoster.h"
#include "Elevator.h"
#include "Intake.h"

class Autonomous {
public:
	Autonomous(DriveTrain&, Sensors&, ShuffleboardPoster&, Elevator&, Intake&);
	void RunAuto();

	void AutonPostValues();
	void AutonPeriodicValues();
	void SwitchFromSide();
	void ScaleFromSide();
	void ScaleFromCenter();
	void SwitchPeriodicValues();
	void ScalePeriodicValues();
	void PutShuffleboardValues();
	void SwitchRightAuto();
	void SwitchLeftAuto();
	void SwitchFromMiddle();
	void Switch();


	void DefaultCross();
	void SetAutoState(int);

private:
	int encoderDist, gyroAngle,
	initDist = 5000,
	lTurn1 = -35,
	lTurn2 = 23,
	lDrive2 = 6000,
	lDrive3 = 2000,
	rTurn1 = 25,
	rTurn2 = -45,
	rDrive2 = 8000,
	rDrive3 = 2000,
	defaultDist = 1750,
	switchSideDist = 4000,
	turnToSwitchAngle = 90,
	driveToSwitchDist = 2500,

	scaleSideDist = 32500,
	faceScaleAngle = 69,
	scaleAdjustDist = 500,

	autoState = InitialStart;

	int drivePastDist = 7000,
	driveAwayDist = 15000;

	int target, startingPosition, ourSwitch, ourScale;



	double autoDriveSpeed, autoTurnSpeed;

	DriveTrain* driveTrain;
	Sensors* sensors;
	ShuffleboardPoster* board;
	Elevator* elevator;
	Intake* intake;
};


#endif /* AUTONOMOUS_H_ */
