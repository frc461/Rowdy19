/*
 * Elevator.h
 *
 *  Created on: Jan 27, 2018
 *      Author: hank
 */
#include <WPILib.h>
#include "ctre/Phoenix.h"

#ifndef SRC_ELEVATOR_H_
#define SRC_ELEVATOR_H_

class Elevator {
public:
	Elevator();
	void goUp();
	void goDown();
	void goToSwitchHeight();
	void goToScaleHeight();
	void goToClimbHeight();
	void goToIntakeExchangeHeight();
	void haltMotion();
	void resetEncoder();

private:
	VictorSPX* elevator1;
	VictorSPX* elevator2;
	VictorSPX* elevator3;
};

#endif /* SRC_ELEVATOR_H_ */
