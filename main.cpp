// #include <thread>
// #include "camera.h"
// #include "util.h"
// #include "MvCameraControl.h"

#include <DarkHelp.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include "detector.h"
// #define CONFIGFILE "armor.cfg"
// #define WEIGHTSFILE "blue_armor.weights"  // change according to the color
// #define NAMESFILE "blue_armor.names"      // of the opponent

// input format: ./detector "config file" "weights file" "name file" "input name"
int main (int argc, char *argv[]) {
    Detector detector;
    DarkHelp darkhelp(argv[1], argv[2], argv[3]);

    cv::Mat frame;
    cv::VideoCapture vid(argv[4]); // CHANGE THIS ACCORDINGLY!

    if (!vid.isOpened())
    {
         std::cout << "Cannot Open Camera!" << std::endl;
        return -1;
    }

    while(vid.read(frame)){
        // std::tuple<float, float> armor_center = detector.DetectLive(frame, darkhelp);
        detector.DetectLive(frame, darkhelp);
        // std::cout << armor_center << std::endl;
        // ADD PROCESSING CODE HERE !!
    }
    vid.release();
}