/*
 * ShuffleboardPoster.h
 *
 *  Created on: Jan 21, 2018
 *      Author: hank
 */

#ifndef SRC_SHUFFLEBOARDPOSTER_H_
#define SRC_SHUFFLEBOARDPOSTER_H_
#include <WPILib.h>

class ShuffleboardPoster {
public:
	ShuffleboardPoster(Encoder&, Encoder&, ADXRS450_Gyro&);
	void TeleopGet();
	void ShufflePeriodic();
	int GetOurSwitch();
	int GetOurScale();
	int GetTheirSideSwitch();

private:
	std::string gameData;
	Encoder *leftDriveEncoder;
	Encoder *rightDriveEncoder;
	ADXRS450_Gyro *gyro;
};

#endif /* SRC_SHUFFLEBOARDPOSTER_H_ */
