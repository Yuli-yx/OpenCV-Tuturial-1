#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include "opencv2/opencv.hpp"
#include "fstream"
#include <vector>
using namespace std;
using namespace cv;

int main() {

    //loading image files
    vector<string> files;
    glob("/home/will-zhu/Documents/OpenCVTuturials/first week/camera calibration/chess", files);

    //defination of variables
    vector<vector<Point2f>> imagePoints;
    vector<vector<Point3f>> objectPoints;

    TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 30,0.001);
    int numCornersHor = 9;                                     //numbers of the horizon corners
    int numCornersVer = 6;                                     //numbers of the vertical corners
    int numSquares = 17;                                       //length of the square on the chess board
    Size s(1280,720);                           //resolution of the image

    vector<Point3f> obj;
    for (int i = 0; i < numCornersHor;i++)
    {
        for (int j = 0; j < numCornersVer;j++)
        {
            obj.push_back(Point3f((float)j * numSquares, (float)i * numSquares,0));
        }
    }
    //finding the chess board and drawing

    for (int i = 0;i < files.size();i++)
    {
        printf("image file : %s \n", files[i].c_str());
        Mat image = imread(files[i]);
        Mat gray;
        cvtColor(image, gray, COLOR_BGR2GRAY);

        vector<Point2f> corners;
        bool ret = findChessboardCornersSB(gray, Size(6, 9), corners,CALIB_CB_EXHAUSTIVE|CALIB_CB_ACCURACY );
        if (ret)
        {
            drawChessboardCorners(image,Size(6,9),corners,ret) ;
            imagePoints.push_back(corners);
            objectPoints.push_back(obj);
//          imshow("calibraton-demo", image);
//          waitKey(250);
        }
    }

    //camera calibration
    Mat cameraMatrix = Mat(3, 3, CV_32FC1);
    Mat distCoeffs;
    vector<Mat> rvecs;
    vector<Mat> tvecs;
    cameraMatrix.ptr<float>(0)[0] = 1;
    cameraMatrix.ptr<float>(1)[1] = 1;

    cout<<"重投影误差" << calibrateCamera(objectPoints, imagePoints, s, cameraMatrix, distCoeffs, rvecs, tvecs)<<endl;
    cout << "cameraMatrix"<< endl<< cameraMatrix<<endl<< endl;
    cout << "distCoeffs"<< endl << distCoeffs<<endl<<endl;
/*
    //Distortion correction
    for (int i = 0; i < files.size();i++){
        Mat dst;
        Mat image = imread(files[i]);
        undistort(image, dst, cameraMatrix, distCoeffs);
        imshow("image",image);
        imshow("undistort image", dst);
        waitKey(2000);
    }

*/
    return 0;
}
