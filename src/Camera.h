/*
 * Camera.h
 *
 *  Created on: Jan 20, 2018
 *      Author: Beck (Vaguely)
 */


#include <WPILib.h>
#include "Robot.h"
#include <opencv2/core/core.hpp>



#ifndef CAMERA_H_
#define CAMERA_H_

class Camera {
	public:
		Camera();
		void cameraPeriodic(bool);

	private:
		enum Cameras {
			kcam0 = 0, kcam1
		};
		cv::Mat source;
		cs::UsbCamera *cam0;
//		222222222ssssssssssssssssssssssssscs::UsbCamera *cam1;
		Cameras currentCam;
		cs::CvSink *cvSink;
		cs::CvSource camOut;
};

#endif /* CAMERA_H_ */
