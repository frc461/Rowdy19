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


	void teleopGet();
	void shufflePeriodic();
	void generateSelectors();

	double getTeleopDriveSpeedLimit();
	double getTeleopRotateSpeedLimit();
	double getTeleopStrafeSpeedLimit();

	int getOurSwitch();
	int getOurScale();
	int getTheirSideSwitch();
	int getStartingPosition();
	int getTarget();

private:
	SendableChooser<int> target;
	SendableChooser<int> startingPosition;

	std::string gameData;
	DriveTrain* driveTrain;
	Sensors* sensors;	
};

#endif /* SRC_SHUFFLEBOARDPOSTER_H_ */
