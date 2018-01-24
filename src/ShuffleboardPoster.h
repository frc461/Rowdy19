/*
 * ShuffleboardPoster.h
 *
 *  Created on: Jan 21, 2018
 *      Author: hank
 */

#ifndef SRC_SHUFFLEBOARDPOSTER_H_
#define SRC_SHUFFLEBOARDPOSTER_H_
#include <WPILib.h>
#include "Sensors.h"
#include "DriveTrain.h"

class ShuffleboardPoster {
public:
	ShuffleboardPoster(DriveTrain&, Sensors&);
	void TeleopGet();
	void ShufflePeriodic();
	int GetOurSwitch();
	int GetOurScale();
	int GetTheirSideSwitch();

private:
	std::string gameData;
	DriveTrain* driveTrain;
	Sensors* sensors;	
};

#endif /* SRC_SHUFFLEBOARDPOSTER_H_ */
