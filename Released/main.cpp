// #include <thread>
// #include "camera.h"
#include "detector.h"
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
// #include "util.h"
// #include "MvCameraControl.h"

int main () {
    Detector detector;

    cv::Mat frame;
    cv::VideoCapture vid(0); // CHANGE THIS ACCORDINGLY!

    if (!vid.isOpened())
    {
         std::cout << "Cannot Open Camera!" << std::endl;
        return -1;
    }

    while(vid.read(frame)){
        std::tuple<float, float> armor_center = detector.DetectLive(frame);
        // ADD PROCESSING CODE HERE !!
    }
    vid.release();

    // destructor for the "detector" somewhere?
}
