/*
 * Camera.cpp
 *
 *  Created on: Jan 20, 2018
 *      Author: Beck
 */

#include "Camera.h"


Camera::Camera() {

	currentCam = Cameras::kcam0;
	cam0 = new cs::UsbCamera("cam0", Cameras::kcam1);
	//cam1 = new cs::UsbCamera("cam1", Cameras::kcam1);

	cam0->SetFPS(30);
	//cam1->SetFPS(30);

	cam0->SetResolution(320, 240);
	//cam1->SetResolution(320, 240);

	camOut = CameraServer::GetInstance()->PutVideo("Camera", 320, 240);

	cvSink = new cs::CvSink("cvsink");
	cvSink->SetSource(*cam0);
}

void Camera::cameraPeriodic(bool state){
//	if (state) {
//				currentCam =
//				(currentCam == Cameras::kcam0) ? Cameras::kcam1 : Cameras::kcam0;
//		if (currentCam) {
//			cvSink->SetSource(*cam0);
//		} else {
//			cvSink->SetSource(*cam1);
//		}
//	}
	cvSink->GrabFrame(source);
	if (!source.empty()) {
		rotate(source, source, cv::ROTATE_90_CLOCKWISE);
		camOut.PutFrame(source);
	} else {
		printf("Empty frame\n");
	}
}

