#include "check_imgs.h"

int searchMaxRect(const Rect &rect1, const Rect &rect2, 
        const Rect &rect3, const Rect &rect4, Rect &maxRect)
{
    double maxRatio = ((double) rect1.width) / ((double) rect1.height), 
           ratio = ((double) rect2.width) / ((double) rect2.height);
    maxRect = rect1;
    if (ratio > maxRatio) 
    {
        maxRatio = ratio;
        maxRect = rect2;
    }
    ratio = ((double) rect3.width) / ((double) rect3.height);
    if (ratio > maxRatio) 
    {
        maxRatio = ratio;
        maxRect = rect3;
    }
    ratio = ((double) rect4.width) / ((double) rect4.height);
    if (ratio > maxRatio) 
    {
        maxRatio = ratio;
        maxRect = rect4;
    }
    return 0;
}

int searchMaxRect(const vector<ImgInfo> &imgs, Rect &bbox)
{
    int maxWidth = imgs[0].bbox.width, maxHeight = imgs[0].bbox.height; 
    for (int i = 1; i < imgs.size(); i++)
    {
        if (imgs[i].bbox.width > maxWidth)
        {
            maxWidth = imgs[i].bbox.width;
        }
        if (imgs[i].bbox.height > maxHeight)
        {
            maxHeight = imgs[i].bbox.height;
        }
    }
    bbox.width = maxWidth;
    bbox.height = maxHeight;
    return 0;
}

int searchMinRect(const vector<ImgInfo> &imgs, Rect &bbox)
{
    int minWidth = imgs[0].bbox.width, minHeight = imgs[0].bbox.height; 
    for (int i = 1; i < imgs.size(); i++)
    {
        if (imgs[i].bbox.width < minWidth)
        {
            minWidth = imgs[i].bbox.width;
        }
        if (imgs[i].bbox.height < minHeight)
        {
            minHeight = imgs[i].bbox.height;
        }
    }
    bbox.width = minWidth;
    bbox.height = minHeight;
    return 0;
}

int showBoundingBoxes(const vector<ImgInfo> &imgs)
{
    const char *winName = "bbox";
    char key = -1;
    Scalar color(255, 0, 0);
    Mat initImg;
    Rect bbox;
    namedWindow(winName);
    for (int i = 0; i < imgs.size() && key != 27; i++)
    {
        imgs[i].img.copyTo(initImg);
        bbox = imgs[i].bbox;
        rectangle(initImg, bbox, color, 1, 8, 0);
        imshow(winName, initImg);
        key = waitKey();
    }
    destroyAllWindows();
    return 0;
}

int showCntBoundingBoxes(const vector<ImgInfo> &imgs)
{
    const char *winName = "cnt_bbox";
    char key = -1;
    Scalar color(255, 0, 0);
    Mat initImg;
    Rect bbox;
    namedWindow(winName);
    for (int i = 0; i < imgs.size() && key != 27; i++)
    {
        imgs[i].img.copyTo(initImg);
        bbox = imgs[i].cntBbox;
        rectangle(initImg, bbox, color, 1, 8, 0);
        imshow(winName, initImg);
        key = waitKey();
    }
    destroyAllWindows();
    return 0;
}

int showImages(const vector<ImgInfo> &imgs)
{
    const char *winName = "dst";
    char key = -1;
    Mat initImg;
    namedWindow(winName);
    for (int i = 0; i < imgs.size() && key != 27; i++)
    {
        imshow(winName, imgs[i].img);
        key = waitKey();
    }
    destroyAllWindows();
    return 0;
}

int computeImgWHRatio(const vector<ImgInfo> &imgs, double &ratioRes)
{
    double ratio = ((double) imgs[0].img.cols) / imgs[0].img.rows, 
           maxRatio = ratio, minRatio = ratio;
    ratioRes = 0.0;
    for (int i = 1; i < imgs.size(); i++)
    {
        ratio = ((double) imgs[i].img.cols) / imgs[i].img.rows;
        ratioRes += ratio;
        if (ratio < minRatio) minRatio = ratio;
        if (ratio > maxRatio) maxRatio = ratio;
    }
    ratioRes /= imgs.size();
    printf("\tImage: minRatio = %f, maxRatio = %f, avrRatio = %f\n", 
        minRatio, maxRatio, ratioRes);
    return 0;
}

