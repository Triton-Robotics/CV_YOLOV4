#include <DarkHelp.hpp>
#include <iostream>
// #include <opencv2/core/core.hpp>
// #include <opencv2/highgui/highgui.hpp>
#include "detector.h"

#define DEBUG 
#define CONFIGFILE "armor.cfg"
#define WEIGHTSFILE "blue_armor.weights"  // change according to the color
#define NAMESFILE "blue_armor.names"      // of the opponent
    
cv::Mat* Detector::addr = NULL;

    Detector::Detector() {

}

// load the neural network (config, weights, and class names)
DarkHelp darkhelp(CONFIGFILE, WEIGHTSFILE, NAMESFILE);

std::tuple<float, float> Detector::DetectLive(cv::Mat &input) {
    int screen_width = 416;
    int screen_height = 416;
    cv::Mat raw;
	//  WE MAY NOT NEED THIS SINCE WE ARE NOT USING THE HIGH SPEED CAMERA
        // camera values     
	    // WARNING: NEED TO BE UPDATED WITH ACTUAL VALUES -----------------------------------------------------------------
// 	    int camera_res[2] = {1280, 1024};
// 	    int camera_fov[2] = {90, 90};
// 	    int camera_midpoint[2] = {camera_res[0]/2, camera_res[1]/2};
	    // WARNING: NEED TO BE UPDATED WITH ACTUAL VALUES -----------------------------------------------------------------
    
    cv::resize(input, raw, cv::Size(screen_width, screen_height));

        // load the neural network (config, weights, and class names)
        // DarkHelp darkhelp(CONFIGFILE, WEIGHTSFILE, NAMESFILE);
	
	// set up variables for choosing armor closest to center
        int center_x = screen_width / 2;
        int center_y = screen_height / 2;
        int final_armor_x = 0;
        int final_armor_y = 0;
        int final_armor_width  = 0;
        int final_armor_height = 0;
        double closest_to_center = DBL_MAX;
        double distance_to_center = DBL_MAX;
        
        darkhelp.sort_predictions = DarkHelp::ESort::kDescending;
        const auto results = darkhelp.predict(raw);
        
        for (const auto & detection : results) {
            // find the armor closest to center
            int armor_x_center = detection.rect.x + detection.rect.width / 2;
            int armor_y_center = detection.rect.y + detection.rect.height / 2;
            distance_to_center = sqrt(pow((center_x - armor_x_center), 2) + pow((center_y - armor_y_center), 2));

            if (distance_to_center < closest_to_center) {
                closest_to_center = distance_to_center;
                final_armor_x = detection.rect.x;
                final_armor_y = detection.rect.y;
                final_armor_width  = detection.rect.width;
                final_armor_height = detection.rect.height;
        }
    }       
            // check if finalarmor is found
            if (closest_to_center != DBL_MAX) {
                #ifdef DEBUG
                cv::Rect rect (final_armor_x, final_armor_y, final_armor_width, final_armor_height);
                cv::rectangle(raw, rect, cv::Scalar(0, 0, 255));
                #endif
                float final_center_x = final_armor_x + final_armor_width / 2;
                float final_center_y = final_armor_y + final_armor_height / 2;
                return std::make_tuple(final_center_x, final_center_y);
		// return x-y coords. of final armor (best armor)  CHANGE THE RETURN INFO. ACCORDINGLY!!
            }
        // return this if final armor not found 
        input = raw;
        return std::make_tuple(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());

    #ifdef DEBUG 
    cv::imshow("armor_plate", raw);
    cv::waitKey(0);
    #endif
}
