#include "utilities.h"

VehicleClass convertVehicleClass(char *className)
{
    VehicleClass vehicleClass;
    if (strcmp(className, "car") == 0)
    {
        vehicleClass = CAR;
    }
    else if (strcmp(className, "van") == 0)
    {
        vehicleClass = VAN;
    }
    else if (strcmp(className, "taxi") == 0)
    {
        vehicleClass = TAXI;
    }
    else if (strcmp(className, "sedan") == 0)
    {
        vehicleClass = SEDAN;
    }
    else
    {
        vehicleClass = NONE;
    }
    return vehicleClass;
}

int readImgsInfo(char *fileName, char *imgsDirName, vector<ImgInfo> &imgsInfo)
{
    char className[10], imgName[255];
    int x1, y1, x2, y2;
    FILE *f = fopen(fileName, "r");
    if (f == 0)
    {
        printf("File %s was not opened.\n");
        return 1;
    }
    while (!feof(f))
    {
        ImgInfo imgInfo;
        fscanf(f, "%s %s %d %d %d %d", &imgInfo.name, &className, 
            &x1, &y1, &x2, &y2);
        imgInfo.vehicleClass = convertVehicleClass(className);
        imgInfo.img = imread(strcat(strcat(strcpy(imgName, imgsDirName), 
            imgInfo.name), ".bmp"));
        imgInfo.bbox.x = (x1 - 4 < 0) ? 0 : x1 - 4;
        imgInfo.bbox.y = (y1 - 4 < 0) ? 0 : y1 - 4;
        x2 = (x2 + 8 > imgInfo.img.cols) ? imgInfo.img.cols : x2 + 8;
        y2 = (y2 + 3 > imgInfo.img.rows) ? imgInfo.img.rows : y2 + 3;
        imgInfo.bbox.width  = x2 - imgInfo.bbox.x;
        imgInfo.bbox.height = y2 - imgInfo.bbox.y;
        imgsInfo.push_back(imgInfo);
    }
    fclose(f);
    return 0;
}

int readImgsInfo(char *mitInDir, const char *subDirs[], 
    const char *fileNames[],
    vector<ImgInfo> &testCarvan, vector<ImgInfo> &testSedantaxi, 
    vector<ImgInfo> &trainCarvan, vector<ImgInfo> &trainSedantaxi)
{
    char imgsDirName[255], strtmp[255];
    strcat(strcat(strcat(strcpy(strtmp, mitInDir), subDirs[0]), "/"), fileNames[0]);
    strcat(strcat(strcat(strcat(strcat(strcpy(imgsDirName, mitInDir), 
        subDirs[0]), "/"), subDirs[0]), "_img"), "/");
    readImgsInfo(strtmp, imgsDirName, testCarvan);

    strcat(strcat(strcat(strcpy(strtmp, mitInDir), subDirs[1]), "/"), fileNames[1]);
    strcat(strcat(strcat(strcat(strcat(strcpy(imgsDirName, mitInDir), 
        subDirs[1]), "/"), subDirs[1]), "_img"), "/");
    readImgsInfo(strtmp, imgsDirName, testSedantaxi);

    strcat(strcat(strcat(strcpy(strtmp, mitInDir), subDirs[2]), "/"), fileNames[2]);
    strcat(strcat(strcat(strcat(strcat(strcpy(imgsDirName, mitInDir), 
        subDirs[2]), "/"), subDirs[2]), "_img"), "/");
    readImgsInfo(strtmp, imgsDirName, trainCarvan);

    strcat(strcat(strcat(strcpy(strtmp, mitInDir), subDirs[3]), "/"), fileNames[3]);
    strcat(strcat(strcat(strcat(strcat(strcpy(imgsDirName, mitInDir), 
        subDirs[3]), "/"), subDirs[3]), "_img"), "/");
    readImgsInfo(strtmp, imgsDirName, trainSedantaxi);
    return 0;
}

