#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include <stdio.h>
#include <iostream>
#include <direct.h>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;


enum VehicleClass
{
    CAR = 0,
    VAN = 1,
    SEDAN = 2,
    TAXI = 3,
    NONE = -1
};

struct ImgInfo
{
    char name[10];
    VehicleClass vehicleClass;
    Rect bbox;
    Rect cntBbox;
    int d_top, d_bot, d_left, d_right;
    double diff, ratio;
    Mat img, cntImg;
};

VehicleClass convertVehicleClass(char *className);

int readImgsInfo(char *fileName, char *imgsDirName, vector<ImgInfo> &imgsInfo);
int readImgsInfo(char *mitInDir, const char *subDirs[], 
        const char *fileNames[],
        vector<ImgInfo> &testCarvan, vector<ImgInfo> &testSedantaxi, 
        vector<ImgInfo> &trainCarvan, vector<ImgInfo> &trainSedantaxi);

int saveImgsInfo(char *imgsDirName,  char *fileName, const char *subDir, 
        const vector<ImgInfo> &imgsInfo);
int saveImgsInfo(const char *fileName, const char *subDirCarvan, 
        const char *subDirSedantaxi, const vector<ImgInfo> &carvan, 
        const vector<ImgInfo> &sedantaxi);
int saveImgsInfo(char *mitOutDir, const char *subDirs[], 
        const char *fileNames[],
        const vector<ImgInfo> &testCarvan, 
        const vector<ImgInfo> &testSedantaxi, 
        const vector<ImgInfo> &trainCarvan, 
        const vector<ImgInfo> &trainSedantaxi);

#endif