int computeBboxWHRatio(const vector<ImgInfo> &imgs, double &ratioRes, 
        Rect &minBbox, Rect &maxBbox)
{
    double ratio = ((double) imgs[0].bbox.width) / imgs[0].bbox.height, 
           maxRatio = ratio, minRatio = ratio;
    minBbox = imgs[0].bbox;
    maxBbox = imgs[0].bbox;
    ratioRes = 0.0;
    for (int i = 1; i < imgs.size(); i++)
    {
        ratio = ((double) imgs[i].bbox.width) / imgs[i].bbox.height;
        ratioRes += ratio;
        if (ratio < minRatio) 
        {
            minRatio = ratio;
            minBbox = imgs[i].bbox;
        }
        if (ratio > maxRatio) 
        {
            maxRatio = ratio;
            maxBbox = imgs[i].bbox;
        }
    }
    ratioRes /= imgs.size();
    printf("\tBbox:  minRatio = %f, maxRatio = %f, avrRatio = %f\n", 
        minRatio, maxRatio, ratioRes);
    return 0;
}

int computeCntBbox(const double ratio, ImgInfo &imgInfo)
{
    int wi = imgInfo.bbox.width, hi = imgInfo.bbox.height,
        width = imgInfo.img.size().width, 
        heigth = imgInfo.img.size().height,
        xi_c = imgInfo.bbox.x + (wi + 1) / 2,
        yi_c = imgInfo.bbox.y + (hi + 1) / 2;
    double r = ((double) wi) / ((double) hi);
    double minRatio = abs(r - ratio);
    imgInfo.cntBbox.x = imgInfo.bbox.x;
    imgInfo.cntBbox.y = imgInfo.bbox.y;
    imgInfo.cntBbox.width = wi;
    imgInfo.cntBbox.height = hi;
    for (int w = wi; w <= 3 * xi_c; w++)
    {
        for (int h = hi; h <= 3 * yi_c; h++)
        {
            int xi_n, yi_n, xi_n_r, yi_n_r, 
                d_top = 0, d_bot = 0, d_right = 0, d_left = 0;
            xi_n = xi_c - (w + 1) / 2;
            xi_n_r = xi_n + w; 
            if (xi_n < 0) 
            {
                d_left = abs(xi_n);
                xi_n = 0;
            }
            yi_n = yi_c - (h + 1) / 2;
            yi_n_r = yi_n + h;
            if (yi_n < 0)
            {
                d_top = abs(yi_n);
                yi_n = 0;
            }
            if (xi_n_r >= width)
            {
                d_right = abs(width - xi_n_r - 1);
                xi_n_r = width - 1;
            }
            if (yi_n_r >= heigth)
            {
                d_bot = abs(heigth - yi_n_r - 1);
                yi_n_r = heigth - 1;
            }
            r = ((double) w) / ((double) h);
            if (abs(r - ratio) <= minRatio)
            {
                imgInfo.cntBbox.x = xi_n;
                imgInfo.cntBbox.y = yi_n;
                imgInfo.cntBbox.width = xi_n_r - xi_n;
                imgInfo.cntBbox.height = yi_n_r - yi_n;
                imgInfo.d_top = d_top;                
                imgInfo.d_bot = d_bot;
                imgInfo.d_left = d_left;
                imgInfo.d_right = d_right;
                imgInfo.diff = r - ratio;
                minRatio = abs(imgInfo.diff);
            }
        }
    }
    imgInfo.ratio = 
        ((double) (imgInfo.cntBbox.width + imgInfo.d_left + imgInfo.d_right)) / 
        ((double) (imgInfo.cntBbox.height + imgInfo.d_top + imgInfo.d_bot));
    // /*        
    printf("%.4f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%.4f\n", imgInfo.diff, 
        imgInfo.cntBbox.x, imgInfo.cntBbox.y,
        imgInfo.cntBbox.width, imgInfo.cntBbox.height,
        imgInfo.d_left, imgInfo.d_right, imgInfo.d_top, imgInfo.d_bot,
        imgInfo.ratio);
    //*/
    return 0;
}

int computeCntBboxes(const Rect &maxBbox, vector<ImgInfo> &imgs)
{
    double ratio = ((double) maxBbox.width) / ((double) maxBbox.height);
    // /*
    printf("diff\tx\ty\tw\th\tl\tr\tt\tb\tratio\n");
    // */
    for (int i = 0; i < imgs.size(); i++)
    {
        computeCntBbox(ratio, imgs[i]); 
    }
    return 0;
}

int computeCntBboxes(const Rect &maxBbox, 
        vector<ImgInfo> &testCarvan, vector<ImgInfo> &testSedantaxi, 
        vector<ImgInfo> &trainCarvan, vector<ImgInfo> &trainSedantaxi)
{
    printf("test_carvan:\n");
    computeCntBboxes(maxBbox, testCarvan);
    printf("test_sedantaxi:\n");
    computeCntBboxes(maxBbox, testSedantaxi);
    printf("train_carvan:\n");
    computeCntBboxes(maxBbox, trainCarvan);
    printf("train_sedantaxi:\n");
    computeCntBboxes(maxBbox, trainSedantaxi);
    return 0;
}
