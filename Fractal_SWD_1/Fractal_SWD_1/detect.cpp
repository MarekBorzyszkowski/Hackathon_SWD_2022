#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
#include <chrono>

void displayImage(cv::Mat& image) {
	cv::namedWindow("Gray Image", cv::WINDOW_AUTOSIZE);
	cv::moveWindow("Gray Image", 0, 0);
	cv::imshow("Gray Image", image);
	cv::waitKey(0);
	cv::destroyWindow("Gray Image");
}

void display2Image(cv::Mat& image, cv::Mat& image2) {
	cv::namedWindow("Gray Image", cv::WINDOW_AUTOSIZE);
	cv::moveWindow("Gray Image", 0, 0);
	cv::imshow("Gray Image", image);	
	cv::namedWindow("Gray Image2", cv::WINDOW_AUTOSIZE);
	cv::moveWindow("Gray Image2", 960, 0);
	cv::imshow("Gray Image2", image2);
	cv::waitKey(0);
	cv::destroyWindow("Gray Image");
	cv::destroyWindow("Gray Image2");
}

int main() {
	std::string fileName;
	//std::cin >> fileName;
	fileName = "pic/przyk³ad_fraktale_2.png";
	auto start = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();;
	std::chrono::duration<double> elapsed_seconds;
	cv::Mat srcImage, scaledImage, result;
	srcImage = cv::imread(fileName, cv::IMREAD_GRAYSCALE);
	std::vector<cv::Mat> completeMSet;
	cv::Mat mandelbrot;
	int n=1, nextPowOf2 = 1, exponent = 0;
	double xmin, xmax, ymin, ymax, theNeaestPointValue =0;
	xmin = ymin = -1;
	double globalMax;
	cv::Point lowPoint, maxLowPoint = cv::Point(0, 0), searchPoint = cv::Point(0,0), searchPointEnd = cv::Point(400, 400);
	double scale = 1.0,scaleFactor = 1.0;
	double dx, dy;
	dx = 2.0 / 400.0;
	dy = 2.0 / 400.0;
	mandelbrot = cv::imread("pic/mandelbrotSet" + std::to_string(1) + ".bmp", cv::IMREAD_GRAYSCALE);
	//completeMSet.push_back(mandelbrot);
	//displayImage(srcImage);
	//displayImage(completeMSet[0]);


	//mandelbrot = cv::imread("pic/mandelbrotSet" + std::to_string((int)pow(2, i)) + ".bmp", cv::IMREAD_GRAYSCALE);
	//completeMSet.push_back(mandelbrot);
	fileName.erase(fileName.end() - 3, fileName.end());
	while(theNeaestPointValue < 0.9 && n<128){
		//scale = scaleFactor * (double)n / (double)nextPowOf2;
		//cv::resize(srcImage, scaledImage, cv::Size(400.0*scale, 400.0 * scale));
		int result_cols = mandelbrot.cols - srcImage.cols + 1;
		int result_rows = mandelbrot.rows - srcImage.rows + 1;
		result.create(result_rows, result_cols, CV_32FC1);
		cv::matchTemplate(mandelbrot, srcImage, result, cv::TM_CCOEFF_NORMED);
		cv::minMaxLoc(result,  nullptr, &globalMax,  nullptr, &lowPoint, cv::Mat());
		result = result * 255.0;
		//cv::imwrite(fileName + "_outResult" + std::to_string(n) + ".png", result);
		//display2Image(srcImage,result);

		if (theNeaestPointValue < globalMax) {

			maxLowPoint =searchPoint + lowPoint;
			xmin = -1.0+dx*(double)(maxLowPoint.x);
			ymin = -1.0 + dy * (double)(maxLowPoint.y);
			xmax = xmin + (400.0 *scale) *dx;
			ymax = ymin + (400.0 *scale) *dy;
			theNeaestPointValue = globalMax;
		}
		if (nextPowOf2 == n && n<64) {
			nextPowOf2 *= 2;
			exponent++;
			mandelbrot = cv::imread("pic/mandelbrotSet" + std::to_string(nextPowOf2) + ".bmp", cv::IMREAD_GRAYSCALE);
			//completeMSet.push_back(mandelbrot);
			if (n > 3) {
				searchPoint.x = maxLowPoint.x - 400.0*4.0*0.15;
				searchPoint.y = maxLowPoint.y - 400.0 * 4.0 *0.15;
				searchPoint.x *= 2;
				searchPoint.y *= 2;
				searchPointEnd.x = maxLowPoint.x + 400.0 * 4.0 * 0.35;
				searchPointEnd.y = maxLowPoint.y + 400.0 * 4.0 * 0.35;
				searchPointEnd.x *= 2;
				searchPointEnd.y *= 2;
				if (searchPoint.x < 0) {
					searchPoint.x = 0;
				}
				if (searchPoint.y <0) {
					searchPoint.y = 0;
				}
				if (searchPointEnd.x > 400.0 * (double)nextPowOf2) {
					searchPointEnd.x = 400.0 * (double)nextPowOf2;
				}
				if (searchPointEnd.y > 400.0 * (double)nextPowOf2) {
					searchPointEnd.y = 400.0 * (double)nextPowOf2;
				}
				scaleFactor *= 0.5;
				mandelbrot = mandelbrot( cv::Range(searchPoint.y, searchPointEnd.y),cv::Range(searchPoint.x, searchPointEnd.x));
			}
			dx = 2.0 / (400.0 * (double)nextPowOf2);
			dy = dx;
		}
		n*=2;
		end = std::chrono::steady_clock::now();
		elapsed_seconds = end - start;
		std::cout << elapsed_seconds.count() << " " << theNeaestPointValue << " " << xmin << " " << ymin<< '\n';
	}
	fileName.erase(fileName.end() - 3, fileName.end());
	fileName += "txt";
	std::ofstream output;
	output.open(fileName);
	std::cout << xmin << " " << xmax << '\n' << ymin << " " << ymax;
	output << xmin << " " << xmax << '\n' << ymin << " " << ymax;
	return 0;
}
