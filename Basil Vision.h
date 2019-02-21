#pragma once


#include <opencv2/core/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <frc/TimedRobot.h>
#include <vector>
using namespace cv;
using namespace std;
class ImageProcess : public frc::TimedRobot {
    void makeGrid(Mat img, int cellSize);
    Mat makeGrid(char *fileName, char *result);
    void RobotInit();
    std::string getPutTextData(int count);
}
