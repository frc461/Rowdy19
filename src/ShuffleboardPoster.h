/*
 * ShuffleboardPoster.h
 *
 *  Created on: Jan 21, 2018
 *      Author: hank
 */

#ifndef SRC_SHUFFLEBOARDPOSTER_H_
#define SRC_SHUFFLEBOARDPOSTER_H_

class ShuffleboardPoster {
public:
	ShuffleboardPoster(Encoder*, Encoder*, AHRS*);
	virtual ~ShuffleboardPoster();
	void AutonGet();
	void TeleopGet();
	void ShufflePeriodic();
	void GetOurSwitch();
	void GetOurScale();
	void GetTheirSwitch();

	int initialDist, lTurn1, lTurn2, lDrive3, lDrive2, rTurn1, rTurn2, rDrive3, rDrive2;
private:
	std::string gameData;
	Encoder *leftDriveEncoder;
	Encoder *rightDriveEncoder;
	AHRS *navxBoard
};

#endif /* SRC_SHUFFLEBOARDPOSTER_H_ */
