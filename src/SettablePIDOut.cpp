/*
 * SetablePIDOut.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: hank
 */

#include <SettablePIDOut.h>

SettablePIDOut::SettablePIDOut() {
	output = 0;
}

void SettablePIDOut::PIDWrite(double output) {
	this->output=output;
}