bool dirExists(const wchar_t *fname)
{
    if (fname == NULL || wcslen(fname) == 0)
    {
        return false;
    }
    DWORD dwAttrs = ::GetFileAttributesW(fname);
    if (dwAttrs == DWORD(-1))
    {
        DWORD dLastError = GetLastError();
        if (ERROR_TOO_MANY_NAMES == dLastError || 
            ERROR_SHARING_VIOLATION == dLastError || 
            ERROR_TOO_MANY_SESS == dLastError || 
            ERROR_SHARING_BUFFER_EXCEEDED == dLastError)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return true;
}

const std::wstring getWC(const char *c)
{
    const size_t cSize = strlen(c) + 1;
    std::wstring wc(cSize, L'#');
    mbstowcs(&wc[0], c, cSize);
    return wc;
}

int saveImgsInfo(char *imgsDirName, const char *subDir, char *fileName, 
        const vector<ImgInfo> &imgsInfo)
{
    const char ext[] = ".jpeg";
    if (!dirExists(&getWC(imgsDirName)[0]))
    {
        mkdir(imgsDirName);
    }
    FILE *f = fopen(fileName, "w+");
    for (int i = 0; i < imgsInfo.size(); i++)
    {
        char imgFileName[255], subFileName[255];
        strcat(strcat(strcpy(imgFileName, imgsDirName), imgsInfo[i].name), ext);
        imwrite(imgFileName, imgsInfo[i].img);
        fprintf(f, "%s %d\n", 
            strcat(strcat(strcat(strcpy(subFileName, subDir), "\\"), 
                    imgsInfo[i].name), ext), 
            imgsInfo[i].vehicleClass);
    }
    fclose(f);
    return 0;
}

int saveImgsInfo(const char *fileName, const char *subDirCarvan, 
        const char *subDirSedantaxi, const vector<ImgInfo> &carvan, 
        const vector<ImgInfo> &sedantaxi)
{
    const char ext[] = ".jpeg";
    FILE *f = fopen(fileName, "w+");
    for (int i = 0; i < carvan.size(); i++)
    {
        char imgFileName[255];
        strcat(strcat(strcat(strcpy(imgFileName, subDirCarvan), "\\"),
            carvan[i].name), ext);
        fprintf(f, "%s %d\n", imgFileName, carvan[i].vehicleClass);
    }
    for (int i = 0; i < sedantaxi.size(); i++)
    {
        char imgFileName[255];
        strcat(strcat(strcat(strcpy(imgFileName, subDirSedantaxi), "\\"), 
            sedantaxi[i].name), ext);
        fprintf(f, "%s %d\n", imgFileName, sedantaxi[i].vehicleClass);
    }
    fclose(f);
    return 0;
}

int saveImgsInfo(char *mitOutDir, const char *subDirs[], 
        const char *fileNames[],
        const vector<ImgInfo> &testCarvan, 
        const vector<ImgInfo> &testSedantaxi, 
        const vector<ImgInfo> &trainCarvan, 
        const vector<ImgInfo> &trainSedantaxi)
{
    char imgsDirName[255], fileName[255], testfile[255], trainfile[255];    
    strcat(strcat(strcpy(imgsDirName, mitOutDir), subDirs[0]), "\\");
    strcat(strcpy(fileName, mitOutDir), fileNames[0]);
    saveImgsInfo(imgsDirName, subDirs[0], fileName, testCarvan);

    strcat(strcat(strcpy(imgsDirName, mitOutDir), subDirs[1]), "\\");
    strcat(strcpy(fileName, mitOutDir), fileNames[1]);
    saveImgsInfo(imgsDirName, subDirs[1], fileName, testSedantaxi);

    strcat(strcat(strcpy(imgsDirName, mitOutDir), subDirs[2]), "\\");
    strcat(strcpy(fileName, mitOutDir), fileNames[2]);
    saveImgsInfo(imgsDirName, subDirs[2], fileName, trainCarvan);

    strcat(strcat(strcpy(imgsDirName, mitOutDir), subDirs[3]), "\\");
    strcat(strcpy(fileName, mitOutDir), fileNames[3]);
    saveImgsInfo(imgsDirName, subDirs[3], fileName, trainSedantaxi);

    strcat(strcpy(testfile, mitOutDir), fileNames[4]);
    saveImgsInfo(testfile, subDirs[0], subDirs[1], testCarvan, testSedantaxi);

    strcat(strcpy(trainfile, mitOutDir), fileNames[5]);
    saveImgsInfo(trainfile, subDirs[2], subDirs[3], trainCarvan, trainSedantaxi);
    return 0;
}
