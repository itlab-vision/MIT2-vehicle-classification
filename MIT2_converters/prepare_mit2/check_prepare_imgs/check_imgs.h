#ifndef __CHECK_IMGS_H__
#define __CHECK_IMGS_H__

#include <vector>
#include <opencv2/opencv.hpp>
#include "utilities.h"

using namespace std;
using namespace cv;

int searchMaxRect(const Rect &rect1, const Rect &rect2, 
        const Rect &rect3, const Rect &rect4, Rect &maxRect);
int searchMaxRect(const vector<ImgInfo> &imgs, Rect &bbox);
int searchMinRect(const vector<ImgInfo> &imgs, Rect &bbox);

int showBoundingBoxes(const vector<ImgInfo> &imgs);
int showCntBoundingBoxes(const vector<ImgInfo> &imgs);
int showImages(const vector<ImgInfo> &imgs);

int computeImgWHRatio(const vector<ImgInfo> &imgs, double &ratioRes);
int computeBboxWHRatio(const vector<ImgInfo> &imgs, double &ratioRes, 
        Rect &minBbox, Rect &maxBbox);

int computeCntBboxes(const Rect &maxBbox, vector<ImgInfo> &imgs);
int computeCntBboxes(const Rect &maxBbox, 
        vector<ImgInfo> &testCarvan, vector<ImgInfo> &testSedantaxi, 
        vector<ImgInfo> &trainCarvan, vector<ImgInfo> &trainSedantaxi);

#endif
