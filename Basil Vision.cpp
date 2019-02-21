/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <thread>

#include "ImageProcess.h"
#include <cameraserver/CameraServer.h>
#include <frc/TimedRobot.h>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <wpi/raw_ostream.h>

/**
 * This is a demo program showing the use of OpenCV to do vision processing. The
 * image is acquired from the USB camera, then a rectangle is put on the image
 * and sent to the dashboard. OpenCV has many methods for different types of
 * processing.
 */
class Robot : public frc::TimedRobot {
#if defined(__linux__)

 private:
  static void VisionThread() {
    // Get the USB camera from CameraServer
    cs::UsbCamera camera =
        frc::CameraServer::GetInstance()->StartAutomaticCapture();
    // Set the resolution
    camera.SetResolution(640, 480);

    // Get a CvSink. This will capture Mats from the Camera
    cs::CvSink cvSink = frc::CameraServer::GetInstance()->GetVideo();
    // Setup a CvSource. This will send images back to the Dashboard
    cs::CvSource outputStream =
        frc::CameraServer::GetInstance()->PutVideo("Rectangle", 640, 480);

    // Mats are very memory expensive. Lets reuse this Mat.
    cv::Mat mat;

    while (true) {
      // Tell the CvSink to grab a frame from the camera and
      // put it
      // in the source mat.  If there is an error notify the
      // output.
      if (cvSink.GrabFrame(mat) == 0) {
        // Send the output the error.
        outputStream.NotifyError(cvSink.GetError());
        // skip the rest of the current iteration
        continue;
      }
      // Put a rectangle on the image
      rectangle(mat, cv::Point(100, 100), cv::Point(400, 400),
                cv::Scalar(255, 255, 255), 5);
      // Give the output stream a new image to display
      outputStream.PutFrame(mat);
    }
  }
#endif

  void RobotInit() override {
  // We need to run our vision program in a separate thread. If not, our robot
  // program will not run.
#if defined(__linux__)
    std::thread visionThread(VisionThread);
    visionThread.detach();
#else
    wpi::errs() << "Vision only available on Linux.\n";
    wpi::errs().flush();
#endif
  }
};

/*std::string ImageProcess::getPutTextData(int count){
      if (count == 1){
          return "---";
      }else if (count == 2){
          return std::to_string(0);
      }else if(count == 3){
          return std::to_string(0.3);
      }else if(count == 4){
          return std::to_string(0.5);
      }else if(count == 5){
          return std::to_string(0.7);
      }else if(count == 6){
          return std::to_string(0.9);
      }else if(count == 7){
          return std::to_string(1.2);
      }else if(count == 8){
          return std::to_string(1.5);
      }else if(count == 9){
          return std::to_string(1.7);
      }else if(count == 10){
          return std::to_string(2);
      }else if(count == 11){
          return std::to_string(2.2) ;
      }else if(count == 12){
          return std::to_string(2.4);
      }else if(count == 13){
          return std::to_string(2.8);
      }else if(count == 14){
          return std::to_string(3.1);
      }else if(count == 15){
          return std::to_string(3.4);
      }else if(count == 16){
          return std::to_string(3.6);
      }else {
          return "-";
      }
  }*/

  void ImageProcess::makeGrid(Mat img, int cellSize) {

    int dist= cellSize;
    int width= img.size().width;
    int height= img.size().height;

    //b g r
    cv::Scalar lineColor(0, 0, 0, 0);
    cv::Scalar centerColor(0, 0, 255, 0);
    cv::Scalar textColor(0, 255, 0, 0);

    int midWidth = width /2;
    int midHeight = height /2;
    
    int lineNum = (height - midHeight) / dist;
    int count = lineNum;
    for (int bHeigth = midHeight; bHeigth<height; bHeigth += dist) {
      cv::line(img, Point(0, bHeigth), Point(width, bHeigth), lineColor);
      putText(img, std::to_string(count), cvPoint(midWidth-cellSize*5, bHeigth+dist), CV_FONT_HERSHEY_SIMPLEX, 0.5, textColor, 1, cv::LINE_8);
      putText(img, std::to_string(count--), cvPoint(midWidth+cellSize*4, bHeigth+dist), CV_FONT_HERSHEY_SIMPLEX, 0.5, textColor, 1, cv::LINE_8);
      std::string putTextData = getPutTextData(count);//std::to_string(count);
      /*if (count % 2 == 0 ){
        putTextData = "";
      }*/
      /*putText(img, putTextData, cvPoint(midWidth-cellSize*7, bHeigth+dist), CV_FONT_HERSHEY_SIMPLEX, 0.5, textColor, 1, cv::LINE_8);
      putText(img, putTextData, cvPoint(midWidth+cellSize*6, bHeigth+dist), CV_FONT_HERSHEY_SIMPLEX, 0.5, textColor, 1, cv::LINE_8);
      count = count - 1;*/
    }
  };
    /*count = ++lineNum;
    for (int uHeight = midHeight; uHeight>0; uHeight -= dist) {
      cv::line(img, Point(0, uHeight), Point(width, uHeight),lineColor);
      putText(img, std::to_string(count), cvPoint(midWidth-cellSize*5, uHeight), CV_FONT_HERSHEY_SIMPLEX, 0.5, textColor, 1, cv::LINE_8);
      putText(img, std::to_string(count++), cvPoint(midWidth+cellSize*4, uHeight), CV_FONT_HERSHEY_SIMPLEX, 0.5, textColor, 1, cv::LINE_8);
      std::string putTextData = std::to_string(count);
      /*if (count % 2 == 0){
          putTextData = "";
      }*/
      /*putText(img, putTextData, cvPoint(midWidth-cellSize*7, uHeight), CV_FONT_HERSHEY_SIMPLEX, 0.5, textColor, 1, cv::LINE_8);
      putText(img, putTextData, cvPoint(midWidth+cellSize*6, uHeight), CV_FONT_HERSHEY_SIMPLEX, 0.5, textColor, 1, cv::LINE_8);
      count = count + 1;
    }

    cv::line(img, Point(0, midHeight), Point(width, midHeight), centerColor,2);
    for (int lWidth = midWidth; lWidth>0; lWidth -= dist) 
      cv::line(img, Point(lWidth, 0), Point(lWidth, height), lineColor);
    for (int rWidth = midWidth; rWidth<width; rWidth += dist) 
      cv::line(img, Point(rWidth, 0), Point(rWidth, height), lineColor);
    cv::line(img, Point(midWidth, 0), Point(midWidth, height), centerColor,2);
    //for (int i = 0; i<width; i += dist) 
    //  cv::line(img, Point(i, 0), Point(i, height), cv::Scalar(255, 0, 0));
  }*/
  /*Mat ImageProcess::makeGrid(char *fileName, char *result) {
    cv::Mat img = cv::imread(fileName, 0);
    makeGrid(img, 10
    );
    imwrite(result, img);
  }*/
#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
