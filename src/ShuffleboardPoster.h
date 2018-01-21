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
	ShuffleboardPoster();
	virtual ~ShuffleboardPoster();
	void AutonGet();
	void TeleopGet();
	void ShufflePeriodic();
	void GetOurSwitch();
	void GetOurScale();
	void GetTheirSwitch();
private:
	std::string gameData;
};

#endif /* SRC_SHUFFLEBOARDPOSTER_H_ */
