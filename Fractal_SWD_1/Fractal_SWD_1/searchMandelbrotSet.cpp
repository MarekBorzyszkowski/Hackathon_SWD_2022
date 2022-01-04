//#include <iostream>
//#include <opencv2/opencv.hpp>
//#include <complex>
//#include <thread> 
//
//int calcIterationInPoint(double x, double y, int maxIteration) {
//	int Iteration = 0;
//	std::complex<double> complexSum, point;
//	point.real(x);
//	point.imag(y);
//	complexSum = 0;
//	do {
//		complexSum = std::pow(complexSum, 2) + point;
//		Iteration++;
//	} while (Iteration < maxIteration && std::norm(complexSum) < 4);
//	return Iteration;
//}
//
//cv::Mat mandelbrotSet;
//int n=1;
//
//void calcMandelbrot( double dx, double dy, int p, double upLeftX = -1, double upLeftY = -1, int maxIterations = 80) {
//	int value;
//	for (int i = p; i <p+ 100 * n; i++) {
//		for (int j = 0; j < 400 * n; j++) {
//			value = 255 - int(((double)calcIterationInPoint(upLeftX + (double)i * dy, upLeftY + (double)j * dx, maxIterations) / (double)maxIterations) * 255.0);
//			mandelbrotSet.at<uchar>(j, i) = value;
//
//		}
//	}
//}
//
//void mandelbrot(int i) {
//	double upLeftX = -1, upLeftY = -1;
//	double dx, dy;
//	uchar value;
//	int maxIterations = 80;
//	dx = dy = 2.0 / (double)n / 400.0;
//	calcMandelbrot(dx, dy, i);
//}
//
//int main() {
//	std::cout << "XD fraktal";
//	std::string fileName;
//	//std::cin >> fileName;
//	fileName = "pic/przyk³ad_fraktale_1";
//	
//	cv::Mat srcImage = cv::imread(fileName + ".png", cv::IMREAD_GRAYSCALE);
//	double upLeftX = -1, upLeftY = -1;
//	double dx, dy;
//	uchar value;
//	int maxIterations = 80;
//	for (n = 1; n <= 64; n *= 2) {
//		mandelbrotSet = cv::Mat(400 * n, 400 * n, srcImage.type());
//		std::thread thred1(mandelbrot, 0 * 100 * n);
//		std::thread thred2(mandelbrot, 1 * 100 * n);
//		std::thread thred3(mandelbrot, 2 * 100 * n);
//		std::thread thred4(mandelbrot, 3 * 100 * n);
//		
//		/*for (int i = 0; i < 400 * n; i++) {
//			for (int j = 0; j < 400 * n; j++) {
//				value = 255 - int(((double)calcIterationInPoint(upLeftX + (double)i * dy, upLeftY + (double)j * dx, maxIterations) / (double)maxIterations) * 255.0);
//				mandelbrotSet.at<uchar>(j, i) = value;
//
//			}
//		}*/
//		thred1.join();
//		thred2.join();
//		thred3.join();
//		thred4.join();
//
//		std::cout << n << '\n';
//		cv::imwrite(fileName + "_out"+std::to_string(n)+".png", mandelbrotSet);
//	}
//	return 0;
//}