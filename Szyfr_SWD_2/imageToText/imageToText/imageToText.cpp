// MiI_Lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>



using namespace cv;
using namespace std;


int main()
{
    //Mat srcImage = imread("szyfr_1.png");
    //Mat secondImage = imread("szyfr_1.png");
    //int indexOfColorChange = 0;

    //namedWindow("Display window", cv::WINDOW_AUTOSIZE);

    //for (int y = 0; y < srcImage.rows; y++)
    //{
    //    Vec3b& colorBefore = srcImage.at<Vec3b>(y, 0);
    //    indexOfColorChange = 1;

    //    for (int x = 1; x < srcImage.cols; x++)
    //    {
    //        // get pixel
    //        Vec3b& color = srcImage.at<Vec3b>(y, x);

    //        // ... do something to the color ....
    //        if (color[0] - colorBefore[0] == 1 &&
    //            color[1] - colorBefore[1] == 1 &&
    //            color[2] - colorBefore[2] == 1) {


    //            secondImage.at<Vec3b>(y, x) = Vec3b(255, 255, 255);

    //        }
    //        else if (color[0] - colorBefore[0] == -1 &&
    //            color[1] - colorBefore[1] == -1 &&
    //            color[2] - colorBefore[2] == -1) {

    //            int tmp = x;

    //            while (x != indexOfColorChange) {
    //                x--;
    //                secondImage.at<Vec3b>(y, x) = Vec3b(255, 255, 255);
    //            }

    //            x = tmp;
    //            colorBefore = color;
    //        }
    //        else {
    //            colorBefore = color;
    //            indexOfColorChange = x;
    //            secondImage.at<Vec3b>(y, x) = Vec3b(0, 0, 0);
    //        }

    //    }
    //}
    //namedWindow("Aleksandra Borsuk");
    //moveWindow("Aleksandra Borsuk", 0, 0);
    //imshow("Aleksandra Borsuk", secondImage);
    //imwrite("output.png", secondImage);

    //waitKey(0);
   


    return 0;
}