/*
 * Elevator.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: hank
 */

#include <Elevator.h>
#include "Robot.h"

Elevator::Elevator() {
	elevator1 = new VictorSPX(Elevator1CAN);
	elevator2 = new VictorSPX(Elevator2CAN);
	elevator3 = new VictorSPX(Elevator3CAN);
}

void Elevator::goUp(){}

void Elevator::goDown(){}

void Elevator::goToSwitchHeight(){}

void Elevator::goToScaleHeight(){}

void Elevator::goToClimbHeight(){}

void Elevator::goToIntakeExchangeHeight(){}

void Elevator::haltMotion(){}

void Elevator::resetEncoder(){}
