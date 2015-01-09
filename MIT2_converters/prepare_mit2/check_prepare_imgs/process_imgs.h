#ifndef __PROCESS_IMGS_H__
#define __PROCESS_IMGS_H__

#include <vector>
#include <opencv2/opencv.hpp>
#include "utilities.h"

using namespace std;
using namespace cv;

int makeBorders(vector<ImgInfo> &imgs);
int makeBorders(vector<ImgInfo> &testCarvan, vector<ImgInfo> &testSedantaxi, 
        vector<ImgInfo> &trainCarvan, vector<ImgInfo> &trainSedantaxi);
int resizeImages(vector<ImgInfo> &imgs, const int width, const int height);
int resizeImages(vector<ImgInfo> &testCarvan, vector<ImgInfo> &testSedantaxi, 
        vector<ImgInfo> &trainCarvan, vector<ImgInfo> &trainSedantaxi,
        const int width, const int height);

#endif
