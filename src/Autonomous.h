/*
 * Autonomous.h
 *
 *  Created on: Jan 23, 2018
 *      Author: hank
 */

#ifndef AUTONOMOUS_H_
#define AUTONOMOUS_H_

class Autonomous {
public:
	Autonomous();
	void GetShuffleboardValues();
	void SwitchRightAuto(double, double);
	void SwitchLeftAuto(double, double);
private:
	int initialDist, lTurn1, lTurn2, lDrive3, lDrive2, rTurn1, rTurn2, rDrive3, rDrive2, 
	double autoDriveSpeed, autoTurnSpeed;
};

#endif /* AUTONOMOUS_H_ */
