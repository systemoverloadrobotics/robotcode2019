#pragma once


#include <opencv2/core/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <frc/TimedRobot.h>
#include <vector>

using namespace cv;
using namespace std;

class ImageProcess : public frc::TimedRobot {
    public:
    vector<Point> imageComparation(Mat object, Mat scene, int match_method, float peek_percent) ;
    double angle( Point pt1, Point pt2, Point pt0 );
    void findSquares( const Mat& image, vector<vector<Point> >& squares );
    void drawSquares( Mat& image, const vector<vector<Point> >& squares );
    void findLines();
    void deskew(const char* filename, double angle);
    void findLines1(char *filename);
    void makeSquare(char *fileName, char *result);
    void makeGrid(Mat img, int cellSize);
    Mat makeGrid(char *fileName, char *result);
    void RobotInit();
    std::string getPutTextData(int count);
};
