#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

int main() {
    Mat src, dst;

    src = imread("/home/will-zhu/Documents/OpenCVTuturials/first week/license plate.jpg");
    imshow("initial image", src);

    Point2f srcPts[4];
    srcPts[0] = Point2f(597,331);
    srcPts[1] = Point2f(603,390);
    srcPts[2] = Point2f(764,332);
    srcPts[3] = Point2f(772,388);

    int MinX = std::min(srcPts[0].x, srcPts[1].x);
    int MaxX = std::max(srcPts[2].x, srcPts[3].x);
    int MinY = std::min(srcPts[0].y, srcPts[2].y);
    int MaxY = std::max(srcPts[1].y, srcPts[3].y);

    Point2f dstPts[4];
    dstPts[0] = cv::Point2f(MinX, MinY);
    dstPts[1] = cv::Point2f(MinX, MaxY);
    dstPts[2] = cv::Point2f(MaxX, MinY);
    dstPts[3] = cv::Point2f(MaxX, MaxY);

    Mat perspectiveMat = getPerspectiveTransform(srcPts, dstPts);

    warpPerspective(src, dst, perspectiveMat, src.size());

    Mat plate;
    Point2f center = Point2f((int)((MinX+MaxX)/2),(int)((MinY+MaxY)/2));

    getRectSubPix(dst,Size(MaxX-MinX,MaxY-MinY),center,plate);
    cvtColor(plate,plate,COLOR_BGR2GRAY);
    threshold(plate,plate,130,255,THRESH_BINARY);
    imshow("transformed", dst);
    imshow("plate",plate);

    waitKey(0);
    return 0;
}
