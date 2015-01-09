#include <vector>
#include <opencv2\opencv.hpp>
#include "check_imgs.h"
#include "process_imgs.h"
#include "utilities.h"

using namespace std;
using namespace cv;


const char *helper = 
    "check_prepare_imgs.exe <mit2_in_dir> <mit2_out_dir>\n";

const char *subdirs[4] = 
    {"test_carvan", "test_sedantaxi", "train_carvan", "train_sedantaxi"};

const char *filenames[4] = 
    {"file_test_carvan.txt", "file_test_sedantaxi.txt", 
     "file_train_carvan.txt", "file_train_sedantaxi.txt"};

const char *outfiles[6] = 
    {"file_test_carvan.txt", "file_test_sedantaxi.txt", 
     "file_train_carvan.txt", "file_train_sedantaxi.txt",
     "file_test.txt", "file_train.txt"};


int processArguments(int argc, char **argv, char *&mitInDir, char *&mitOutDir);


int main(int argc, char **argv)
{
    vector<ImgInfo> testCarvan, testSedantaxi, trainCarvan, trainSedantaxi;
    char *mitInDir, *mitOutDir;
    Rect maxRectTestCarvan,  maxRectTestSedantaxi, 
         maxRectTrainCarvan, maxRectTrainSedantaxi,
         minRectTestCarvan,  minRectTestSedantaxi, 
         minRectTrainCarvan, minRectTrainSedantaxi;
    double ratioTestCarvan, ratioTrainCarvan, 
        ratioTestSedantaxi, ratioTrainSedantaxi;
    if (processArguments(argc, argv, mitInDir, mitOutDir) != 0)
    {
        return 1;
    }
    
    readImgsInfo(mitInDir, subdirs, filenames, 
        testCarvan, testSedantaxi, trainCarvan, trainSedantaxi);
    /*
    printf("Show test_carvan...\n");
    showBoundingBoxes(testCarvan);
    printf("Show test_sedantaxi...\n");
    showBoundingBoxes(testSedantaxi);
    printf("Show train_carvan...\n");
    showBoundingBoxes(trainCarvan);
    printf("Show train_sedantaxi...\n");
    showBoundingBoxes(trainSedantaxi);
    // */
    
    Rect minBboxTestCarvan, maxBboxTestCarvan;
    printf("test_carvan: \n");
    searchMaxRect(testCarvan, maxRectTestCarvan);
    searchMinRect(testCarvan, minRectTestCarvan);
    computeImgWHRatio(testCarvan, ratioTestCarvan);
    computeBboxWHRatio(testCarvan, ratioTestCarvan, minBboxTestCarvan, 
        maxBboxTestCarvan);
    printf("\tminWidth = %d, minHeigth = %d\n", 
        minRectTestCarvan.width, minRectTestCarvan.height);
    printf("\tmaxWidth = %d, maxHeigth = %d\n", 
        maxRectTestCarvan.width, maxRectTestCarvan.height);
    
    Rect minBboxTestSedantaxi, maxBboxTestSedantaxi;
    printf("test_sedantaxi: \n");
    searchMaxRect(testSedantaxi, maxRectTestSedantaxi);
    searchMinRect(testSedantaxi, minRectTestSedantaxi);
    computeImgWHRatio(testSedantaxi, ratioTestSedantaxi);
    computeBboxWHRatio(testSedantaxi, ratioTestSedantaxi, minBboxTestSedantaxi,
        maxBboxTestSedantaxi);
    printf("\tminWidth = %d, minHeigth = %d\n", 
        minRectTestSedantaxi.width, minRectTestSedantaxi.height);
    printf("\tmaxWidth = %d, maxHeigth = %d\n", 
        maxRectTestSedantaxi.width, maxRectTestSedantaxi.height);
    
    Rect minBboxTrainCarvan, maxBboxTrainCarvan;
    printf("train_carvan: \n");
    searchMaxRect(trainCarvan, maxRectTrainCarvan);
    searchMinRect(trainCarvan, minRectTrainCarvan);    
    computeImgWHRatio(trainCarvan, ratioTrainCarvan);
    computeBboxWHRatio(trainCarvan, ratioTrainCarvan, minBboxTrainCarvan, 
        maxBboxTrainCarvan);
    printf("\tminWidth = %d, minHeigth = %d\n", 
        minRectTrainCarvan.width, minRectTrainCarvan.height);
    printf("\tmaxWidth = %d, maxHeigth = %d\n", 
        maxRectTrainCarvan.width, maxRectTrainCarvan.height);
    
    Rect minBboxTrainSedantaxi, maxBboxTrainSedantaxi;
    printf("train_sedantaxi: \n");
    searchMaxRect(trainSedantaxi, maxRectTrainSedantaxi);
    searchMinRect(trainSedantaxi, minRectTrainSedantaxi);
    computeImgWHRatio(trainSedantaxi, ratioTrainSedantaxi);
    computeBboxWHRatio(trainSedantaxi, ratioTrainSedantaxi, 
        minBboxTrainSedantaxi, maxBboxTrainSedantaxi);
    printf("\tminWidth = %d, minHeigth = %d\n", 
        minRectTrainSedantaxi.width, minRectTrainSedantaxi.height);
    printf("\tmaxWidth = %d, maxHeigth = %d\n", 
        maxRectTrainSedantaxi.width, maxRectTrainSedantaxi.height);

    Rect maxRect;
    searchMaxRect(maxBboxTestCarvan, maxBboxTestSedantaxi, 
        maxBboxTrainCarvan, maxBboxTrainSedantaxi, maxRect);
    printf("\n\nw = %d, h = %d, r = %f\n\n", maxRect.width, maxRect.height,
        ((double)maxRect.width) / ((double)maxRect.height));

    computeCntBboxes(maxRect, testCarvan, testSedantaxi, 
        trainCarvan, trainSedantaxi);
    /*
    printf("Show test_carvan...\n");
    showCntBoundingBoxes(testCarvan);
    printf("Show test_sedantaxi...\n");
    showCntBoundingBoxes(testSedantaxi);
    printf("Show train_carvan...\n");
    showCntBoundingBoxes(trainCarvan);
    printf("Show train_sedantaxi...\n");
    showCntBoundingBoxes(trainSedantaxi);
    // */

    makeBorders(testCarvan, testSedantaxi, trainCarvan, trainSedantaxi);
    resizeImages(testCarvan, testSedantaxi, trainCarvan, trainSedantaxi,
        maxRect.width, maxRect.height);
    /*
    printf("Show test_carvan...\n");
    showImages(testCarvan);
    printf("Show test_sedantaxi...\n");
    showImages(testSedantaxi);
    printf("Show train_carvan...\n");
    showImages(trainCarvan);
    printf("Show train_sedantaxi...\n");
    showImages(trainSedantaxi);
    // */

    saveImgsInfo(mitOutDir, subdirs, outfiles, testCarvan, testSedantaxi, 
        trainCarvan, trainSedantaxi);
    return 0;
}

int processArguments(int argc, char **argv, char *&mitInDir, char *&mitOutDir)
{
    if (argc < 3) 
    {
        printf("Incorrect number of arguments.\n");
        printf("%s", helper);
        return 1;
    }
    mitInDir = argv[1];
    mitOutDir = argv[2];
    return 0;
}
