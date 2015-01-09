#include "process_imgs.h"

int makeBorders(vector<ImgInfo> &imgs)
{
    for (int i = 0; i < imgs.size(); i++)
    {
        copyMakeBorder(imgs[i].img, imgs[i].cntImg, imgs[i].d_top, 
            imgs[i].d_bot, imgs[i].d_left, imgs[i].d_right, BORDER_REPLICATE);
    }
    return 0;
}

int makeBorders(vector<ImgInfo> &testCarvan, vector<ImgInfo> &testSedantaxi, 
        vector<ImgInfo> &trainCarvan, vector<ImgInfo> &trainSedantaxi)
{
    makeBorders(testCarvan);
    makeBorders(testSedantaxi);
    makeBorders(trainCarvan);
    makeBorders(trainSedantaxi);
    return 0;
}

int resizeImages(vector<ImgInfo> &imgs, const int width, const int height)
{
    Size size(width, height);
    for (int i =0; i < imgs.size(); i++)
    {
        resize(imgs[i].cntImg, imgs[i].img, size, 0.0, 0.0, INTER_LANCZOS4);
    }
    return 0;
}

int resizeImages(vector<ImgInfo> &testCarvan, vector<ImgInfo> &testSedantaxi, 
        vector<ImgInfo> &trainCarvan, vector<ImgInfo> &trainSedantaxi, 
        const int width, const int height)
{
    resizeImages(testCarvan, width, height);
    resizeImages(testSedantaxi, width, height);
    resizeImages(trainCarvan, width, height);
    resizeImages(trainSedantaxi, width, height);
    return 0;
}
