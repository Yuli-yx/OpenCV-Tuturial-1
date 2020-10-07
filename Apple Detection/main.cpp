#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

Mat src; Mat src_HSV;Mat dst;

int main()
{
    src = imread( "/home/will-zhu/Documents/OpenCVTuturials/first week/AppleDetection/apple.jpg", 1 );
    Mat src1= src.clone();

    cvtColor( src, src_HSV, COLOR_BGR2HSV );
    vector<Mat> channels;
    inRange(src_HSV,Scalar(20,0,0),Scalar(170,255,255),dst);


    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(3,3), Point(-1,-1));
    Mat kernel1 = getStructuringElement(MORPH_ELLIPSE, Size(30,30), Point(-1,-1));

    morphologyEx(dst, dst,MORPH_OPEN,kernel);
    morphologyEx(dst, dst,MORPH_CLOSE,kernel1);

    Canny(dst,dst,100,150);


    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    vector<vector<Point> > minEllipse;

    findContours(dst, contours, hierarchy,RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    Mat blank = Mat::zeros(src.size(),CV_8UC3);

    for(int i = 0; i < contours.size();i ++)
    {
        RotatedRect box = fitEllipse(contours[i]);

       if (MAX(box.size.width,box.size.height)< 20 ) continue;

//        drawContours(src1,contours,i,Scalar(0,255,0),1,8);
        ellipse(src1,box,Scalar(50,0,255),5,8);
    }

    imshow("result",src1);
    imwrite("result.jpg",src1);
    waitKey(0);
    return 0;
}
