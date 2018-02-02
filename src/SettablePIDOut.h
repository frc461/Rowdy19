/*
 * SetablePIDOut.h
 *
 *  Created on: Jan 25, 2018
 *      Author: hank
 */

#ifndef SRC_SETTABLEPIDOUT_H_
#define SRC_SETTABLEPIDOUT_H_
#include "WPILib.h"

class SettablePIDOut: public PIDOutput{
public:
	double output;
	SettablePIDOut();

	void PIDWrite(double output);
};

#endif /* SRC_SETTABLEPIDOUT_H_ */
